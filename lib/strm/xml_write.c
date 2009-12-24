/** @file
 * @brief HID report descriptor - XML stream type - writing
 *
 * Copyright (C) 2009 Nikolai Kondrashov
 *
 * This file is part of hidrd.
 *
 * Hidrd is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Hidrd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with hidrd; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * @author Nikolai Kondrashov <spbnick@gmail.com>
 *
 * @(#) $Id$
 */


#include <string.h>
#include <libxml/parser.h>
#include "hidrd/strm/xml.h"
#include "xml.h"

/** String formatting type */
typedef enum str_fmt {
    STR_FMT_NULL,   /**< NULL string */
    STR_FMT_UINT,   /**< Unsigned integer */
    STR_FMT_STRDUP, /**< String duplication */
    STR_FMT_STROWN, /**< String ownership taking */
    STR_FMT_HEX     /**< Hex string */
} str_fmt;


/**
 * Format hex string.
 *
 * @param buf   Data buffer to format.
 * @param size  Data size.
 *
 * @return Dynamically allocated hex string.
 */
static char *
fmt_str_hex(uint8_t *buf, size_t size)
{
    static const char   map[16] = "0123456789ABCDEF";
    char               *str;
    char               *p;
    uint8_t             b;

    str = malloc((size * 2) + 1);
    if (str == NULL)
        return NULL;

    for (p = str; size > 0; size--, buf++)
    {
        b = *buf;
        *p++ = map[b >> 4];
        *p++ = map[b & 0xF];
    }

    *p = '\0';

    return str;
}


/**
 * Format a string according to format type.
 *
 * @param pstr  Location for a (dynamically allocated) resulting string
 *              pointer.
 * @param fmt   Format type.
 * @param ap    Format arguments.
 *
 * @return True if formatted successfully, false otherwise.
 */
static bool
fmt_strpv(char     **pstr,
          str_fmt    fmt,
          va_list   *pap)
{
    char       *str;

    switch (fmt)
    {
        case STR_FMT_NULL:
            str = NULL;
            break;
        case STR_FMT_UINT:
            if (asprintf(&str, "%u", va_arg(*pap, unsigned int)) < 0)
                return false;
            break;
        case STR_FMT_STRDUP:
            {
                const char *arg = va_arg(*pap, const char *);

                assert(arg != NULL);

                str = strdup(arg);
                if (str == NULL)
                    return false;
            }
            break;
        case STR_FMT_STROWN:
            {
                char       *arg = va_arg(*pap, char *);

                assert(arg != NULL);

                str = arg;
            }
            break;
        case STR_FMT_HEX:
            {
                void   *buf     = va_arg(*pap, void *);
                size_t  size    = va_arg(*pap, size_t);

                str = fmt_str_hex(buf, size);
                if (str == NULL)
                    return false;
            }
            break;
        default:
            assert(!"Unknown string format");
            return false;
    }

    if (pstr != NULL)
        *pstr = str;
    else
        free(str);

    return true;
}


static bool
element_new(hidrd_strm_xml_inst        *strm_xml,
            const char                 *name)
{
    assert(strm_xml->cur == NULL);

    strm_xml->cur = xmlNewChild(strm_xml->prnt, NULL, BAD_CAST name, NULL);

    return (strm_xml->cur != NULL);
}


static bool
element_set_attrpv(hidrd_strm_xml_inst  *strm_xml,
                   const char           *name,
                   str_fmt               fmt,
                   va_list              *pap)
{
    char       *value;
    xmlAttrPtr  attr;

    assert(strm_xml->cur != NULL);

    if (!fmt_strpv(&value, fmt, pap))
        return false;

    attr = xmlSetProp(strm_xml->cur, BAD_CAST name, BAD_CAST value);

    free(value);

    return (attr != NULL);
}


static bool
element_set_contentpv(hidrd_strm_xml_inst   *strm_xml,
                      str_fmt                fmt,
                      va_list               *pap)
{
    char   *content;

    assert(strm_xml->cur != NULL);

    if (!fmt_strpv(&content, fmt, pap))
        return false;

    xmlNodeSetContent(strm_xml->cur, BAD_CAST content);

    free(content);

    return true;
}


static void
element_commit(hidrd_strm_xml_inst *strm_xml,
               bool                 container)
{
    assert(strm_xml->cur != NULL);
    
    if (container)
        strm_xml->prnt = strm_xml->cur;

    strm_xml->cur = NULL;
}


/** Node type */
typedef enum nt {
    NT_NONE,
    NT_CONTENT,
    NT_ATTR
} nt;

static bool
element_addv(hidrd_strm_xml_inst   *strm_xml,
             bool                   container,
             const char            *name,
             va_list                ap)
{
    bool    success = true;
    bool    end     = false;

    assert(strm_xml->cur == NULL);

    if (!element_new(strm_xml, name))
        return false;

    while (success && !end)
    {
        nt  node_type = va_arg(ap, nt);

        switch (node_type)
        {
            case NT_ATTR:
                {
                    const char *name        = va_arg(ap, const char *);
                    str_fmt     value_fmt   = va_arg(ap, str_fmt);

                    success = element_set_attrpv(strm_xml,
                                                 name, value_fmt, &ap);
                }
                break;

            case NT_CONTENT:
                {
                    str_fmt content_fmt  = va_arg(ap, str_fmt);

                    success = element_set_contentpv(strm_xml,
                                                    content_fmt, &ap);
                }
                break;

            case NT_NONE:
                end = true;
                break;

            default:
                assert(!"Unknown node type");
                success = false;
                break;
        }
    }

    element_commit(strm_xml, container);

    return success;
}


static bool
element_add(hidrd_strm_xml_inst    *strm_xml,
            bool                    container,
            const char             *name,
            ...)
{
    va_list ap;
    bool    success;

    va_start(ap, name);
    success = element_addv(strm_xml, container, name, ap);
    va_end(ap);

    return success;
}


#if 0
static void
element_seal(hidrd_strm_xml_inst   *strm_xml)
{
    assert(strm_xml->cur == NULL);

    /*
     * TODO think about handling invalid nesting
     */

    if (strm_xml->prnt->parent != NULL)
        strm_xml->prnt = strm_xml->prnt->parent;
}
#endif


#define ATTR(_name, _fmt, _args...) \
    NT_ATTR, #_name, STR_FMT_##_fmt, ##_args

#define CONTENT(_fmt, _args...) \
    NT_CONTENT, STR_FMT_##_fmt, ##_args

#define SIMPLE(_name, _args...) \
    element_add(strm_xml, false, #_name, ##_args, NT_NONE)

#define CONTAINER_START(_name, _args...) \
    element_add(strm_xml, true, #_name, ##_args, NT_NONE)

#define CONTAINER_END \
    element_seal(strm_xml)

static bool
hidrd_strm_xml_write_element(hidrd_strm_xml_inst   *strm_xml,
                             const hidrd_item      *item)
{
    switch (hidrd_item_basic_get_format(item))
    {
        case HIDRD_ITEM_BASIC_FORMAT_LONG:
            return SIMPLE(long,
                          ATTR(tag, UINT, hidrd_item_long_get_tag(item)),
                          CONTENT(
                              HEX,
                              /* We promise we won't change it */
                              hidrd_item_long_get_data((hidrd_item *)item)),
                              hidrd_item_long_get_data_size(item));

        case HIDRD_ITEM_BASIC_FORMAT_SHORT:
            switch (hidrd_item_short_get_type(item))
            {
                case HIDRD_ITEM_SHORT_TYPE_MAIN:
                    switch (hidrd_item_main_get_tag(item))
                    {
                        default:
                            return SIMPLE(
                                    main,
                                    ATTR(tag, STROWN,
                                         hidrd_item_main_get_tag_token(item)),
                                    CONTENT(
                                        HEX,
                                        /* We promise we won't change it */
                                        hidrd_item_short_get_data((hidrd_item *)item)),
                                        hidrd_item_short_get_data_size_bytes(item));
                    }
                    break;
                default:
                    return SIMPLE(short,
                            ATTR(type, STROWN,
                                 hidrd_item_short_get_type_token(item)),
                            ATTR(tag, STROWN,
                                 hidrd_item_short_get_tag_token(item)),
                            CONTENT(
                                HEX,
                                /* We promise we won't change it */
                                hidrd_item_short_get_data((hidrd_item *)item)),
                                hidrd_item_short_get_data_size_bytes(item));
            }
            break;
        default:
            return SIMPLE(basic,
                    ATTR(type, STROWN,
                         hidrd_item_basic_get_type_token(item)),
                    ATTR(tag, STROWN,
                         hidrd_item_basic_get_tag_token(item)),
                    ATTR(tag, UINT,
                         hidrd_item_basic_get_data_size_bytes(item)));
    }
}


bool
hidrd_strm_xml_write(hidrd_strm *strm, const hidrd_item *item)
{
    hidrd_strm_xml_inst    *strm_xml    = (hidrd_strm_xml_inst *)strm;

    assert(!hidrd_strm_xml_being_read(strm));

    if (strm_xml->doc == NULL)
    {
        assert(strm_xml->prnt == NULL);
        assert(strm_xml->cur == NULL);

        strm_xml->doc = xmlNewDoc(BAD_CAST "1.1");
        if (strm_xml->doc == NULL)
        {
            strm->error = true;
            return false;
        }

        strm_xml->prnt = xmlNewNode(NULL, BAD_CAST "descriptor");
        if (strm_xml->prnt == NULL)
        {
            xmlFreeDoc(strm_xml->doc);
            strm_xml->doc = NULL;
            strm->error = true;
            return false;
        }

        xmlDocSetRootElement(strm_xml->doc, strm_xml->prnt);
    }

    assert(strm_xml->prnt != NULL);

    strm_xml->changed = true;

    return hidrd_strm_xml_write_element(strm_xml, item);
}



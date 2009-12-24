/** @file
 * @brief HID report descriptor - XML file stream type
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
#include "hidrd/strm/inst.h"

typedef struct hidrd_strm_xml_inst {
    hidrd_strm      strm;   /**< Parent structure */
    void          **pbuf;
    size_t         *psize;
    bool            format;

    void           *buf;
    size_t          size;
    xmlDocPtr       doc;
    xmlNodePtr      prnt;
    xmlNodePtr      cur;
    bool            changed;

    hidrd_item      item[HIDRD_ITEM_MAX_SIZE];
} hidrd_strm_xml_inst;


static bool
hidrd_strm_xml_init(hidrd_strm *strm, va_list ap)
{
    hidrd_strm_xml_inst    *strm_xml    = (hidrd_strm_xml_inst *)strm;
    void                  **pbuf        = va_arg(ap, void **);
    size_t                 *psize       = va_arg(ap, size_t *);
    bool                    format      = (va_arg(ap, int) != 0);

    assert(pbuf == NULL ||  /* No input nor location for output buffer,
                               maybe location for output size */
           (
            pbuf != NULL && psize != NULL && /* Location for both output
                                                buffer and size, maybe
                                                input buffer or size */
            (*psize == 0 || *pbuf != NULL) /* Either input size of zero or
                                              buffer must be there */
           )
          );

    strm_xml->pbuf      = pbuf;
    strm_xml->psize     = psize;
    strm_xml->format    = format;

    strm_xml->buf       = (pbuf != NULL) ? *pbuf : NULL;
    strm_xml->size      = (psize != NULL) ? *psize : 0;
    strm_xml->doc       = NULL;
    strm_xml->prnt      = NULL;
    strm_xml->cur       = NULL;
    strm_xml->changed   = false;

    return true;
}


static bool
hidrd_strm_xml_being_read(const hidrd_strm *strm)
{
    const hidrd_strm_xml_inst  *strm_xml    =
                                    (const hidrd_strm_xml_inst *)strm;

    return strm_xml->doc != NULL && !strm_xml->changed;
}


static bool
hidrd_strm_xml_being_written(const hidrd_strm *strm)
{
    const hidrd_strm_xml_inst  *strm_xml    =
                                    (const hidrd_strm_xml_inst *)strm;

    return strm_xml->doc != NULL && strm_xml->changed;
}


static bool
hidrd_strm_xml_valid(const hidrd_strm *strm)
{
    const hidrd_strm_xml_inst  *strm_xml    =
                                    (const hidrd_strm_xml_inst *)strm;

    if (strm_xml->doc == NULL)
        return strm_xml->prnt == NULL &&
               strm_xml->cur == NULL &&
               !strm_xml->changed;
    else
        return (strm_xml->prnt != NULL || strm_xml->cur == NULL);
}


static bool
hidrd_strm_xml_read_buf(hidrd_strm *strm)
{
    hidrd_strm_xml_inst    *strm_xml    = (hidrd_strm_xml_inst *)strm;

    assert(strm_xml->doc == NULL);
    assert(strm_xml->prnt == NULL);
    assert(strm_xml->cur == NULL);

    /* If there is no input */
    if (strm_xml->size == 0)
        return false;

    strm_xml->doc = xmlParseMemory(*strm_xml->pbuf, *strm_xml->psize);
    if (strm_xml->doc == NULL)
    {
        strm->error = true;
        return false;
    }

    /* TODO XML schema validation with xmlSchemaValidateDoc */

    /* Retrieve the root */
    strm_xml->prnt = xmlDocGetRootElement(strm_xml->doc);

    /* Retrieve the first child */
    if (strm_xml->prnt != NULL)
        strm_xml->cur = strm_xml->prnt->children;

    return true;
}


static const hidrd_item *
hidrd_strm_xml_read(hidrd_strm *strm)
{
    hidrd_strm_xml_inst    *strm_xml    = (hidrd_strm_xml_inst *)strm;
    xmlNodePtr              old_prnt;

    assert(!hidrd_strm_xml_being_written(strm));

    /* If the document hasn't been parsed yet */
    if (strm_xml->doc == NULL)
    {
        /* Parse the document and locate first node */
        if (!hidrd_strm_xml_read_buf(strm))
            return NULL;
    }

    /*
     * Get next element (go forward and up).
     */
    while (true)
    {
        while (strm_xml->cur == NULL)
        {
            if (strm_xml->prnt == NULL)
                return NULL;

            old_prnt = strm_xml->prnt;
            strm_xml->prnt = old_prnt->parent;
            if (strm_xml->prnt == NULL)
                return NULL;
            strm_xml->cur = old_prnt->next;
        }

        if (strm_xml->cur->type == XML_ELEMENT_NODE)
            break;

        strm_xml->cur = strm_xml->cur->next;
    }

    /*
     * Process element
     */

    return NULL;
}


typedef enum str_fmt {
    STR_FMT_NULL,
    STR_FMT_UINT,
    STR_FMT_STRDUP,
    STR_FMT_STROWN,
    STR_FMT_HEX
} str_fmt;


static char *
fmt_str_hex(uint8_t *buf, size_t size)
{
    static const char   map[16] = "0123456789ABCDEF";
    char               *str;
    uint8_t             b;

    str = malloc((size * 2) + 1);
    if (str == NULL)
        return NULL;

    for (; size > 0; size--, buf++)
    {
        b = *buf;
        *str++ = map[b >> 4];
        *str++ = map[b & 0xF];
    }

    *str = '\0';

    return str;
}


static bool
fmt_strv(char     **pstr,
         str_fmt    fmt,
         va_list    ap)
{
    char       *str;

    switch (fmt)
    {
        case STR_FMT_NULL:
            str = NULL;
            break;
        case STR_FMT_UINT:
            if (asprintf(&str, "%u", va_arg(ap, unsigned int)) < 0)
                return false;
            break;
        case STR_FMT_STRDUP:
            str = strdup(va_arg(ap, const char *));
            if (str == NULL)
                return false;
            break;
        case STR_FMT_STROWN:
            str = va_arg(ap, char *);
            break;
        case STR_FMT_HEX:
            {
                void   *buf     = va_arg(ap, void *);
                size_t  size    = va_arg(ap, size_t);

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
element_set_attrv(hidrd_strm_xml_inst  *strm_xml,
                  const char           *name,
                  str_fmt               fmt,
                  va_list               ap)
{
    char       *value;
    xmlAttrPtr  attr;

    assert(strm_xml->cur != NULL);

    if (!fmt_strv(&value, fmt, ap))
        return false;

    attr = xmlSetProp(strm_xml->cur, BAD_CAST name, BAD_CAST value);

    free(value);

    return (attr != NULL);
}


static bool
element_set_contentv(hidrd_strm_xml_inst   *strm_xml,
                     str_fmt                fmt,
                     va_list                ap)
{
    char   *content;

    assert(strm_xml->cur != NULL);

    if (!fmt_strv(&content, fmt, ap))
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

                    success = element_set_attrv(strm_xml,
                                                name, value_fmt, ap);
                }
                break;

            case NT_CONTENT:
                {
                    str_fmt content_fmt  = va_arg(ap, str_fmt);

                    success = element_set_contentv(strm_xml,
                                                   content_fmt, ap);
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


static bool
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


static bool
hidrd_strm_xml_flush_doc(hidrd_strm *strm)
{
    bool                    result          = false;
    hidrd_strm_xml_inst    *strm_xml        = (hidrd_strm_xml_inst *)strm;
    xmlBufferPtr            xml_buf         = NULL;
    xmlOutputBufferPtr      xml_out_buf     = NULL;
    void                   *new_buf         = NULL;
    size_t                  new_size;

    if (!strm_xml->changed)
    {
        result = true;
        goto finish;
    }

    xml_buf = xmlBufferCreate();
    if (xml_buf == NULL)
        goto finish;

    xml_out_buf = xmlOutputBufferCreateBuffer(xml_buf, NULL);
    if (xml_out_buf == NULL)
        goto finish;

    if (xmlSaveFormatFileTo(xml_out_buf, strm_xml->doc,
                            NULL, strm_xml->format) < 0)
        goto finish;
    /* xml_out_buf is closed by xmlSaveFormatFileTo */
    xml_out_buf = NULL;

    new_size = xmlBufferLength(xml_buf);
    new_buf = realloc(strm_xml->buf, new_size);
    if (new_buf == NULL)
        goto finish;
    memcpy(new_buf, xmlBufferContent(xml_buf), new_size);

    strm_xml->buf = new_buf;
    if (strm_xml->pbuf != NULL)
        *strm_xml->pbuf = new_buf;
    strm_xml->size = new_size;

    new_buf = NULL;

    result = true;

finish:

    strm->error = (strm->error || !result);

#if 0
cleanup:
#endif

    free(new_buf);

    if (xml_out_buf != NULL)
        xmlOutputBufferClose(xml_out_buf);

    if (xml_buf != NULL)
        xmlBufferFree(xml_buf);

    return result;
}


static bool
hidrd_strm_xml_flush(hidrd_strm *strm)
{
    hidrd_strm_xml_inst    *strm_xml        = (hidrd_strm_xml_inst *)strm;

    if (!hidrd_strm_xml_being_written(strm))
        return true;

    /* Dump document to the buffer (updates *pbuf also) */
    if (!hidrd_strm_xml_flush_doc(strm))
        return false;

    /* Output size */
    if (strm_xml->psize != NULL)
        *strm_xml->psize = strm_xml->size;

    return true;
}


static void
hidrd_strm_xml_clnp(hidrd_strm *strm)
{
    hidrd_strm_xml_inst    *strm_xml    = (hidrd_strm_xml_inst *)strm;

    if (strm_xml->doc != NULL)
    {
        xmlFreeDoc(strm_xml->doc);
        strm_xml->doc = NULL;
    }
}


const hidrd_strm_type hidrd_strm_xml = {
    .size   = sizeof(hidrd_strm_xml_inst),
    .init   = hidrd_strm_xml_init,
    .valid  = hidrd_strm_xml_valid,
    .read   = hidrd_strm_xml_read,
    .write  = hidrd_strm_xml_write,
    .flush  = hidrd_strm_xml_flush,
    .clnp   = hidrd_strm_xml_clnp,
};



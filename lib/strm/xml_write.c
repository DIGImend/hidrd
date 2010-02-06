/** @file
 * @brief HID report descriptor - XML stream type - writing
 *
 * Copyright (C) 2009-2010 Nikolai Kondrashov
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


/**
 * Pad a dynamically allocated string with spaces on both sides.
 *
 * @param str   A dynamically allocated string to pad; will be freed, even
 *              in case of failure.
 *
 * @return Dynamically allocated padded string, or NULL, if failed to
 *         allocate memory.
 */
static char *
strpada(char *str)
{
    char   *padded;
    int     rc;

    rc = asprintf(&padded, " %s ", str);

    free(str);

    return (rc >= 0) ? padded : NULL;
}


/**
 * Prototype for a function used to create and setup an element.
 *
 * @param doc       Document.
 * @param ns        Namespace.
 *
 * @return Created element, or NULL if failed.
 */
typedef xmlNodePtr create_element_fn(xmlDocPtr doc, xmlNsPtr ns);


/**
 * Break open an element.
 *
 * @alg Add a starting element next to the original element, with
 *      specified name, and the original element's properties. Move the
 *      contents of the original element right after the new element. Add an
 *      ending element with specified name next to the moved original
 *      contents. Remove the original element.
 *
 * @param element       The element to break.
 * @param create_start  Starting element creation function, could be NULL,
 *                      if starting element is not needed.
 * @param create_end    Ending element creation function, could be NULL,
 *                      if ending element is not needed.
 *
 * @return True if broken successfully, false otherwise.
 */
static bool
break_element(xmlNodePtr            element,
              create_element_fn    *create_start,
              create_element_fn    *create_end)
{
    xmlNodePtr  sibling;
    xmlNodePtr  child;
    xmlNodePtr  next_child;

    assert(element != NULL);
    assert(element->parent != NULL);

    /* If starting element is NOT requested */
    if (create_start == NULL)
        sibling = element;
    else
    {
        /* Create starting element */
        sibling = create_start(element->doc, element->ns);
        if (sibling == NULL)
            return false;

        /* Add it right after the original one */
        sibling = xmlAddNextSibling(element, sibling);
        if (sibling == NULL)
            return false;

        /* Copy original element's properties */
        xmlCopyPropList(sibling, element->properties);
    }

    /* For each child of the original element */
    for (child = element->children;
         child != NULL; child = next_child)
    {
        /* Remember next child before this one is unlinked */
        next_child = child->next;
        /* Move the child after the new element */
        sibling = xmlAddNextSibling(sibling, child);
        if (sibling == NULL)
            return false;
    }

    /* If ending element is requested */
    if (create_end != NULL)
    {
        /* Create ending element */
        sibling = create_end(element->doc, element->ns);
        if (sibling == NULL)
            return false;

        /* Add it right after the contents */
        sibling = xmlAddNextSibling(element, sibling);
        if (sibling == NULL)
            return false;
    }

    /* Unlink original element */
    xmlUnlinkNode(element);

    /* Free original element */
    xmlFreeNode(element);

    return true;
}


/**
 * Prototype for a function used to retrieve names of the starting and
 * ending elements when breaking.
 *
 * @param name          Element name to break.
 * @param pcreate_start Location for a pointer to the start element creation
 *                      function.
 * @param pcreate_end   Location for a pointer to the end element creation
 *                      function.
 *
 * @return True if element is known, false otherwise.
 */
typedef bool break_fn(const char *name,
                      create_element_fn **pcreate_start,
                      create_element_fn **pcreate_end);

/**
 * Break open an element branch up to the specified parent.
 *
 * @alg Break open the specified element and all its parent elements up to
 *      but not including the specified parent element.
 *
 * @param parent    Parent element to stop at.
 * @param element   Element to start breaking from.
 * @param cb        Break function - used to retrieve starting and ending
 *                  element creation functions when breaking.
 *
 * @return True if broken successfuly, false otherwise.
 */
static bool
break_branch(xmlNodePtr parent, xmlNodePtr element, break_fn *cb)
{
    create_element_fn  *create_start;
    create_element_fn  *create_end;
    xmlNodePtr          element_parent;

    /* For each element in the stack until the target one */
    for (; element != parent; element = element_parent)
    {
        if (!(*cb)((const char *)element->name, &create_start, &create_end))
            return false;

        /* Remember parent element before this one is unlinked and freed */
        element_parent = element->parent;

        /* Break open the element - it is not finished */
        if (!break_element(element, create_start, create_end))
            return false;
    }

    return true;
}


static bool
create_doc(hidrd_strm_xml_inst *strm_xml)
{
    assert(strm_xml->doc == NULL);
    assert(strm_xml->prnt == NULL);
    assert(strm_xml->cur == NULL);

    strm_xml->doc = xmlNewDoc(BAD_CAST "1.0");
    if (strm_xml->doc == NULL)
        goto failure;

    strm_xml->prnt = xmlNewNode(NULL, BAD_CAST "descriptor");
    if (strm_xml->prnt == NULL)
        goto failure;

    if (xmlSetProp(strm_xml->prnt, BAD_CAST "xmlns",
                   BAD_CAST HIDRD_STRM_XML_NS) == NULL)
        goto failure;

    if (xmlSetProp(strm_xml->prnt, BAD_CAST "xmlns:xsi",
                   BAD_CAST HIDRD_STRM_XML_NS_XSI) == NULL)
        goto failure;

    if (xmlSetProp(strm_xml->prnt, BAD_CAST "xsi:schemaLocation",
                   BAD_CAST HIDRD_STRM_XML_XSI_SCHEMA_LOCATION) == NULL)
        goto failure;

    xmlDocSetRootElement(strm_xml->doc, strm_xml->prnt);

    return true;

failure:

    strm_xml->prnt = NULL;

    if (strm_xml->doc != NULL)
    {
        xmlFreeDoc(strm_xml->doc);
        strm_xml->doc = NULL;
    }

    return false;
}


/** String formatting type */
typedef enum str_fmt {
    STR_FMT_NULL,   /**< NULL string */
    STR_FMT_INT,    /**< Signed integer */
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
        case STR_FMT_INT:
            if (asprintf(&str, "%d", va_arg(*pap, int)) < 0)
                return false;
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
element_add_contentpv(hidrd_strm_xml_inst   *strm_xml,
                      str_fmt                fmt,
                      va_list               *pap)
{
    char   *content;

    assert(strm_xml->cur != NULL);

    if (!fmt_strpv(&content, fmt, pap))
        return false;

    xmlNodeAddContent(strm_xml->cur, BAD_CAST content);

    free(content);

    return true;
}


static bool
element_add_commentpv(hidrd_strm_xml_inst   *strm_xml,
                      str_fmt                fmt,
                      va_list               *pap)
{
    char       *content;
    xmlNodePtr  comment;

    assert(strm_xml->cur != NULL);

    if (!fmt_strpv(&content, fmt, pap))
        return false;

    comment = xmlNewDocComment(strm_xml->doc, BAD_CAST content);
    free(content);
    if (comment == NULL)
        return false;

    return (xmlAddChild(strm_xml->cur, comment) != NULL);
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
    NT_COMMENT,
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

            case NT_COMMENT:
                {
                    str_fmt comment_fmt  = va_arg(ap, str_fmt);

                    success = element_add_commentpv(strm_xml,
                                                    comment_fmt, &ap);
                }
                break;

            case NT_CONTENT:
                {
                    str_fmt content_fmt  = va_arg(ap, str_fmt);

                    success = element_add_contentpv(strm_xml,
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


typedef struct group {
    const char *name;
    create_element_fn  *create_start;
    create_element_fn  *create_end;
} group;

static bool
group_valid(const group *g)
{
    return g != NULL &&
           g->name != NULL &&
           *g->name != '\0' &&
           g->create_start != NULL &&
           g->create_end != NULL;
}

static xmlNodePtr
create_element_collection(xmlDocPtr doc, xmlNsPtr ns)
{
    return xmlNewDocNode(doc, ns, BAD_CAST "collection", NULL);
}

static xmlNodePtr
create_element_end_collection(xmlDocPtr doc, xmlNsPtr ns)
{
    return xmlNewDocNode(doc, ns, BAD_CAST "end_collection", NULL);
}

static xmlNodePtr
create_element_push(xmlDocPtr doc, xmlNsPtr ns)
{
    return xmlNewDocNode(doc, ns, BAD_CAST "push", NULL);
}

static xmlNodePtr
create_element_pop(xmlDocPtr doc, xmlNsPtr ns)
{
    return xmlNewDocNode(doc, ns, BAD_CAST "pop", NULL);
}

static xmlNodePtr
create_element_delimiter_open(xmlDocPtr doc, xmlNsPtr ns)
{
    xmlNodePtr  e;

    e = xmlNewDocNode(doc, ns, BAD_CAST "delimiter", NULL);
    if (e == NULL)
        return NULL;

    if (xmlSetProp(e, BAD_CAST "open", BAD_CAST "true") == NULL)
        return NULL;

    return e;
}

static xmlNodePtr
create_element_delimiter_close(xmlDocPtr doc, xmlNsPtr ns)
{
    xmlNodePtr  e;

    e = xmlNewDocNode(doc, ns, BAD_CAST "delimiter", NULL);
    if (e == NULL)
        return NULL;

    if (xmlSetProp(e, BAD_CAST "open", BAD_CAST "false") == NULL)
        return NULL;

    return e;
}


static const group group_list[] = {
    {.name          = "COLLECTION",
     .create_start  = create_element_collection,
     .create_end    = create_element_end_collection},
    {.name          = "PUSH",
     .create_start  = create_element_push,
     .create_end    = create_element_pop},
    {.name          = "SET",
     .create_start  = create_element_delimiter_open,
     .create_end    = create_element_delimiter_close},
    {.name = NULL}
};

static const group *
lookup_group(const char *name)
{
    const group    *g;
    for (g = group_list; g->name != NULL; g++)
        if (strcmp(g->name, name) == 0)
        {
            assert(group_valid(g));
            return g;
        }

    return NULL;
}

static break_fn group_break_cb;
static bool
group_break_cb(const char          *name,
               create_element_fn  **pcreate_start,
               create_element_fn  **pcreate_end)
{
    const group    *g;

    assert(name != NULL);

    g = lookup_group(name);
    assert(g != NULL);

    if (g == NULL)
        return false;

    if (pcreate_start != NULL)
        *pcreate_start = g->create_start;

    if (pcreate_end != NULL)
        *pcreate_end = NULL;

    return true;
}


static bool
group_end(hidrd_strm_xml_inst  *strm_xml,
          const char           *name)
{
    const group    *target_group;
    xmlNodePtr      target_element;

    assert(strm_xml->cur == NULL);
    assert(name != NULL);

    target_group = lookup_group(name);
    /* There must be such group */
    assert(target_group != NULL);

    /* Look up an element with the same name up the parent stack */
    for (target_element = strm_xml->prnt;
         target_element != NULL && target_element->type == XML_ELEMENT_NODE;
         target_element = target_element->parent)
        if (strcmp((const char *)target_element->name, name) == 0)
            break;

    /* If not found */
    if (target_element == NULL || target_element->type != XML_ELEMENT_NODE)
    {
        xmlNodePtr  end_element;

        /* Insert closing element */
        end_element = target_group->create_end(strm_xml->doc, NULL);
        return xmlAddChild(strm_xml->prnt, end_element) != NULL;
    }
    else
    {
        /* Break open the branch up to the target element */
        if (!break_branch(target_element, strm_xml->prnt, group_break_cb))
            return false;

        /* Element done */
        strm_xml->prnt = target_element->parent;
    }

    return true;
}


#define ATTR(_name, _fmt, _args...) \
    NT_ATTR, #_name, STR_FMT_##_fmt, ##_args

#define CONTENT(_fmt, _args...) \
    NT_CONTENT, STR_FMT_##_fmt, ##_args

#define COMMENT(_fmt, _args...) \
    NT_COMMENT, STR_FMT_##_fmt, ##_args

#define SIMPLE(_name, _args...) \
    element_add(strm_xml, false, #_name, ##_args, NT_NONE)

#define GROUP_START(_name, _args...) \
    element_add(strm_xml, true, #_name, ##_args, NT_NONE)

#define GROUP_END(_name) \
    group_end(strm_xml, #_name)

#define SIMPLE_INT(_TYPE, _NAME, _name) \
    case HIDRD_ITEM_##_TYPE##_TAG_##_NAME:                          \
        return SIMPLE(                                              \
                _name,                                              \
                CONTENT(INT,                                        \
                        (int)hidrd_item_##_name##_get_value(item)))

#define SIMPLE_UINT(_TYPE, _NAME, _name) \
    case HIDRD_ITEM_##_TYPE##_TAG_##_NAME:                          \
        return SIMPLE(                                              \
                _name,                                              \
                CONTENT(INT,                                        \
                        (unsigned int)                              \
                            hidrd_item_##_name##_get_value(item)))


static bool
write_main_bit_elements(hidrd_strm_xml_inst   *strm_xml,
                        const hidrd_item      *item)
{
    uint8_t bit;
    char    name[6];

    assert(strm_xml->cur == NULL);
    assert(hidrd_item_main_valid(item));
    assert(hidrd_item_input_valid(item) ||
           hidrd_item_output_valid(item) ||
           hidrd_item_feature_valid(item));

#define BIT(_idx, _on_name) \
    do {                                                                \
        if (hidrd_item_main_get_bit(item, _idx) && !SIMPLE(_on_name))   \
            return false;                                               \
    } while (0)

    BIT(0, constant);
    BIT(1, variable);
    BIT(2, relative);
    BIT(3, wrap);
    BIT(4, non_linear);
    BIT(5, no_preferred);
    BIT(6, null_state);
    if (hidrd_item_main_get_tag(item) == HIDRD_ITEM_MAIN_TAG_INPUT)
        BIT(7, bit7);
    else
        BIT(7, volatile);
    BIT(8, buffered_bytes);

#undef BIT

    for (bit = 9; bit < 32; bit++)
        if (hidrd_item_main_get_bit(item, bit))
        {
            if (snprintf(name, sizeof(name), "bit%hhu", bit) >=
                (int)sizeof(name))
                return false;

            if (!element_add(strm_xml, false, name, NT_NONE))
                return false;
        }

    return true;
}

static bool
write_main_element(hidrd_strm_xml_inst   *strm_xml,
                   const hidrd_item      *item)
{
    hidrd_item_main_tag tag;

    assert(hidrd_item_main_valid(item));

    switch (tag = hidrd_item_main_get_tag(item))
    {
        case HIDRD_ITEM_MAIN_TAG_COLLECTION:
            return GROUP_START(
                    COLLECTION,
                    ATTR(type, STROWN,
                         hidrd_item_collection_get_type_token(item)));
        case HIDRD_ITEM_MAIN_TAG_END_COLLECTION:
            return GROUP_END(COLLECTION);

        case HIDRD_ITEM_MAIN_TAG_INPUT:
        case HIDRD_ITEM_MAIN_TAG_OUTPUT:
        case HIDRD_ITEM_MAIN_TAG_FEATURE:
            {
                char   *token;
                bool    result;

                token   = hidrd_item_main_tag_to_token(tag);
                result = element_add(strm_xml, true, token, NT_NONE);
                free(token);
                if (!result)
                    return false;

                if (!write_main_bit_elements(strm_xml, item))
                    return false;

                strm_xml->prnt = strm_xml->prnt->parent;

                return true;
            }
        default:
            return SIMPLE(
                    main,
                    ATTR(tag, STROWN,
                         hidrd_item_main_tag_to_token(tag)),
                    CONTENT(
                        HEX,
                        /* We promise we won't change it */
                        hidrd_item_short_get_data((hidrd_item *)item)),
                        hidrd_item_short_get_data_size_bytes(item));
    }
}


static bool
write_global_element(hidrd_strm_xml_inst   *strm_xml,
                   const hidrd_item      *item)
{
    assert(hidrd_item_global_valid(item));

    switch (hidrd_item_global_get_tag(item))
    {
        SIMPLE_INT(GLOBAL, LOGICAL_MINIMUM, logical_minimum);
        SIMPLE_INT(GLOBAL, LOGICAL_MAXIMUM, logical_maximum);
        SIMPLE_INT(GLOBAL, PHYSICAL_MINIMUM, physical_minimum);
        SIMPLE_INT(GLOBAL, PHYSICAL_MAXIMUM, physical_maximum);
        SIMPLE_INT(GLOBAL, UNIT_EXPONENT, unit_exponent);
        SIMPLE_UINT(GLOBAL, REPORT_SIZE, report_size);
        SIMPLE_UINT(GLOBAL, REPORT_ID, report_id);
        SIMPLE_UINT(GLOBAL, REPORT_COUNT, report_count);

        /* TODO unit item */

        case HIDRD_ITEM_GLOBAL_TAG_USAGE_PAGE:
            return SIMPLE(
                    usage_page,
                    CONTENT(STROWN,
                            hidrd_usage_page_to_token(
                                hidrd_item_usage_page_get_value(item))),
                    COMMENT(STROWN,
                            strpada(
                                hidrd_usage_page_desc(
                                    hidrd_item_usage_page_get_value(
                                        item)))));

        case HIDRD_ITEM_GLOBAL_TAG_PUSH:
            return GROUP_START(PUSH);
        case HIDRD_ITEM_GLOBAL_TAG_POP:
            return GROUP_END(PUSH);
        default:
            return SIMPLE(
                    global,
                    ATTR(tag, STROWN,
                         hidrd_item_global_get_tag_token(item)),
                    CONTENT(HEX,
                            /* We promise we won't change it */
                            hidrd_item_short_get_data((hidrd_item *)item)),
                            hidrd_item_short_get_data_size_bytes(item));
    }
}


static bool
write_local_element(hidrd_strm_xml_inst   *strm_xml,
                   const hidrd_item      *item)
{
    assert(hidrd_item_local_valid(item));

    switch (hidrd_item_local_get_tag(item))
    {
        /* FIXME use tokens */
        SIMPLE_UINT(LOCAL, USAGE, usage);
        /* FIXME use tokens */
        SIMPLE_UINT(LOCAL, USAGE_MINIMUM, usage_minimum);
        /* FIXME use tokens */
        SIMPLE_UINT(LOCAL, USAGE_MAXIMUM, usage_maximum);

        SIMPLE_UINT(LOCAL, DESIGNATOR_INDEX, designator_index);
        SIMPLE_UINT(LOCAL, DESIGNATOR_MINIMUM, designator_minimum);
        SIMPLE_UINT(LOCAL, DESIGNATOR_MAXIMUM, designator_maximum);
        SIMPLE_UINT(LOCAL, STRING_INDEX, string_index);
        SIMPLE_UINT(LOCAL, STRING_MINIMUM, string_minimum);
        SIMPLE_UINT(LOCAL, STRING_MAXIMUM, string_maximum);

        case HIDRD_ITEM_LOCAL_TAG_DELIMITER:
            return (hidrd_item_delimiter_get_value(item) ==
                    HIDRD_ITEM_DELIMITER_SET_OPEN)
                        ? GROUP_START(SET)
                        : GROUP_END(SET);

        default:
            return SIMPLE(
                    local,
                    ATTR(tag, STROWN,
                         hidrd_item_local_get_tag_token(item)),
                    CONTENT(HEX,
                            /* We promise we won't change it */
                            hidrd_item_short_get_data((hidrd_item *)item)),
                            hidrd_item_short_get_data_size_bytes(item));
    }
}


static bool
write_short_element(hidrd_strm_xml_inst   *strm_xml,
                    const hidrd_item      *item)
{
    assert(hidrd_item_short_valid(item));

    switch (hidrd_item_short_get_type(item))
    {
        case HIDRD_ITEM_SHORT_TYPE_MAIN:
            return write_main_element(strm_xml, item);
        case HIDRD_ITEM_SHORT_TYPE_GLOBAL:
            return write_global_element(strm_xml, item);
        case HIDRD_ITEM_SHORT_TYPE_LOCAL:
            return write_local_element(strm_xml, item);
        default:
            return SIMPLE(short,
                    ATTR(type, STROWN,
                         hidrd_item_short_get_type_token(item)),
                    ATTR(tag, STROWN,
                         hidrd_item_short_get_tag_token(item)),
                    CONTENT(HEX,
                            /* We promise we won't change it */
                            hidrd_item_short_get_data((hidrd_item *)item)),
                            hidrd_item_short_get_data_size_bytes(item));
    }
}


static bool
write_basic_element(hidrd_strm_xml_inst   *strm_xml,
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
            return write_short_element(strm_xml, item);
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
hidrd_strm_xml_write_break(hidrd_strm *strm)
{
    hidrd_strm_xml_inst    *strm_xml    = (hidrd_strm_xml_inst *)strm;
    xmlNodePtr              root;

    assert(!hidrd_strm_xml_being_read(strm));
    assert(strm_xml->doc != NULL);
    assert(strm_xml->prnt != NULL);

    root = xmlDocGetRootElement(strm_xml->doc);
    if (!break_branch(root, strm_xml->prnt, group_break_cb))
        return false;

    strm_xml->prnt = root;

    return true;
}


bool
hidrd_strm_xml_write(hidrd_strm *strm, const hidrd_item *item)
{
    hidrd_strm_xml_inst    *strm_xml    = (hidrd_strm_xml_inst *)strm;

    assert(!hidrd_strm_xml_being_read(strm));

    if (strm_xml->doc == NULL  && !create_doc(strm_xml))
        goto failure;

    strm_xml->changed = true;

    if (!write_basic_element(strm_xml, item))
        goto failure;

    return true;

failure:

    strm->error = true;

    return false;
}



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

#include "hidrd/fmt/xml/prop.h"
#include "hidrd/fmt/xml/snk.h"


/**
 * Uppercase the first character of a string.
 *
 * @param str   String to modify.
 *
 * @return Modified string.
 */
static char *
str_uc_first(char *str)
{
    assert(str != NULL);

    if (*str >= 'a' && *str <= 'z')
        *str -= ('a' - 'A');

    return str;
}


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
str_apada(char *str)
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
element_new(hidrd_xml_snk_inst        *xml_snk,
            const char                 *name)
{
    assert(xml_snk->cur == NULL);

    xml_snk->cur = xmlNewChild(xml_snk->prnt, NULL, BAD_CAST name, NULL);

    return (xml_snk->cur != NULL);
}


static bool
element_set_attrpv(hidrd_xml_snk_inst  *xml_snk,
                   const char           *name,
                   str_fmt               fmt,
                   va_list              *pap)
{
    char       *value;
    xmlAttrPtr  attr;

    assert(xml_snk->cur != NULL);

    if (!fmt_strpv(&value, fmt, pap))
        return false;

    attr = xmlSetProp(xml_snk->cur, BAD_CAST name, BAD_CAST value);

    free(value);

    return (attr != NULL);
}


static bool
element_add_contentpv(hidrd_xml_snk_inst   *xml_snk,
                      str_fmt                fmt,
                      va_list               *pap)
{
    char   *content;

    assert(xml_snk->cur != NULL);

    if (!fmt_strpv(&content, fmt, pap))
        return false;

    xmlNodeAddContent(xml_snk->cur, BAD_CAST content);

    free(content);

    return true;
}


static bool
element_add_commentpv(hidrd_xml_snk_inst   *xml_snk,
                      str_fmt                fmt,
                      va_list               *pap)
{
    char       *content;
    xmlNodePtr  comment;

    assert(xml_snk->cur != NULL);

    if (!fmt_strpv(&content, fmt, pap))
        return false;

    comment = xmlNewDocComment(xml_snk->doc, BAD_CAST content);
    free(content);
    if (comment == NULL)
        return false;

    return (xmlAddChild(xml_snk->cur, comment) != NULL);
}


static void
element_commit(hidrd_xml_snk_inst *xml_snk,
               bool                 container)
{
    assert(xml_snk->cur != NULL);
    
    if (container)
        xml_snk->prnt = xml_snk->cur;

    xml_snk->cur = NULL;
}


/** Node type */
typedef enum nt {
    NT_NONE,
    NT_CONTENT,
    NT_COMMENT,
    NT_ATTR
} nt;

static bool
element_addpv(hidrd_xml_snk_inst   *xml_snk,
              bool                   container,
              const char            *name,
              va_list               *pap)
{
    bool    success = true;
    bool    end     = false;

    assert(xml_snk->cur == NULL);

    if (!element_new(xml_snk, name))
        return false;

    while (success && !end)
    {
        nt  node_type = va_arg(*pap, nt);

        switch (node_type)
        {
            case NT_ATTR:
                {
                    const char *name        = va_arg(*pap, const char *);
                    str_fmt     value_fmt   = va_arg(*pap, str_fmt);

                    success = element_set_attrpv(xml_snk,
                                                 name, value_fmt, pap);
                }
                break;

            case NT_COMMENT:
                {
                    str_fmt comment_fmt  = va_arg(*pap, str_fmt);

                    success = element_add_commentpv(xml_snk,
                                                    comment_fmt, pap);
                }
                break;

            case NT_CONTENT:
                {
                    str_fmt content_fmt  = va_arg(*pap, str_fmt);

                    success = element_add_contentpv(xml_snk,
                                                    content_fmt, pap);
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

    element_commit(xml_snk, container);

    return success;
}


static bool
element_add(hidrd_xml_snk_inst    *xml_snk,
            bool                    container,
            const char             *name,
            ...)
{
    va_list ap;
    bool    success;

    va_start(ap, name);
    success = element_addpv(xml_snk, container, name, &ap);
    va_end(ap);

    return success;
}


typedef struct group {
    const char *name;
    create_element_fn  *create_start;
    create_element_fn  *create_end;
} group;

#ifndef NDEBUG
static bool
group_valid(const group *g)
{
    return g != NULL &&
           g->name != NULL &&
           *g->name != '\0' &&
           g->create_start != NULL &&
           g->create_end != NULL;
}
#endif

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
group_end(hidrd_xml_snk_inst  *xml_snk,
          const char           *name)
{
    const group    *target_group;
    xmlNodePtr      target_element;

    assert(xml_snk->cur == NULL);
    assert(name != NULL);

    target_group = lookup_group(name);
    /* There must be such group */
    assert(target_group != NULL);

    /* Look up an element with the same name up the parent stack */
    for (target_element = xml_snk->prnt;
         target_element != NULL && target_element->type == XML_ELEMENT_NODE;
         target_element = target_element->parent)
        if (strcmp((const char *)target_element->name, name) == 0)
            break;

    /* If not found */
    if (target_element == NULL || target_element->type != XML_ELEMENT_NODE)
    {
        xmlNodePtr  end_element;

        /* Insert closing element */
        end_element = target_group->create_end(xml_snk->doc, NULL);
        return xmlAddChild(xml_snk->prnt, end_element) != NULL;
    }
    else
    {
        /* Break open the branch up to the target element */
        if (!break_branch(target_element, xml_snk->prnt, group_break_cb))
            return false;

        /* Element done */
        xml_snk->prnt = target_element->parent;
    }

    return true;
}


#define ATTR(_name, _fmt, _args...) \
    NT_ATTR, #_name, STR_FMT_##_fmt, ##_args

#define CONTENT(_fmt, _args...) \
    NT_CONTENT, STR_FMT_##_fmt, ##_args

#define COMMENT(_fmt, _args...) \
    NT_COMMENT, STR_FMT_##_fmt, ##_args

#define ADD_SIMPLE(_name, _args...) \
    element_add(xml_snk, false, #_name, ##_args, NT_NONE)

#define GROUP_START(_name, _args...) \
    element_add(xml_snk, true, #_name, ##_args, NT_NONE)

#define GROUP_END(_name) \
    group_end(xml_snk, #_name)

#define CASE_SIMPLE_INT(_TYPE, _NAME, _name) \
    case HIDRD_ITEM_##_TYPE##_TAG_##_NAME:                          \
        return ADD_SIMPLE(                                          \
                _name,                                              \
                CONTENT(INT,                                        \
                        (int)hidrd_item_##_name##_get_value(item)))

#define CASE_SIMPLE_UINT(_TYPE, _NAME, _name) \
    case HIDRD_ITEM_##_TYPE##_TAG_##_NAME:                          \
        return ADD_SIMPLE(                                          \
                _name,                                              \
                CONTENT(INT,                                        \
                        (unsigned int)                              \
                            hidrd_item_##_name##_get_value(item)))


static bool
write_main_bit_elements(hidrd_xml_snk_inst   *xml_snk,
                        const hidrd_item      *item)
{
    uint8_t bit;
    char    name[6];

    assert(xml_snk->cur == NULL);
    assert(hidrd_item_main_valid(item));
    assert(hidrd_item_input_valid(item) ||
           hidrd_item_output_valid(item) ||
           hidrd_item_feature_valid(item));

#define BIT(_idx, _on_name) \
    do {                                            \
        if (hidrd_item_main_get_bit(item, _idx) &&  \
            !ADD_SIMPLE(_on_name))                  \
            return false;                           \
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

            if (!element_add(xml_snk, false, name, NT_NONE))
                return false;
        }

    return true;
}

static bool
write_main_element(hidrd_xml_snk_inst   *xml_snk,
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
                result = element_add(xml_snk, true, token, NT_NONE);
                free(token);
                if (!result)
                    return false;

                if (!write_main_bit_elements(xml_snk, item))
                    return false;

                xml_snk->prnt = xml_snk->prnt->parent;

                return true;
            }
        default:
            return ADD_SIMPLE(
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
write_unit_generic_element(hidrd_xml_snk_inst *xml_snk,
                           hidrd_unit           unit)
{
    bool            success = false;
    bool            inside  = false;
    hidrd_unit_exp  exp;

    if (!element_add(xml_snk, true, "generic",
                     ATTR(system, STROWN,
                          hidrd_unit_system_to_token_or_dec(
                            hidrd_unit_get_system(unit))),
                     NT_NONE))
        goto cleanup;

    inside = true;

#define EXP(_name) \
    do {                                                                \
        exp = hidrd_unit_get_##_name(unit);                             \
        if (exp != HIDRD_UNIT_EXP_0)                                    \
        {                                                               \
            if (exp == HIDRD_UNIT_EXP_1)                                \
            {                                                           \
                if (!ADD_SIMPLE(_name))                                 \
                    goto cleanup;                                       \
            }                                                           \
            else                                                        \
            {                                                           \
                if (!ADD_SIMPLE(_name,                                  \
                                CONTENT(INT,                            \
                                        hidrd_unit_exp_to_int(exp))))   \
                    goto cleanup;                                       \
            }                                                           \
        }                                                               \
    } while (0)

    EXP(length);
    EXP(mass);
    EXP(time);
    EXP(temperature);
    EXP(current);
    EXP(luminous_intensity);

#undef EXP

    success = true;

cleanup:

    if (inside)
        xml_snk->prnt = xml_snk->prnt->parent;

    return success;
}


static bool
write_unit_specific_element(hidrd_xml_snk_inst *xml_snk,
                            hidrd_unit           unit)
{
    bool                success = false;
    hidrd_unit_system   system;
    bool                inside  = false;
    hidrd_unit_exp      exp;

    assert(hidrd_unit_valid(unit));
    system = hidrd_unit_get_system(unit);
    assert(hidrd_unit_system_known(system));

    if (!element_add(xml_snk, true, hidrd_unit_system_to_token(system),
                     NT_NONE))
        goto cleanup;

    inside = true;

#define EXP(_gen_name, _spec_expr) \
    do {                                                                \
        exp = hidrd_unit_get_##_gen_name(unit);                         \
        if (exp != HIDRD_UNIT_EXP_0)                                    \
        {                                                               \
            const char *_spec_name = (_spec_expr);                      \
                                                                        \
            if (exp == HIDRD_UNIT_EXP_1)                                \
            {                                                           \
                if (!element_add(xml_snk, false, _spec_name, NT_NONE)) \
                    goto cleanup;                                       \
            }                                                           \
            else                                                        \
            {                                                           \
                if (!element_add(xml_snk, false, _spec_name,           \
                                 CONTENT(INT,                           \
                                         hidrd_unit_exp_to_int(exp)),   \
                                 NT_NONE))                              \
                    goto cleanup;                                       \
            }                                                           \
        }                                                               \
    } while (0)

    EXP(length,
        (system == HIDRD_UNIT_SYSTEM_SI_LINEAR)
            ? "centimeter"
            : (system == HIDRD_UNIT_SYSTEM_SI_ROTATION)
                ? "radians"
                : (system == HIDRD_UNIT_SYSTEM_ENGLISH_LINEAR)
                    ? "inch"
                    : "degrees");
    EXP(mass,
        (system == HIDRD_UNIT_SYSTEM_SI_LINEAR ||
         system == HIDRD_UNIT_SYSTEM_SI_ROTATION)
            ? "gram"
            : "slug");
    EXP(time, "seconds");
    EXP(temperature,
        (system == HIDRD_UNIT_SYSTEM_SI_LINEAR ||
         system == HIDRD_UNIT_SYSTEM_SI_ROTATION)
            ? "kelvin"
            : "fahrenheit");
    EXP(current, "ampere");
    EXP(luminous_intensity, "candela");

#undef EXP

    success = true;

cleanup:

    if (inside)
        xml_snk->prnt = xml_snk->prnt->parent;

    return success;
}


static bool
write_unit_element(hidrd_xml_snk_inst *xml_snk,
                   hidrd_unit           unit)
{
    bool    success     = false;
    bool    inside      = false;

    if (!element_add(xml_snk, true, "unit", NT_NONE))
        goto cleanup;
    inside = true;

    /*
     * If the unit value could be interpreted with our API and it does
     * contain something meaningful.
     */
    /* If the unit is "none" - i.e. there is no units */
    if (unit == HIDRD_UNIT_NONE)
        success = ADD_SIMPLE(none);
    /*
     * If the unit is void (indicates no particular units) or 
     * unknown, (cannot be interpreted by our API)
     */
    else if (hidrd_unit_void(unit) || !hidrd_unit_known(unit))
        success = ADD_SIMPLE(value, CONTENT(HEX, &unit, sizeof(unit)));
    else
        /* If the unit system is known to us */
        success = hidrd_unit_system_known(hidrd_unit_get_system(unit))
                    ? write_unit_specific_element(xml_snk, unit)
                    : write_unit_generic_element(xml_snk, unit);

cleanup:

    if (inside)
        xml_snk->prnt = xml_snk->prnt->parent;

    return success;
}


static bool
write_global_element(hidrd_xml_snk_inst   *xml_snk,
                   const hidrd_item      *item)
{
    assert(hidrd_item_global_valid(item));

    switch (hidrd_item_global_get_tag(item))
    {
        CASE_SIMPLE_INT(GLOBAL, LOGICAL_MINIMUM, logical_minimum);
        CASE_SIMPLE_INT(GLOBAL, LOGICAL_MAXIMUM, logical_maximum);
        CASE_SIMPLE_INT(GLOBAL, PHYSICAL_MINIMUM, physical_minimum);
        CASE_SIMPLE_INT(GLOBAL, PHYSICAL_MAXIMUM, physical_maximum);
        CASE_SIMPLE_INT(GLOBAL, UNIT_EXPONENT, unit_exponent);
        CASE_SIMPLE_UINT(GLOBAL, REPORT_SIZE, report_size);
        CASE_SIMPLE_UINT(GLOBAL, REPORT_ID, report_id);
        CASE_SIMPLE_UINT(GLOBAL, REPORT_COUNT, report_count);

        case HIDRD_ITEM_GLOBAL_TAG_UNIT:
            return write_unit_element(xml_snk,
                                      hidrd_item_unit_get_value(item));

        case HIDRD_ITEM_GLOBAL_TAG_USAGE_PAGE:
            xml_snk->state->usage_page =
                hidrd_item_usage_page_get_value(item);
            return ADD_SIMPLE(
                    usage_page,
                    CONTENT(STROWN,
                            hidrd_usage_page_to_token_or_hex(
                                hidrd_item_usage_page_get_value(item))),
                    COMMENT(STROWN,
                            str_apada(
                                str_uc_first(
                                    hidrd_usage_page_desc(
                                        hidrd_item_usage_page_get_value(
                                            item))))));

        case HIDRD_ITEM_GLOBAL_TAG_PUSH:
            {
                hidrd_xml_snk_state   *new_state;

                /* Push state */
                new_state = malloc(sizeof(*new_state));
                if (new_state == NULL)
                    return false;
                memcpy(new_state, xml_snk->state, sizeof(*new_state));
                new_state->prev = xml_snk->state;
                xml_snk->state = new_state;

                return GROUP_START(PUSH);
            }
        case HIDRD_ITEM_GLOBAL_TAG_POP:
            {
                hidrd_xml_snk_state   *prev_state;

                /* Pop state, if possible */
                prev_state = xml_snk->state->prev;
                if (prev_state != NULL)
                {
                    free(xml_snk->state);
                    xml_snk->state = prev_state;
                }
                return GROUP_END(PUSH);
            }
        default:
            return ADD_SIMPLE(
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
write_usage_element(hidrd_xml_snk_inst    *xml_snk,
                    const char             *name,
                    hidrd_usage             usage)
{
    bool    success         = false;
    char   *token_or_hex;
    char   *desc            = NULL;

    if (!hidrd_usage_defined_page(usage))
        usage = hidrd_usage_set_page(usage, xml_snk->state->usage_page);

    if (hidrd_usage_get_page(usage) == xml_snk->state->usage_page)
    {
        token_or_hex = hidrd_usage_to_token_or_hex_id(usage);
        if (token_or_hex == NULL)
            goto cleanup;
        desc = hidrd_usage_desc_id(usage);
        if (desc == NULL)
            goto cleanup;
    }
    else
    {
        token_or_hex = hidrd_usage_to_token_or_hex(usage);
        if (token_or_hex == NULL)
            goto cleanup;
        desc = hidrd_usage_desc(usage);
        if (desc == NULL)
            goto cleanup;
    }

    if (*desc == '\0')
    {
        success = element_add(xml_snk, false, name,
                              CONTENT(STROWN, token_or_hex), NT_NONE);
        token_or_hex = NULL;
    }
    else
    {
        success = element_add(xml_snk, false, name,
                              CONTENT(STROWN, token_or_hex),
                              COMMENT(STROWN, str_apada(str_uc_first(desc))),
                              NT_NONE);
        token_or_hex = NULL;
        desc = NULL;
    }

cleanup:

    free(desc);
    free(token_or_hex);

    return success;
}


static bool
write_local_element(hidrd_xml_snk_inst   *xml_snk,
                   const hidrd_item      *item)
{
    assert(hidrd_item_local_valid(item));

    switch (hidrd_item_local_get_tag(item))
    {
        CASE_SIMPLE_UINT(LOCAL, DESIGNATOR_INDEX, designator_index);
        CASE_SIMPLE_UINT(LOCAL, DESIGNATOR_MINIMUM, designator_minimum);
        CASE_SIMPLE_UINT(LOCAL, DESIGNATOR_MAXIMUM, designator_maximum);
        CASE_SIMPLE_UINT(LOCAL, STRING_INDEX, string_index);
        CASE_SIMPLE_UINT(LOCAL, STRING_MINIMUM, string_minimum);
        CASE_SIMPLE_UINT(LOCAL, STRING_MAXIMUM, string_maximum);

        case HIDRD_ITEM_LOCAL_TAG_USAGE:
            return write_usage_element(xml_snk, "usage",
                                       hidrd_item_usage_get_value(item));

        case HIDRD_ITEM_LOCAL_TAG_USAGE_MINIMUM:
            return write_usage_element(
                        xml_snk, "usage_minimum",
                        hidrd_item_usage_minimum_get_value(item));

        case HIDRD_ITEM_LOCAL_TAG_USAGE_MAXIMUM:
            return write_usage_element(
                        xml_snk, "usage_maximum",
                        hidrd_item_usage_maximum_get_value(item));

        case HIDRD_ITEM_LOCAL_TAG_DELIMITER:
            return (hidrd_item_delimiter_get_value(item) ==
                    HIDRD_ITEM_DELIMITER_SET_OPEN)
                        ? GROUP_START(SET)
                        : GROUP_END(SET);

        default:
            return ADD_SIMPLE(
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
write_short_element(hidrd_xml_snk_inst   *xml_snk,
                    const hidrd_item      *item)
{
    assert(hidrd_item_short_valid(item));

    switch (hidrd_item_short_get_type(item))
    {
        case HIDRD_ITEM_SHORT_TYPE_MAIN:
            return write_main_element(xml_snk, item);
        case HIDRD_ITEM_SHORT_TYPE_GLOBAL:
            return write_global_element(xml_snk, item);
        case HIDRD_ITEM_SHORT_TYPE_LOCAL:
            return write_local_element(xml_snk, item);
        default:
            return ADD_SIMPLE(short,
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
write_basic_element(hidrd_xml_snk_inst   *xml_snk,
                    const hidrd_item      *item)
{
    switch (hidrd_item_basic_get_format(item))
    {
        case HIDRD_ITEM_BASIC_FORMAT_LONG:
            return ADD_SIMPLE(
                        long,
                        ATTR(tag, UINT, hidrd_item_long_get_tag(item)),
                        CONTENT(
                            HEX,
                            /* We promise we won't change it */
                            hidrd_item_long_get_data((hidrd_item *)item)),
                            hidrd_item_long_get_data_size(item));

        case HIDRD_ITEM_BASIC_FORMAT_SHORT:
            return write_short_element(xml_snk, item);
        default:
            return ADD_SIMPLE(basic,
                    ATTR(type, STROWN,
                         hidrd_item_basic_get_type_token(item)),
                    ATTR(tag, STROWN,
                         hidrd_item_basic_get_tag_token(item)),
                    ATTR(tag, UINT,
                         hidrd_item_basic_get_data_size_bytes(item)));
    }
}


/************************************************************
 * TODO refactor all of the above to separate files
 ************************************************************/

static bool
init(hidrd_snk *snk, bool format)
{
    hidrd_xml_snk_inst     *xml_snk = (hidrd_xml_snk_inst *)snk;
    hidrd_xml_snk_state    *state   = NULL;
    xmlDocPtr               doc     = NULL;
    xmlNodePtr              root    = NULL;

    /* Create item state table stack */
    state = malloc(sizeof(*state));
    if (state == NULL)
        goto failure;
    state->prev         = NULL;
    state->usage_page   = HIDRD_USAGE_PAGE_UNDEFINED;

    /* Create the document */
    doc = xmlNewDoc(BAD_CAST "1.0");
    if (doc == NULL)
        goto failure;

    /* Create root node and use it as the initial parent */
    root = xmlNewNode(NULL, BAD_CAST "descriptor");
    if (root == NULL)
        goto failure;

    /*
     * Set root node properties
     */
    if (xmlSetProp(root, BAD_CAST "xmlns",
                   BAD_CAST HIDRD_XML_PROP_NS) == NULL)
        goto failure;

    if (xmlSetProp(root, BAD_CAST "xmlns:xsi",
                   BAD_CAST HIDRD_XML_PROP_NS_XSI) == NULL)
        goto failure;

    if (xmlSetProp(root, BAD_CAST "xsi:schemaLocation",
                   BAD_CAST HIDRD_XML_PROP_XSI_SCHEMA_LOCATION) == NULL)
        goto failure;

    /* Set root element */
    xmlDocSetRootElement(doc, root);

    /* Initialize the sink */
    xml_snk->format = format;
    xml_snk->state  = state;
    xml_snk->doc    = doc;
    xml_snk->prnt   = root;

    return true;

failure:

    xmlFreeNode(root);

    if (doc != NULL)
        xmlFreeDoc(doc);

    if (state != NULL)
        free(state);

    return false;
}


static bool
hidrd_xml_snk_init(hidrd_snk *snk, va_list ap)
{
    bool    format  = (va_arg(ap, int) != 0);

    return init(snk, format);
}


#ifdef HIDRD_WITH_OPT
const hidrd_opt_spec hidrd_xml_snk_opts_spec[] = {
    {.name  = "format",
     .type  = HIDRD_OPT_TYPE_BOOLEAN,
     .req   = false,
     .dflt  = {
         .boolean = true
     },
     .desc  = "Format XML output"},
    {.name  = NULL}
};

static bool
hidrd_xml_snk_init_opts(hidrd_snk *snk, const hidrd_opt *list)
{
    return init(snk, hidrd_opt_list_get_boolean(list, "format"));
}
#endif /* HIDRD_WITH_OPT */


static bool
hidrd_xml_snk_valid(const hidrd_snk *snk)
{
    const hidrd_xml_snk_inst   *xml_snk = (const hidrd_xml_snk_inst *)snk;

    return snk->type->size >= sizeof(hidrd_xml_snk_inst) &&
           xml_snk->state != NULL &&
           xml_snk->doc != NULL &&
           xml_snk->prnt != NULL;
}


static bool
hidrd_xml_snk_break_groups(hidrd_snk *snk)
{
    hidrd_xml_snk_inst *xml_snk = (hidrd_xml_snk_inst *)snk;
    xmlNodePtr          root;

    assert(xml_snk->doc != NULL);
    assert(xml_snk->prnt != NULL);

    root = xmlDocGetRootElement(xml_snk->doc);
    if (!break_branch(root, xml_snk->prnt, group_break_cb))
        return false;

    xml_snk->prnt = root;

    return true;
}


static bool
hidrd_xml_snk_flush(hidrd_snk *snk)
{
    bool                result      = false;
    hidrd_xml_snk_inst *xml_snk     = (hidrd_xml_snk_inst *)snk;
    xmlBufferPtr        xml_buf     = NULL;
    xmlOutputBufferPtr  xml_out_buf = NULL;
    void               *new_buf;
    size_t              new_size;

    /* Break any unfinished groups */
    if (!hidrd_xml_snk_break_groups(snk))
        goto finish;

    /* Create an XML buffer */
    xml_buf = xmlBufferCreate();
    if (xml_buf == NULL)
        goto finish;

    /* Create an XML output buffer from the generic buffer */
    xml_out_buf = xmlOutputBufferCreateBuffer(xml_buf, NULL);
    if (xml_out_buf == NULL)
        goto finish;

    /* Format XML from the document */
    if (xmlSaveFormatFileTo(xml_out_buf, xml_snk->doc,
                            NULL, xml_snk->format) < 0)
        goto finish;
    /* xml_out_buf is closed by xmlSaveFormatFileTo */
    xml_out_buf = NULL;

    /* Retrieve resulting size */
    new_size = xmlBufferLength(xml_buf);

    /* If we have a location for the buffer pointer */
    if (snk->pbuf != NULL)
    {
        /* Retension and update the buffer */
        new_buf = realloc(*snk->pbuf, new_size);
        if (new_size > 0 && new_buf == NULL)
            goto finish;
        memcpy(new_buf, xmlBufferContent(xml_buf), new_size);
        /* Update the buffer pointer */
        *snk->pbuf = new_buf;
    }

    /* Output size */
    if (snk->psize != NULL)
        *snk->psize = new_size;

    result = true;

finish:

    if (xml_out_buf != NULL)
        xmlOutputBufferClose(xml_out_buf);

    if (xml_buf != NULL)
        xmlBufferFree(xml_buf);

    return result;
}


static void
hidrd_xml_snk_clnp(hidrd_snk *snk)
{
    hidrd_xml_snk_inst    *xml_snk    = (hidrd_xml_snk_inst *)snk;
    hidrd_xml_snk_state   *state;
    hidrd_xml_snk_state   *prev_state;

    /* Free the document, if there is any */
    if (xml_snk->doc != NULL)
    {
        xmlFreeDoc(xml_snk->doc);
        xml_snk->doc = NULL;
    }

    /* Free the state stack, if there is any */
    for (state = xml_snk->state; state != NULL; state = prev_state)
    {
        prev_state = state->prev;
        free(state);
    }
    xml_snk->state = NULL;
}


static bool
hidrd_xml_snk_put(hidrd_snk *snk, const hidrd_item *item)
{
    hidrd_xml_snk_inst *xml_snk = (hidrd_xml_snk_inst *)snk;

    return write_basic_element(xml_snk, item);
}


const hidrd_snk_type hidrd_xml_snk = {
    .size       = sizeof(hidrd_xml_snk_inst),
    .init       = hidrd_xml_snk_init,
#ifdef HIDRD_WITH_OPT
    .init_opts  = hidrd_xml_snk_init_opts,
    .opts_spec  = hidrd_xml_snk_opts_spec,
#endif
    .valid      = hidrd_xml_snk_valid,
    .put        = hidrd_xml_snk_put,
    .flush      = hidrd_xml_snk_flush,
    .clnp       = hidrd_xml_snk_clnp,
};



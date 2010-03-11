/** @file
 * @brief HID report descriptor - XML source - element handling
 *
 * Copyright (C) 2010 Nikolai Kondrashov
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

#include "hidrd/util/hex.h"
#include "src_element.h"


/**
 * Prototype for an element processing function.
 *
 * @param xml_src   XML source instance.
 * @param e         Element to handle (src->cur - the encountered element).
 * 
 * @return Element processing result code.
 */
typedef element_rc element_fn(hidrd_xml_src_inst   *xml_src,
                              xmlNodePtr            e);

#define ELEMENT(_name) \
    static element_rc                                           \
    element_##_name(hidrd_xml_src_inst *xml_src, xmlNodePtr e)

#define ELEMENT_EXIT(_name) \
    static element_rc                                                   \
    element_##_name##_exit(hidrd_xml_src_inst *xml_src, xmlNodePtr e)

#define PROP_DECL(_type, _name) \
    char           *_name##_str = NULL; \
    hidrd_##_type   _name

#define PROP_RETR(_type, _name, _repr) \
    do {                                                        \
        _name##_str = (char *)xmlGetProp(e, BAD_CAST #_name);   \
        if (_name##_str == NULL)                                \
            goto cleanup;                                       \
        if (!hidrd_##_type##_from_##_repr(&_name, _name##_str)) \
            goto cleanup;                                       \
    } while (0)

#define PROP_CLNP(_name) \
    xmlFree(_name##_str)

ELEMENT(basic)
{
    element_rc  result_rc   = ELEMENT_RC_ERROR;
    char       *data_str    = NULL;
    size_t      data_len;

    PROP_DECL(item_basic_data_bytes,    size);
    PROP_DECL(item_basic_type,          type);
    PROP_DECL(item_basic_tag,           tag);

    PROP_RETR(item_basic_data_bytes,    size,   dec);
    PROP_RETR(item_basic_type,          type,   token_or_dec);
    PROP_RETR(item_basic_tag,           tag,    dec);

    hidrd_item_basic_init(xml_src->item, type, tag,
                          hidrd_item_basic_data_size_from_bytes(size));

    data_str = (char *)xmlNodeGetContent(e);
    if (data_str == NULL)
        goto cleanup;
    if (!hidrd_hex_buf_from_str(xml_src->item + HIDRD_ITEM_BASIC_MIN_SIZE,
                                (HIDRD_ITEM_BASIC_MAX_SIZE -
                                 HIDRD_ITEM_BASIC_MIN_SIZE),
                                &data_len, data_str))
        goto cleanup;

    if (!hidrd_item_valid(xml_src->item))
        goto cleanup;

    if (hidrd_item_get_size(xml_src->item) !=
        (data_len + HIDRD_ITEM_BASIC_MIN_SIZE))
        goto cleanup;

    result_rc = ELEMENT_RC_ITEM;

cleanup:

    xmlFree(data_str);
    PROP_CLNP(tag);
    PROP_CLNP(type);
    PROP_CLNP(size);

    return result_rc;
}

ELEMENT(short)
{
    element_rc  result_rc   = ELEMENT_RC_ERROR;
    char       *data_str    = NULL;
    size_t      data_len;

    PROP_DECL(item_short_type,  type);
    PROP_DECL(item_short_tag,   tag);

    PROP_RETR(item_short_type,  type,   token_or_dec);
    PROP_RETR(item_short_tag,   tag,    dec);

    hidrd_item_short_init(xml_src->item, type, tag);

    data_str = (char *)xmlNodeGetContent(e);
    if (data_str == NULL)
        goto cleanup;
    if (!hidrd_hex_buf_from_str(hidrd_item_short_get_data(xml_src->item),
                                HIDRD_ITEM_SHORT_DATA_BYTES_MAX,
                                &data_len, data_str))
        goto cleanup;

    hidrd_item_short_set_data_size(
            xml_src->item, hidrd_item_short_data_size_from_bytes(data_len));

    if (!hidrd_item_valid(xml_src->item))
        goto cleanup;

    result_rc = ELEMENT_RC_ITEM;

cleanup:

    xmlFree(data_str);
    PROP_CLNP(tag);
    PROP_CLNP(type);

    return result_rc;
}

ELEMENT(main)
{
    element_rc  result_rc   = ELEMENT_RC_ERROR;
    char       *data_str    = NULL;
    size_t      data_len;

    PROP_DECL(item_main_tag,    tag);

    PROP_RETR(item_main_tag,    tag,    token_or_dec);

    hidrd_item_main_init(xml_src->item, tag);

    data_str = (char *)xmlNodeGetContent(e);
    if (data_str == NULL)
        goto cleanup;
    if (!hidrd_hex_buf_from_str(hidrd_item_short_get_data(xml_src->item),
                                HIDRD_ITEM_SHORT_DATA_BYTES_MAX,
                                &data_len, data_str))
        goto cleanup;

    hidrd_item_short_set_data_size(
            xml_src->item, hidrd_item_short_data_size_from_bytes(data_len));

    if (!hidrd_item_valid(xml_src->item))
        goto cleanup;

    result_rc = ELEMENT_RC_ITEM;

cleanup:

    xmlFree(data_str);
    PROP_CLNP(tag);

    return result_rc;
}

ELEMENT(global)
{
    element_rc  result_rc   = ELEMENT_RC_ERROR;
    char       *data_str    = NULL;
    size_t      data_len;

    PROP_DECL(item_global_tag,    tag);

    PROP_RETR(item_global_tag,    tag,    token_or_dec);

    hidrd_item_global_init(xml_src->item, tag);

    data_str = (char *)xmlNodeGetContent(e);
    if (data_str == NULL)
        goto cleanup;
    if (!hidrd_hex_buf_from_str(hidrd_item_short_get_data(xml_src->item),
                                HIDRD_ITEM_SHORT_DATA_BYTES_MAX,
                                &data_len, data_str))
        goto cleanup;

    hidrd_item_short_set_data_size(
            xml_src->item, hidrd_item_short_data_size_from_bytes(data_len));

    if (!hidrd_item_valid(xml_src->item))
        goto cleanup;

    result_rc = ELEMENT_RC_ITEM;

cleanup:

    xmlFree(data_str);
    PROP_CLNP(tag);

    return result_rc;
}

ELEMENT(local)
{
    element_rc  result_rc   = ELEMENT_RC_ERROR;
    char       *data_str    = NULL;
    size_t      data_len;

    PROP_DECL(item_local_tag,    tag);

    PROP_RETR(item_local_tag,    tag,    token_or_dec);

    hidrd_item_local_init(xml_src->item, tag);

    data_str = (char *)xmlNodeGetContent(e);
    if (data_str == NULL)
        goto cleanup;
    if (!hidrd_hex_buf_from_str(hidrd_item_short_get_data(xml_src->item),
                                HIDRD_ITEM_SHORT_DATA_BYTES_MAX,
                                &data_len, data_str))
        goto cleanup;

    hidrd_item_short_set_data_size(
            xml_src->item, hidrd_item_short_data_size_from_bytes(data_len));

    if (!hidrd_item_valid(xml_src->item))
        goto cleanup;

    result_rc = ELEMENT_RC_ITEM;

cleanup:

    xmlFree(data_str);
    PROP_CLNP(tag);

    return result_rc;
}

ELEMENT(COLLECTION)
{
    element_rc  result_rc   = ELEMENT_RC_ERROR;

    PROP_DECL(item_collection_type, type);

    PROP_RETR(item_collection_type, type,   token_or_dec);

    hidrd_item_collection_init(xml_src->item, type);

    result_rc = ELEMENT_RC_ITEM;

cleanup:

    PROP_CLNP(type);
    return result_rc;
}

ELEMENT_EXIT(COLLECTION)
{
    (void)e;
    hidrd_item_end_collection_init(xml_src->item);
    return ELEMENT_RC_ITEM;
}

#define NUM_ELEMENT(_name, _t) \
    ELEMENT(_name)                                              \
    {                                                           \
        element_rc              result_rc   = ELEMENT_RC_ERROR; \
        char                   *value_str   = NULL;             \
        HIDRD_NUM_##_t##_TYPE   value;                          \
                                                                \
        value_str = (char *)xmlNodeGetContent(e);               \
        if (value_str == NULL)                                  \
            goto cleanup;                                       \
        if (!hidrd_dec_##_t##_from_str(&value, value_str))      \
            goto cleanup;                                       \
                                                                \
        hidrd_item_##_name##_init(xml_src->item, value);        \
                                                                \
        result_rc = ELEMENT_RC_ITEM;                            \
                                                                \
    cleanup:                                                    \
                                                                \
        xmlFree(value_str);                                     \
                                                                \
        return result_rc;                                       \
    }

NUM_ELEMENT(logical_minimum,    s32)
NUM_ELEMENT(logical_maximum,    s32)
NUM_ELEMENT(physical_minimum,   s32)
NUM_ELEMENT(physical_maximum,   s32)

ELEMENT(long)
{
    element_rc  result_rc       = ELEMENT_RC_ERROR;
    char       *data_str        = NULL;
    size_t      data_len;

    PROP_DECL(item_long_tag,    tag);

    PROP_RETR(item_long_tag,    tag,    dec);

    hidrd_item_long_init(xml_src->item, tag);

    data_str = (char *)xmlNodeGetContent(e);
    if (data_str == NULL)
        goto cleanup;
    if (!hidrd_hex_buf_from_str(hidrd_item_long_get_data(xml_src->item),
                                HIDRD_ITEM_LONG_DATA_SIZE_MAX,
                                &data_len, data_str))
        goto cleanup;

    hidrd_item_long_set_data_size(xml_src->item, data_len);

    if (!hidrd_item_valid(xml_src->item))
        goto cleanup;

    result_rc = ELEMENT_RC_ITEM;

cleanup:

    xmlFree(data_str);
    PROP_CLNP(tag);

    return result_rc;
}

ELEMENT(descriptor)
{
    (void)xml_src;
    (void)e;
    /* No item yet */
    return ELEMENT_RC_NONE;
}

ELEMENT_EXIT(descriptor)
{
    (void)xml_src;
    (void)e;
    /* No more items */
    return ELEMENT_RC_END;
}

/** Element handler */
typedef struct element_handler {
    const char *name;           /**< Element name */
    element_fn *handle;         /**< Element handling function */
    element_fn *handle_exit;    /**< Element exit handling function */
} element_handler;

/** Element handler list */
static const element_handler handler_list[] = {
#define IGNORE(_name)       {.name = #_name}
#define HANDLE(_name)       {.name = #_name, .handle = element_##_name}
#define ENTER(_name)        {.name = #_name, \
                             .handle = element_##_name,             \
                             .handle_exit = element_##_name##_exit}
    HANDLE(basic),
    HANDLE(short),
    HANDLE(main),
    IGNORE(input),
    IGNORE(output),
    IGNORE(feature),
    IGNORE(collection),
    IGNORE(end_collection),
    ENTER(COLLECTION),
    HANDLE(global),
    IGNORE(usage_page),
    HANDLE(logical_minimum),
    HANDLE(logical_maximum),
    HANDLE(physical_minimum),
    HANDLE(physical_maximum),
    IGNORE(unit_exponent),
    IGNORE(unit),
    IGNORE(report_size),
    IGNORE(report_count),
    IGNORE(report_id),
    IGNORE(push),
    IGNORE(pop),
    IGNORE(PUSH),
    HANDLE(local),
    IGNORE(usage),
    IGNORE(usage_minimum),
    IGNORE(usage_maximum),
    IGNORE(designator_index),
    IGNORE(designator_minimum),
    IGNORE(designator_maximum),
    IGNORE(string_index),
    IGNORE(string_minimum),
    IGNORE(string_maximum),
    IGNORE(delimiter),
    IGNORE(SET),
    HANDLE(long),
    ENTER(descriptor),
#undef IGNORE
#undef HANDLE
};


element_rc
element(hidrd_xml_src_inst *xml_src, bool *penter)
{
    const char             *name;
    size_t                  i;
    const element_handler  *handler;

    assert(xml_src != NULL);
    assert(penter != NULL);
    /* We have to process something */
    assert(xml_src->cur != NULL);
    /* We process elements only */
    assert(xml_src->cur->type == XML_ELEMENT_NODE);
    /* Either no parent or an element parent */
    assert(xml_src->prnt == NULL ||
           xml_src->prnt->type == XML_ELEMENT_NODE);

    name = (const char *)xml_src->cur->name;

    for (i = 0; i < sizeof(handler_list) / sizeof(*handler_list); i++)
    {
        handler = handler_list + i;

        if (strcmp(handler->name, name) == 0)
        {
            if (handler->handle_exit != NULL)
                *penter = true;
            if (handler->handle == NULL)
                return ELEMENT_RC_NONE;
            return (*handler->handle)(xml_src, xml_src->cur);
        }
    }

    return ELEMENT_RC_ERROR;
}


element_rc
element_exit(hidrd_xml_src_inst *xml_src)
{
    const char             *name;
    size_t                  i;
    const element_handler  *handler;

    assert(xml_src != NULL);
    /* We have to process something */
    assert(xml_src->prnt != NULL);
    /* We process elements only */
    assert(xml_src->prnt->type == XML_ELEMENT_NODE);
    /* We should be at the end of the node list */
    assert(xml_src->cur == NULL);

    name = (const char *)xml_src->prnt->name;

    for (i = 0; i < sizeof(handler_list) / sizeof(*handler_list); i++)
    {
        handler = handler_list + i;
        if (strcmp(handler->name, name) == 0)
        {
            assert(handler->handle_exit != NULL);
            return (*handler->handle_exit)(xml_src, xml_src->prnt);
        }
    }

    return ELEMENT_RC_ERROR;
}



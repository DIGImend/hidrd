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
#include "hidrd/util/str.h"
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

typedef struct main_bit_desc {
    const char *off;
    const char *on;
} main_bit_desc;

#define MBD(_num, _off, _on) \
    static const main_bit_desc mbd##_num = {.off = #_off, .on = #_on}

MBD(0, data, constant);
MBD(1, array, variable);
MBD(2, absolute, relative);
MBD(3, no_wrap, wrap);
MBD(4, linear, non_linear);
MBD(5, preferred_state, no_preferred);
MBD(6, no_null_position, null_state);
MBD(7, non_volatile, volatile);
MBD(8, bit_field, buffered_bytes);

#undef MBD

typedef const main_bit_desc    *main_bitmap_desc[32];

#define MBMD(_name, _fields...) \
    static const main_bitmap_desc   _name##_bmd = {_fields}

MBMD(input,  &mbd0, &mbd1, &mbd2, &mbd3, &mbd4, &mbd5, &mbd6, NULL,  &mbd8);
MBMD(output, &mbd0, &mbd1, &mbd2, &mbd3, &mbd4, &mbd5, &mbd6, &mbd7, &mbd8);
#define feature_bmd output_bmd

static bool parse_bitmap_element(uint32_t                  *pbitmap,
                                 xmlNodePtr                 e,
                                 const main_bitmap_desc     bmd)
{
    bool        result      = false;
    uint32_t    bitmap      = 0;
    char       *data_str    = NULL;
    bool        data;
    size_t      i;
    char        i_name[6]   = "bit";

    for (i = 0, e = e->children; e != NULL; e = e->next)
    {
        if (e->type != XML_ELEMENT_NODE)
            continue;

        data_str = (char *)xmlNodeGetContent(e);
        if (data_str == NULL)
            goto cleanup;
        if (hidrd_str_isblank(data_str))
            data = true;
        else if (!hidrd_bool_from_str(&data, data_str))
            goto cleanup;
        xmlFree(data_str);
        data_str = NULL;

        while (true)
        {
            if (bmd[i] != NULL)
            {
                if (strcmp(bmd[i]->off, (const char *)e->name) == 0)
                {
                    bitmap = HIDRD_BIT_SET(bitmap, i, !data);
                    break;
                }
                else if (strcmp(bmd[i]->on, (const char *)e->name) == 0)
                {
                    bitmap = HIDRD_BIT_SET(bitmap, i, data);
                    break;
                }
            }
            snprintf(i_name + 3, sizeof(i_name) - 3, "%u", (unsigned int)i);
            if (strcmp(i_name, (const char *)e->name) == 0)
            {
                bitmap = HIDRD_BIT_SET(bitmap, i, data);
                break;
            }
            i++;
            if (i > 31)
                /* Unkown element name */
                goto cleanup;
        }
    }

    if (pbitmap != NULL)
        *pbitmap = bitmap;

    result = true;

cleanup:

    xmlFree(data_str);

    return result;
}

#define BITMAP_ELEMENT(_name) \
    ELEMENT(_name)                                          \
    {                                                       \
        uint32_t    bitmap;                                 \
                                                            \
        if (!parse_bitmap_element(&bitmap, e, _name##_bmd)) \
            return ELEMENT_RC_ERROR;                        \
                                                            \
        hidrd_item_##_name##_init(xml_src->item, bitmap);   \
                                                            \
        return ELEMENT_RC_ITEM;                             \
    }

BITMAP_ELEMENT(input)
BITMAP_ELEMENT(output)
BITMAP_ELEMENT(feature)

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

ELEMENT(usage_page)
{
    element_rc      result_rc   = ELEMENT_RC_ERROR;
    char           *value_str   = NULL;
    hidrd_usage     value;

    value_str = (char *)xmlNodeGetContent(e);
    if (value_str == NULL)
        goto cleanup;
    value = hidrd_usage_page_from_token_or_hex(value_str);
    if (!hidrd_usage_page_valid(value))
        goto cleanup;

    hidrd_item_usage_page_init(xml_src->item, value);

    result_rc = ELEMENT_RC_ITEM;

cleanup:

    xmlFree(value_str);

    return result_rc;
}

ELEMENT(push)
{
    (void)e;
    hidrd_item_push_init(xml_src->item);
    return ELEMENT_RC_ITEM;
}

ELEMENT(pop)
{
    (void)e;
    hidrd_item_pop_init(xml_src->item);
    return ELEMENT_RC_ITEM;
}

ELEMENT(PUSH)
{
    (void)e;
    hidrd_item_push_init(xml_src->item);
    return ELEMENT_RC_ITEM;
}

ELEMENT_EXIT(PUSH)
{
    (void)e;
    hidrd_item_pop_init(xml_src->item);
    return ELEMENT_RC_ITEM;
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

ELEMENT(collection)
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

ELEMENT(end_collection)
{
    (void)e;
    hidrd_item_end_collection_init(xml_src->item);
    return ELEMENT_RC_ITEM;
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
NUM_ELEMENT(unit_exponent,      s32)
NUM_ELEMENT(report_size,        u32)
NUM_ELEMENT(report_count,       u32)
NUM_ELEMENT(report_id,          u8)

#define USAGE_ELEMENT(_name) \
    ELEMENT(_name)                                              \
    {                                                           \
        element_rc      result_rc   = ELEMENT_RC_ERROR;         \
        char           *value_str   = NULL;                     \
        hidrd_usage     value;                                  \
                                                                \
        value_str = (char *)xmlNodeGetContent(e);               \
        if (value_str == NULL)                                  \
            goto cleanup;                                       \
        if (!hidrd_usage_from_token_or_hex(&value, value_str))  \
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

USAGE_ELEMENT(usage);
USAGE_ELEMENT(usage_minimum);
USAGE_ELEMENT(usage_maximum);

NUM_ELEMENT(designator_index,   u32)
NUM_ELEMENT(designator_minimum, u32)
NUM_ELEMENT(designator_maximum, u32)
NUM_ELEMENT(string_index,       u32)
NUM_ELEMENT(string_minimum,     u32)
NUM_ELEMENT(string_maximum,     u32)

ELEMENT(delimiter)
{
    element_rc  result_rc   = ELEMENT_RC_ERROR;

    PROP_DECL(item_delimiter_set, open);

    PROP_RETR(item_delimiter_set, open,   bool_str);

    hidrd_item_delimiter_init(xml_src->item, open);

    result_rc = ELEMENT_RC_ITEM;

cleanup:

    PROP_CLNP(open);
    return result_rc;
}

ELEMENT(SET)
{
    (void)e;
    hidrd_item_delimiter_init(xml_src->item,
                              HIDRD_ITEM_DELIMITER_SET_OPEN);
    return ELEMENT_RC_ITEM;
}

ELEMENT_EXIT(SET)
{
    (void)e;
    hidrd_item_delimiter_init(xml_src->item,
                              HIDRD_ITEM_DELIMITER_SET_CLOSE);
    return ELEMENT_RC_ITEM;
}

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
    HANDLE(input),
    HANDLE(output),
    HANDLE(feature),
    HANDLE(collection),
    HANDLE(end_collection),
    ENTER(COLLECTION),
    HANDLE(global),
    HANDLE(usage_page),
    HANDLE(logical_minimum),
    HANDLE(logical_maximum),
    HANDLE(physical_minimum),
    HANDLE(physical_maximum),
    HANDLE(unit_exponent),
    IGNORE(unit),
    HANDLE(report_size),
    HANDLE(report_count),
    HANDLE(report_id),
    HANDLE(push),
    HANDLE(pop),
    ENTER(PUSH),
    HANDLE(local),
    HANDLE(usage),
    HANDLE(usage_minimum),
    HANDLE(usage_maximum),
    HANDLE(designator_index),
    HANDLE(designator_minimum),
    HANDLE(designator_maximum),
    HANDLE(string_index),
    HANDLE(string_minimum),
    HANDLE(string_maximum),
    HANDLE(delimiter),
    ENTER(SET),
    HANDLE(long),
    ENTER(descriptor),
#undef ENTER
#undef HANDLE
#undef IGNORE
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



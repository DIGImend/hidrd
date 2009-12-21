/** @file
 * @brief HID report descriptor - short item
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

#ifndef __HIDRD_ITEM_SHORT_H__
#define __HIDRD_ITEM_SHORT_H__

#include <assert.h>
#include "hidrd/item/basic.h"
#include "hidrd/bit.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HIDRD_ITEM_SHORT_MIN_SIZE   1
#define HIDRD_ITEM_SHORT_MAX_SIZE   (1 + 4)

typedef hidrd_item_pfx_type hidrd_item_short_type;
#define HIDRD_ITEM_SHORT_TYPE_MAIN      HIDRD_ITEM_PFX_TYPE_MAIN
#define HIDRD_ITEM_SHORT_TYPE_GLOBAL    HIDRD_ITEM_PFX_TYPE_GLOBAL
#define HIDRD_ITEM_SHORT_TYPE_LOCAL     HIDRD_ITEM_PFX_TYPE_LOCAL

static inline bool
hidrd_item_short_type_valid(hidrd_item_short_type type)
{
    switch (type)
    {
        case HIDRD_ITEM_SHORT_TYPE_MAIN:
        case HIDRD_ITEM_SHORT_TYPE_GLOBAL:
        case HIDRD_ITEM_SHORT_TYPE_LOCAL:
            return true;
        default:
            return false;
    }
}


typedef hidrd_item_pfx_tag hidrd_item_short_tag;

#define HIDRD_ITEM_SHORT_TAG_MIN    HIDRD_ITEM_PFX_TAG_MIN
#define HIDRD_ITEM_SHORT_TAG_MAX    HIDRD_ITEM_PFX_TAG_MAX

static inline bool
hidrd_item_short_tag_valid(hidrd_item_short_tag tag)
{
    return hidrd_item_pfx_tag_valid(tag);
}


typedef hidrd_item_pfx_size hidrd_item_short_data_size;
#define HIDRD_ITEM_SHORT_DATA_SIZE_0B   HIDRD_ITEM_PFX_SIZE_0B
#define HIDRD_ITEM_SHORT_DATA_SIZE_1B   HIDRD_ITEM_PFX_SIZE_1B
#define HIDRD_ITEM_SHORT_DATA_SIZE_2B   HIDRD_ITEM_PFX_SIZE_2B
#define HIDRD_ITEM_SHORT_DATA_SIZE_4B   HIDRD_ITEM_PFX_SIZE_4B


static inline size_t
hidrd_item_short_data_size_to_bytes(hidrd_item_short_data_size size)
{
    return hidrd_item_pfx_size_to_bytes(size);
}


static inline bool
hidrd_item_short_data_size_valid(hidrd_item_short_data_size size)
{
    return hidrd_item_pfx_size_valid(size);
}


static inline bool
hidrd_item_short_valid_class(const hidrd_item *item)
{
    return hidrd_item_basic_valid(item) &&
           hidrd_item_basic_is_short(item);
}


static inline bool
hidrd_item_short_valid_inst(const hidrd_item *item)
{
    assert(hidrd_item_short_valid_class(item));
    return true;
}


static inline bool
hidrd_item_short_valid(const hidrd_item *item)
{
    return hidrd_item_short_valid_class(item) &&
           hidrd_item_short_valid_inst(item);
}


static inline hidrd_item *
hidrd_item_short_validate(hidrd_item *item)
{
    assert(hidrd_item_short_valid(item));
    return item;
}


static inline hidrd_item_short_type
hidrd_item_short_get_type(const hidrd_item *item)
{
    assert(hidrd_item_short_valid(item));
    return hidrd_item_pfx_get_type(hidrd_item_basic_get_pfx(item));
}


static inline hidrd_item_short_tag
hidrd_item_short_get_tag(const hidrd_item *item)
{
    assert(hidrd_item_short_valid(item));
    return hidrd_item_pfx_get_tag(hidrd_item_basic_get_pfx(item));
}


static inline hidrd_item_short_data_size
hidrd_item_short_get_data_size(const hidrd_item *item)
{
    assert(hidrd_item_short_valid(item));
    return hidrd_item_pfx_get_size(hidrd_item_basic_get_pfx(item));
}


static inline hidrd_item *
hidrd_item_short_set_type(hidrd_item *item, hidrd_item_short_type type)
{
    assert(hidrd_item_short_valid(item));
    assert(hidrd_item_short_type_valid(type));
    return hidrd_item_basic_set_pfx(
                item,
                hidrd_item_pfx_set_type(
                    hidrd_item_basic_get_pfx(item),
                    type));
}


static inline hidrd_item *
hidrd_item_short_set_tag(hidrd_item *item, hidrd_item_short_tag tag)
{
    assert(hidrd_item_short_valid(item));
    assert(hidrd_item_short_tag_valid(tag));
    return hidrd_item_basic_set_pfx(
                item,
                hidrd_item_pfx_set_tag(
                    hidrd_item_basic_get_pfx(item),
                    tag));
}


static inline hidrd_item *
hidrd_item_short_set_data_size(hidrd_item *item, hidrd_item_short_data_size size)
{
    assert(hidrd_item_short_valid(item));
    assert(hidrd_item_short_data_size_valid(size));
    return hidrd_item_basic_set_pfx(
                item,
                hidrd_item_pfx_set_size(
                    hidrd_item_basic_get_pfx(item),
                    size));
}


static inline void *
hidrd_item_short_get_data(hidrd_item *item)
{
    assert(hidrd_item_short_valid(item));
    return &item[1];
}


static inline size_t
hidrd_item_short_get_size(const hidrd_item *item)
{
    assert(hidrd_item_short_valid(item));
    return 1 + hidrd_item_short_data_size_to_bytes(
                hidrd_item_short_get_data_size(item));
}


extern uint32_t hidrd_item_short_get_unsigned(const hidrd_item *item);
extern hidrd_item* hidrd_item_short_set_unsigned(hidrd_item *item,
                                                 uint32_t data);

extern int32_t hidrd_item_short_get_signed(const hidrd_item *item);
extern hidrd_item* hidrd_item_short_set_signed(hidrd_item *item,
                                               int32_t data);

static inline bool
hidrd_item_short_get_bit(const hidrd_item *item, uint8_t idx)
{
    assert(hidrd_item_short_valid(item));
    assert(idx <= 31);
    return HIDRD_BIT_GET(hidrd_item_short_get_unsigned(item), idx) != 0;
}


static inline hidrd_item *
hidrd_item_short_set_bit(hidrd_item *item, uint8_t idx, bool val)
{
    assert(hidrd_item_short_valid(item));
    assert(idx <= 31);
    return hidrd_item_short_set_unsigned(
            item,
            HIDRD_BIT_SET(hidrd_item_short_get_unsigned(item), idx, val));
}


static inline hidrd_item *
hidrd_item_short_init(hidrd_item            *item,
                      hidrd_item_short_type  type,
                      hidrd_item_short_tag   tag)
{
    assert(hidrd_item_short_type_valid(type));
    assert(hidrd_item_short_tag_valid(tag));

    return hidrd_item_basic_validate(
        hidrd_item_basic_set_pfx(
            hidrd_item_basic_init(item, HIDRD_ITEM_BASIC_TYPE_SHORT),
            hidrd_item_pfx_set_size(
                hidrd_item_pfx_set_tag(
                    hidrd_item_pfx_set_type(
                        hidrd_item_basic_get_pfx(item),
                        type),
                    tag),
                0)));
}


static inline hidrd_item *
hidrd_item_short_init_signed(hidrd_item            *item,
                             hidrd_item_short_type  type,
                             hidrd_item_short_tag   tag,
                             int32_t                data)
{
    assert(hidrd_item_short_type_valid(type));
    assert(hidrd_item_short_tag_valid(tag));

    return hidrd_item_short_set_signed(
                hidrd_item_short_init(item, type, tag), data);
}


static inline hidrd_item *
hidrd_item_short_init_unsigned(hidrd_item              *item,
                               hidrd_item_short_type    type,
                               hidrd_item_short_tag     tag,
                               uint32_t                 data)
{
    assert(hidrd_item_short_type_valid(type));
    assert(hidrd_item_short_tag_valid(tag));

    return hidrd_item_short_set_unsigned(
                hidrd_item_short_init(item, type, tag), data);
}


#define HIDRD_ITEM_SHORT_GEN_FUNCS(_name, _NAME) \
    static inline bool                                                  \
    hidrd_item_##_name##_valid_class(const hidrd_item *item)            \
    {                                                                   \
        return hidrd_item_short_valid(item) &&                          \
               (hidrd_item_short_get_type(item) ==                      \
                HIDRD_ITEM_SHORT_TYPE_##_NAME);                         \
    }                                                                   \
                                                                        \
    static inline bool                                                  \
    hidrd_item_##_name##_valid_inst(const hidrd_item *item)             \
    {                                                                   \
        assert(hidrd_item_##_name##_valid_class(item));                 \
        return hidrd_item_##_name##_tag_valid(                          \
                    hidrd_item_short_get_tag(item));                    \
    }                                                                   \
                                                                        \
    static inline bool                                                  \
    hidrd_item_##_name##_valid(const hidrd_item *item)                  \
    {                                                                   \
        return hidrd_item_##_name##_valid_class(item) &&                \
               hidrd_item_##_name##_valid_inst(item);                   \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_validate(hidrd_item *item)                     \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
        return item;                                                    \
    }                                                                   \
                                                                        \
    static inline hidrd_item_##_name##_tag                              \
    hidrd_item_##_name##_get_tag(const hidrd_item *item)                \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
        return hidrd_item_short_get_tag(item);                          \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_set_tag(hidrd_item                *item,       \
                                 hidrd_item_##_name##_tag   tag)        \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
        return hidrd_item_short_set_tag(item, tag);                     \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_init(hidrd_item               *item,           \
                              hidrd_item_##_name##_tag  tag)            \
    {                                                                   \
        assert(hidrd_item_##_name##_tag_valid(tag));                    \
                                                                        \
        return hidrd_item_##_name##_validate(                           \
            hidrd_item_short_init(item,                                 \
                                  HIDRD_ITEM_SHORT_TYPE_##_NAME,        \
                                  tag));                                \
    }                                                                   \
                                                                        \
    static inline int32_t                                               \
    hidrd_item_##_name##_get_signed(const hidrd_item *item)             \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
                                                                        \
        return hidrd_item_short_get_signed(item);                       \
    }                                                                   \
                                                                        \
    static inline uint32_t                                              \
    hidrd_item_##_name##_get_unsigned(const hidrd_item *item)           \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
                                                                        \
        return hidrd_item_short_get_unsigned(item);                     \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_set_signed(hidrd_item *item, int32_t data)     \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
                                                                        \
        return hidrd_item_short_set_signed(item, data);                 \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_set_unsigned(hidrd_item *item, uint32_t data)  \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
                                                                        \
        return hidrd_item_short_set_unsigned(item, data);               \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_init_signed(hidrd_item                *item,   \
                                     hidrd_item_##_name##_tag   tag,    \
                                     int32_t                    data)   \
    {                                                                   \
        assert(hidrd_item_##_name##_tag_valid(tag));                    \
                                                                        \
        return hidrd_item_##_name##_validate(                           \
            hidrd_item_##_name##_set_signed(                            \
                hidrd_item_##_name##_init(item, tag), data));           \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_init_unsigned(hidrd_item               *item,  \
                                       hidrd_item_##_name##_tag  tag,   \
                                       uint32_t                  data)  \
    {                                                                   \
        assert(hidrd_item_##_name##_tag_valid(tag));                    \
                                                                        \
        return hidrd_item_##_name##_validate(                           \
            hidrd_item_##_name##_set_unsigned(                          \
                hidrd_item_##_name##_init(item, tag), data));           \
    }


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_SHORT_H__ */

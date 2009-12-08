/** @file
 * @brief HID report descriptor - global item
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

#ifndef __HIDRD_ITEM_GLOBAL_H__
#define __HIDRD_ITEM_GLOBAL_H__

#include "hidrd/item/short.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HIDRD_ITEM_GLOBAL_TAG_MIN HIDRD_ITEM_SHORT_TAG_MIN

typedef enum hidrd_item_global_tag {
    HIDRD_ITEM_GLOBAL_TAG_USAGE_PAGE    = HIDRD_ITEM_GLOBAL_TAG_MIN,
    HIDRD_ITEM_GLOBAL_TAG_LOGICAL_MINIMUM,
    HIDRD_ITEM_GLOBAL_TAG_LOGICAL_MAXIMUM,
    HIDRD_ITEM_GLOBAL_TAG_PHYSICAL_MINIMUM,
    HIDRD_ITEM_GLOBAL_TAG_PHYSICAL_MAXIMUM,
    HIDRD_ITEM_GLOBAL_TAG_UNIT_EXPONENT,
    HIDRD_ITEM_GLOBAL_TAG_UNIT,
    HIDRD_ITEM_GLOBAL_TAG_REPORT_SIZE,
    HIDRD_ITEM_GLOBAL_TAG_REPORT_ID,
    HIDRD_ITEM_GLOBAL_TAG_REPORT_COUNT,
    HIDRD_ITEM_GLOBAL_TAG_PUSH,
    HIDRD_ITEM_GLOBAL_TAG_POP
} hidrd_item_global_tag;

#define HIDRD_ITEM_GLOBAL_TAG_MAX HIDRD_ITEM_SHORT_TAG_MAX

#define HIDRD_ITEM_GLOBAL_TAG_KNOWN_MAX   HIDRD_ITEM_GLOBAL_TAG_POP

#define HIDRD_ITEM_GLOBAL_TAG_RESERVED_MIN \
            (HIDRD_ITEM_GLOBAL_TAG_KNOWN_MAX + 1)
#define HIDRD_ITEM_GLOBAL_TAG_RESERVED_MAX \
            HIDRD_ITEM_GLOBAL_TAG_MAX


static inline bool
hidrd_item_global_tag_valid(hidrd_item_global_tag tag)
{
    hidrd_item_global_tag   min = HIDRD_ITEM_GLOBAL_TAG_MIN;

    return (tag >= min) &&
           (tag <= HIDRD_ITEM_GLOBAL_TAG_MAX);
}

static inline bool
hidrd_item_global_tag_known(hidrd_item_global_tag tag)
{
    assert(hidrd_item_global_tag_valid(tag));
    return (tag <= HIDRD_ITEM_GLOBAL_TAG_KNOWN_MAX);
}

static inline bool
hidrd_item_global_tag_reserved(hidrd_item_global_tag tag)
{
    assert(hidrd_item_global_tag_valid(tag));
    return (tag >= HIDRD_ITEM_GLOBAL_TAG_RESERVED_MIN) &&
           (tag <= HIDRD_ITEM_GLOBAL_TAG_RESERVED_MAX);
}


static inline bool
hidrd_item_global_valid(const hidrd_item *item)
{
    return hidrd_item_short_valid(item) &&
           (hidrd_item_short_get_type(item) ==
            HIDRD_ITEM_SHORT_TYPE_GLOBAL) &&
           hidrd_item_global_tag_valid(hidrd_item_short_get_tag(item));
}

static inline hidrd_item_global_tag
hidrd_item_global_get_tag(const hidrd_item *item)
{
    assert(hidrd_item_global_valid(item));
    return hidrd_item_short_get_tag(item);
}


static inline hidrd_item *
hidrd_item_global_set_tag(hidrd_item *item, hidrd_item_global_tag tag)
{
    assert(hidrd_item_global_valid(item));
    return hidrd_item_short_set_tag(item, tag);
}


#define HIDRD_ITEM_GLOBAL_FUNCS(_name, _NAME, \
                                _sign, _int_type, _ext_type)            \
    static inline bool                                                  \
    hidrd_item_##_name##_valid(const hidrd_item *item)                  \
    {                                                                   \
        return hidrd_item_global_valid(item) &&                         \
               hidrd_item_global_get_tag(item) ==                       \
               HIDRD_ITEM_GLOBAL_TAG_##_NAME &&                         \
               hidrd_item_##_name##_value_valid(                        \
                    (_int_type)hidrd_item_short_get_##_sign(item));     \
    }                                                                   \
                                                                        \
    static inline _ext_type                                             \
    hidrd_item_##_name##_get_value(const hidrd_item *item)              \
    {                                                                   \
        _int_type value;                                                \
        assert(hidrd_item_##_name##_valid(item));                       \
        value = (_int_type)hidrd_item_short_get_##_sign(item);          \
        assert(hidrd_item_##_name##_value_valid(value));                \
        return (_ext_type)value;                                        \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_set_value(hidrd_item *item, _ext_type value)   \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
        assert(hidrd_item_##_name##_value_valid((_int_type)value));     \
        return hidrd_item_short_set_##_sign(item, (_int_type)value);    \
    }


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_GLOBAL_H__ */


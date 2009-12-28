/** @file
 * @brief HID report descriptor - local item
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

#ifndef __HIDRD_ITEM_LOCAL_H__
#define __HIDRD_ITEM_LOCAL_H__

#include "hidrd/item/short.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HIDRD_ITEM_LOCAL_TAG_MIN HIDRD_ITEM_SHORT_TAG_MIN

typedef enum hidrd_item_local_tag {
    HIDRD_ITEM_LOCAL_TAG_USAGE                  = HIDRD_ITEM_LOCAL_TAG_MIN,
    HIDRD_ITEM_LOCAL_TAG_USAGE_MINIMUM,
    HIDRD_ITEM_LOCAL_TAG_USAGE_MAXIMUM,
    HIDRD_ITEM_LOCAL_TAG_DESIGNATOR_INDEX,
    HIDRD_ITEM_LOCAL_TAG_DESIGNATOR_MINIMUM,
    HIDRD_ITEM_LOCAL_TAG_DESIGNATOR_MAXIMUM,
    HIDRD_ITEM_LOCAL_TAG_INVALID,               /**< Specification has
                                                     a hole here */
    HIDRD_ITEM_LOCAL_TAG_STRING_INDEX,
    HIDRD_ITEM_LOCAL_TAG_STRING_MINIMUM,
    HIDRD_ITEM_LOCAL_TAG_STRING_MAXIMUM,
    HIDRD_ITEM_LOCAL_TAG_DELIMITER
} hidrd_item_local_tag;

#define HIDRD_ITEM_LOCAL_TAG_MAX HIDRD_ITEM_SHORT_TAG_MAX

#define HIDRD_ITEM_LOCAL_TAG_KNOWN_MAX   HIDRD_ITEM_LOCAL_TAG_DELIMITER

#define HIDRD_ITEM_LOCAL_TAG_RESERVED_MIN \
            (HIDRD_ITEM_LOCAL_TAG_KNOWN_MAX + 1)
#define HIDRD_ITEM_LOCAL_TAG_RESERVED_MAX \
            HIDRD_ITEM_LOCAL_TAG_MAX

static inline bool
hidrd_item_local_tag_valid(hidrd_item_local_tag tag)
{
    return (tag <= HIDRD_ITEM_LOCAL_TAG_MAX) &&
           (tag != HIDRD_ITEM_LOCAL_TAG_INVALID);
}

static inline bool
hidrd_item_local_tag_known(hidrd_item_local_tag tag)
{
    assert(hidrd_item_local_tag_valid(tag));
    return (tag <= HIDRD_ITEM_LOCAL_TAG_KNOWN_MAX);
}

static inline bool
hidrd_item_local_tag_reserved(hidrd_item_local_tag tag)
{
    assert(hidrd_item_local_tag_valid(tag));
    return (tag >= HIDRD_ITEM_LOCAL_TAG_RESERVED_MIN) &&
           (tag <= HIDRD_ITEM_LOCAL_TAG_RESERVED_MAX);
}


HIDRD_ITEM_SHORT_GEN_FUNCS(local, LOCAL)


#define HIDRD_ITEM_LOCAL_FUNCS(_name, _NAME, _int_type, _ext_type) \
    static inline bool                                                  \
    hidrd_item_##_name##_valid_class(const hidrd_item *item)            \
    {                                                                   \
        return hidrd_item_local_valid_class(item) &&                    \
               hidrd_item_local_get_tag(item) ==                        \
               HIDRD_ITEM_LOCAL_TAG_##_NAME;                            \
    }                                                                   \
                                                                        \
    static inline bool                                                  \
    hidrd_item_##_name##_valid_inst(const hidrd_item *item)             \
    {                                                                   \
        assert(hidrd_item_##_name##_valid_class(item));                 \
        return hidrd_item_local_valid_inst(item) &&                     \
               hidrd_item_##_name##_value_valid(                        \
                    (_int_type)hidrd_item_local_get_unsigned(item));    \
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
    static inline _ext_type                                             \
    hidrd_item_##_name##_get_value(const hidrd_item *item)              \
    {                                                                   \
        _int_type value;                                                \
        assert(hidrd_item_##_name##_valid(item));                       \
        value = (_int_type)hidrd_item_local_get_unsigned(item);         \
        assert(hidrd_item_##_name##_value_valid(value));                \
        return (_ext_type)value;                                        \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_set_value(hidrd_item *item, _ext_type value)   \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
        assert(hidrd_item_##_name##_value_valid((_int_type)value));     \
        return hidrd_item_local_set_unsigned(item, (_int_type)value);   \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_init(hidrd_item *item, _ext_type value)        \
    {                                                                   \
        assert(hidrd_item_##_name##_value_valid((_int_type)value));     \
                                                                        \
        return hidrd_item_##_name##_validate(                           \
            hidrd_item_local_init_unsigned(                             \
                item, HIDRD_ITEM_LOCAL_TAG_##_NAME,                     \
                (_int_type)value));                                     \
    }


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_LOCAL_H__ */

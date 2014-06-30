/** @file
 * @brief HID report descriptor - collection item
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
 */

#ifndef __HIDRD_ITEM_COLLECTION_H__
#define __HIDRD_ITEM_COLLECTION_H__

#include "hidrd/cfg.h"
#include "hidrd/item/main.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HIDRD_ITEM_COLLECTION_TYPE_MIN 0x00

typedef enum hidrd_item_collection_type {
    HIDRD_ITEM_COLLECTION_TYPE_PHYSICAL = HIDRD_ITEM_COLLECTION_TYPE_MIN,
    HIDRD_ITEM_COLLECTION_TYPE_APPLICATION,
    HIDRD_ITEM_COLLECTION_TYPE_LOGICAL,
    HIDRD_ITEM_COLLECTION_TYPE_REPORT,
    HIDRD_ITEM_COLLECTION_TYPE_NAMED_ARRAY,
    HIDRD_ITEM_COLLECTION_TYPE_USAGE_SWITCH,
    HIDRD_ITEM_COLLECTION_TYPE_USAGE_MODIFIER
} hidrd_item_collection_type;

#define HIDRD_ITEM_COLLECTION_TYPE_MAX 0xFF

#define HIDRD_ITEM_COLLECTION_TYPE_KNOWN_MAX \
            HIDRD_ITEM_COLLECTION_TYPE_USAGE_MODIFIER

#define HIDRD_ITEM_COLLECTION_TYPE_RESERVED_MIN \
            (HIDRD_ITEM_COLLECTION_TYPE_KNOWN_MAX + 1)
#define HIDRD_ITEM_COLLECTION_TYPE_RESERVED_MAX 0x7F

#define HIDRD_ITEM_COLLECTION_TYPE_VENDOR_MIN \
            (HIDRD_ITEM_COLLECTION_TYPE_RESERVED_MAX + 1)
#define HIDRD_ITEM_COLLECTION_TYPE_VENDOR_MAX \
            HIDRD_ITEM_COLLECTION_TYPE_MAX

static inline bool
hidrd_item_collection_type_valid(hidrd_item_collection_type type)
{
    return (type <= HIDRD_ITEM_COLLECTION_TYPE_MAX);
}


/* Declare type numeric string conversion functions */
HIDRD_NUM_CONV_DECLS(item_collection_type);

#ifdef HIDRD_WITH_TOKENS
/* Declare type token conversion functions */
HIDRD_TKN_CONV_DECLS(item_collection_type);
#endif /* HIDRD_WITH_TOKENS */

static inline bool
hidrd_item_collection_type_known(hidrd_item_collection_type type)
{
    assert(hidrd_item_collection_type_valid(type));
    return (type <= HIDRD_ITEM_COLLECTION_TYPE_KNOWN_MAX);
}


static inline bool
hidrd_item_collection_type_reserved(hidrd_item_collection_type type)
{
    assert(hidrd_item_collection_type_valid(type));
    return (type >= HIDRD_ITEM_COLLECTION_TYPE_RESERVED_MIN) &&
           (type <= HIDRD_ITEM_COLLECTION_TYPE_RESERVED_MAX);
}


static inline bool
hidrd_item_collection_type_vendor(hidrd_item_collection_type type)
{
    assert(hidrd_item_collection_type_valid(type));
    return (type >= HIDRD_ITEM_COLLECTION_TYPE_VENDOR_MIN) &&
           (type <= HIDRD_ITEM_COLLECTION_TYPE_VENDOR_MAX);
}


static inline bool
hidrd_item_collection_valid_class(const hidrd_item *item)
{
    return hidrd_item_main_valid_class(item) &&
           (hidrd_item_main_get_tag(item) ==
            HIDRD_ITEM_MAIN_TAG_COLLECTION);
}


static inline bool
hidrd_item_collection_valid_inst(const hidrd_item *item)
{
    assert(hidrd_item_collection_valid_class(item));
    return hidrd_item_main_valid_inst(item) &&
           hidrd_item_collection_type_valid(
                hidrd_item_short_get_unsigned(item));
}


static inline bool
hidrd_item_collection_valid(const hidrd_item *item)
{
    return hidrd_item_collection_valid_class(item) &&
           hidrd_item_collection_valid_inst(item);
}


static inline hidrd_item *
hidrd_item_collection_validate(hidrd_item *item)
{
    assert(hidrd_item_collection_valid(item));
    return item;
}


static inline hidrd_item_collection_type
hidrd_item_collection_get_type(const hidrd_item *item)
{
    assert(hidrd_item_collection_valid(item));
    return hidrd_item_short_get_unsigned(item);
}


static inline hidrd_item *
hidrd_item_collection_set_type(hidrd_item *item,
                               hidrd_item_collection_type type)
{
    assert(hidrd_item_collection_valid(item));
    assert(hidrd_item_collection_type_valid(type));
    return hidrd_item_short_set_unsigned(item, type);
}


static inline hidrd_item *
hidrd_item_collection_init(hidrd_item *item,
                           hidrd_item_collection_type type)
{
    assert(hidrd_item_collection_type_valid(type));
    return hidrd_item_collection_validate(
        hidrd_item_main_init_unsigned(item,
                                      HIDRD_ITEM_MAIN_TAG_COLLECTION,
                                      type));
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_COLLECTION_H__ */

/** @file
 * @brief HID report descriptor - long item
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

#ifndef __HIDRD_ITEM_LONG_H__
#define __HIDRD_ITEM_LONG_H__

#include <assert.h>
#include "hidrd/item/basic.h"

#ifdef __cplusplus
extern "C" {
#endif


#define HIDRD_ITEM_LONG_MIN_SIZE    3
#define HIDRD_ITEM_LONG_DATA_SIZE_MAX   UINT8_MAX
#define HIDRD_ITEM_LONG_MAX_SIZE    (HIDRD_ITEM_LONG_MIN_SIZE + \
                                     HIDRD_ITEM_LONG_DATA_SIZE_MAX)


static inline bool
hidrd_item_long_valid_class(const hidrd_item *item)
{
    return hidrd_item_basic_valid_class(item) &&
           hidrd_item_basic_is_long(item);
}


static inline bool
hidrd_item_long_valid_inst(const hidrd_item *item)
{
    assert(hidrd_item_long_valid_class(item));
    return hidrd_item_basic_valid_inst(item);
}


static inline bool
hidrd_item_long_valid(const hidrd_item *item)
{
    return hidrd_item_long_valid_class(item) &&
           hidrd_item_long_valid_inst(item);
}


static inline hidrd_item *
hidrd_item_long_validate(hidrd_item *item)
{
    assert(hidrd_item_long_valid(item));
    return (hidrd_item *)item;
}


typedef uint8_t hidrd_item_long_tag;

static inline bool
hidrd_item_long_tag_valid(hidrd_item_long_tag tag)
{
    (void)tag;
    return true;
}

/** Data size */
typedef uint8_t hidrd_item_long_data_size;

static inline bool
hidrd_item_long_data_size_valid(hidrd_item_long_data_size size)
{
    (void)size;
    return true;
}

static inline hidrd_item_long_data_size
hidrd_item_long_get_data_size(const hidrd_item *item)
{
    assert(hidrd_item_long_valid(item));
    /* We promise not to change the item */
    return ((uint8_t *)hidrd_item_basic_get_data((hidrd_item *)item))[0];
}

static inline hidrd_item *
hidrd_item_long_set_data_size(hidrd_item                   *item,
                              hidrd_item_long_data_size     size)
{
    assert(hidrd_item_long_valid(item));
    assert(hidrd_item_long_data_size_valid(size));
    ((uint8_t *)hidrd_item_basic_get_data(item))[0] = size;
    return item;
}

static inline hidrd_item_long_tag
hidrd_item_long_get_tag(const hidrd_item *item)
{
    assert(hidrd_item_long_valid(item));
    /* We promise not to change the item */
    return ((uint8_t *)hidrd_item_basic_get_data((hidrd_item *)item))[1];
}

static inline hidrd_item *
hidrd_item_long_set_tag(hidrd_item *item, hidrd_item_long_tag tag)
{
    assert(hidrd_item_long_valid(item));
    ((uint8_t *)hidrd_item_basic_get_data(item))[1] = tag;
    return item;
}

/* Declare tag numeric string conversion functions */
HIDRD_NUM_CONV_DECLS(item_long_tag);

static inline void *
hidrd_item_long_get_data(hidrd_item *item)
{
    assert(hidrd_item_long_valid(item));
    return &((uint8_t *)hidrd_item_basic_get_data(item))[2];
}

static inline size_t
hidrd_item_long_get_size(const hidrd_item *item)
{
    assert(hidrd_item_long_valid(item));
    return HIDRD_ITEM_LONG_MIN_SIZE + hidrd_item_long_get_data_size(item);
}

static inline hidrd_item *
hidrd_item_long_init(hidrd_item            *item,
                     hidrd_item_long_tag    tag)
{
    return hidrd_item_long_validate(
            hidrd_item_long_set_tag(
                hidrd_item_long_set_data_size(
                    hidrd_item_basic_init(item,
                                          HIDRD_ITEM_BASIC_TYPE_LONG,
                                          HIDRD_ITEM_BASIC_TAG_LONG,
                                          HIDRD_ITEM_BASIC_DATA_SIZE_LONG),
                    0),
                tag));
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_LONG_H__ */

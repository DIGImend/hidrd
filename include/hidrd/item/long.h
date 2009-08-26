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


static inline bool
hidrd_item_long_valid(const hidrd_item *item)
{
    return hidrd_item_basic_valid(item) &&
           hidrd_item_basic_is_long(item);
}


typedef uint8_t hidrd_item_long_tag;

static inline uint8_t
hidrd_item_long_get_data_size(const hidrd_item *item)
{
    assert(webui_hidrd_item_basic_is_long(item));
    return item[1];
}

static inline hidrd_item *
hidrd_item_long_set_data_size(hidrd_item *item, uint8_t size)
{
    assert(hidrd_item_long_valid(item));
    item[1] = size;
    return item;
}

static inline hidrd_item_long_tag
hidrd_item_long_get_tag(const hidrd_item *item)
{
    assert(hidrd_item_long_valid(item));
    return item[2];
}

static inline hidrd_item *
hidrd_item_long_set_tag(hidrd_item *item, hidrd_item_long_tag tag)
{
    assert(hidrd_item_long_valid(item));
    item[2] = tag;
    return item;
}

static inline void *
hidrd_item_long_get_data(hidrd_item *item)
{
    assert(hidrd_item_long_valid(item));
    return &item[3];
}

#define HIDRD_ITEM_LONG_MAX_SIZE    (3 + UINT8_MAX)

static inline size_t
hidrd_item_long_get_size(hidrd_item *item)
{
    assert(hidrd_item_long_valid(item));
    return 3 + hidrd_item_long_get_data_size(item);
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_LONG_H__ */

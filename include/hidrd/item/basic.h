/** @file
 * @brief HID report descriptor - basic item.
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

#ifndef __HIDRD_ITEM_BASIC_H__
#define __HIDRD_ITEM_BASIC_H__

#include "hidrd/item/type.h"
#include "hidrd/item/pfx.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HIDRD_ITEM_BASIC_MIN_SIZE 1

static inline bool
hidrd_item_basic_valid(const hidrd_item *item)
{
    return hidrd_item_valid(item);
}


static inline hidrd_item_pfx
hidrd_item_basic_get_pfx(const hidrd_item *item)
{
    assert(hidrd_item_basic_valid(item));
    return item[0];
}


static inline hidrd_item *
hidrd_item_basic_set_pfx(hidrd_item *item, hidrd_item_pfx pfx)
{
    assert(hidrd_item_basic_valid(item));
    item[0] = pfx;
    return item;
}


typedef enum hidrd_item_basic_type {
    HIDRD_ITEM_BASIC_TYPE_SHORT,
    HIDRD_ITEM_BASIC_TYPE_LONG
} hidrd_item_basic_type;


static inline hidrd_item_basic_type
hidrd_item_basic_get_type(const hidrd_item *item)
{
    assert(hidrd_item_basic_valid(item));
    /* Check if bTag indicates long item */
    return (hidrd_item_pfx_get_tag(hidrd_item_basic_get_pfx(item)) ==
            HIDRD_ITEM_PFX_TAG_LONG)
            ? HIDRD_ITEM_BASIC_TYPE_LONG
            : HIDRD_ITEM_BASIC_TYPE_SHORT;
}


static inline hidrd_item *
hidrd_item_basic_set_type(hidrd_item *item, hidrd_item_basic_type type)
{
    assert(hidrd_item_basic_valid(item));

    if (type != hidrd_item_basic_get_type(item))
    {
        return hidrd_item_basic_set_pfx(
                    item,
                    (type == HIDRD_ITEM_BASIC_TYPE_SHORT)
                        ? HIDRD_ITEM_PFX_SHORT
                        : HIDRD_ITEM_PFX_LONG);
    }
    else
        return item;
}


static inline bool
hidrd_item_basic_is_short(const hidrd_item *item)
{
    assert(hidrd_item_basic_valid(item));
    return hidrd_item_basic_get_type(item) == HIDRD_ITEM_BASIC_TYPE_SHORT;
}

static inline bool
hidrd_item_basic_is_long(const hidrd_item *item)
{
    assert(hidrd_item_basic_valid(item));
    return hidrd_item_basic_get_type(item) == HIDRD_ITEM_BASIC_TYPE_LONG;
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_BASIC_H__ */

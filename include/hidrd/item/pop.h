/** @file
 * @brief HID report descriptor - pop item
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

#ifndef __HIDRD_ITEM_POP_H__
#define __HIDRD_ITEM_POP_H__

#include "hidrd/item/global.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline bool
hidrd_item_pop_valid_class(const hidrd_item *item)
{
    return hidrd_item_global_valid(item) &&
           hidrd_item_global_get_tag(item) ==
           HIDRD_ITEM_GLOBAL_TAG_POP;
}


static inline bool
hidrd_item_pop_valid_inst(const hidrd_item *item)
{
    assert(hidrd_item_pop_valid_class(item));
    return true;
}


static inline bool
hidrd_item_pop_valid(const hidrd_item *item)
{
    return hidrd_item_pop_valid_class(item) &&
           hidrd_item_pop_valid_inst(item);
}


static inline hidrd_item *
hidrd_item_pop_validate(hidrd_item *item)
{
    assert(hidrd_item_pop_valid(item));
    return item;
}


static inline hidrd_item *
hidrd_item_pop_init(hidrd_item *item)
{
    return hidrd_item_pop_validate(
        hidrd_item_global_init(item,
                               HIDRD_ITEM_GLOBAL_TAG_POP));
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_POP_H__ */


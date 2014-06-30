/** @file
 * @brief HID report descriptor - item (one byte) prefix
 *
 * @author Nikolai Kondrashov <spbnick@gmail.com>
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
 */

#ifndef __HIDRD_ITEM_PFX_H__
#define __HIDRD_ITEM_PFX_H__

#include "hidrd/item/type.h"
#include "hidrd/item/pfx/size.h"
#include "hidrd/item/pfx/type.h"
#include "hidrd/item/pfx/tag.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t hidrd_item_pfx;

/* Default short item prefix */
#define HIDRD_ITEM_PFX_SHORT 0

/* Long item prefix (0xFE) */
#define HIDRD_ITEM_PFX_LONG \
    ((HIDRD_ITEM_PFX_SIZE_LONG << HIDRD_ITEM_PFX_SIZE_SHFT) |   \
     (HIDRD_ITEM_PFX_TYPE_LONG << HIDRD_ITEM_PFX_TYPE_SHFT) |   \
     (HIDRD_ITEM_PFX_TAG_LONG << HIDRD_ITEM_PFX_TAG_SHFT))

static inline hidrd_item_pfx_size
hidrd_item_pfx_get_size(hidrd_item_pfx pfx)
{
    return (pfx >> HIDRD_ITEM_PFX_SIZE_SHFT) & HIDRD_ITEM_PFX_SIZE_MASK;
}


static inline hidrd_item_pfx_type
hidrd_item_pfx_get_type(hidrd_item_pfx pfx)
{
    return (pfx >> HIDRD_ITEM_PFX_TYPE_SHFT) & HIDRD_ITEM_PFX_TYPE_MASK;
}


static inline hidrd_item_pfx_tag
hidrd_item_pfx_get_tag(hidrd_item_pfx pfx)
{
    return (pfx >> HIDRD_ITEM_PFX_TAG_SHFT) & HIDRD_ITEM_PFX_TAG_MASK;
}


static inline hidrd_item_pfx
hidrd_item_pfx_set_size(hidrd_item_pfx pfx, hidrd_item_pfx_size size)
{
    return (pfx & ~(HIDRD_ITEM_PFX_SIZE_MASK << HIDRD_ITEM_PFX_SIZE_SHFT)) |
           ((size & HIDRD_ITEM_PFX_SIZE_MASK) << HIDRD_ITEM_PFX_SIZE_SHFT);
}


static inline hidrd_item_pfx
hidrd_item_pfx_set_type(hidrd_item_pfx pfx, hidrd_item_pfx_type type)
{
    return (pfx & ~(HIDRD_ITEM_PFX_TYPE_MASK << HIDRD_ITEM_PFX_TYPE_SHFT)) |
           ((type & HIDRD_ITEM_PFX_TYPE_MASK) << HIDRD_ITEM_PFX_TYPE_SHFT);
}


static inline hidrd_item_pfx
hidrd_item_pfx_set_tag(hidrd_item_pfx pfx, hidrd_item_pfx_tag tag)
{
    return (pfx & ~(HIDRD_ITEM_PFX_TAG_MASK << HIDRD_ITEM_PFX_TAG_SHFT)) |
           ((tag & HIDRD_ITEM_PFX_TAG_MASK) << HIDRD_ITEM_PFX_TAG_SHFT);
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_PFX_H__ */



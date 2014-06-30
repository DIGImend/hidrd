/** @file
 * @brief HID report descriptor - item prefix tag field.
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

#ifndef __HIDRD_ITEM_PFX_TAG_H__
#define __HIDRD_ITEM_PFX_TAG_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HIDRD_ITEM_PFX_TAG_MASK  0x0F
#define HIDRD_ITEM_PFX_TAG_SHFT  4

typedef uint8_t hidrd_item_pfx_tag;

#define HIDRD_ITEM_PFX_TAG_MIN  0x00
#define HIDRD_ITEM_PFX_TAG_MAX  HIDRD_ITEM_PFX_TAG_MASK

static inline bool
hidrd_item_pfx_tag_valid(hidrd_item_pfx_tag tag)
{
    return (tag & ~HIDRD_ITEM_PFX_TAG_MASK) == 0;
}

#define HIDRD_ITEM_PFX_TAG_LONG     0xF

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_PFX_TAG_H__ */



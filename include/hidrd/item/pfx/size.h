/** @file
 * @brief HID report descriptor - item prefix size field.
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

#ifndef __HIDRD_ITEM_PFX_SIZE_H__
#define __HIDRD_ITEM_PFX_SIZE_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HIDRD_ITEM_PFX_SIZE_MASK 0x03
#define HIDRD_ITEM_PFX_SIZE_SHFT 0

typedef enum hidrd_item_pfx_size {
    HIDRD_ITEM_PFX_SIZE_0B  = 0,
    HIDRD_ITEM_PFX_SIZE_1B  = 1,
    HIDRD_ITEM_PFX_SIZE_2B  = 2,
    HIDRD_ITEM_PFX_SIZE_4B  = 3,
} hidrd_item_pfx_size;

static inline bool
hidrd_item_pfx_size_valid(hidrd_item_pfx_size size)
{
    return (size & ~HIDRD_ITEM_PFX_SIZE_MASK) == 0;
}

typedef size_t hidrd_item_pfx_bytes;

extern hidrd_item_pfx_bytes hidrd_item_pfx_size_to_bytes(
                                    hidrd_item_pfx_size size);

static inline bool
hidrd_item_pfx_bytes_valid(hidrd_item_pfx_bytes bytes)
{
    return (bytes <= 2) || (bytes == 4);
}

extern hidrd_item_pfx_size hidrd_item_pfx_size_from_bytes(
                                    hidrd_item_pfx_bytes bytes);

#define HIDRD_ITEM_PFX_SIZE_LONG    HIDRD_ITEM_PFX_SIZE_2B

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_PFX_SIZE_H__ */




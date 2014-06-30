/** @file
 * @brief HID report descriptor - item prefix type field.
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

#ifndef __HIDRD_ITEM_PFX_TYPE_H__
#define __HIDRD_ITEM_PFX_TYPE_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HIDRD_ITEM_PFX_TYPE_MASK 0x03
#define HIDRD_ITEM_PFX_TYPE_SHFT 2

typedef enum hidrd_item_pfx_type {
    HIDRD_ITEM_PFX_TYPE_MAIN        = 0,
    HIDRD_ITEM_PFX_TYPE_GLOBAL      = 1,
    HIDRD_ITEM_PFX_TYPE_LOCAL       = 2,
    HIDRD_ITEM_PFX_TYPE_RESERVED    = 3,
} hidrd_item_pfx_type;

static inline bool
hidrd_item_pfx_type_valid(hidrd_item_pfx_type type)
{
    return (type & ~HIDRD_ITEM_PFX_TYPE_MASK) == 0;
}

#define HIDRD_ITEM_PFX_TYPE_LONG    HIDRD_ITEM_PFX_TYPE_RESERVED

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_PFX_TYPE_H__ */




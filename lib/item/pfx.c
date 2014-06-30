/** @file
 * @brief HID report descriptor - item prefix.
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

#include <assert.h>
#include "hidrd/item/pfx.h"

hidrd_item_pfx_bytes
hidrd_item_pfx_size_to_bytes(hidrd_item_pfx_size size)
{
    assert(hidrd_item_pfx_size_valid(size));

    return (size == HIDRD_ITEM_PFX_SIZE_4B) ? 4 : size;
}

hidrd_item_pfx_size
hidrd_item_pfx_size_from_bytes(hidrd_item_pfx_bytes bytes)
{
    assert(hidrd_item_pfx_bytes_valid(bytes));
    return (bytes == 4) ? HIDRD_ITEM_PFX_SIZE_4B : bytes;
}


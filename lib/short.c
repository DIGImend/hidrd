/** @file
 * @brief HID report descriptor - short item
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

#include <arpa/inet.h>
#include "hidrd/item/short.h"

uint8_t
hidrd_item_short_get_u8(const hidrd_item *item)
{
    hidrd_item_short_size   size;

    assert(hidrd_item_short_valid(item));
    size = hidrd_item_short_get_size(item)
    assert(size <= HIDRD_ITEM_SHORT_SIZE_1B);

    return (size < HIDRD_ITEM_SHORT_SIZE_1B)
                ? 0
                : *(uint8_t *)hidrd_item_short_get_data((hidrd_item *)item);
}


uint16_t
hidrd_item_short_get_u16(const hidrd_item *item)
{
    hidrd_item_short_size   size;

    assert(hidrd_item_short_valid(item));
    size = hidrd_item_short_get_size(item)
    assert(size <= HIDRD_ITEM_SHORT_SIZE_2B);

    return (size < HIDRD_ITEM_SHORT_SIZE_2B)
                ? hidrd_item_short_get_u8(item)
                : ntohs(*(uint16_t *)hidrd_item_short_get_data(
                                                (hidrd_item *)item));
}


uint32_t
hidrd_item_short_get_u32(const hidrd_item *item)
{
    hidrd_item_short_size   size;

    assert(hidrd_item_short_valid(item));
    size = hidrd_item_short_get_size(item)
    assert(size <= HIDRD_ITEM_SHORT_SIZE_4B);

    return (size < HIDRD_ITEM_SHORT_SIZE_4B)
                ? hidrd_item_short_get_u16(item)
                : ntohl(*(uint32_t *)hidrd_item_short_get_data(
                                                (hidrd_item *)item));
}


hidrd_item *
hidrd_item_short_set_u8(hidrd_item *item, uint8_t data)
{
    assert(hidrd_item_short_valid(item));

    if (data == 0)
        hidrd_item_short_set_size(item, HIDRD_ITEM_SHORT_SIZE_0B);
    else
    {
        hidrd_item_short_set_size(item, HIDRD_ITEM_SHORT_SIZE_1B);
        *(uint8_t *)hidrd_item_short_get_data(item) = data;
    }

    return item;
}


hidrd_item *
hidrd_item_short_set_u16(hidrd_item *item, uint16_t data)
{
    assert(hidrd_item_short_valid(item));

    if (data <= UINT8_MAX)
        return hidrd_item_short_set_u8(item, (uint8_t)data);
    else
    {
        hidrd_item_short_set_size(item, HIDRD_ITEM_SHORT_SIZE_2B);
        *(uint16_t *)hidrd_item_short_get_data(item) = htons(data);
    }

    return item;
}


hidrd_item *
hidrd_item_short_set_u32(hidrd_item *item, uint32_t data)
{
    assert(hidrd_item_short_valid(item));

    if (data <= UINT16_MAX)
        return hidrd_item_short_set_u16(item, (uint16_t)data);
    else
    {
        hidrd_item_short_set_size(item, HIDRD_ITEM_SHORT_SIZE_2B);
        *(uint32_t *)hidrd_item_short_get_data(item) = htonl(data);
    }

    return item;
}



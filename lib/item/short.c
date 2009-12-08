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

#include "hidrd/item/short.h"


static uint32_t
get_unsigned(hidrd_item_short_data_size size, const uint8_t *pin)
{
    uint32_t    out;

    assert(hidrd_item_short_data_size_valid(size));

    if (size == HIDRD_ITEM_SHORT_DATA_SIZE_0B)
        return 0;

    out = *pin;

    if (size == HIDRD_ITEM_SHORT_DATA_SIZE_1B)
        return out;

    out |= *++pin << 8;

    if (size == HIDRD_ITEM_SHORT_DATA_SIZE_2B)
        return out;

    out |= *++pin << 16;
    out |= *++pin << 24;

    return out;
}


static int32_t
get_signed(hidrd_item_short_data_size size, const uint8_t *pin)
{
    uint32_t    out;

    assert(hidrd_item_short_data_size_valid(size));

    if (size == HIDRD_ITEM_SHORT_DATA_SIZE_0B)
        return 0;

    out = *pin;

    if (size == HIDRD_ITEM_SHORT_DATA_SIZE_1B)
        return (int8_t)out;

    out |= *++pin << 8;

    if (size == HIDRD_ITEM_SHORT_DATA_SIZE_2B)
        return (int16_t)out;

    out |= *++pin << 16;
    out |= *++pin << 24;

    return (int32_t)out;
}


uint32_t
hidrd_item_short_get_unsigned(const hidrd_item *item)
{
    assert(hidrd_item_short_valid(item));

    return get_unsigned(hidrd_item_short_get_data_size(item),
                        /* We promise not to change the item */
                        (const uint8_t *)
                            hidrd_item_short_get_data((hidrd_item *)item));
}


int32_t
hidrd_item_short_get_signed(const hidrd_item *item)
{
    assert(hidrd_item_short_valid(item));

    return get_signed(hidrd_item_short_get_data_size(item),
                      /* We promise not to change the item */
                      (const uint8_t *)
                        hidrd_item_short_get_data((hidrd_item *)item));
}


static hidrd_item_short_data_size
set(uint8_t *pout, uint32_t in)
{
    if (in == 0)
        return HIDRD_ITEM_SHORT_DATA_SIZE_0B;

    *pout = in & 0xFF;
    in >>= 8;

    if (in == 0)
        return HIDRD_ITEM_SHORT_DATA_SIZE_1B;

    *++pout = in & 0xFF;
    in >>= 8;

    if (in == 0)
        return HIDRD_ITEM_SHORT_DATA_SIZE_2B;

    *++pout = in & 0xFF;
    in >>= 8;
    *++pout = in & 0xFF;

    return HIDRD_ITEM_SHORT_DATA_SIZE_4B;
}


hidrd_item *
hidrd_item_short_set_unsigned(hidrd_item *item, uint32_t data)
{
    assert(hidrd_item_short_valid(item));

    return hidrd_item_short_set_data_size(
            item,
            set((uint8_t *)hidrd_item_short_get_data(item),
                data));
}


hidrd_item *
hidrd_item_short_set_signed(hidrd_item *item, int32_t data)
{
    assert(hidrd_item_short_valid(item));

    return hidrd_item_short_set_data_size(
            item,
            set((uint8_t *)hidrd_item_short_get_data(item),
                (uint32_t)data));
}



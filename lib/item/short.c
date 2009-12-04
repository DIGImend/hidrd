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


uint32_t
hidrd_item_short_get_unsigned(const hidrd_item *item)
{
    hidrd_item_short_data_size   size;
    const void                  *data;

    assert(hidrd_item_short_valid(item));

    size = hidrd_item_short_get_data_size(item);
    assert(hidrd_item_short_data_size_valid(size));
    /* We promise not to change the item */
    data = hidrd_item_short_get_data((hidrd_item *)item);

    switch (size)
    {
        case HIDRD_ITEM_SHORT_DATA_SIZE_0B:
            return 0;
        case HIDRD_ITEM_SHORT_DATA_SIZE_1B:
            return *(const uint8_t *)data;
        case HIDRD_ITEM_SHORT_DATA_SIZE_2B:
            return ntohs(*(const uint16_t *)data);
        case HIDRD_ITEM_SHORT_DATA_SIZE_4B:
            return ntohl(*(const uint32_t *)data);
        default:
            assert(!"unknown short item data size");
            return 0;
    }
}


int32_t
hidrd_item_short_get_signed(const hidrd_item *item)
{
    hidrd_item_short_data_size   size;
    const void             *data;

    assert(hidrd_item_short_valid(item));

    size = hidrd_item_short_get_data_size(item);
    assert(hidrd_item_short_data_size_valid(size));
    /* We promise not to change the item */
    data = hidrd_item_short_get_data((hidrd_item *)item);

    switch (size)
    {
        case HIDRD_ITEM_SHORT_DATA_SIZE_0B:
            return 0;
        case HIDRD_ITEM_SHORT_DATA_SIZE_1B:
            return *(const int8_t *)data;
        case HIDRD_ITEM_SHORT_DATA_SIZE_2B:
            return (int16_t)ntohs(*(const uint16_t *)data);
        case HIDRD_ITEM_SHORT_DATA_SIZE_4B:
            return (int32_t)ntohl(*(const uint32_t *)data);
        default:
            assert(!"unknown short item data size");
            return 0;
    }
}


hidrd_item *
hidrd_item_short_set_unsigned(hidrd_item *item, uint32_t data)
{
    assert(hidrd_item_short_valid(item));

    if (data == 0)
        hidrd_item_short_set_data_size(item, HIDRD_ITEM_SHORT_DATA_SIZE_0B);
    else if (data <= UINT8_MAX)
    {
        hidrd_item_short_set_data_size(item, HIDRD_ITEM_SHORT_DATA_SIZE_1B);
        *(uint8_t *)hidrd_item_short_get_data(item) = data;
    }
    else if (data <= UINT16_MAX)
    {
        hidrd_item_short_set_data_size(item, HIDRD_ITEM_SHORT_DATA_SIZE_2B);
        *(uint16_t *)hidrd_item_short_get_data(item) = htons(data);
    }
    else
    {
        hidrd_item_short_set_data_size(item, HIDRD_ITEM_SHORT_DATA_SIZE_4B);
        *(uint32_t *)hidrd_item_short_get_data(item) = htonl(data);
    }

    return item;
}


hidrd_item *
hidrd_item_short_set_signed(hidrd_item *item, int32_t data)
{
    assert(hidrd_item_short_valid(item));

    if (data == 0)
        hidrd_item_short_set_data_size(item, HIDRD_ITEM_SHORT_DATA_SIZE_0B);
    else if (data >= INT8_MIN && data <= INT8_MAX)
    {
        hidrd_item_short_set_data_size(item, HIDRD_ITEM_SHORT_DATA_SIZE_1B);
        *(int8_t *)hidrd_item_short_get_data(item) = data;
    }
    else if (data >= INT16_MIN && data <= INT16_MAX)
    {
        hidrd_item_short_set_data_size(item, HIDRD_ITEM_SHORT_DATA_SIZE_2B);
        *(uint16_t *)hidrd_item_short_get_data(item) = htons(data);
    }
    else
    {
        hidrd_item_short_set_data_size(item, HIDRD_ITEM_SHORT_DATA_SIZE_4B);
        *(uint32_t *)hidrd_item_short_get_data(item) = htonl(data);
    }

    return item;
}



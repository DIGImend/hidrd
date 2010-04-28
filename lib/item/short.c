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

#include <string.h>
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
set_unsigned(uint8_t *pout, uint32_t in)
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
            set_unsigned((uint8_t *)hidrd_item_short_get_data(item),
                         data));
}


hidrd_item *
hidrd_item_short_set_signed(hidrd_item *item, int32_t data)
{
    uint8_t    *pdata   = (uint8_t *)hidrd_item_short_get_data(item);

    assert(hidrd_item_short_valid(item));

    if (data == 0)
        return hidrd_item_short_set_data_size(
                    item, HIDRD_ITEM_SHORT_DATA_SIZE_0B);
    else if (data >= INT8_MIN && data <= INT8_MAX)
    {
        pdata[0] = (int8_t)data;

        return hidrd_item_short_set_data_size(
                    item, HIDRD_ITEM_SHORT_DATA_SIZE_1B);
    }
    else if (data >= INT16_MIN && data <= INT16_MAX)
    {
        uint16_t    data16 = (int16_t)data;

        pdata[0] = data16 & 0xFF;
        pdata[1] = data16 >> 8;

        return hidrd_item_short_set_data_size(
                    item, HIDRD_ITEM_SHORT_DATA_SIZE_2B);
    }
    else
    {
        uint32_t    data32 = data;

        pdata[0] = data32 & 0xFF;
        pdata[1] = (data32 >> 8) & 0xFF;
        pdata[2] = (data32 >> 16) & 0xFF;
        pdata[3] = data32 >> 24;

        return hidrd_item_short_set_data_size(
                    item, HIDRD_ITEM_SHORT_DATA_SIZE_4B);
    }
}


/* Define numeric string conversion functions for data size in bytes */
HIDRD_NUM_CONV_DEFS(item_short_data_bytes, u32);

/* Define type numeric string conversion functions */
HIDRD_NUM_CONV_DEFS(item_short_type, u32);

/* Define tag numeric string conversion functions */
HIDRD_NUM_CONV_DEFS(item_short_tag, u32);

#ifdef HIDRD_WITH_TOKENS
static const hidrd_tkn_link item_short_type_map[] = {
#define MAP(_NAME, _name)   \
    {.str= #_name, .num = HIDRD_ITEM_SHORT_TYPE_##_NAME}
    MAP(MAIN,       main),
    MAP(GLOBAL,     global),
    MAP(LOCAL,      local),
#undef MAP
    {.str = NULL}
};

/* Define type token conversion functions */
HIDRD_TKN_CONV_DEFS(item_short_type)

#endif /* HIDRD_WITH_TOKENS */



/** @file
 * @brief HID report descriptor item - universal methods.
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

#include "hidrd/item.h"


bool
hidrd_item_valid(const hidrd_item *item)
{
    assert(hidrd_item_basic_valid(item));

    switch (hidrd_item_basic_type(item))
    {
        case HIDRD_ITEM_BASIC_TYPE_LONG:
            return hidrd_item_long_valid(item);
        case HIDRD_ITEM_BASIC_TYPE_SHORT:
            switch (hidrd_item_short_get_type(item))
            {
                case HIDRD_ITEM_SHORT_TYPE_MAIN:
                    switch (hidrd_item_main_get_tag(item))
                    {
                        case HIDRD_ITEM_MAIN_TAG_INPUT:
                            hidrd_item_input_valid(item);
                        case HIDRD_ITEM_MAIN_TAG_OUTPUT:
                            hidrd_item_output_valid(item);
                        case HIDRD_ITEM_MAIN_TAG_COLLECTION:
                            hidrd_item_collection_valid(item);
                        case HIDRD_ITEM_MAIN_TAG_FEATURE:
                            hidrd_item_feature_valid(item);
                        case HIDRD_ITEM_MAIN_TAG_END_COLLECTION:
                            hidrd_item_end_collection_valid(item);
                    }
            }
    }
}



size_t 
hidrd_item_get_size(const hidrd_item *item)
{
    return hidrd_item_basic_is_short(item)
            ? hidrd_item_short_get_size(item)
            : hidrd_item_long_get_size(item);
}



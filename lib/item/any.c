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


#define MAP_MAIN(_NAME, _name) \
    case HIDRD_ITEM_MAIN_TAG_##_NAME:               \
        return hidrd_item_##_name##_valid(item);

#define MAP_GLOBAL(_NAME, _name) \
    case HIDRD_ITEM_GLOBAL_TAG_##_NAME:             \
        return hidrd_item_##_name##_valid(item);

#define MAP_LOCAL(_NAME, _name) \
    case HIDRD_ITEM_LOCAL_TAG_##_NAME:              \
        return hidrd_item_##_name##_valid(item);


bool
hidrd_item_size_valid(const hidrd_item *item, size_t size)
{
    assert(hidrd_item_basic_valid(item));

    if (size == 0)
        return false;

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
                        MAP_MAIN(INPUT, input)
                        MAP_MAIN(OUTPUT, output)
                        MAP_MAIN(COLLECTION, collection)
                        MAP_MAIN(FEATURE, feature)
                        MAP_MAIN(END_COLLECTION, end_collection)
                    }
                    break;
                case HIDRD_ITEM_SHORT_TYPE_GLOBAL:
                    switch (hidrd_item_global_get_tag(item))
                    {
                        MAP_GLOBAL(USAGE_PAGE, usage_page)
                        MAP_GLOBAL(LOGICAL_MINIMUM, logical_minimum)
                        MAP_GLOBAL(LOGICAL_MAXIMUM, logical_maximum)
                        MAP_GLOBAL(PHYSICAL_MINIMUM, physical_minimum)
                        MAP_GLOBAL(PHYSICAL_MAXIMUM, physical_maximum)
                        MAP_GLOBAL(UNIT_EXPONENT, unit_exponent)
                        MAP_GLOBAL(UNIT, unit)
                        MAP_GLOBAL(REPORT_SIZE, report_size)
                        MAP_GLOBAL(REPORT_ID, report_id)
                        MAP_GLOBAL(REPORT_COUNT, report_count)
                        MAP_GLOBAL(PUSH, push)
                        MAP_GLOBAL(POP, pop)
                    }
                    break;
                case HIDRD_ITEM_SHORT_TYPE_LOCAL:
                    switch (hidrd_item_local_get_tag(item))
                    {
                        MAP_LOCAL(USAGE, usage)
                        MAP_LOCAL(USAGE_MINIMUM, usage_minimum)
                        MAP_LOCAL(USAGE_MAXIMUM, usage_maximum)
                        MAP_LOCAL(DESIGNATOR_INDEX, designator_index)
                        MAP_LOCAL(DESIGNATOR_MINIMUM, designator_minimum)
                        MAP_LOCAL(DESIGNATOR_MAXIMUM, designator_maximum)
                        MAP_LOCAL(INVALID, invalid)
                        MAP_LOCAL(STRING_INDEX, string_index)
                        MAP_LOCAL(STRING_MINIMUM, string_minimum)
                        MAP_LOCAL(STRING_MAXIMUM, string_maximum)
                        MAP_LOCAL(DELIMITER, delimiter)
                    }
                    break;
            }
            break;
    }
    return false;
}


#undef MAP_LOCAL
#undef MAP_GLOBAL
#undef MAP_MAIN


bool
hidrd_item_valid(const hidrd_item *item)
{
    return hidrd_item_size_valid(item, SIZE_MAX);
}


size_t 
hidrd_item_get_size(const hidrd_item *item)
{
    return hidrd_item_basic_is_short(item)
            ? hidrd_item_short_get_size(item)
            : hidrd_item_long_get_size(item);
}



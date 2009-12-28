/** @file
 * @brief HID report descriptor - local item
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
#include "hidrd/item/local.h"

#ifdef HIDRD_WITH_TOKENS
char *
hidrd_item_local_tag_to_token(hidrd_item_local_tag tag)
{
    assert(hidrd_item_local_tag_valid(tag));

    switch (tag)
    {
#define MAP(_NAME, _name) \
    case HIDRD_ITEM_LOCAL_TAG_##_NAME:   \
        return strdup(#_name)

        MAP(USAGE, usage);
        MAP(USAGE_MINIMUM, usage_minimum);
        MAP(USAGE_MAXIMUM, usage_maximum);
        MAP(DESIGNATOR_INDEX, designator_index);
        MAP(DESIGNATOR_MINIMUM, designator_minimum);
        MAP(DESIGNATOR_MAXIMUM, designator_maximum);
        MAP(INVALID, invalid);
        MAP(STRING_INDEX, string_index);
        MAP(STRING_MINIMUM, string_minimum);
        MAP(STRING_MAXIMUM, string_maximum);
        MAP(DELIMITER, delimiter);

#undef MAP

    default:
        return hidrd_item_local_tag_valid(tag)
                ? hidrd_item_basic_tag_to_token(tag)
                : NULL;
    }
}
#endif /* HIDRD_WITH_TOKENS */

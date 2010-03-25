/** @file
 * @brief HID report descriptor - specification example sink - item output
 *
 * Copyright (C) 2010 Nikolai Kondrashov
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

#include "item.h"

static bool
spec_snk_item_main(hidrd_spec_snk_inst *spec_snk,
                   const hidrd_item    *item)
{
    assert(hidrd_item_main_valid(item));

    switch (hidrd_item_short_get_type(item))
    {
        case HIDRD_ITEM_MAIN_TAG_COLLECTION:
            return text_itemf(spec_snk,
                              HIDRD_FMT_TYPE_STRDUP, "Collection",
                              HIDRD_FMT_TYPE_NULL, NULL,
                              HIDRD_FMT_TYPE_STROWN, NULL);
        default:
            /* Unknown short item type */
            return false;
    }
}


static bool
spec_snk_item_short(hidrd_spec_snk_inst    *spec_snk,
                    const hidrd_item       *item)
{
    assert(hidrd_item_short_valid(item));

    switch (hidrd_item_short_get_type(item))
    {
        case HIDRD_ITEM_SHORT_TYPE_MAIN:
            return spec_snk_item_main(spec_snk, item);
#if 0
        case HIDRD_ITEM_SHORT_TYPE_GLOBAL:
            return spec_snk_item_global(spec_snk, item);
        case HIDRD_ITEM_SHORT_TYPE_LOCAL:
            return spec_snk_item_local(spec_snk, item);
#endif
        default:
            /* Unknown short item type */
            return false;
    }
}


bool
spec_snk_item_basic(hidrd_spec_snk_inst    *spec_sink,
                    const hidrd_item       *item)
{
    switch (hidrd_item_basic_get_format(item))
    {
        case HIDRD_ITEM_BASIC_FORMAT_SHORT:
            return spec_snk_item_short(spec_snk, item);
        default:
            /* Unknown basic format */
            return false;
    }
}



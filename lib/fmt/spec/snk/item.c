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

#include "hidrd/item.h"
#include "item_ent.h"
#include "item.h"

#define ITEM(_name_tkn, _args...) \
    spec_snk_item_entf(spec_snk, #_name_tkn,                \
                       ##_args, SPEC_SNK_ITEM_ENT_NT_NONE)

#define VALUE(_fmt, _args...) \
    SPEC_SNK_ITEM_ENT_NT_VALUE, HIDRD_FMT_TYPE_##_fmt, ##_args

#define COMMENT(_fmt, _args...) \
    SPEC_SNK_ITEM_ENT_NT_COMMENT, HIDRD_FMT_TYPE_##_fmt, ##_args

static bool
spec_snk_item_main(hidrd_spec_snk_inst *spec_snk,
                   const hidrd_item    *item)
{
    assert(hidrd_item_main_valid(item));

    switch (hidrd_item_main_get_tag(item))
    {
        case HIDRD_ITEM_MAIN_TAG_COLLECTION:
            if (!ITEM(collection,
                      VALUE(STROWN,
                           hidrd_tkn_hmnz(
                            hidrd_item_collection_type_to_token_or_dec(
                                hidrd_item_collection_get_type(item)),
                            HIDRD_TKN_HMNZ_CAP_WF))))
                return false;

            spec_snk->depth++;
            return true;

        case HIDRD_ITEM_MAIN_TAG_END_COLLECTION:
            spec_snk->depth--;
            return ITEM(end_collection);

        default:
            /* TODO add contents value */
            return ITEM(main);
    }
}


static bool
spec_snk_item_short(hidrd_spec_snk_inst    *spec_snk,
                    const hidrd_item       *item)
{
    hidrd_item_short_type   type;

    assert(hidrd_item_short_valid(item));

    switch (type = hidrd_item_short_get_type(item))
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
            /* TODO add contents value */
            return ITEM(short);
    }
}


static bool
spec_snk_item_long(hidrd_spec_snk_inst *spec_snk,
                   const hidrd_item    *item)
{
    assert(hidrd_item_long_valid(item));
    (void)item;

    /* TODO add contents value */
    return ITEM(long);
                
}


bool
spec_snk_item_basic(hidrd_spec_snk_inst    *spec_snk,
                    const hidrd_item       *item)
{
    switch (hidrd_item_basic_get_format(item))
    {
        case HIDRD_ITEM_BASIC_FORMAT_SHORT:
            return spec_snk_item_short(spec_snk, item);
        case HIDRD_ITEM_BASIC_FORMAT_LONG:
            return spec_snk_item_long(spec_snk, item);
        default:
            /* Unknown basic format */
            return false;
    }
}



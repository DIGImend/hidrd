/** @file
 * @brief HID report descriptor - main item
 *
 * Copyright (C) 2009-2010 Nikolai Kondrashov
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
#include "hidrd/item/main.h"

/* Define tag decimal string conversion functions */
HIDRD_DEC_CONV_DEFS(item_main_tag, tag, uint32_t, u32);

#ifdef HIDRD_WITH_TOKENS
static const hidrd_tkn_link tag_map[] = {
#define MAP(_NAME, _name)   \
    {.str= #_name, .num = HIDRD_ITEM_MAIN_TAG_##_NAME}
    MAP(INPUT,          input),
    MAP(OUTPUT,         output),
    MAP(COLLECTION,     collection),
    MAP(FEATURE,        feature),
    MAP(END_COLLECTION, end_collection),
#undef MAP
    {.str = NULL}
};

/* Define tag token conversion functions */
HIDRD_TKN_CONV_DEFS(item_main_tag, tag, dec)

#endif /* HIDRD_WITH_TOKENS */

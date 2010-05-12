/** @file
 * @brief HID report descriptor - basic item.
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
#include <stdio.h>
#include "hidrd/cfg.h"
#include "hidrd/util/str.h"
#include "hidrd/item/basic.h"

/* Define numeric string conversion functions for data size in bytes */
HIDRD_NUM_CONV_DEFS(item_basic_data_bytes, u32);

/* Define type numeric string conversion functions */
HIDRD_NUM_CONV_DEFS(item_basic_type, u32);

/* Define tag numeric string conversion functions */
HIDRD_NUM_CONV_DEFS(item_basic_tag, u32);

#ifdef HIDRD_WITH_TOKENS
/* Define type token conversion functions */
#define MAP(_N, _n) HIDRD_TKN_LINK(HIDRD_ITEM_BASIC_TYPE_##_N, _n)
HIDRD_TKN_CONV_DEFS(item_basic_type,
                    MAP(MAIN,       main),
                    MAP(GLOBAL,     global),
                    MAP(LOCAL,      local),
                    MAP(RESERVED,   reserved))
#undef MAP
#endif /* HIDRD_WITH_TOKENS */

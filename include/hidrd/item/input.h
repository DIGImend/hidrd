/** @file
 * @brief HID report descriptor - input item
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

#ifndef __HIDRD_ITEM_INPUT_H__
#define __HIDRD_ITEM_INPUT_H__

#include "hidrd/item/main.h"

#ifdef __cplusplus
extern "C" {
#endif

HIDRD_ITEM_MAIN_GEN_FUNCS(input, INPUT)
HIDRD_ITEM_MAIN_BIT_FUNCS(input, INPUT)
HIDRD_ITEM_MAIN_BIT_ACC(input, 0, data, constant)
HIDRD_ITEM_MAIN_BIT_ACC(input, 1, array, variable)
HIDRD_ITEM_MAIN_BIT_ACC(input, 2, absolute, relative)
HIDRD_ITEM_MAIN_BIT_ACC(input, 3, no_wrap, wrap)
HIDRD_ITEM_MAIN_BIT_ACC(input, 4, linear, non_linear)
HIDRD_ITEM_MAIN_BIT_ACC(input, 5, preferred_state, no_preferred)
HIDRD_ITEM_MAIN_BIT_ACC(input, 6, no_null_position, null_state)
HIDRD_ITEM_MAIN_BIT_ACC(input, 8, bit_field, buffered_bytes)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_INPUT_H__ */


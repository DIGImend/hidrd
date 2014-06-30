/** @file
 * @brief HID report descriptor - utilities - decimal conversions
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
 */

#ifndef __HIDRD_UTIL_DEC_H__
#define __HIDRD_UTIL_DEC_H__

#include <stddef.h>
#include <assert.h>
#include "hidrd/util/num.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert a specified integer number type to a decimal string.
 *
 * @param _t    Short integer number type name (u32/s32/u16/s16/u8/s8).
 * @param _n    Number.
 *
 * @return Dynamically allocated string, or NULL, if failed to allocate
 *         memory.
 */
#define HIDRD_DEC_TO_STR(_t, _n) \
    HIDRD_NUM_TO_STR(_t, _n, NONE, DEC)

/**
 * Convert a decimal string to a specified integer type.
 *
 * @param _t    Short integer number type name (u32/s32/u16/s16/u8/s8).
 * @param _pn   Location for resulting number.
 * @param _s    String to parse.
 *
 * @return True if the string was valid and parsed successfully, false
 *         otherwise.
 */
#define HIDRD_DEC_FROM_STR(_t, _pn, _s) \
    HIDRD_NUM_FROM_STR(_t, _pn, _s, NONE, DEC)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_DEC_H__ */

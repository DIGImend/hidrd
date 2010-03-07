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
 *
 * @(#) $Id$
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
 * Convert a decimal string to an unsigned 32-bit integer.
 *
 * @param pnum  Location for the converted number; could be NULL.
 * @param str   Decimal string to convert from.
 *
 * @return True if the string was valid and converted successfully, false
 *         otherwise.
 */
static inline bool
hidrd_dec_u32_from_str(uint32_t *pnum, const char *str)
{
    assert(str != NULL);
    return hidrd_num_u32_from_str(pnum, str, 10);
}

/**
 * Convert an unsigned 32-bit integer to a decimal string.
 *
 * @param num   The number to convert.
 *
 * @return Dynamically allocated decimal string, or NULL if failed to
 *         allocate memory.
 */
static inline char *
hidrd_dec_u32_to_str(uint32_t num)
{
    return hidrd_num_u32_to_str(num, 10);
}

/**
 * Convert a decimal string to an unsigned 16-bit integer.
 *
 * @param pnum  Location for the converted number; could be NULL.
 * @param str   Decimal string to convert from.
 *
 * @return True if the string was valid and converted successfully, false
 *         otherwise.
 */
static inline bool
hidrd_dec_u16_from_str(uint16_t *pnum, const char *str)
{
    assert(str != NULL);
    return hidrd_num_u16_from_str(pnum, str, 10);
}

/**
 * Convert an unsigned 16-bit integer to a decimal string.
 *
 * @param num   The number to convert.
 *
 * @return Dynamically allocated decimal string, or NULL if failed to
 *         allocate memory.
 */
static inline char *
hidrd_dec_u16_to_str(uint16_t num)
{
    return hidrd_num_u16_to_str(num, 10);
}

/**
 * Convert a decimal string to an unsigned 8-bit integer.
 *
 * @param pnum  Location for the converted number; could be NULL.
 * @param str   Decimal string to convert from.
 *
 * @return True if the string was valid and converted successfully, false
 *         otherwise.
 */
static inline bool
hidrd_dec_u8_from_str(uint8_t *pnum, const char *str)
{
    assert(str != NULL);
    return hidrd_num_u8_from_str(pnum, str, 10);
}

/**
 * Convert an unsigned 8-bit integer to a decimal string.
 *
 * @param num   The number to convert.
 *
 * @return Dynamically allocated decimal string, or NULL if failed to
 *         allocate memory.
 */
static inline char *
hidrd_dec_u8_to_str(uint8_t num)
{
    return hidrd_num_u8_to_str(num, 10);
}

/**
 * Declare a function pair for converting specified number type to from a
 * decimal string.
 *
 * @param _type     Long (global) name of the type being converted; will be
 *                  used in the function names.
 * @param _t        Short (local) name of the type being converted; will be
 *                  used for local variable names.
 */
#define HIDRD_DEC_CONV_DECLS(_type, _t) \
    HIDRD_NUM_CONV_DECLS(_type, _t, dec)

/**
 * Define a function pair for converting specified number type to from a
 * decimal string.
 *
 * @param _type     Long (global) name of the type being converted; will be
 *                  used in the function names.
 * @param _t        Short (local) name of the type being converted; will be
 *                  used for local variable names.
 * @param _num      Long (full) name of the number type (like uint32_t).
 * @param _n        Short (convenience) name of the number type (like s8).
 */
#define HIDRD_DEC_CONV_DEFS(_type, _t, _num, _n) \
    HIDRD_NUM_CONV_DEFS(_type, _t, _num, _n, dec, DEC)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_DEC_H__ */

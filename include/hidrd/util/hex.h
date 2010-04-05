/** @file
 * @brief HID report descriptor - utilities - hexadecimal conversions
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

#ifndef __HIDRD_UTIL_HEX_H__
#define __HIDRD_UTIL_HEX_H__

#include <stddef.h>
#include <assert.h>
#include "hidrd/util/num.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert a hexadecimal string to an unsigned 32-bit integer.
 *
 * @param pnum  Location for the converted number; could be NULL.
 * @param str   Hexadecimal string to convert from.
 *
 * @return True if the string was valid and converted successfully, false
 *         otherwise.
 */
static inline bool
hidrd_hex_u32_from_str(uint32_t *pnum, const char *str)
{
    assert(str != NULL);
    return hidrd_num_u32_from_str(pnum, str, HIDRD_NUM_BASE_HEX);
}

/**
 * Convert an unsigned 32-bit integer to a hexadecimal string.
 *
 * @param num   The number to convert.
 *
 * @return Dynamically allocated hexadecimal string, or NULL if failed to
 *         allocate memory.
 */
static inline char *
hidrd_hex_u32_to_str(uint32_t num)
{
    return hidrd_num_u32_to_str(num, HIDRD_NUM_BASE_HEX);
}

/**
 * Convert an unsigned 32-bit integer to a base-suffixed hexadecimal string.
 *
 * @param num   The number to convert.
 *
 * @return Dynamically allocated base-suffixed hexadecimal string, or NULL
 *         if failed to allocate memory.
 */
static inline char *
hidrd_hex_u32_to_bstr(uint32_t num)
{
    return hidrd_num_u32_to_bstr(num, HIDRD_NUM_BASE_HEX);
}

/**
 * Convert a hexadecimal string to an unsigned 16-bit integer.
 *
 * @param pnum  Location for the converted number; could be NULL.
 * @param str   Hexadecimal string to convert from.
 *
 * @return True if the string was valid and converted successfully, false
 *         otherwise.
 */
static inline bool
hidrd_hex_u16_from_str(uint16_t *pnum, const char *str)
{
    assert(str != NULL);
    return hidrd_num_u16_from_str(pnum, str, HIDRD_NUM_BASE_HEX);
}

/**
 * Convert an unsigned 16-bit integer to a hexadecimal string.
 *
 * @param num   The number to convert.
 *
 * @return Dynamically allocated hexadecimal string, or NULL if failed to
 *         allocate memory.
 */
static inline char *
hidrd_hex_u16_to_str(uint16_t num)
{
    return hidrd_num_u16_to_str(num, HIDRD_NUM_BASE_HEX);
}

/**
 * Convert an unsigned 16-bit integer to a base-suffixed hexadecimal string.
 *
 * @param num   The number to convert.
 *
 * @return Dynamically allocated base-suffixed hexadecimal string, or NULL
 *         if failed to allocate memory.
 */
static inline char *
hidrd_hex_u16_to_bstr(uint16_t num)
{
    return hidrd_num_u16_to_bstr(num, HIDRD_NUM_BASE_HEX);
}

/**
 * Convert a hexadecimal string to an unsigned 8-bit integer.
 *
 * @param pnum  Location for the converted number; could be NULL.
 * @param str   Hexadecimal string to convert from.
 *
 * @return True if the string was valid and converted successfully, false
 *         otherwise.
 */
static inline bool
hidrd_hex_u8_from_str(uint8_t *pnum, const char *str)
{
    assert(str != NULL);
    return hidrd_num_u8_from_str(pnum, str, HIDRD_NUM_BASE_HEX);
}

/**
 * Convert an unsigned 8-bit integer to a hexadecimal string.
 *
 * @param num   The number to convert.
 *
 * @return Dynamically allocated hexadecimal string, or NULL if failed to
 *         allocate memory.
 */
static inline char *
hidrd_hex_u8_to_str(uint8_t num)
{
    return hidrd_num_u8_to_str(num, HIDRD_NUM_BASE_HEX);
}

/**
 * Convert an unsigned 8-bit integer to a base-suffixed hexadecimal string.
 *
 * @param num   The number to convert.
 *
 * @return Dynamically allocated base-suffixed hexadecimal string, or NULL
 *         if failed to allocate memory.
 */
static inline char *
hidrd_hex_u8_to_bstr(uint8_t num)
{
    return hidrd_num_u8_to_bstr(num, HIDRD_NUM_BASE_HEX);
}

/**
 * Parse a hexadecimal string into a buffer.
 *
 * @param buf   Output buffer pointer.
 * @param size  Output buffer size.
 * @param plen  Location for number of read bytes; could be NULL.
 * @param str   Hex string to parse.
 *
 * @return True if parsed successfully and the data fit in the buffer, false
 *         otherwise.
 */
extern bool hidrd_hex_buf_from_str(void        *buf,
                                   size_t       size,
                                   size_t      *plen,
                                   const char  *str);

/**
 * Convert a buffer to a hexadecimal string.
 *
 * @param buf   Pointer to buffer to format.
 * @param size  Size of the buffer to format.
 *
 * @return Dynamically allocated hexadecimal string, or NULL if failed to
 *         allocate memory.
 */
extern char *hidrd_hex_buf_to_str(void *buf, size_t size);

/**
 * Convert a buffer to a base-suffixed hexadecimal string.
 *
 * @param buf   Pointer to buffer to format.
 * @param size  Size of the buffer to format.
 *
 * @return Dynamically allocated base-suffixed hexadecimal string, or NULL
 *         if failed to allocate memory.
 */
extern char *hidrd_hex_buf_to_bstr(void *buf, size_t size);

/**
 * Declare a function pair for converting specified number type to from a
 * hexadecimal string.
 *
 * @param _type     Long (global) name of the type being converted; will be
 *                  used in the function names.
 * @param _t        Short (local) name of the type being converted; will be
 *                  used for local variable names.
 */
#define HIDRD_HEX_CONV_DECLS(_type, _t) \
    HIDRD_NUM_CONV_DECLS(_type, _t, hex)

/**
 * Define a function pair for converting specified number type to from a
 * hexadecimal string.
 *
 * @param _type     Long (global) name of the type being converted; will be
 *                  used in the function names.
 * @param _t        Short (local) name of the type being converted; will be
 *                  used for local variable names.
 * @param _n        Short (convenience) name of the number type (like s8).
 */
#define HIDRD_HEX_CONV_DEFS(_type, _t, _n) \
    HIDRD_NUM_CONV_DEFS(_type, _t, _n, hex)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_HEX_H__ */

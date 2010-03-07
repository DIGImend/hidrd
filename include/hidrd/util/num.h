/** @file
 * @brief HID report descriptor - utilities - number conversions
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

#ifndef __HIDRD_UTIL_NUM_H__
#define __HIDRD_UTIL_NUM_H__

#include <stdbool.h>
#include <stdint.h>
#include "hidrd/util/num.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum hidrd_num_base {
    HIDRD_NUM_BASE_DEC  = 10,
    HIDRD_NUM_BASE_HEX  = 16
} hidrd_num_base;

static inline bool
hidrd_num_base_valid(hidrd_num_base base)
{
    return (base == HIDRD_NUM_BASE_DEC || base == HIDRD_NUM_BASE_HEX);
}

/**
 * Convert a string to an unsigned 32-bit integer.
 *
 * @param pnum  Location for the converted number; could be NULL.
 * @param str   String to convert from.
 * @param base  Number base to convert from; only decimal and hexadecimal
 *              bases are supported.
 *
 * @return True if the string was valid and converted successfully, false
 *         otherwise.
 */
extern bool hidrd_num_u32_from_str(uint32_t        *pnum,
                                   const char      *str,
                                   hidrd_num_base   base);

/**
 * Convert a string to an unsigned 16-bit integer.
 *
 * @param pnum  Location for the converted number; could be NULL.
 * @param str   String to convert from.
 * @param base  Number base to convert from; only decimal and hexadecimal
 *              bases are supported.
 *
 * @return True if the string was valid and converted successfully, false
 *         otherwise.
 */
extern bool hidrd_num_u16_from_str(uint16_t        *pnum,
                                   const char      *str,
                                   hidrd_num_base   base);

/**
 * Convert a string to an unsigned 8-bit integer.
 *
 * @param pnum  Location for the converted number; could be NULL.
 * @param str   String to convert from.
 * @param base  Number base to convert from; only decimal and hexadecimal
 *              bases are supported.
 *
 * @return True if the string was valid and converted successfully, false
 *         otherwise.
 */
extern bool hidrd_num_u8_from_str(uint8_t          *pnum,
                                   const char      *str,
                                   hidrd_num_base   base);

/**
 * Convert an unsigned 32-bit integer to a string.
 *
 * @param num   The number to convert.
 * @param base  Number base to convert to; only decimal and hexadecimal
 *              bases are supported.
 *
 * @return Dynamically allocated string, or NULL if failed to allocate
 *         memory.
 */
extern char *hidrd_num_u32_to_str(uint32_t num, hidrd_num_base base);

/**
 * Convert an unsigned 16-bit integer to a string.
 *
 * @param num   The number to convert.
 * @param base  Number base to convert to; only decimal and hexadecimal
 *              bases are supported.
 *
 * @return Dynamically allocated string, or NULL if failed to allocate
 *         memory.
 */
static inline char *
hidrd_num_u16_to_str(uint16_t num, hidrd_num_base base)
{
    return hidrd_num_u32_to_str(num, base);
}

/**
 * Convert an unsigned 8-bit integer to a string.
 *
 * @param num   The number to convert.
 * @param base  Number base to convert to; only decimal and hexadecimal
 *              bases are supported.
 *
 * @return Dynamically allocated string, or NULL if failed to allocate
 *         memory.
 */
static inline char *
hidrd_num_u8_to_str(uint8_t num, hidrd_num_base base)
{
    return hidrd_num_u32_to_str(num, base);
}

/**
 * Declare a function pair for converting specified number type to/from a
 * string.
 *
 * @param _type     Long (global) name of the type being converted; will be
 *                  used in the function names.
 * @param _t        Short (local) name of the type being converted; will be
 *                  used for local variable names.
 * @param _b        Base of the string representation of the number
 *                  (lowercase).
 */
#define HIDRD_NUM_CONV_DECLS(_type, _t, _b) \
    extern char *hidrd_##_type##_to_##_b(hidrd_##_type _t);         \
                                                                    \
    extern bool hidrd_##_type##_from_##_b(hidrd_##_type *p##_t,     \
                                          const char      *str);


/**
 * Define a function pair for converting specified number type to from a
 * string.
 *
 * @param _type     Long (global) name of the type being converted; will be
 *                  used in the function names.
 * @param _t        Short (local) name of the type being converted; will be
 *                  used for local variable names.
 * @param _num      Long (full) name of the number type (like uint32_t).
 * @param _n        Short (convenience) name of the number type (like s8).
 * @param _b        Base of the string representation of the number
 *                  (lowercase - dec or hex).
 * @param _B        Base of the string representation of the number
 *                  (uppercase - DEC or HEX).
 */
#define HIDRD_NUM_CONV_DEFS(_type, _t, _num, _n, _b, _B) \
    char *                                                          \
    hidrd_##_type##_to_##_b(hidrd_##_type _t)                       \
    {                                                               \
        assert(hidrd_##_type##_valid(_t));                          \
        return hidrd_num_##_n##_to_str(_t, HIDRD_NUM_BASE_##_B);    \
    }                                                               \
                                                                    \
                                                                    \
    bool                                                            \
    hidrd_##_type##_from_##_b(hidrd_##_type *p##_t,                 \
                              const char      *str)                 \
    {                                                               \
        _num    _t;                                                 \
                                                                    \
        assert(str != NULL);                                        \
                                                                    \
        if (!hidrd_num_##_n##_from_str(&_t, str,                    \
                                    HIDRD_NUM_BASE_##_B) ||         \
            !hidrd_##_type##_valid(_t))                             \
            return false;                                           \
                                                                    \
        if (p##_t != NULL)                                          \
            *p##_t = _t;                                            \
                                                                    \
        return true;                                                \
    }

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_NUM_H__ */

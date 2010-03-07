/** @file
 * @brief HID report descriptor - utilities - token conversions
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

#ifndef __HIDRD_UTIL_TKN_H__
#define __HIDRD_UTIL_TKN_H__

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Find a token in a constant string; a token is considered to contain only
 * alphanumeric characters or underscores.
 *
 * @param ptkn  Location for the token start pointer; could be NULL.
 * @param plen  Location for the token length; could be NULL.
 * @param str   String to look through.
 *
 * @return True if the token was found and there was nothing else except
 *         whitespace in the string.
 */
extern bool hidrd_tkn_strip(const char    **ptkn,
                            size_t         *plen,
                            const char     *str);

/** Token number-string 1ink */
typedef struct hidrd_tkn_link {
    uint32_t    num;    /**< Token numer */
    const char *str;    /**< Token string */
} hidrd_tkn_link;

/**
 * Convert a string token to number, according to a map.
 *
 * @param pnum  Location for resulting number.
 * @param str   String token to convert.
 * @param map   Token map to look through,
 *              terminated by an entry with NULL str.
 *
 * @return True if the token was recognized and found in the map, false
 *         otherwise.
 */
extern bool hidrd_tkn_to_num(uint32_t *pnum,
                             const char *str,
                             const hidrd_tkn_link *map);

/**
 * Convert a token number to a string, according to a map.
 *
 * @param num   Token number to convert.
 * @param map   Token map to look through,
 *              terminated by an entry with NULL str.
 *
 * @return Token string from the map, if found, false otherwise.
 */
extern const char *hidrd_tkn_from_num(uint32_t              num,
                                      const hidrd_tkn_link *map);

/**
 * Declare token conversion functions for specified type.
 *
 * @param _type Long (global) type name (without hidrd_ prefix).
 * @param _t    Short (local) type name (possibly just last word).
 * @param _b    Number base (dec or hex) used in string representation for
 *              missing token strings.
 */
#define HIDRD_TKN_CONV_DECLS(_type, _t, _b) \
    extern const char *hidrd_##_type##_to_token(hidrd_##_type   _t);        \
                                                                            \
    extern bool hidrd_##_type##_from_token(hidrd_##_type   *p##_t,          \
                                           const char      *str);           \
                                                                            \
    extern char *hidrd_##_type##_to_token_or_##_b(hidrd_##_type _t);        \
                                                                            \
    extern bool hidrd_##_type##_from_token_or_##_b(hidrd_##_type   *p##_t,  \
                                                   const char      *str)

/**
 * Define token conversion functions for specified type, conversion to
 * numeric strings and validation functions, token map must be declared and
 * defined separately.
 *
 * @param _type Long (global) type name (without hidrd_ prefix).
 * @param _t    Short (local) type name (possibly just last word).
 * @param _b    Number base (dec or hex) used in string representation for
 *              missing tokens.
 */
#define HIDRD_TKN_CONV_DEFS(_type, _t, _b) \
    const char *                                                \
    hidrd_##_type##_to_token(hidrd_##_type _t)                  \
    {                                                           \
        assert(hidrd_##_type##_valid(_t));                      \
        return hidrd_tkn_from_num(_t, _t##_map);                \
    }                                                           \
                                                                \
                                                                \
    bool                                                        \
    hidrd_##_type##_from_token(hidrd_##_type   *p##_t,          \
                               const char      *str)            \
    {                                                           \
        uint32_t    _t;                                         \
                                                                \
        assert(str != NULL);                                    \
                                                                \
        if (!hidrd_tkn_to_num(&_t, str, _t##_map))              \
            return false;                                       \
                                                                \
        if (!hidrd_##_type##_valid(_t))                         \
            return false;                                       \
                                                                \
        if (p##_t != NULL)                                      \
            *p##_t = _t;                                        \
                                                                \
        return true;                                            \
    }                                                           \
                                                                \
                                                                \
    char *                                                      \
    hidrd_##_type##_to_token_or_##_b(hidrd_##_type _t)          \
    {                                                           \
        const char *token;                                      \
                                                                \
        assert(hidrd_##_type##_valid(_t));                      \
                                                                \
        token = hidrd_##_type##_to_token(_t);                   \
                                                                \
        return (token != NULL)                                  \
                    ? strdup(token)                             \
                    : hidrd_##_type##_to_##_b(_t);              \
    }                                                           \
                                                                \
    bool                                                        \
    hidrd_##_type##_from_token_or_##_b(hidrd_##_type   *p##_t,  \
                                       const char      *str)    \
    {                                                           \
        return hidrd_##_type##_from_token(p##_t, str) ||        \
               hidrd_##_type##_from_##_b(p##_t, str);           \
    }

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_TKN_H__ */

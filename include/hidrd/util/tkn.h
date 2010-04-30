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
 * Check if a token is valid.
 *
 * @param tkn   Token to check.
 *
 * @return True if the token is valid, false otherwise.
 */
extern bool hidrd_tkn_valid(const char *tkn);

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
 *              terminated by an entry with NULL str field.
 *
 * @return Dynamically allocated token string, or NULL if not found or
 *         failed to allocate memory; check errno for the latter.
 */
extern char *hidrd_tkn_from_num(uint32_t              num,
                                const hidrd_tkn_link *map);

/**
 * Declare token conversion functions for specified type.
 *
 * @param _t    Name of the type being converted, without hidrd_ prefix.
 */
#define HIDRD_TKN_CONV_DECLS(_t) \
    extern char *hidrd_##_t##_to_token(hidrd_##_t v);                   \
    extern bool hidrd_##_t##_from_token(hidrd_##_t *pv, const char *s);

/**
 * Generate a hidrd_tkn_1ink initializer.
 *
 * @param _val  Value.
 * @param _tkn  Token.
 */
#define HIDRD_TKN_LINK(_val, _tkn) {.num = _val, .str = #_tkn}

/**
 * Define token map and conversion functions for specified type.
 *
 * @param _t        Name of the type being converted, without hidrd_ prefix.
 * @param _links    List of HIDRD_TKN_LINK macro calls.
 */
#define HIDRD_TKN_CONV_DEFS(_t, _links...) \
    static const hidrd_tkn_link hidrd_##_t##_tkn_map[] = {      \
        _links,                                                 \
        {.str = NULL}                                           \
    };                                                          \
                                                                \
    char *                                                      \
    hidrd_##_t##_to_token(hidrd_##_t v)                         \
    {                                                           \
        assert(hidrd_##_t##_valid(v));                          \
        return hidrd_tkn_from_num(v, hidrd_##_t##_tkn_map);     \
    }                                                           \
                                                                \
                                                                \
    bool                                                        \
    hidrd_##_t##_from_token(hidrd_##_t *pv, const char *str)    \
    {                                                           \
        uint32_t    v;                                          \
                                                                \
        assert(str != NULL);                                    \
                                                                \
        if (!hidrd_tkn_to_num(&v, str, hidrd_##_t##_tkn_map))   \
            return false;                                       \
                                                                \
        if (!hidrd_##_t##_valid(v))                             \
            return false;                                       \
                                                                \
        if (pv != NULL)                                         \
            *pv = v;                                            \
                                                                \
        return true;                                            \
    }


/**
 * Check if a token could be "humanized", in effect if it doesn't contain
 * leading, trailing or successive underscores.
 *
 * @param tkn   Token to check.
 *
 * @return True if the token could be "humanized", false otherwise.
 */
extern bool hidrd_tkn_hmnzbl(const char *tkn);


/** "Humanized" token capitalization type */
typedef enum hidrd_tkn_hmnz_cap {
    HIDRD_TKN_HMNZ_CAP_NONE,    /**< None */
    HIDRD_TKN_HMNZ_CAP_FWF,     /**< First character of the first word */
    HIDRD_TKN_HMNZ_CAP_WF,      /**< First character of every word */
    HIDRD_TKN_HMNZ_CAP_ALL,     /**< All characters */
} hidrd_tkn_hmnz_cap;

/**
 * Check if a humanized token capitalization type is valid.
 *
 * @param cap   Capitalization type to check.
 *
 * @return True if the capitalization type to check, false otherwise.
 */
extern bool hidrd_tkn_hmnz_cap_valid(hidrd_tkn_hmnz_cap cap);

/**
 * "Humanize" a token: convert underscores to spaces and uppercase specified
 * character positions.
 *
 * @param tkn   Token to "humanize".
 * @param cap   Capitalization type.
 *
 * @return "Humanized" (original) token pointer.
 */
extern char *hidrd_tkn_hmnz(char *tkn, hidrd_tkn_hmnz_cap cap);

/**
 * "Humanize" a token: convert underscores to spaces and uppercase specified
 * character positions; this version returns dynamically allocated result.
 *
 * @param tkn   Token to "humanize".
 * @param cap   Capitalization type.
 *
 * @return Dynamically allocated "humanized" token pointer.
 */
extern char *hidrd_tkn_ahmnz(const char *tkn, hidrd_tkn_hmnz_cap cap);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_TKN_H__ */

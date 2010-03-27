/** @file
 * @brief HID report descriptor - utilities - string operations
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

#ifndef __HIDRD_UTIL_STR_H__
#define __HIDRD_UTIL_STR_H__

#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "hidrd/util/char.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check if a string is blank, in effect is empty or contains nothing but
 * whitespace.
 *
 * @param str   String to check.
 *
 * @return True if the string is blank, false otherwise.
 */
extern bool hidrd_str_isblank(const char *str);

/**
 * Uppercase the first character of a string.
 *
 * @param str   String to modify.
 *
 * @return Modified string.
 */
extern char *hidrd_str_uc_first(char *str);

/**
 * Pad a dynamically allocated string with spaces on both sides.
 *
 * @param str   A dynamically allocated string to pad; will be freed, even
 *              in case of failure.
 *
 * @return Dynamically allocated padded string, or NULL, if failed to
 *         allocate memory.
 */
extern char *hidrd_str_apada(char *str);

/**
 * Check if a string matches length and contents of another string chunk,
 * case insensitively.
 *
 * @param str   String to match.
 * @param chunk String chunk to match.
 * @param len   String chunk length.
 *
 * @return strncasecmp(3) semantics, plus will return 1 if str is longer
 *         than chunk.
 */
extern int hidrd_str_ncasecmpn(const char  *str,
                               const char  *chunk,
                               size_t len);


/** String character position bit */
typedef enum hidrd_str_cp_bit {
    HIDRD_STR_CP_BIT_FIRST,         /**< First character */
    HIDRD_STR_CP_BIT_LAST,          /**< Last character */
    HIDRD_STR_CP_BIT_WORD,          /**< Word character */
    HIDRD_STR_CP_BIT_FIRST_WORD,    /**< First word character */
    HIDRD_STR_CP_BIT_NON_WORD,      /**< Non-word characters */
    HIDRD_STR_CP_BIT_WORD_FIRST,    /**< First character of a word */
} hidrd_str_cp_bit;

#define HIDRD_STR_CP_BIT_MAX    HIDRD_STR_CP_BIT_WORD_FIRST;

static inline bool
hidrd_str_cp_bit_valid(hidrd_str_cp_bit bit)
{
    return bit <= HIDRD_STR_CP_BIT_MAX;
}

/** String character position */
typedef enum hidrd_str_cp {
#define MAP(_NAME) \
    HIDRD_STR_CP_##_NAME = 1 << HIDRD_STR_CP_BIT_##_NAME
    MAP(FIRST),
    MAP(LAST),
    MAP(WORD),
    MAP(FIRST_WORD),
    MAP(NON_WORD),
    MAP(WORD_FIRST),
#undef MAP
} hidrd_str_cp;

/** String character position set (bitmap) */
typedef uint32_t    hidrd_str_cp_set;

/** No character positions set */
#define HIDRD_STR_CP_SET_NONE   0

/** All character positions set */
#define HIDRD_STR_CP_SET_ALL    (UINT32_MAX >> (32 - HIDRD_STR_CP_BIT_MAX))


/** String character position classification state */
typedef struct hidrd_str_cp_clsf {
    const char *p;              /**< Next character pointer */
    bool        got_char;       /**< Got a character */
    bool        got_word;       /**< Got a word */
    bool        word;           /**< Word run */
} hidrd_str_cp_clsf;

/**
 * Start string character position classification.
 *
 * @param clsf  Classification state to initialize to the start of the
 *              specified string.
 * @param str   String to classify character positions for.
 */
extern void hidrd_str_cp_clsf_start(hidrd_str_cp_clsf *clsf,
                                    const char *str);

/**
 * Classify next character position of a string.
 *
 * @param clsf  Classification state.
 * @param pp    Location for classified character pointer; could be NULL.
 *
 * @return Character position set (HIDRD_STR_CP_SET_NONE for '\0').
 */
extern hidrd_str_cp_set hidrd_str_cp_clsf_next(hidrd_str_cp_clsf *clsf,
                                               const char **pp);

/**
 * Prototype for a function used to match a string character position set.
 *
 * @param set   Set to match.
 * @param data  Opaque data.
 *
 * @return Match result.
 */
typedef bool hidrd_str_cp_match_fn(hidrd_str_cp_set set, void *data);


/**
 * Character position conjuction matching function.
 *
 * @param set   Set to match.
 * @param data  Pointer to a set to match against.
 *
 * @return Match result.
 */
extern bool hidrd_str_cp_match_and(hidrd_str_cp_set set, void *data);


/**
 * Character position disjuction matching function.
 *
 * @param set   Set to match.
 * @param data  Pointer to a set to match against.
 *
 * @return Match result.
 */
extern bool hidrd_str_cp_match_or(hidrd_str_cp_set set, void *data);


/**
 * Process a string inline matching character positions.
 *
 * @param str           String to modify.
 * @param match         Position set matching function.
 * @param match_data    Position set matching function data.
 * @param proc          Character processing function.
 *
 * @return Modified (original) string pointer.
 */
extern char *hidrd_str_cp_iproc(char *str,
                                hidrd_str_cp_match_fn  *match,
                                void                   *match_data,
                                hidrd_char_proc_fn     *proc);

/**
 * Uppercase string characters on specified positions inline.
 *
 * @param str   String to uppercase.
 * @param match Character position set matching function.
 * @param data  Character position set matching function data.
 *
 * @return Uppercase (original) string pointer.
 */
static inline char *
hidrd_str_cp_iuc(char *str, hidrd_str_cp_match_fn *match, void *data)
{
    assert(str != NULL);
    assert(match != NULL);

    return hidrd_str_cp_iproc(str, match, data, hidrd_char_uc);
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_STR_H__ */

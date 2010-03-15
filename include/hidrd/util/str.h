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

#include <stddef.h>
#include <stdbool.h>

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

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_STR_H__ */

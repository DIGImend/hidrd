/** @file
 * @brief HID report descriptor - utilities - character operations
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

#ifndef __HIDRD_UTIL_CHAR_H__
#define __HIDRD_UTIL_CHAR_H__

#include <stdbool.h>
#include <ctype.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check if a character is a token character; only standard ASCII is
 * supported.
 *
 * @param c Character to check.
 *
 * @return True if the character is a token character, false otherwise.
 */
static inline bool
hidrd_char_istkn(char c)
{
    return (isalnum(c) || c == '_');
}

/**
 * Check if a character is word character; only standard ASCII is supported.
 *
 * @param c Character to check.
 *
 * @return True if the character is a word character, false otherwise.
 */
static inline bool
hidrd_char_isword(char c)
{
    /* XXX not quite sure about the character set */
    return (isalnum(c) || c == '-' || c == '_');
}

/**
 * Prototype for a character processing function; only standard ASCII is
 * supported.
 *
 * @param c Character to process.
 *
 * @return Processed character.
 */
typedef char hidrd_char_proc_fn(char c);

/**
 * Character uppercasing function.
 *
 * @param p Character to uppercase.
 *
 * @return Uppercased character
 */
extern char hidrd_char_uc(char c);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_CHAR_H__ */

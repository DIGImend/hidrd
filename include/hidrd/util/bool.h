/** @file
 * @brief HID report descriptor - utilities - boolean conversions
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

#ifndef __HIDRD_UTIL_BOOL_H__
#define __HIDRD_UTIL_BOOL_H__

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert a string ("true"/"yes"/non-zero number or "false"/"no"/zero
 * number) to a boolean value.
 *
 * @param pvalue    Location for resulting value.
 * @param str       String to convert from.
 *
 * @return True if the string was recognized and converted, false otherwise.
 */
extern bool hidrd_bool_from_str(bool   *pvalue, const char *str);

/**
 * Convert a boolean value to a string ("true" or "false").
 *
 * @param value Value to convert.
 *
 * @return A constant string: either "true" or "false".
 */
extern const char *hidrd_bool_to_str(bool value);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_BOOL_H__ */

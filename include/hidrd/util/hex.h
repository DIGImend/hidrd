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
extern char *hidrd_hex_buf_to_sstr(void *buf, size_t size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_HEX_H__ */

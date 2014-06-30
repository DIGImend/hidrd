/** @file
 * @brief HID report descriptor - utilities - "universal" string formatting
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
 */

#ifndef __HIDRD_UTIL_FMT_H__
#define __HIDRD_UTIL_FMT_H__

#include <stdbool.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Formatting type */
typedef enum hidrd_fmt_type {
    HIDRD_FMT_TYPE_NULL,    /**< NULL string */
    HIDRD_FMT_TYPE_S32,     /**< Signed 32-bit integer */
    HIDRD_FMT_TYPE_U32,     /**< Unsigned 32-bit integer */
    HIDRD_FMT_TYPE_STRDUP,  /**< String duplication */
    HIDRD_FMT_TYPE_STROWN,  /**< String ownership taking */
    HIDRD_FMT_TYPE_HEX,     /**< Hex string */
    HIDRD_FMT_TYPE_SHEX     /**< Base-suffixed hex string */
} hidrd_fmt_type;

/**
 * Format a dynamically allocated string according to format type; va_list
 * pointer version.
 *
 * @param pstr  Location for a (dynamically allocated) resulting string
 *              pointer.
 * @param type  Format type.
 * @param pap   Pointer to a va_list containing format arguments.
 *
 * @return True if formatted successfully, false otherwise.
 *
 * @sa hidrdm_fmt_type
 */
extern bool hidrd_fmtpva(char             **pstr,
                         hidrd_fmt_type     type,
                         va_list           *pap);

/**
 * Free format arguments for a specified format, if needed.
 *
 * @param type  Format type.
 * @param pap   Pointer to a va_list containing format arguments.
 */
extern void hidrd_fmtfreepv(hidrd_fmt_type      type,
                            va_list            *pap);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_FMT_H__ */

/** @file
 * @brief HID report descriptor - option tokens list
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

#ifndef __HIDRD_OPT_TKNS_LIST_H__
#define __HIDRD_OPT_TKNS_LIST_H__

#include <stddef.h>
#include "hidrd/opt/tkns.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check if an option token pair list is valid.
 *
 * @param list  Option token pair list to check.
 *
 * @return True if the list is valid, false otherwise.
 */
extern bool hidrd_opt_tkns_list_valid(const hidrd_opt_tkns *list);

/**
 * Get an option token pair list length.
 *
 * @param list  Option token pair list to get length of.
 *
 * @return List length, in options.
 */
extern size_t hidrd_opt_tkns_list_len(const hidrd_opt_tkns *list);

/**
 * Parse string as an option token pair list, modifying it and
 * referencing in the resulting list.
 *
 * @param buf   String to parse, will be modified and referenced in the
 *              resulting option token pair list.
 *
 * @return Dynamically allocated resulting option token pair list,
 *         referencing modified original string, or NULL, if failed to
 *         parse or allocate memory.
 */
extern hidrd_opt_tkns *hidrd_opt_tkns_list_parse(char *buf);

/**
 * Format a string representation of an option token pair list.
 *
 * @param tkns_list Option token pair list to format.
 *
 * @return Dynamically allocated string representation of the list, or NULL,
 *         if failed to allocate memory.
 */
extern char *hidrd_opt_tkns_list_format(const hidrd_opt_tkns *tkns_list);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_OPT_TKNS_LIST_H__ */

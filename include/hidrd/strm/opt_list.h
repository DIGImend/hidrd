/** @file
 * @brief HID report descriptor - stream initialization option list
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

#ifndef __HIDRD_STRM_OPT_LIST_H__
#define __HIDRD_STRM_OPT_LIST_H__

#include <stddef.h>
#include "hidrd/strm/opt.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Grow an option list to make specified index valid.
 *
 * @param plist     Location of the option array pointer.
 * @param palloc    Location of the option array allocated size, in options.
 * @param index     Option index to be made valid.
 *
 * @return True if grown successfully, false otherwise.
 */
extern bool hidrd_strm_opt_list_grow(hidrd_strm_opt   **plist,
                                     size_t            *palloc,
                                     size_t             index);

/**
 * Check if an option list is empty.
 *
 * @param list  Option list array pointer.
 *
 * @return True if the option list is empty, false otherwise.
 */
extern bool hidrd_strm_opt_list_empty(const hidrd_strm_opt *list);

/**
 * Parse an option list string, modifying it and referencing in the
 * resulting list.
 *
 * @param buf   Option list string buffer; will be modified and referenced
 *              in the resulting option list.
 *
 * @return Dynamically allocated option list array, with names and values
 *         referenced from the string, or NULL, if failed to allocate
 *         memory.
 */
extern hidrd_strm_opt *hidrd_strm_opt_list_parse(char *buf);


/**
 * Lookup an option in an option list.
 *
 * @param list  Option list array pointer.
 * @param name  Option name to lookup.
 *
 * @return Option pointer, if found; NULL otherwise.
 */
extern const hidrd_strm_opt *hidrd_strm_opt_list_lkp(
                                            const hidrd_strm_opt   *list,
                                            const char             *name);

/**
 * Get a boolean option value.
 *
 * @param list  Option list array pointer.
 * @param name  Option name to get value from.
 * @param dflt  Default value.
 *
 * @return Option value, or @e dflt, if not found.
 */
extern bool hidrd_strm_opt_list_get_bool(const hidrd_strm_opt  *list,
                                         const char            *name,
                                         bool                   dflt);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_STRM_OPT_LIST_H__ */



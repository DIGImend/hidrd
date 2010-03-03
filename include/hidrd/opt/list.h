/** @file
 * @brief HID report descriptor - option list
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

#ifndef __HIDRD_OPT_LIST_H__
#define __HIDRD_OPT_LIST_H__

#include <stddef.h>
#include "hidrd/opt/inst.h"
#include "hidrd/opt/spec_list.h"
#include "hidrd/opt/tkns_list.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check if an option list is valid.
 *
 * @param list  Option list array pointer.
 *
 * @return True if the option list is valid.
 */
extern bool hidrd_opt_list_valid(const hidrd_opt *list);

/**
 * Check if an option list is empty.
 *
 * @param list  Option list array pointer.
 *
 * @return True if the option list is empty, false otherwise.
 */
extern bool hidrd_opt_list_empty(const hidrd_opt *list);

/**
 * Get an option list length.
 *
 * @param list  Option list to get length of.
 *
 * @return List length, in options.
 */
extern size_t hidrd_opt_list_len(const hidrd_opt *list);

/**
 * Lookup an option in an option list.
 *
 * @param list  Option list array pointer.
 * @param name  Option name to lookup.
 *
 * @return Option pointer, if found; NULL otherwise.
 */
extern const hidrd_opt *hidrd_opt_list_lkp(const hidrd_opt *list,
                                           const char      *name);

/**
 * Get a boolean option value.
 *
 * @param list  Option list array pointer.
 * @param name  Option name to get value from.
 * @param dflt  Default value.
 *
 * @return Option value.
 */
extern bool hidrd_opt_list_get_boolean(const hidrd_opt *list,
                                       const char      *name);

/**
 * Get a string option value.
 *
 * @param list  Option list array pointer.
 * @param name  Option name to get value from.
 * @param dflt  Default value.
 *
 * @return Option value.
 */
extern const char *hidrd_opt_list_get_string(const hidrd_opt   *list,
                                             const char        *name);

/**
 * Parse a token pair list representation of an option list.
 *
 * @param spec_list Option specification list to apply.
 * @param tkns_list Option token pair list to format.
 *
 * @return Dynamically allocated option list with names and string values
 *         referenced from the token pair list or specification list; will
 *         return NULL if failed to parse or allocate memory.
 */
extern hidrd_opt *hidrd_opt_list_parse_tkns_list(
                                    const hidrd_opt_spec   *spec_list,
                                    const hidrd_opt_tkns   *tkns_list);

/**
 * Parse a string representation of an option list.
 *
 * @param spec_list Option specification list to apply.
 * @param buf       String representation of the option list; will be
 *                  modified and possibly referenced from the resulting
 *                  option list.
 *
 * @return Dynamically allocated option list with names and string values
 *         referenced from the original string or specification list; will
 *         return NULL if failed to parse or allocate memory.
 */
extern hidrd_opt *hidrd_opt_list_parse(const hidrd_opt_spec    *spec_list,
                                       char                    *buf);

/**
 * Format a token pair list representation of an option list.
 *
 * @param opt_list  Option list to format.
 *
 * @return Dynamically allocated token pair list with dynamically allocated
 *         value tokens and name tokens referenced from the options; will
 *         return NULL if failed to allocate memory.
 */
extern hidrd_opt_tkns *hidrd_opt_list_format_tkns_list(
                                            const hidrd_opt *opt_list);

/**
 * Format a string representation of an option list.
 *
 * @param opt_list  Option list to format.
 *
 * @return Dynamically allocated string representation of the list, or NULL,
 *         if failed to allocate memory.
 */
extern char *hidrd_opt_list_format(const hidrd_opt *opt_list);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_OPT_LIST_H__ */

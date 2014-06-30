/** @file
 * @brief HID report descriptor - option specification list
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

#ifndef __HIDRD_OPT_SPEC_LIST_H__
#define __HIDRD_OPT_SPEC_LIST_H__

#include <stddef.h>
#include "hidrd/opt/spec.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check if an option specification list is valid.
 *
 * @param list  Option specification list to check.
 *
 * @return True if the list is valid, false otherwise.
 */
extern bool hidrd_opt_spec_list_valid(const hidrd_opt_spec *list);

/**
 * Get an option specification list length.
 *
 * @param list  Option specification list to get length of.
 *
 * @return List length, in options.
 */
extern size_t hidrd_opt_spec_list_len(const hidrd_opt_spec *list);

/**
 * Lookup an option specification in an option specification list.
 *
 * @param list  Option specification list to lookup in.
 * @param name  Option name to lookup.
 *
 * @return Option specification, or NULL if not found.
 */
extern const hidrd_opt_spec *hidrd_opt_spec_list_lkp(
                                            const hidrd_opt_spec   *list,
                                            const char             *name);

/**
 * Parse a token pair list as an option specification list, modifying
 * token values and referencing strings from them.
 *
 * @param tkns_list  Token pair list to parse.
 *
 * @return Dynamically allocated option specification list, referencing
 *         names and modified values from the token pair list, or NULL, if
 *         failed to parse or allocate memory.
 */
extern hidrd_opt_spec *hidrd_opt_spec_list_parse_tkns_list(
                                                hidrd_opt_tkns *tkns_list);

/**
 * Parse string as an option specification list, modifying it and
 * referencing in the resulting list.
 *
 * @param buf   String to parse, will be modified and referenced in the
 *              resulting option specification list.
 *
 * @return Resulting option specification list, referencing modified
 *         original string, or NULL, if failed to parse or allocate memory.
 */
extern hidrd_opt_spec *hidrd_opt_spec_list_parse(char *buf);

/**
 * Format a token pair list representation of an option specification list.
 *
 * @param spec_list Option specification list to format.
 *
 * @return Dynamically allocated token pair list; each token will contain
 *         dynamically allocated value (which will need to be freed)
 *         and name referenced from a corresponding specification; will
 *         return NULL in case of memory allocation failure.
 */
extern hidrd_opt_tkns *hidrd_opt_spec_list_format_tkns_list(
                                        const hidrd_opt_spec *spec_list);

/**
 * Format a string representation of an option specification list.
 *
 * @param spec_list Option specification list to format.
 *
 * @return Dynamically allocated string representation of the list, or NULL,
 *         if failed to allocate memory.
 */
extern char *hidrd_opt_spec_list_format(const hidrd_opt_spec *spec_list);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_OPT_SPEC_LIST_H__ */

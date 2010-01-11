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
 *
 * @(#) $Id$
 */

#ifndef __HIDRD_OPT_SPEC_LIST_H__
#define __HIDRD_OPT_SPEC_LIST_H__

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
 * Parse a string option list as an option specification list, modifying
 * option values and referencing strings from them.
 *
 * @param opt_list  Option list to parse.
 *
 * @return Dynamically allocated option specification list, referencing
 *         names and modified values of the option list, or NULL, if failed
 *         to parse or allocate memory.
 *
 * @sa hidrd_opt_spec_parse_opt
 */
extern hidrd_opt_spec *hidrd_opt_spec_list_parse_opt_list(
                                                hidrd_opt  *opt_list);

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
 * Format a string representation of an option specification list.
 *
 * @param spec_list Option specification list to format.
 *
 * @return Dynamically allocated string representation of the list, or NULL,
 *         if failed to allocate memory.
 */
extern char *hidrd_opt_spec_list_format(const hidrd_opt_spec *spec_list);

/**
 * Apply option specification list to a string option list, converting
 * options to specific types.
 *
 * @param spec_list Option specification list; default values from the
 *                  specifications maybe referenced in the resulting option
 *                  list.
 * @param opt_list  String option list to validate and convert to specific
 *                  types.
 *
 * @return True if the option list was successfully converted to specific
 *         list and all the mandatory options were present.
 */
extern bool hidrd_opt_spec_list_apply(const hidrd_opt_spec *spec_list,
                                      hidrd_opt            *opt_list);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_OPT_SPEC_LIST_H__ */

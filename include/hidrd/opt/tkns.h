/** @file
 * @brief HID report descriptor - option tokens (name and value pair)
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

#ifndef __HIDRD_OPT_TKNS_H__
#define __HIDRD_OPT_TKNS_H__

#include <stddef.h>
#include "hidrd/opt/name_tkn.h"
#include "hidrd/opt/value_tkn.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Option tokens (pair - name and value) */
typedef struct hidrd_opt_tkns {
    const char *name;
    const char *value;
} hidrd_opt_tkns;


/**
 * Check if an option token pair is valid.
 *
 * @param tkns  Option token pair to check.
 *
 * @return True if the token pair is valid, false otherwise.
 */
static inline bool
hidrd_opt_tkns_valid(const hidrd_opt_tkns *tkns)
{
    return tkns != NULL &&
           hidrd_opt_name_tkn_valid(tkns->name) &&
           hidrd_opt_value_tkn_valid(tkns->value);
}

/**
 * Parse the string representation of an option token pair (in effect
 * "name=value"), modifying it and referencing in the resulting token pair.
 *
 * @param tkns  Output tokens, will have parts of the string referenced as
 *              the name and value.
 * @param buf   String representation of a token pair (in effect
 *              "name=value"); will be modified and referenced in the
 *              resulting token pair.
 *
 * @return True if parsed successfully, false otherwise.
 */
extern bool hidrd_opt_tkns_parse(hidrd_opt_tkns *tkns, char *buf);

/**
 * Format the string representation of an option token pair (in effect
 * "name=value").
 *
 * @param tkns  Option token pair to format.
 *
 * @return The string representation of the option token pair, or NULL, if
 *         failed to allocate memory.
 */
extern char *hidrd_opt_tkns_format(const hidrd_opt_tkns *tkns);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_OPT_TKNS_H__ */

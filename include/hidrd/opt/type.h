/** @file
 * @brief HID report descriptor - option type
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

#ifndef __HIDRD_OPT_TYPE_H__
#define __HIDRD_OPT_TYPE_H__

#include <stdbool.h>
#include "hidrd/opt/value.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Option value type */
typedef enum hidrd_opt_type {
    HIDRD_OPT_TYPE_STRING   = 's',  /**< String  */
    HIDRD_OPT_TYPE_BOOLEAN  = 'b',  /**< Boolean */
} hidrd_opt_type;

/**
 * Check if an option type is valid.
 *
 * @param type  Option type to check.
 *
 * @return True if the type is valid, false otherwise.
 */
static inline bool
hidrd_opt_type_valid(hidrd_opt_type type)
{
    switch (type)
    {
        case HIDRD_OPT_TYPE_STRING:
        case HIDRD_OPT_TYPE_BOOLEAN:
            return true;
        default:
            return false;
    }
}

/**
 * Parse a string as a string value (simply reference it).
 *
 * @param pval  Location for resulting string pointer.
 * @param str   String to parse as a string value.
 *
 * @return True if parsed successfully, false otherwise.
 */
extern bool hidrd_opt_type_parse_string(const char **pval, const char *str);

/**
 * Parse a string as a boolean value.
 *
 * @param pval  Location for resulting value.
 * @param str   String to parse as a boolean value.
 *
 * @return True if parsed successfully, false otherwise.
 */
extern bool hidrd_opt_type_parse_boolean(bool *pval, const char *str);

/**
 * Parse a string as a value of specified type.
 *
 * @param type  Value type to parse accordingly.
 * @param pval  Location for resulting value.
 * @param str   String to parse as a value of @e type type.
 *
 * @return True if parsed successfully, false otherwise.
 */
extern bool
hidrd_opt_type_parse_value(hidrd_opt_type   type,
                           hidrd_opt_value *pval,
                           const char      *str);

/**
 * Format a string representation of a string value (simply duplicate it).
 *
 * @param val  String value to format.
 *
 * @return Dynamically allocated string representation of the value, or
 *         NULL, if failed to allocate.
 */
extern char *hidrd_opt_type_format_string(const char *val);

/**
 * Format a string representation of a boolean value ("yes" or "no").
 *
 * @param val  Boolean value to format.
 *
 * @return Dynamically allocated string representation of the value, or
 *         NULL, if failed to allocate.
 */
extern char *hidrd_opt_type_format_boolean(bool val);

/**
 * Format a string representation of a value of specified type.
 *
 * @param type  Value type to format accordingly.
 * @param pval  Pointer to a value to format.
 *
 * @return Dynamically allocated string representation of the value, or
 *         NULL, if failed to allocate.
 */
extern char *hidrd_opt_type_format_value(hidrd_opt_type         type,
                                         const hidrd_opt_value *pval);

/**
 * Compare two boolean values.
 *
 * @param a Left-hand operand.
 * @param b Right-hand operand.
 *
 * @return 0 if values are equal, -1 if @e a less than @e b, 1 otherwise.
 */
extern int hidrd_opt_type_cmp_boolean(bool a, bool b);

/**
 * Compare two string values.
 *
 * @param a Left-hand operand.
 * @param b Right-hand operand.
 *
 * @return 0 if values are equal, -1 if @e a less than @e b, 1 otherwise.
 */
extern int hidrd_opt_type_cmp_string(const char *a, const char *b);

/**
 * Compare two values of specified type.
 *
 * @param a Left-hand operand.
 * @param b Right-hand operand.
 *
 * @return 0 if values are equal, -1 if @e a less than @e b, 1 otherwise.
 */
extern int hidrd_opt_type_cmp_value(hidrd_opt_type          type,
                                    const hidrd_opt_value  *a,
                                    const hidrd_opt_value  *b);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_OPT_TYPE_H__ */

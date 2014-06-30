/** @file
 * @brief HID report descriptor - option specification
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
 * The token pair representation of the option specification is the
 * following:
 *
 * Name token is the option token. Value token contains the rest of the
 * specification in the following format:
 *
 *       TYPE ['?' DEFAULT_VALUE] ['\'' DESCRIPTION]
 *       TYPE is a hidrd_opt_type value. DEFAULT_VALUE is a string
 *       representation of the value. If there is no DEFAULT_VALUE part, the
 *       option is considered mandatory. DESCRIPTION is the human-readable
 *       option description.
 *
 */

#ifndef __HIDRD_OPT_SPEC_H__
#define __HIDRD_OPT_SPEC_H__

#include "hidrd/opt/tkns.h"
#include "hidrd/opt/type.h"
#include "hidrd/opt/value.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Option specification */
typedef struct hidrd_opt_spec {
    const char         *name;   /**< Name */
    hidrd_opt_type      type;   /**< Value type */
    bool                req;    /**< "Required" flag */
    hidrd_opt_value     dflt;   /**< Default value */
    const char         *desc;   /**< Human-readable description */
} hidrd_opt_spec;

/**
 * Check if an option specification is valid.
 *
 * @param spec  Option specification to check.
 *
 * @return True if the option specification is valid, false otherwise.
 */
extern bool hidrd_opt_spec_valid(const hidrd_opt_spec *spec);

/**
 * Parse an option token pair as an option specification, modifying the
 * value token and referencing strings from it.
 *
 * @param spec  Location for output option specification.
 * @param tkns  Option token pair to be parsed, modified and referenced in
 *              the resulting option specification.
 *
 * @return True if parsed successfully, false otherwise.
 */
extern bool hidrd_opt_spec_parse_tkns(hidrd_opt_spec       *spec,
                                      const hidrd_opt_tkns *tkns);

/**
 * Format the option token pair representation of an option specification.
 *
 * @param opt   Output option token pair; will contain dynamically allocated
 *              string value token (which will need to be freed) and name
 *              referenced from the specification.
 * @param spec  Option specification to format.
 *
 * @return True, if formatted successfully, false if failed to allocate
 *         memory.
 */
extern bool hidrd_opt_spec_format_tkns(hidrd_opt_tkns          *tkns,
                                       const hidrd_opt_spec    *spec);

/**
 * Parse a string representation of an option specification (in effect, the
 * string representation of the token pair representation), modifying it and
 * referencing in the resulting specification.
 *
 * @param spec  Location for output option specification.
 * @param buf   String representation of the options specification; will be
 *              modified and referenced in the specification.
 *
 * @return True if parsed successfully, false otherwise.
 */
extern bool hidrd_opt_spec_parse(hidrd_opt_spec *spec, char *buf);
                                 
/**
 * Format a string representation of an option specification.
 *
 * @param spec  Option specification to format.
 *
 * @return Dynamically allocated string representation of the option
 *         specification, or NULL, if failed to allocate memory.
 */
extern char *hidrd_opt_spec_format(const hidrd_opt_spec *spec);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_OPT_SPEC_H__ */

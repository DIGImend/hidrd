/** @file
 * @brief HID report descriptor - stream initialization option
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

#include <stddef.h>
#include <assert.h>
#include <ctype.h>
#include <strings.h>
#include "hidrd/strm/opt.h"

bool
hidrd_strm_opt_get_bool(const hidrd_strm_opt *opt, bool dflt)
{
    const char *v;
    const char *p;
    bool        got_nonzero;

    assert(opt != NULL);

    v = opt->value;

    if (v == NULL || *v == '\0')
        return dflt;

#define MATCH(_token) (strcasecmp(v, #_token) == 0)
    if (MATCH(yes) || MATCH(true))
        return true;

    if (MATCH(no) || MATCH(false))
        return false;
#undef MATCH

    for (p = v, got_nonzero = false; *p != '\0'; p++)
    {
        if (!isdigit(*p))
            return false;
        if (*p != '0')
            got_nonzero = true;
    }

    return got_nonzero;
}

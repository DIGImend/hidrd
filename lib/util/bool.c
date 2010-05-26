/** @file
 * @brief HID report descriptor - utilities - boolean conversions
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

#include <assert.h>
#include <ctype.h>
#include <strings.h>
#include "hidrd/util/str.h"
#include "hidrd/util/tkn.h"
#include "hidrd/util/bool.h"


bool
hidrd_bool_from_str(bool *pvalue, const char *str)
{
    bool        value;
    const char *tkn;
    size_t      len;

    if (!hidrd_str_find_tkn(&tkn, &len, str))
        return false;

    do {
        if (hidrd_str_ncasecmpn("true", tkn, len) == 0 ||
            hidrd_str_ncasecmpn("yes", tkn, len) == 0 ||
            hidrd_str_ncasecmpn("on", tkn, len) == 0)
        {
            value = true;
            break;
        }

        if (hidrd_str_ncasecmpn("false", tkn, len) == 0 ||
            hidrd_str_ncasecmpn("no", tkn, len) == 0 ||
            hidrd_str_ncasecmpn("off", tkn, len) == 0)
        {
            value = false;
            break;
        }

        /* hidrd_tkn_strip should return non-zero length string */
        assert(len > 0);
        for (value = false; len > 0; len--, tkn++)
        {
            if (!isdigit(*tkn))
                return false;
            else if (*tkn != '0')
                value = true;
        }
    } while (0);

    if (pvalue != NULL)
        *pvalue = value;

    return true;
}

const char *
hidrd_bool_to_str(bool value)
{
    return value ? "true" : "false";
}



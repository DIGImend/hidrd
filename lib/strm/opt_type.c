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

#include <stddef.h>
#include <assert.h>
#include <ctype.h>
#include <strings.h>
#include "hidrd/strm/opt_type.h"


static bool
parse_string(const char **pval, const char *str)
{
    assert(pval != NULL);
    assert(str != NULL);

    *pval = str;

    return true;
}


static bool
parse_boolean(bool *pval, const char *str)
{
    const char *p;
    bool        got_nonzero;

    assert(pval != NULL);
    assert(str != NULL);

    if (*str == '\0')
        return false;

#define MATCH(_token) (strcasecmp(str, #_token) == 0)
    if (MATCH(yes) || MATCH(true))
    {
        *pval = true;
        return true;
    }

    if (MATCH(no) || MATCH(false))
    {
        *pval = false;
        return true;
    }
#undef MATCH

    for (p = str, got_nonzero = false; *p != '\0'; p++)
    {
        if (!isdigit(*p))
            return false;
        if (*p != '0')
            got_nonzero = true;
    }

    *pval = got_nonzero;
    return true;
}


bool
hidrd_strm_opt_type_parse_value(hidrd_strm_opt_type     type,
                                hidrd_strm_opt_value   *pval,
                                const char             *str)
{
    assert(hidrd_strm_opt_type_valid(type));
    assert(pval != NULL);
    assert(str != NULL);

    switch (type)
    {
#define MAP(_T, _t) \
    case HIDRD_STRM_OPT_TYPE_##_T:          \
        return parse_##_t(&pval->_t, str)

        MAP(STRING, string);
        MAP(BOOLEAN, boolean);

#undef MAP

        default:
            assert(!"Unknown type");
            return false;
    }
}



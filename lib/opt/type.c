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
#include <string.h>
#include <strings.h>
#include "hidrd/opt/type.h"


bool
hidrd_opt_type_parse_string(const char **pval, const char *str)
{
    assert(pval != NULL);
    assert(str != NULL);

    *pval = str;

    return true;
}


bool
hidrd_opt_type_parse_boolean(bool *pval, const char *str)
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
hidrd_opt_type_parse_value(hidrd_opt_type   type,
                           hidrd_opt_value *pval,
                           const char      *str)
{
    assert(hidrd_opt_type_valid(type));
    assert(pval != NULL);
    assert(str != NULL);

    switch (type)
    {
#define MAP(_T, _t) \
    case HIDRD_OPT_TYPE_##_T:                               \
        return hidrd_opt_type_parse_##_t(&pval->_t, str)

        MAP(STRING, string);
        MAP(BOOLEAN, boolean);

#undef MAP

        default:
            assert(!"Unknown type");
            return false;
    }
}


char *
hidrd_opt_type_format_string(const char *val)
{
    assert(val != NULL);

    return strdup(val);
}


char *
hidrd_opt_type_format_boolean(bool val)
{
    return val ? strdup("yes") : strdup("no");
}


char *
hidrd_opt_type_format_value(hidrd_opt_type          type,
                            const hidrd_opt_value  *pval)
{
    assert(hidrd_opt_type_valid(type));
    assert(pval != NULL);

    switch (type)
    {
#define MAP(_T, _t) \
    case HIDRD_OPT_TYPE_##_T:                       \
        return hidrd_opt_type_format_##_t(pval->_t)

        MAP(STRING, string);
        MAP(BOOLEAN, boolean);

#undef MAP

        default:
            assert(!"Unknown type");
            return NULL;
    }
}


int
hidrd_opt_type_cmp_boolean(bool a, bool b)
{
    return ((a == false) == (b == false)) ? 0 : ((a == false) ? -1 : 1);
}


int
hidrd_opt_type_cmp_string(const char *a, const char *b)
{
    assert(a != NULL);
    assert(b != NULL);

    return strcmp(a, b);
}


int
hidrd_opt_type_cmp_value(hidrd_opt_type         type,
                         const hidrd_opt_value *a,
                         const hidrd_opt_value *b)
{
    assert(hidrd_opt_type_valid(type));
    assert(a != NULL);
    assert(b != NULL);

    switch (type)
    {
#define MAP(_T, _t) \
    case HIDRD_OPT_TYPE_##_T:                           \
        return hidrd_opt_type_cmp_##_t(a->_t, b->_t)

        MAP(BOOLEAN, boolean);
        MAP(STRING, string);

#undef MAP

        default:
            assert(!"Unknown type");
            return 0;
    }
}

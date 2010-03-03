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

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include "hidrd/opt/tkns.h"


bool
hidrd_opt_tkns_parse(hidrd_opt_tkns *tkns, char *buf)
{
    char           *p;
    char           *next_p;
    char           *space       = NULL;
    const char     *name;
    const char     *value;

    assert(tkns != NULL);
    assert(buf != NULL);

#define GET_TOKEN(_name, _run_cond) \
    do {                                        \
        /* Skip leading space */                \
        for (p = next_p; isspace(*p); p++);     \
                                                \
        /* Remember token start */              \
        _name = p;                              \
                                                \
        /* While run condition is true */       \
        for (; (_run_cond) && *p != '\0'; p++)  \
        {                                       \
            /* Remember last space run start */ \
            if (isspace(*p))                    \
            {                                   \
                if (space == NULL)              \
                    space = p;                  \
            }                                   \
            else                                \
                space = NULL;                   \
        }                                       \
                                                \
        /* Proceed to next token */             \
        next_p = (*p == '\0') ? p : (p + 1);    \
                                                \
        /* Cut token */                         \
        if (space == NULL)                      \
            *p = '\0';                          \
        else                                    \
        {                                       \
            *space = '\0';                      \
            space = NULL;                       \
        }                                       \
    } while (0)

    next_p = buf;
    GET_TOKEN(name, (*p != '='));
    if (*next_p == '\0')
        value = "";
    else
        GET_TOKEN(value, true);

#undef GET_TOKEN

    if (!hidrd_opt_name_tkn_valid(name) ||
        !hidrd_opt_value_tkn_valid(value))
        return false;

    tkns->name = name;
    tkns->value = value;

    assert(hidrd_opt_tkns_valid(tkns));

    return true;
}


char *
hidrd_opt_tkns_format(const hidrd_opt_tkns *tkns)
{
    char   *result;

    assert(hidrd_opt_tkns_valid(tkns));

    if (asprintf(&result, "%s=%s", tkns->name, tkns->value) < 0)
        return NULL;

    return result;
}



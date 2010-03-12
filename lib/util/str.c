/** @file
 * @brief HID report descriptor - utilities - string operations
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
#include <stdio.h>
#include <stdlib.h>
#include "hidrd/util/str.h"


bool
hidrd_str_isblank(const char *str)
{
    assert(str != NULL);

    for (; *str != '\0'; str++)
        if (!isspace(*str))
            return false;
    return true;
}


char *
hidrd_str_uc_first(char *str)
{
    assert(str != NULL);

    if (*str >= 'a' && *str <= 'z')
        *str -= ('a' - 'A');

    return str;
}


char *
hidrd_str_apada(char *str)
{
    char   *padded;
    int     rc;

    assert(str != NULL);

    rc = asprintf(&padded, " %s ", str);

    free(str);

    return (rc >= 0) ? padded : NULL;
}


int
hidrd_str_ncasecmpn(const char  *str,
                    const char  *chunk,
                    size_t len)
{
    int rc;

    rc = strncasecmp(str, chunk, len);
    if (rc != 0)
        return rc;

    return (str[len] == '\0') ? 0 : 1;
}



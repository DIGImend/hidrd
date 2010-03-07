/** @file
 * @brief HID report descriptor - utilities - token conversions
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
#include <string.h>
#include "hidrd/util/tkn.h"


bool
hidrd_tkn_strip(const char **ptkn, size_t *plen, const char *str)
{
    const char *start;
    const char *end;
    const char *zero;
    size_t      len;

    assert(str != NULL);

    for (start = str; isspace(*start); start++);
    for (end = start; isalnum(*end) || *end == '_'; end++);
    len = end - start;
    if (len == 0)
        return false;
    for (zero = end; isspace(*zero); zero++);
    if (*zero != '\0')
        return false;

    if (ptkn != NULL)
        *ptkn = start;
    if (plen != NULL)
        *plen = len;

    return true;
}


bool
hidrd_tkn_to_num(uint32_t *pnum, const char *str, const hidrd_tkn_link *map)
{
    const char             *tkn;
    size_t                  len;
    const hidrd_tkn_link   *link;

    assert(str != NULL);
    assert(map != NULL);

    if (!hidrd_tkn_strip(&tkn, &len, str))
        return false;

    for (link = map; link->str != NULL; link++)
        if (strlen(link->str) == len &&
            strncasecmp(link->str, tkn, len) == 0)
        {
            if (pnum != NULL)
                *pnum = link->num;
            return true;
        }

    return false;
}


const char *
hidrd_tkn_from_num(uint32_t num, const hidrd_tkn_link *map)
{
    const hidrd_tkn_link   *link;

    assert(map != NULL);

    for (link = map; link->str != NULL; link++)
        if (link->num == num)
            return link->str;

    return NULL;
}



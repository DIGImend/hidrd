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
#include "hidrd/util/str.h"
#include "hidrd/util/tkn.h"


bool
hidrd_tkn_valid(const char *tkn)
{
    const char *p;

    if (tkn == NULL)
        return false;

    for (p = tkn; *p != '\0'; p++)
        if (!hidrd_char_istkn(*p))
            return false;

    return (p > tkn);
}


bool
hidrd_tkn_to_num(uint32_t *pnum, const char *str, const hidrd_tkn_link *map)
{
    const hidrd_tkn_link   *link;

    assert(str != NULL);
    assert(map != NULL);

    for (link = map; link->str != NULL; link++)
        if (strcasecmp(link->str, str) == 0)
        {
            if (pnum != NULL)
                *pnum = link->num;
            return true;
        }

    return false;
}


char *
hidrd_tkn_from_num(uint32_t num, const hidrd_tkn_link *map)
{
    const hidrd_tkn_link   *link;

    assert(map != NULL);

    for (link = map; link->str != NULL; link++)
        if (link->num == num)
            return strdup(link->str);

    return NULL;
}


bool
hidrd_tkn_hmnzbl(const char *tkn)
{
    const char *p;
    bool        u;

    assert(hidrd_tkn_valid(tkn));

    for (p = tkn, u = false; *p != '\0'; p++)
    {
        if (*p == '_')
        {
            if (p == tkn)
                return false;
            if (u)
                return false;
            u = true;
        }
        else
            u = false;
    }

    return !u;
}


bool
hidrd_tkn_hmnz_cap_valid(hidrd_tkn_hmnz_cap cap)
{
    switch (cap)
    {
        case HIDRD_TKN_HMNZ_CAP_NONE:
        case HIDRD_TKN_HMNZ_CAP_FWF:
        case HIDRD_TKN_HMNZ_CAP_WF:
        case HIDRD_TKN_HMNZ_CAP_ALL:
            return true;
        default:
            return false;
    }
}


char *
hidrd_tkn_hmnz(char *tkn, hidrd_tkn_hmnz_cap cap)
{
    hidrd_str_cp_set    set;

    assert(tkn != NULL);
    assert(hidrd_tkn_valid(tkn));
    assert(hidrd_tkn_hmnzbl(tkn));
    assert(hidrd_tkn_hmnz_cap_valid(cap));

    hidrd_str_crplc(tkn, '_', ' ');

    switch (cap)
    {
        case HIDRD_TKN_HMNZ_CAP_FWF:
            set = HIDRD_STR_CP_FIRST_WORD | HIDRD_STR_CP_WORD_FIRST;
            break;
        case HIDRD_TKN_HMNZ_CAP_WF:
            set = HIDRD_STR_CP_WORD_FIRST;
            break;
        case HIDRD_TKN_HMNZ_CAP_ALL:
            set = HIDRD_STR_CP_SET_ALL;
            break;
        default:
            return tkn;
    }

    return hidrd_str_cp_uc(tkn, hidrd_str_cp_match_and, &set);
}


char *
hidrd_tkn_ahmnz(const char *tkn, hidrd_tkn_hmnz_cap cap)
{
    assert(hidrd_tkn_valid(tkn));
    assert(hidrd_tkn_hmnzbl(tkn));
    assert(hidrd_tkn_hmnz_cap_valid(cap));

    return hidrd_tkn_hmnz(strdup(tkn), cap);
}



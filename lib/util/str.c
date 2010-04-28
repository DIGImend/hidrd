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
#include <string.h>
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
hidrd_str_uc(char *str)
{
    char   *p;

    assert(str != NULL);

    for (p = str; *p != '\0'; p++)
        if (*p >= 'a' && *p <= 'z')
            *p -= ('a' - 'A');

    return str;
}


char *
hidrd_str_lc(char *str)
{
    char   *p;

    assert(str != NULL);

    for (p = str; *p != '\0'; p++)
        if (*p >= 'A' && *p <= 'Z')
            *p += ('a' - 'A');

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


void
hidrd_str_cp_clsf_start(hidrd_str_cp_clsf *clsf, const char *str)
{
    assert(clsf != NULL);
    assert(str != NULL);

    memset(clsf, 0, sizeof(*clsf));
    clsf->p = str;
}


hidrd_str_cp_set
hidrd_str_cp_clsf_next(hidrd_str_cp_clsf *clsf, const char **pp)
{
    hidrd_str_cp_set    set     = HIDRD_STR_CP_SET_NONE;

    assert(clsf != NULL);

    if (pp != NULL)
        *pp = clsf->p;

    if (*clsf->p == '\0')
        return set;

    if (!clsf->got_char)
    {
        clsf->got_char = true;
        set |= HIDRD_STR_CP_FIRST;
    }

    if (hidrd_char_isword(*clsf->p))
    {
        set |= HIDRD_STR_CP_WORD;
        if (!clsf->word)
        {
            clsf->word = true;
            set |= HIDRD_STR_CP_WORD_FIRST;
        }
        if (!clsf->got_word)
            set |= HIDRD_STR_CP_FIRST_WORD;
    }
    else
    {
        set |= HIDRD_STR_CP_NON_WORD;
        if (clsf->word)
        {
            clsf->word = false;
            clsf->got_word = true;
        }
    }

    if (clsf->p[1] == '\0')
        set |= HIDRD_STR_CP_LAST;

    clsf->p++;

    return set;
}


bool
hidrd_str_cp_match_and(hidrd_str_cp_set set, void *data)
{
    hidrd_str_cp_set   *pset    = (hidrd_str_cp_set *)data;

    return (set & *pset) == *pset;
}


bool
hidrd_str_cp_match_or(hidrd_str_cp_set set, void *data)
{
    hidrd_str_cp_set   *pset    = (hidrd_str_cp_set *)data;

    return (set & *pset) != 0;
}


char *
hidrd_str_cp_proc(char                     *str,
                  hidrd_str_cp_match_fn    *match,
                  void                     *data,
                  hidrd_char_proc_fn       *proc)
{
    hidrd_str_cp_clsf   clsf;
    hidrd_str_cp_set    set;
    char               *p;

    assert(str != NULL);
    assert(match != NULL);

    hidrd_str_cp_clsf_start(&clsf, str);

    while ((set = hidrd_str_cp_clsf_next(&clsf, (const char **)&p)) !=
           HIDRD_STR_CP_SET_NONE)
        if ((*match)(set, data))
            *p = (*proc)(*p);

    return str;
}


char *
hidrd_str_crplc(char *str, char match, char rplc)
{
    for (; *str != '\0'; str++)
        if (*str == match)
            *str = rplc;
    return str;
}



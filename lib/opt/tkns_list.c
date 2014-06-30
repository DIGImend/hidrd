/** @file
 * @brief HID report descriptor - option token pair list
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
 */

#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include "hidrd/opt/tkns_list.h"

bool
hidrd_opt_tkns_list_valid(const hidrd_opt_tkns *list)
{
    if (list == NULL)
        return false;

    for (; list->name != NULL; list++)
        if (!hidrd_opt_tkns_valid(list))
            return false;

    return true;
}


size_t
hidrd_opt_tkns_list_len(const hidrd_opt_tkns *list)
{
    const hidrd_opt_tkns   *tkns;

    assert(hidrd_opt_tkns_list_valid(list));

    for (tkns = list; tkns->name != NULL; tkns++);

    return tkns - list;
}


static hidrd_opt_tkns *
hidrd_opt_tkns_list_new(void)
{
    hidrd_opt_tkns  *list;

    list = malloc(sizeof(*list));
    list->name = NULL;

    return list;
}


static bool
hidrd_opt_tkns_list_add(hidrd_opt_tkns **plist, const hidrd_opt_tkns *tkns)
{
    size_t          len;
    hidrd_opt_tkns *new_list;

    assert(plist != NULL);
    assert(hidrd_opt_tkns_list_valid(*plist));
    assert(hidrd_opt_tkns_valid(tkns));

    len = hidrd_opt_tkns_list_len(*plist);
    new_list = realloc(*plist, sizeof(*new_list) * (len + 2));
    if (new_list == NULL)
        return false;

    *plist = new_list;

    memcpy(&new_list[len], tkns, sizeof(*tkns));

    new_list[len + 1].name = NULL;

    return true;
}


hidrd_opt_tkns *
hidrd_opt_tkns_list_parse(char *buf)
{
    hidrd_opt_tkns *result          = NULL;
    hidrd_opt_tkns *list            = NULL;
    char           *next_tkns_buf;
    char           *tkns_buf;
    char           *p;
    bool            got_nonspc;
    hidrd_opt_tkns  tkns;

    list = hidrd_opt_tkns_list_new();
    if (list == NULL)
        goto cleanup;

    next_tkns_buf = buf;
    do {
        tkns_buf = next_tkns_buf;

        /*
         * Find next option terminator and check if there is anything except
         * whitespace before it
         */
        for (p = tkns_buf, got_nonspc = false; *p != ',' && *p != '\0'; p++)
            if (!isspace(*p))
                got_nonspc = true;

        /* If it is the end of the string */
        if (*p == '\0')
            next_tkns_buf = NULL;
        else
        {
            *p = '\0';
            next_tkns_buf = p + 1;
        }

        /* Parse and add the tokens, if any */
        if (got_nonspc &&
            (!hidrd_opt_tkns_parse(&tkns, tkns_buf) ||
             !hidrd_opt_tkns_list_add(&list, &tkns)))
            goto cleanup;
    } while (next_tkns_buf != NULL);

    result = list;
    list = NULL;
    assert(hidrd_opt_tkns_list_valid(result));

cleanup:

    free(list);

    return result;
}


char *
hidrd_opt_tkns_list_format(const hidrd_opt_tkns *tkns_list)
{
    char                   *result      = NULL;
    char                   *str         = NULL;
    char                   *new_str     = NULL;
    const hidrd_opt_tkns   *tkns;

    assert(hidrd_opt_tkns_list_valid(tkns_list));

    str = strdup("");
    if (str == NULL)
        goto cleanup;

    for (tkns = tkns_list; tkns->name != NULL; tkns++)
    {
        if (asprintf(&new_str,
                     ((tkns[1].name == NULL) ? "%s%s=%s" : "%s%s=%s,"),
                     str, tkns->name, tkns->value) < 0)
            goto cleanup;
        free(str);
        str = new_str;
        new_str = NULL;
    }

    result = str;
    str = NULL;

cleanup:

    free(new_str);
    free(str);

    return result;
}



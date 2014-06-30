/** @file
 * @brief HID report descriptor - option specification list
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
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include "hidrd/opt/list.h"
#include "hidrd/opt/spec_list.h"

bool
hidrd_opt_spec_list_valid(const hidrd_opt_spec *list)
{
    if (list == NULL)
        return false;

    for (; list->name != NULL; list++)
        if (!hidrd_opt_spec_valid(list))
            return false;

    return true;
}


size_t
hidrd_opt_spec_list_len(const hidrd_opt_spec *list)
{
    const hidrd_opt_spec   *spec;

    assert(hidrd_opt_spec_list_valid(list));

    for (spec = list; spec->name != NULL; spec++);

    return spec - list;
}


const hidrd_opt_spec *
hidrd_opt_spec_list_lkp(const hidrd_opt_spec *list,
                             const char                *name)
{
    assert(hidrd_opt_spec_list_valid(list));

    for (; list->name != NULL; list++)
        if (strcasecmp(list->name, name) == 0)
            return list;

    return NULL;
}


hidrd_opt_spec *
hidrd_opt_spec_list_parse_tkns_list(hidrd_opt_tkns *tkns_list)
{
    hidrd_opt_spec    *result      = NULL;
    hidrd_opt_spec    *spec_list   = NULL;
    hidrd_opt_spec    *spec;
    hidrd_opt_tkns    *tkns;

    assert(hidrd_opt_tkns_list_valid(tkns_list));

    spec_list = malloc(sizeof(*spec_list) *
                       (hidrd_opt_tkns_list_len(tkns_list) + 1));
    if (spec_list == NULL)
        goto cleanup;

    /* Parse every token pair */
    for (tkns = tkns_list, spec = spec_list;
         tkns->name != NULL;
         tkns++, spec++)
        if (!hidrd_opt_spec_parse_tkns(spec, tkns))
            goto cleanup;

    /* Terminate */
    spec->name = NULL;

    result = spec_list;
    spec_list = NULL;

    assert(hidrd_opt_spec_list_valid(result));
                                           
cleanup:

    free(spec_list);

    return result;
}


hidrd_opt_spec *
hidrd_opt_spec_list_parse(char *buf)
{
    hidrd_opt_tkns    *tkns_list;
    hidrd_opt_spec    *spec_list;

    assert(buf != NULL);

    tkns_list = hidrd_opt_tkns_list_parse(buf);
    if (tkns_list == NULL)
        return NULL;

    spec_list = hidrd_opt_spec_list_parse_tkns_list(tkns_list);

    free(tkns_list);

    return spec_list;
}


hidrd_opt_tkns *
hidrd_opt_spec_list_format_tkns_list(const hidrd_opt_spec *spec_list)
{
    hidrd_opt_tkns *result      = NULL;
    size_t          len;
    hidrd_opt_tkns *tkns_list   = NULL;
    size_t          i           = 0;

    assert(hidrd_opt_spec_list_valid(spec_list));

    len = hidrd_opt_spec_list_len(spec_list);
    tkns_list = malloc(sizeof(*tkns_list) * (len + 1));
    if (tkns_list == NULL)
        goto cleanup;

    for (; i < len; i++)
        if (!hidrd_opt_spec_format_tkns(&tkns_list[i], &spec_list[i]))
            goto cleanup;

    /* Terminate */
    tkns_list[i].name = NULL;

    /* Output */
    result = tkns_list;
    i = 0;
    tkns_list = NULL;

cleanup:

    while (i > 0)
        /* We made it so we free it - we know what we do */
        free((char *)tkns_list[--i].value);

    free(tkns_list);

    return result;
}


char *
hidrd_opt_spec_list_format(const hidrd_opt_spec *spec_list)
{
    char           *result      = NULL;
    hidrd_opt_tkns *tkns_list   = NULL;

    assert(hidrd_opt_spec_list_valid(spec_list));

    /* Format the specification list as a token pair list */
    tkns_list = hidrd_opt_spec_list_format_tkns_list(spec_list);
    if (tkns_list == NULL)
        goto cleanup;

    /* Format token pair list as a string */
    result = hidrd_opt_tkns_list_format(tkns_list);

cleanup:

    if (tkns_list != NULL)
    {
        hidrd_opt_tkns *tkns;

        for (tkns = tkns_list; tkns->name != NULL; tkns++)
            /* We made it so we free it - we know what we do */
            free((char *)tkns->value);

        free(tkns_list);
    }

    return result;
}



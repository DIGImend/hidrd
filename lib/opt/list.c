/** @file
 * @brief HID report descriptor - option list
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
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include "hidrd/opt/list.h"


bool
hidrd_opt_list_valid(const hidrd_opt *list)
{
    if (list == NULL)
        return false;

    for (; list->name != NULL; list++)
        if (!hidrd_opt_valid(list))
            return false;

    return true;
}


bool
hidrd_opt_list_empty(const hidrd_opt *list)
{
    assert(hidrd_opt_list_valid(list));

    return list->name == NULL;
}


size_t
hidrd_opt_list_len(const hidrd_opt *list)
{
    const hidrd_opt   *opt;

    assert(hidrd_opt_list_valid(list));

    for (opt = list; opt->name != NULL; opt++);

    return opt - list;
}


const hidrd_opt *
hidrd_opt_list_lkp(const hidrd_opt *list, const char *name)
{
    assert(hidrd_opt_list_valid(list));
    assert(hidrd_opt_name_tkn_valid(name));

    for (; list->name != NULL; list++)
        if (strcasecmp(list->name, name) == 0)
            return list;

    return NULL;
}


bool
hidrd_opt_list_get_boolean(const hidrd_opt *list,
                           const char      *name)
{
    assert(hidrd_opt_list_valid(list));
    assert(hidrd_opt_name_tkn_valid(name));

    return hidrd_opt_get_boolean(hidrd_opt_list_lkp(list, name));
}


const char *
hidrd_opt_list_get_string(const hidrd_opt  *list,
                          const char       *name)
{
    assert(hidrd_opt_list_valid(list));
    assert(hidrd_opt_name_tkn_valid(name));

    return hidrd_opt_get_string(hidrd_opt_list_lkp(list, name));
}


int32_t
hidrd_opt_list_get_s32(const hidrd_opt *list,
                       const char      *name)
{
    assert(hidrd_opt_list_valid(list));
    assert(hidrd_opt_name_tkn_valid(name));

    return hidrd_opt_get_s32(hidrd_opt_list_lkp(list, name));
}


uint32_t
hidrd_opt_list_get_u32(const hidrd_opt *list,
                       const char      *name)
{
    assert(hidrd_opt_list_valid(list));
    assert(hidrd_opt_name_tkn_valid(name));

    return hidrd_opt_get_u32(hidrd_opt_list_lkp(list, name));
}


hidrd_opt *
hidrd_opt_list_parse_tkns_list(const hidrd_opt_spec    *spec_list,
                               const hidrd_opt_tkns    *tkns_list)
{
    hidrd_opt              *result      = NULL;
    hidrd_opt              *opt_list    = NULL;
    hidrd_opt              *opt;
    const hidrd_opt_tkns   *tkns;
    const hidrd_opt_spec   *spec;

    assert(hidrd_opt_spec_list_valid(spec_list));
    assert(hidrd_opt_tkns_list_valid(tkns_list));

    /* Allocate output option list */
    opt_list = malloc(sizeof(*opt_list) *
                      (hidrd_opt_spec_list_len(spec_list) + 1));
    if (opt_list == NULL)
        goto cleanup;
    /* Begin with the first option */
    opt = opt_list;
    /* Keep it terminated */
    opt->name = NULL;

    /*
     * Convert each token pair
     */
    for (tkns = tkns_list; tkns->name != NULL; tkns++)
    {
        /* Lookup specification for this token name */
        spec = hidrd_opt_spec_list_lkp(spec_list, tkns->name);
        /* If there is no such specification */
        if (spec == NULL)
            goto cleanup;

        /* Parse the value according to the specification type */
        if (!hidrd_opt_type_parse_value(spec->type, &opt->value,
                                        tkns->value))
            goto cleanup;

        /* Fill-in remaining fields */
        opt->name = spec->name;
        opt->type = spec->type;

        /* Proceed with the next option */
        opt++;
        /* Keep it terminated */
        opt->name = NULL;
    }

    /*
     * Check option presence, add missing
     */
    for (spec = spec_list; spec->name != NULL; spec++)
    {
        /* If the option is there */
        if (hidrd_opt_list_lkp(opt_list, spec->name) != NULL)
            continue;

        /* If option is required */
        if (spec->req)
            goto cleanup;

        /* Add the option with default value */
        opt->name   = spec->name;
        opt->type   = spec->type;
        opt->value  = spec->dflt;

        /* Proceed with the next option */
        opt++;
        /* Keep it terminated */
        opt->name = NULL;
    }

    /* Output */
    result = opt_list;
    opt_list = NULL;
    assert(hidrd_opt_list_valid(result));

cleanup:

    free(opt_list);

    return result;
}


hidrd_opt *
hidrd_opt_list_parse(const hidrd_opt_spec  *spec_list,
                     char                  *buf)
{
    hidrd_opt_tkns    *tkns_list;
    hidrd_opt    *opt_list;

    assert(buf != NULL);

    tkns_list = hidrd_opt_tkns_list_parse(buf);
    if (tkns_list == NULL)
        return NULL;

    opt_list = hidrd_opt_list_parse_tkns_list(spec_list, tkns_list);

    free(tkns_list);

    return opt_list;
}


hidrd_opt_tkns *
hidrd_opt_list_format_tkns_list(const hidrd_opt *opt_list)
{
    hidrd_opt_tkns *result      = NULL;
    size_t          len;
    hidrd_opt_tkns *tkns_list   = NULL;
    size_t          i           = 0;

    assert(hidrd_opt_list_valid(opt_list));

    len = hidrd_opt_list_len(opt_list);
    tkns_list = malloc(sizeof(*tkns_list) * (len + 1));
    if (tkns_list == NULL)
        goto cleanup;

    for (; i < len; i++)
        if (!hidrd_opt_format_tkns(&tkns_list[i], &opt_list[i]))
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
hidrd_opt_list_format(const hidrd_opt *opt_list)
{
    char           *result      = NULL;
    hidrd_opt_tkns *tkns_list   = NULL;

    assert(hidrd_opt_list_valid(opt_list));

    /* Format the optification list as a token pair list */
    tkns_list = hidrd_opt_list_format_tkns_list(opt_list);
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



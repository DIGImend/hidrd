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
 *
 * @(#) $Id$
 */

#include <assert.h>
#include <stdlib.h>
#include <strings.h>
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
hidrd_opt_spec_list_parse_opt_list(hidrd_opt *opt_list)
{
    hidrd_opt_spec    *result      = NULL;
    hidrd_opt_spec    *spec_list   = NULL;
    hidrd_opt_spec    *spec;
    hidrd_opt         *opt;

    assert(hidrd_opt_list_valid(opt_list));
    assert(hidrd_opt_list_uniform(opt_list,
                                       HIDRD_OPT_TYPE_STRING));

    spec_list = malloc(sizeof(*spec_list) *
                       (hidrd_opt_list_len(opt_list) + 1));
    if (spec_list == NULL)
        goto cleanup;

    /* Parse every option */
    for (opt = opt_list, spec = spec_list;
         opt->name != NULL; opt++, spec++)
        if (!hidrd_opt_spec_parse_opt(spec, opt))
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
    hidrd_opt         *opt_list;
    hidrd_opt_spec    *spec_list;

    assert(buf != NULL);

    opt_list = hidrd_opt_list_tknz(buf);
    if (opt_list == NULL)
        return NULL;

    spec_list = hidrd_opt_spec_list_parse_opt_list(opt_list);

    free(opt_list);

    return spec_list;
}


bool
hidrd_opt_spec_list_apply(const hidrd_opt_spec   *spec_list,
                               hidrd_opt              *opt_list)
{
    hidrd_opt             *opt;
    const hidrd_opt_spec  *spec;

    assert(hidrd_opt_list_valid(opt_list));
    assert(hidrd_opt_list_uniform(opt_list,
                                       HIDRD_OPT_TYPE_STRING));
    assert(hidrd_opt_spec_list_valid(spec_list));

    /* Convert each option */
    for (opt = opt_list; opt->name != NULL; opt++)
    {
        /* Lookup specification */
        spec = hidrd_opt_spec_list_lkp(spec_list, opt->name);
        /* If there is no such specification */
        if (spec == NULL)
            return false;

        /* If there is no value */
        if (*opt->value.string == '\0')
        {
            /* If value is required */
            if (spec->req)
                return false;
            else
                /* Use default value */
                opt->value = spec->dflt;
        }
        else
        {
            /* Parse the value according to the specification type */
            if (!hidrd_opt_type_parse_value(spec->type, &opt->value,
                                                 opt->value.string))
                return false;
            opt->type = spec->type;
        }
    }

    /* Check mandatory option presence */
    for (spec = spec_list; spec->name != NULL; spec++)
        if (spec->req &&
            hidrd_opt_list_lkp(opt_list, spec->name) == NULL)
            return false;

    return true;
}



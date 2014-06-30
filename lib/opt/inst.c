/** @file
 * @brief HID report descriptor - option
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
#include <stdio.h>
#include "hidrd/opt/name_tkn.h"
#include "hidrd/opt/value_tkn.h"
#include "hidrd/opt/inst.h"


bool
hidrd_opt_valid(const hidrd_opt *opt)
{
    if (opt == NULL)
        return false;

    /* Check name */
    if (!hidrd_opt_name_tkn_valid(opt->name))
        return false;

    /* Check type */
    if (!hidrd_opt_type_valid(opt->type))
        return false;

    /* Check value */
    switch (opt->type)
    {
        case HIDRD_OPT_TYPE_STRING:
            return hidrd_opt_value_tkn_valid(opt->value.string);
        default:
            return true;
    }
}


const char *
hidrd_opt_get_string(const hidrd_opt *opt)
{
    assert(hidrd_opt_valid(opt));
    assert(opt->type == HIDRD_OPT_TYPE_STRING);

    return opt->value.string;
}


bool
hidrd_opt_get_boolean(const hidrd_opt *opt)
{
    assert(hidrd_opt_valid(opt));
    assert(opt->type == HIDRD_OPT_TYPE_BOOLEAN);

    return opt->value.boolean;
}


int32_t
hidrd_opt_get_s32(const hidrd_opt *opt)
{
    assert(hidrd_opt_valid(opt));
    assert(opt->type == HIDRD_OPT_TYPE_S32);

    return opt->value.s32;
}


uint32_t
hidrd_opt_get_u32(const hidrd_opt *opt)
{
    assert(hidrd_opt_valid(opt));
    assert(opt->type == HIDRD_OPT_TYPE_U32);

    return opt->value.u32;
}


bool
hidrd_opt_format_tkns(hidrd_opt_tkns   *tkns,
                      const hidrd_opt  *opt)
{
    const char *value;

    assert(tkns != NULL);
    assert(hidrd_opt_valid(opt));

    value = hidrd_opt_type_format_value(opt->type, &opt->value);
    if (value == NULL)
        return false;

    tkns->name = opt->name;
    tkns->value = value;

    return true;
}


char *
hidrd_opt_format(const hidrd_opt *opt)
{
    char           *result  = NULL;
    hidrd_opt_tkns  tkns    = {.value = NULL};

    assert(hidrd_opt_valid(opt));

    if (!hidrd_opt_format_tkns(&tkns, opt))
        goto cleanup;

    result = hidrd_opt_tkns_format(&tkns);

cleanup:

    /* We made it so we free it - we know what we do */
    free((char *)tkns.value);

    return result;
}


bool
hidrd_opt_parse_tkns(hidrd_opt             *opt,
                     const hidrd_opt_spec  *spec,
                     const hidrd_opt_tkns  *tkns)
{
    assert(opt != NULL);
    assert(hidrd_opt_spec_valid(spec));
    assert(hidrd_opt_tkns_valid(tkns));

    /* If there is no value */
    if (*tkns->value == '\0')
    {
        /* If value is required */
        if (spec->req)
            /* Failed */
            return false;
        else
            /* Use default value */
            opt->value = spec->dflt;
    }
    else
    {
        /* Parse the value according to the specification type */
        if (!hidrd_opt_type_parse_value(spec->type,
                                        &opt->value,
                                        tkns->value))
            return false;
    }

    opt->name = tkns->name;
    opt->type = spec->type;

    assert(hidrd_opt_valid(opt));

    return true;
}


bool
hidrd_opt_parse(hidrd_opt              *opt,
                const hidrd_opt_spec   *spec,
                char                   *buf)
{
    hidrd_opt_tkns  tkns;

    assert(opt != NULL);
    assert(hidrd_opt_spec_valid(spec));
    assert(buf != NULL);

    return hidrd_opt_tkns_parse(&tkns, buf) &&
           hidrd_opt_parse_tkns(opt, spec, &tkns);
}



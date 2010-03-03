/** @file
 * @brief HID report descriptor - option specification
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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "hidrd/opt/spec.h"

bool
hidrd_opt_spec_valid(const hidrd_opt_spec *spec)
{
    return spec != NULL &&
           spec->name != NULL && *spec->name != '\0' &&
           hidrd_opt_type_valid(spec->type);
}


typedef enum parse_state {
    PARSE_STATE_NONE,
    PARSE_STATE_DFLT,
    PARSE_STATE_DESC
} parse_state;


bool
hidrd_opt_spec_parse_tkns(hidrd_opt_spec       *spec,
                          const hidrd_opt_tkns *tkns)
{
    char               *buf;
    hidrd_opt_type      type;
    parse_state         state;
    char               *p;
    char                c;
    const char         *str         = NULL;
    const char         *dflt_str    = NULL;
    const char         *desc        = "";
    hidrd_opt_value     dflt;

    assert(spec != NULL);
    assert(hidrd_opt_tkns_valid(tkns));

    /* Let's hope the caller knows what we're doing here */
    buf = (char *)tkns->value;

    type = (hidrd_opt_type)*buf;
    if (!hidrd_opt_type_valid(type))
        return false;

    /*
     * Extract default value and description
     */
    for (state = PARSE_STATE_NONE, p = buf + 1; ; p++)
    {
        c = *p;

        /* If it is not a marker/terminator */
        if (c != '?' && c != '\'' && c != '\0')
            continue;

        if (state == PARSE_STATE_DFLT)
            dflt_str = str;
        else if (state == PARSE_STATE_DESC)
            desc = str;

        if (c == '\0')
            break;

        state = (c == '?')
                    ? PARSE_STATE_DFLT
                    : PARSE_STATE_DESC;
        *p = '\0';
        p++;
        str = p;
    }

    /* Parse default value, if any */
    if (dflt_str == NULL)
        memset(&dflt, 0, sizeof(dflt));
    else if (!hidrd_opt_type_parse_value(type, &dflt, dflt_str))
        return false;

    /*
     * Output specification
     */
    spec->name = tkns->name;
    spec->type = type;
    spec->req = (dflt_str == NULL);
    spec->dflt = dflt;
    spec->desc = desc;

    assert(hidrd_opt_spec_valid(spec));

    return true;
}


bool
hidrd_opt_spec_parse(hidrd_opt_spec *spec, char *buf)
{
    hidrd_opt_tkns  tkns;

    assert(spec != NULL);
    assert(buf != NULL);

    return hidrd_opt_tkns_parse(&tkns, buf) &&
           hidrd_opt_spec_parse_tkns(spec, &tkns);
}


bool
hidrd_opt_spec_format_tkns(hidrd_opt_tkns          *tkns,
                           const hidrd_opt_spec    *spec)
{
    bool    result  = false;
    char   *str     = NULL;
    char   *new_str = NULL;
    char   *dflt    = NULL;

    assert(tkns != NULL);
    assert(hidrd_opt_spec_valid(spec));

    if (asprintf(&str, "%c", spec->type) < 0)
        goto cleanup;

#define APPENDF(_fmt, _args...) \
    do {                                                        \
        if (asprintf(&new_str, "%s" _fmt, str, ##_args) < 0)    \
            goto cleanup;                                       \
        free(str);                                              \
        str = new_str;                                          \
        new_str = NULL;                                         \
    } while (0)

    if (!spec->req)
    {
        dflt = hidrd_opt_type_format_value(spec->type, &spec->dflt);
        if (dflt == NULL)
            goto cleanup;
        APPENDF("?%s", dflt);
        free(dflt);
        dflt = NULL;
    }

    if (*spec->desc != '\0')
        APPENDF("'%s", spec->desc);

#undef APPENDF

    tkns->name  = spec->name;
    tkns->value = str;
    str = NULL;

    result = true;

cleanup:

    free(dflt);
    free(new_str);
    free(str);

    return result;
}


char *
hidrd_opt_spec_format(const hidrd_opt_spec *spec)
{
    char           *result  = NULL;
    hidrd_opt_tkns  tkns    = {.value = NULL};

    assert(hidrd_opt_spec_valid(spec));

    if (!hidrd_opt_spec_format_tkns(&tkns, spec))
        goto cleanup;

    result = hidrd_opt_tkns_format(&tkns);

cleanup:

    /* We made it so we free it - we know what we do */
    free((char *)tkns.value);

    return result;
}



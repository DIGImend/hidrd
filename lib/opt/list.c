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


bool
hidrd_opt_list_uniform(const hidrd_opt *list,
                       hidrd_opt_type   type)
{
    assert(hidrd_opt_list_valid(list));
    assert(hidrd_opt_type_valid(type));

    for (; list->name != NULL; list++)
        if (list->type != type)
            return false;

    return true;
}


const hidrd_opt *
hidrd_opt_list_lkp(const hidrd_opt *list, const char *name)
{
    assert(hidrd_opt_list_valid(list));

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
    assert(name != NULL);
    assert(*name != '\0');

    return hidrd_opt_get_boolean(hidrd_opt_list_lkp(list, name));
}


const char *
hidrd_opt_list_get_string(const hidrd_opt  *list,
                          const char       *name)
{
    assert(hidrd_opt_list_valid(list));
    assert(name != NULL);
    assert(*name != '\0');

    return hidrd_opt_get_string(hidrd_opt_list_lkp(list, name));
}


hidrd_opt *
hidrd_opt_list_new(void)
{
    hidrd_opt  *list;

    list = malloc(sizeof(*list));
    list->name = NULL;

    return list;
}


bool
hidrd_opt_list_add(hidrd_opt **plist, const hidrd_opt *opt)
{
    size_t      len;
    hidrd_opt  *new_list;

    assert(plist != NULL);
    assert(hidrd_opt_list_valid(*plist));
    assert(hidrd_opt_valid(opt));

    len = hidrd_opt_list_len(*plist);
    new_list = realloc(*plist, sizeof(*new_list) * (len + 2));
    if (new_list == NULL)
        return false;

    *plist = new_list;

    memcpy(&new_list[len], opt, sizeof(*opt));

    new_list[len + 1].name = NULL;

    return true;
}


/** Option list tokenizing state */
typedef enum tknz_state {
    TKNZ_STATE_NONE,    /**< Nothing found of this option */
    TKNZ_STATE_TOKEN,   /**< Processing token (name or value) */
    TKNZ_STATE_EQUALS   /**< Got equals */
} tknz_state;


hidrd_opt *
hidrd_opt_list_parse(char *buf)
{
    char           *p;
    char            c;
    hidrd_opt      *result      = NULL;
    hidrd_opt      *list        = NULL;
    hidrd_opt       new_opt     = {.type = HIDRD_OPT_TYPE_STRING};
    tknz_state      state       = TKNZ_STATE_NONE;
    const char     *name        = NULL;
    const char     *value       = "";
    char           *space       = NULL;

    list = hidrd_opt_list_new();
    if (list == NULL)
        goto cleanup;

    for (p = buf; ; p++)
    {
        c = *p;

        switch (state)
        {
            case TKNZ_STATE_NONE:
            case TKNZ_STATE_EQUALS:
                /* Skip space, stop on '\0' */
                if (isspace(c) || c == '\0')
                    break;

                if (state == TKNZ_STATE_NONE)
                    name = p;
                else
                    value = p;
                state = TKNZ_STATE_TOKEN;
                break;

            case TKNZ_STATE_TOKEN:
                /* Skip space, but remember the start */
                if (isspace(c))
                {
                    if (space == NULL)
                        space = p;
                    break;
                }

                /* Reset space start */
                space = NULL;

                /* If it is not a terminator */
                if (c != '=' && c != ',' && c != '\0')
                    break;

                /* Terminate token (name or value) */
                if (space == NULL)
                    *p = '\0';
                else
                {
                    *space = '\0';
                    space = NULL;
                }

                /*
                 * If it is not a name/value separator
                 * (i.e. a pair terminator) and there is name
                 */
                if (c != '=' && name != NULL)
                {
                    /* Commit name/value pair */
                    new_opt.name = name;
                    new_opt.value.string = value;
                    if (!hidrd_opt_list_add(&list, &new_opt))
                        goto cleanup;

                    name = NULL;
                    value = "";
                }

                /* Proceed */
                state = (c == '=')
                            ? TKNZ_STATE_EQUALS
                            : TKNZ_STATE_NONE;
                break;
        }

        if (c == '\0')
            break;
    }

    /* Output */
    result = list;
    list = NULL;

cleanup:

    free(list);

    return result;
}


char *
hidrd_opt_list_format(const hidrd_opt *opt_list)
{
    char            *result     = NULL;
    char            *str        = NULL;
    char            *new_str    = NULL;
    const hidrd_opt *opt;
    char            *opt_str    = NULL;

    assert(hidrd_opt_list_valid(opt_list));

    str = strdup("");
    if (str == NULL)
        goto cleanup;

    for (opt = opt_list; opt->name != NULL; opt++)
    {
        opt_str = hidrd_opt_format(opt);
        if (opt_str == NULL)
            goto cleanup;
        if (asprintf(&new_str,
                     ((opt[1].name == NULL) ? "%s%s" : "%s%s,"),
                     str, opt_str) < 0)
            goto cleanup;
        free(opt_str);
        opt_str = NULL;
        free(str);
        str = new_str;
        new_str = NULL;
    }

    result = str;
    str = NULL;

cleanup:

    free(opt_str);
    free(new_str);
    free(str);

    return result;
}



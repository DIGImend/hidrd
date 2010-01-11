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
#include <strings.h>
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


bool
hidrd_opt_list_grow(hidrd_opt **plist,
                    size_t     *palloc,
                    size_t      index)
{
    hidrd_opt *new_list;
    size_t          new_alloc;

    assert(plist != NULL);
    assert(palloc != NULL);

    if (index < *palloc)
        return true;

    new_alloc = (*palloc == 0) ? 4 : (*palloc * 2);
    new_list = realloc(*plist, sizeof(*new_list) * new_alloc);
    if (new_list == NULL)
        return false;

    *plist = new_list;
    *palloc = new_alloc;

    return true;
}


/** Option list tokenizing state */
typedef enum tknz_state {
    TKNZ_STATE_NONE,    /**< Nothing found of this option */
    TKNZ_STATE_TOKEN,   /**< Processing token (name or value) */
    TKNZ_STATE_EQUALS   /**< Got equals */
} tknz_state;


hidrd_opt *
hidrd_opt_list_tknz(char *buf)
{
    char           *p;
    char            c;
    hidrd_opt *result  = NULL;
    hidrd_opt *list;
    size_t          alloc   = 0;
    size_t          index   = 0;
    tknz_state      state   = TKNZ_STATE_NONE;
    const char     *name    = NULL;
    const char     *value   = "";
    char           *space   = NULL;

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

                /* Commit name/value pair (if any) */
                if (name != NULL)
                {
                    if (!hidrd_opt_list_grow(&list, &alloc, index))
                        goto cleanup;
                    list[index].name = name;
                    list[index].type = HIDRD_OPT_TYPE_STRING;
                    list[index].value.string = value;
                    index++;

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

    /* Terminate the list */
    if (!hidrd_opt_list_grow(&list, &alloc, index))
        goto cleanup;
    list[index].name    = NULL;

    /* Output */
    result = list;
    list = NULL;

cleanup:

    free(list);

    return result;
}



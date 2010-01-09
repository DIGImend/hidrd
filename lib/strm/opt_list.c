/** @file
 * @brief HID report descriptor - stream initialization option list
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
#include "hidrd/strm/opt_list.h"


bool
hidrd_strm_opt_list_grow(hidrd_strm_opt   **plist,
                         size_t            *palloc,
                         size_t             index)
{
    hidrd_strm_opt *new_list;
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


/** Option list parse state */
typedef enum parse_state {
    PARSE_STATE_NONE,   /**< Nothing found of this option */
    PARSE_STATE_TOKEN,  /**< Processing token (name or value) */
    PARSE_STATE_EQUALS  /**< Got equals */
} parse_state;


/** Parse option list string buffer */
hidrd_strm_opt *
hidrd_strm_opt_list_parse(char *buf)
{
    char           *p;
    char            c;
    hidrd_strm_opt *result  = NULL;
    hidrd_strm_opt *list;
    size_t          alloc   = 0;
    size_t          index   = 0;
    parse_state     state   = PARSE_STATE_NONE;
    const char     *name    = NULL;
    const char     *value   = NULL;
    char           *space   = NULL;

    for (p = buf; ; p++)
    {
        c = *p;

        switch (state)
        {
            case PARSE_STATE_NONE:
            case PARSE_STATE_EQUALS:
                /* Skip space, stop on '\0' */
                if (isspace(c) || c == '\0')
                    break;

                if (state == PARSE_STATE_NONE)
                    name = p;
                else
                    value = p;
                state = PARSE_STATE_TOKEN;
                break;

            case PARSE_STATE_TOKEN:
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
                    if (!hidrd_strm_opt_list_grow(&list, &alloc, index))
                        goto cleanup;
                    list[index].name = name;
                    list[index].value = value;
                    index++;

                    name = NULL;
                    value = NULL;
                }

                /* Proceed */
                state = (c == '=')
                            ? PARSE_STATE_EQUALS
                            : PARSE_STATE_NONE;
                break;
        }

        if (c == '\0')
            break;
    }

    /* Terminate the list */
    if (!hidrd_strm_opt_list_grow(&list, &alloc, index))
        goto cleanup;
    list[index].name    = NULL;

    /* Output */
    result = list;
    list = NULL;

cleanup:

    free(list);

    return result;
}


bool
hidrd_strm_opt_list_empty(const hidrd_strm_opt *list)
{
    assert(list != NULL);

    return list->name == NULL;
}


const hidrd_strm_opt *
hidrd_strm_opt_list_lkp(const hidrd_strm_opt *list, const char *name)
{
    assert(list != NULL);

    for (; list->name != NULL; list++)
        if (strcasecmp(list->name, name) == 0)
            return list;

    return NULL;
}


bool
hidrd_strm_opt_list_get_bool(const hidrd_strm_opt  *list,
                             const char            *name,
                             bool                   dflt)
{
    list = hidrd_strm_opt_list_lkp(list, name);

    return (list == NULL) ? dflt : hidrd_strm_opt_get_bool(list, true);
}



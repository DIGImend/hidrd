/** @file
 * @brief HID report descriptor - specification example sink - entry
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
#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "hidrd/fmt/spec/snk/ent.h"

bool
hidrd_spec_snk_ent_name_valid(const char *name)
{
    bool    got_alnum;

    if (name == NULL)
        return false;

    for (got_alnum = false; *name != '\0'; name++)
        if (isalnum(*name))
            got_alnum = true;
        else if (!isspace(*name))
            return false;

    return got_alnum;
}


bool
hidrd_spec_snk_ent_value_valid(const char *value)
{
    if (value == NULL)
        return false;

    for (; *value != '\0'; value++)
        if (!isprint(*value) ||
            *value == '(' || *value == ')' || *value == ';')
            return false;

    return true;
}


bool
hidrd_spec_snk_ent_comment_valid(const char *comment)
{
    if (comment == NULL)
        return false;

    for (; *comment != '\0'; comment++)
        if (!isprint(*comment))
            return false;

    return true;
}


bool
hidrd_spec_snk_ent_valid(const hidrd_spec_snk_ent *ent)
{
    return (ent != NULL) &&
           (ent->item == NULL || hidrd_item_valid(ent->item)) &&
           (ent->name == NULL ||
            hidrd_spec_snk_ent_name_valid(ent->name)) &&
           (ent->value == NULL ||
            hidrd_spec_snk_ent_value_valid(ent->value)) &&
           (ent->comment == NULL ||
            hidrd_spec_snk_ent_comment_valid(ent->comment)) &&
           /* Item and name should be either both present or both missing */
           ((ent->item != NULL && ent->name != NULL) ||
            (ent->item == NULL && ent->name == NULL)) &&
           /* Value is not allowed without an item and a name */
           (ent->value == NULL || ent->name != NULL);
}


hidrd_spec_snk_ent *
hidrd_spec_snk_ent_inita(hidrd_spec_snk_ent    *ent,
                         int                    depth,
                         hidrd_item            *item,
                         char                  *name,
                         char                  *value,
                         char                  *comment)
{
    assert(ent != NULL);
    assert(item == NULL || hidrd_item_valid(item));
    assert(name == NULL || hidrd_spec_snk_ent_name_valid(name));
    assert(value == NULL || hidrd_spec_snk_ent_value_valid(value));
    assert(comment == NULL || hidrd_spec_snk_ent_comment_valid(comment));
    /* Item and name should be either both present or both missing */
    assert((item != NULL && name != NULL) ||
           (item == NULL && name == NULL));
    /* Value is not allowed without an item and a name */
    assert(value == NULL || name != NULL);

    ent->depth = depth;
    ent->item = item;
    ent->name = name;
    ent->value = value;
    ent->comment = comment;

    assert(hidrd_spec_snk_ent_valid(ent));

    return ent;
}


hidrd_spec_snk_ent *
hidrd_spec_snk_ent_newa(int                 depth,
                        hidrd_item         *item,
                        char               *name,
                        char               *value,
                        char               *comment)
{
    return hidrd_spec_snk_ent_inita(malloc(sizeof(hidrd_spec_snk_ent)),
                                    depth, item, name, value, comment);
}


hidrd_spec_snk_ent *
hidrd_spec_snk_ent_init(hidrd_spec_snk_ent *ent,
                        int                 depth,
                        const hidrd_item   *item,
                        const char         *name,
                        const char         *value,
                        const char         *comment)
{
    assert(ent != NULL);
    assert(item == NULL || hidrd_item_valid(item));
    assert(name == NULL || hidrd_spec_snk_ent_name_valid(name));
    assert(value == NULL || hidrd_spec_snk_ent_value_valid(value));
    assert(comment == NULL || hidrd_spec_snk_ent_comment_valid(comment));
    /* Item and name should be either both present or both missing */
    assert((item != NULL && name != NULL) ||
           (item == NULL && name == NULL));
    /* Value is not allowed without an item and a name */
    assert(value == NULL || name != NULL);

    ent->depth = depth;
    ent->item = (item == NULL) ? NULL : hidrd_item_dup(item);
    ent->name = (name == NULL) ? NULL : strdup(name);
    ent->value = (value == NULL) ? NULL : strdup(value);
    ent->comment = (comment == NULL) ? NULL : strdup(comment);

    assert(hidrd_spec_snk_ent_valid(ent));

    return ent;
}


hidrd_spec_snk_ent *
hidrd_spec_snk_ent_new(int                  depth,
                       const hidrd_item    *item,
                       const char          *name,
                       const char          *value,
                       const char          *comment)
{
    return hidrd_spec_snk_ent_init(malloc(sizeof(hidrd_spec_snk_ent)),
                                   depth, item, name, value, comment);
}


void
hidrd_spec_snk_ent_clnp(hidrd_spec_snk_ent *ent)
{
    assert(hidrd_spec_snk_ent_valid(ent));

    free(ent->item);
    free(ent->name);
    free(ent->value);
    free(ent->comment);

    hidrd_spec_snk_ent_inita(ent, 0, NULL, NULL, NULL, NULL);
}


void
hidrd_spec_snk_ent_delete(hidrd_spec_snk_ent *ent)
{
    if (ent == NULL)
        return;

    assert(hidrd_spec_snk_ent_valid(ent));

    hidrd_spec_snk_ent_clnp(ent);
    free(ent);
}



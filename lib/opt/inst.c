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
 *
 * @(#) $Id$
 */

#include <assert.h>
#include <stdlib.h>
#include "hidrd/opt/inst.h"


bool
hidrd_opt_valid(const hidrd_opt *opt)
{
    if (opt == NULL)
        return false;

    /* Check name */
    if (opt->name == NULL || *opt->name == '\0')
        return false;

    /* Check type */
    if (!hidrd_opt_type_valid(opt->type))
        return false;

    /* Check value */
    switch (opt->type)
    {
        case HIDRD_OPT_TYPE_STRING:
            return opt->value.string != NULL;
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



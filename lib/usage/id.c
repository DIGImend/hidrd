/** @file
 * @brief HID report descriptor - usage ID
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
#include <stdio.h>
#include "hidrd/util/hex.h"
#include "hidrd/usage/id.h"


char *
hidrd_usage_id_to_hex(hidrd_usage_id id)
{
    char   *hex;

    assert(hidrd_usage_id_valid(id));

    if (asprintf(&hex, ((id <= UINT8_MAX) ? "%.2hX" : "%.4hX"), id) < 0)
        return NULL;

    return hex;
}


char *
hidrd_usage_id_to_bhex(hidrd_usage_id id)
{
    char   *bhex;

    assert(hidrd_usage_id_valid(id));

    if (asprintf(&bhex, ((id <= UINT8_MAX) ? "%.2hXh" : "%.4hXh"), id) < 0)
        return NULL;

    return bhex;
}


bool
hidrd_usage_id_from_hex(hidrd_usage_id *pid, const char *hex)
{
    assert(hex != NULL);

    return hidrd_hex_u16_from_str(pid, hex);
}


bool
hidrd_usage_id_from_bstr(hidrd_usage_id *pid, const char *str)
{
    assert(str != NULL);

    return hidrd_num_u16_from_bstr(pid, str);
}



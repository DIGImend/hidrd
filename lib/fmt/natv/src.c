/** @file
 * @brief HID report descriptor - native source type
 *
 * Copyright (C) 2009-2010 Nikolai Kondrashov
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

#include <errno.h>
#include <string.h>
#include "hidrd/fmt/natv/src.h"

static bool
hidrd_natv_src_valid(const hidrd_src *src)
{
    const hidrd_natv_src_inst  *natv_src    =
                                        (const hidrd_natv_src_inst *)src;

    return (src->type->size >= sizeof(hidrd_natv_src_inst)) &&
           (natv_src->pos <= src->size);
}


static const hidrd_item *
hidrd_natv_src_get(hidrd_src *src)
{
    hidrd_natv_src_inst    *natv_src    = (hidrd_natv_src_inst *)src;
    const hidrd_item       *item;
    size_t                  item_size;

    item = (hidrd_item *)((uint8_t *)src->buf + natv_src->pos);

    if (!hidrd_item_fits(item,
                         src->size - natv_src->pos, &item_size))
        return NULL;

    if (!hidrd_item_valid(item))
    {
        src->error = true;
        errno = EINVAL;
        return NULL;
    }

    natv_src->pos += item_size;

    return item;
}


const hidrd_src_type hidrd_natv_src = {
    .size   = sizeof(hidrd_natv_src_inst),
    .valid  = hidrd_natv_src_valid,
    .get    = hidrd_natv_src_get,
};



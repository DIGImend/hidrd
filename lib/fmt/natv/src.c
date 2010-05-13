/** @file
 * @brief HID report descriptor - native source
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


static char *
hidrd_natv_src_errmsg(const hidrd_src *src)
{
    const hidrd_natv_src_inst  *natv_src    =
                                    (const hidrd_natv_src_inst *)src;
    const char                 *msg;

    switch (natv_src->err)
    {
        case HIDRD_NATV_SRC_ERR_NONE:
            msg = "";
            break;
        case HIDRD_NATV_SRC_ERR_SHORT:
            msg = "item buffer ended prematurely";
            break;
        case HIDRD_NATV_SRC_ERR_INVALID:
            msg = "invalid item encountered";
            break;
        default:
            assert(!"Unknown error code");
            return NULL;
    }

    return strdup(msg);
}


static size_t
hidrd_natv_src_getpos(const hidrd_src *src)
{
    const hidrd_natv_src_inst  *natv_src    = (hidrd_natv_src_inst *)src;

    return natv_src->pos;
}


static char *
hidrd_natv_src_fmtpos(const hidrd_src *src, size_t pos)
{
    char   *str;

    (void)src;

    if (asprintf(&str, "offset %zu", pos) < 0)
        return NULL;

    return str;
}


static const hidrd_item *
hidrd_natv_src_get(hidrd_src *src)
{
    hidrd_natv_src_inst    *natv_src    = (hidrd_natv_src_inst *)src;
    const hidrd_item       *item;
    size_t                  item_size;

    item = (hidrd_item *)((uint8_t *)src->buf + natv_src->pos);

    if (natv_src->pos >= src->size)
        return NULL;

    if (!hidrd_item_fits(item,
                         src->size - natv_src->pos, &item_size))
    {
        src->error = true;
        natv_src->err = HIDRD_NATV_SRC_ERR_SHORT;
        return NULL;
    }

    if (!hidrd_item_valid(item))
    {
        src->error = true;
        natv_src->err = HIDRD_NATV_SRC_ERR_INVALID;
        return NULL;
    }

    natv_src->pos += item_size;

    return item;
}


const hidrd_src_type hidrd_natv_src = {
    .size   = sizeof(hidrd_natv_src_inst),
    .valid  = hidrd_natv_src_valid,
    .getpos = hidrd_natv_src_getpos,
    .fmtpos = hidrd_natv_src_fmtpos,
    .errmsg = hidrd_natv_src_errmsg,
    .get    = hidrd_natv_src_get,
};



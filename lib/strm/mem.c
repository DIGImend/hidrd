/** @file
 * @brief HID report descriptor - memory stream
 *
 * Copyright (C) 2009 Nikolai Kondrashov
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

#include "hidrd/strm_mem.h"

typedef struct hidrd_strm_mem_inst {
    hidrd_strm  strm;
    void       *buf;
    size_t      size;
    size_t      pos;
} hidrd_strm_mem_inst;

bool
hidrd_strm_mem_init(hidrd_strm *strm, va_list ap)
{
    hidrd_strm_mem_inst    *strm_mem    = (hidrd_strm_mem_inst *)strm;
    void                   *buf         = va_arg(ap, void *);
    size_t                  size        = va_arg(ap, size_t);

    if (buf == NULL && size != 0)
    {
        buf = malloc(size);
        if (buf == NULL)
            return false;
    }

    strm_mem->buf = buf;
    strm_mem->size = size;
    strm_mem->pos = 0;

    return true;
}


bool
hidrd_strm_mem_valid(const hidrd_strm *strm)
{
    const hidrd_strm_mem_inst  *strm_mem    =
                                    (const hidrd_strm_mem_inst *)strm;

    return (strm_mem->size == 0 || strm_mem->buf != NULL) &&
           (strm_mem->pos <= strm_mem->size);
}


const hidrd_item *
hidrd_strm_mem_read(hidrd_strm *strm)
{
    hidrd_strm_mem_inst    *strm_mem    = (hidrd_strm_mem_inst *)strm;
    const hidrd_item       *item;
    size_t                  item_size;
    size_t                  new_pos;

    if (strm_mem->pos >= strm_mem->size)
        return NULL;

    item = (hidrd_item *)((uint8_t *)strm_mem->buf + strm_mem->pos);
    item_size = hidrd_item_size(item);
    if ((strm_mem->size - strm_mem->pos) < item_size ||
        !hidrd_item_valid(item))
    {
        strm->error = true;
        return NULL;
    }

    strm_mem->pos += item_size;

    return item;
}


const hidrd_strm_type hidrd_strm_mem {
    .size   = sizeof(hidrd_strm_mem_inst),
    .init   = hidrd_strm_mem_init,
} hidrd_strm_mem;



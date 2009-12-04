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


static bool
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


static bool
hidrd_strm_mem_valid(const hidrd_strm *strm)
{
    const hidrd_strm_mem_inst  *strm_mem    =
                                    (const hidrd_strm_mem_inst *)strm;

    return (strm_mem->size == 0 || strm_mem->buf != NULL) &&
           (strm_mem->pos <= strm_mem->size);
}


static const hidrd_item *
hidrd_strm_mem_read(hidrd_strm *strm)
{
    hidrd_strm_mem_inst    *strm_mem    = (hidrd_strm_mem_inst *)strm;
    const hidrd_item       *item;
    size_t                  item_size;

    item = (hidrd_item *)((uint8_t *)strm_mem->buf + strm_mem->pos);

    if (!hidrd_item_fits(item, strm_mem->size - strm_mem->pos, &item_size))
        return NULL;

    if (!hidrd_item_valid(item))
    {
        strm->error = true;
        return NULL;
    }

    strm_mem->pos += item_size;

    return item;
}


static bool
hidrd_strm_mem_write(hidrd_strm *strm, const hidrd_item *item)
{
    hidrd_strm_mem_inst    *strm_mem    = (hidrd_strm_mem_inst *)strm;
    size_t                  item_size;
    size_t                  new_pos;
    size_t                  new_size;
    void                   *new_buf;

    assert(hidrd_item_valid(item));

    item_size = hidrd_item_size(item);
    new_pos = strm_mem->pos + item_size;

    if (new_pos >= strm_mem->size)
    {
        new_size = (strm_mem->size < HIDRD_ITEM_MAX_SIZE * 2)
                        ? HIDRD_ITEM_MAX_SIZE * 4
                        : strm_mem->size * 2;
        new_buf = realloc(strm_mem->size, new_size);
        if (new_buf == NULL)
        {
            strm->error = true;
            return false;
        }
        strm_mem->buf = new_buf;
        strm_mem->size = new_size;
    }

    memcpy((uint8_t *)strm_mem->buf + strm_mem->pos, item, item_size);
    strm_mem->pos = new_pos;

    return true;
}


static bool
hidrd_strm_mem_flush(hidrd_strm *strm)
{
    hidrd_strm_mem_inst    *strm_mem    = (hidrd_strm_mem_inst *)strm;
    void                   *new_buf;

    /* Retension buffer */
    new_buf = realloc(strm_mem->buf, strm_mem->size);
    if (strm_mem->size != 0 && new_buf == NULL)
    {
        strm->error = 1;
        return false;
    }
    strm_mem->buf = new_buf;

    return true;
}


void
hidrd_strm_mem_clnp(hidrd_strm *strm)
{
    free(strm->buf);
    strm->buf   = NULL;
    strm->size  = 0;
    strm->pos   = 0;
}


const hidrd_strm_type hidrd_strm_mem {
    .size   = sizeof(hidrd_strm_mem_inst),
    .init   = hidrd_strm_mem_init,
    .valid  = hidrd_strm_mem_valid,
    .read   = hidrd_strm_mem_read,
    .write  = hidrd_strm_mem_write,
    .flush  = hidrd_strm_mem_flush,
    .clnp   = hidrd_strm_mem_clnp,
} hidrd_strm_mem;



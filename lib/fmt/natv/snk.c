/** @file
 * @brief HID report descriptor - native stream type
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

#include <errno.h>
#include <string.h>
#include "hidrd/strm/natv.h"
#include "hidrd/strm/inst.h"

static bool
init(hidrd_snk *snk)
{
    hidrd_natv_snk_inst    *natv_snk    = (hidrd_natv_snk_inst *)snk;

    void   *buf     = (snk->pbuf != NULL) ? *snk->pbuf : NULL;
    size_t  size    = (snk->psize != NULL) ? *snk->psize : 0;

    natv_snk->buf      = buf;
    natv_snk->size     = size;
    natv_snk->alloc    = size;
    natv_snk->pos      = 0;

    return true;
}


static bool
hidrd_natv_snk_init(hidrd_snk *snk, va_list ap)
{
    (void)ap;
    return init(snk);
}


static bool
hidrd_natv_snk_valid(const hidrd_snk *snk)
{
    const hidrd_natv_snk_inst  *natv_snk    =
                                    (const hidrd_natv_snk_inst *)snk;

    return (snk->type->size >= sizeof(hidrd_natv_snk_inst)) &&
           (natv_snk->size == 0 || natv_snk->buf != NULL) &&
           (natv_snk->pos <= natv_snk->size);
}


static bool
hidrd_natv_snk_put(hidrd_snk *snk, const hidrd_item *item)
{
    hidrd_natv_snk_inst    *natv_snk   = (hidrd_natv_snk_inst *)snk;
    size_t                  item_size;
    size_t                  new_pos;
    size_t                  new_alloc;
    void                   *new_buf;

    assert(hidrd_item_valid(item));

    item_size = hidrd_item_get_size(item);
    new_pos = natv_snk->pos + item_size;

    if (new_pos >= natv_snk->alloc)
    {
        new_alloc = (natv_snk->alloc < HIDRD_ITEM_MAX_SIZE * 2)
                        ? HIDRD_ITEM_MAX_SIZE * 4
                        : natv_snk->alloc * 2;
        new_buf = realloc(natv_snk->buf, new_alloc);
        if (new_buf == NULL)
        {
            snk->error = true;
            return false;
        }
        natv_snk->buf = new_buf;
        /* Sync user's buffer pointer */
        if (snk->pbuf != NULL)
            *snk->pbuf = new_buf;
        natv_snk->alloc = new_alloc;
    }

    memcpy((uint8_t *)natv_snk->buf + natv_snk->pos, item, item_size);
    if (new_pos > natv_snk->size)
        natv_snk->size = new_pos;
    natv_snk->pos = new_pos;

    return true;
}


static bool
hidrd_natv_snk_flush(hidrd_snk *snk)
{
    hidrd_natv_snk_inst   *natv_snk   = (hidrd_natv_snk_inst *)snk;
    void                   *new_buf;

    /* Retension buffer, if needed */
    if (natv_snk->alloc != natv_snk->size)
    {
        new_buf = realloc(natv_snk->buf, natv_snk->size);
        if (natv_snk->size != 0 && new_buf == NULL)
        {
            snk->error = 1;
            return false;
        }
        natv_snk->buf = new_buf;
        /* Sync user's buffer pointer */
        if (snk->pbuf != NULL)
            *snk->pbuf = new_buf;
        natv_snk->alloc = natv_snk->size;
    }

    /* Sync user's buffer size */
    if (snk->psize != NULL)
        *snk->psize = natv_snk->size;

    return true;
}


static void
hidrd_natv_snk_clnp(hidrd_snk *snk)
{
    hidrd_natv_snk_inst   *natv_snk   = (hidrd_natv_snk_inst *)snk;

    /* If the user owns the buffer */
    if (snk->pbuf != NULL)
        return;

    free(natv_snk->buf);
    natv_snk->buf      = NULL;
    natv_snk->size     = 0;
    natv_snk->alloc    = 0;
    natv_snk->pos      = 0;
}


const hidrd_snk_type hidrd_natv_snk = {
    .size   = sizeof(hidrd_natv_snk_inst),
    .init   = hidrd_natv_snk_init,
    .valid  = hidrd_natv_snk_valid,
    .put    = hidrd_natv_snk_put,
    .flush  = hidrd_natv_snk_flush,
    .clnp   = hidrd_natv_snk_clnp,
};



/** @file
 * @brief HID report descriptor - hex dump sink
 *
 * Copyright (C) 2014 Nikolai Kondrashov
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

#include "hidrd/fmt/hex/snk.h"

static bool
hidrd_hex_snk_init(hidrd_snk *snk, char **perr)
{
    hidrd_hex_snk_inst    *hex_snk    = (hidrd_hex_snk_inst *)snk;

    hidrd_buf_init(&hex_snk->buf);
    hex_snk->bytes = 0;
    hex_snk->err   = HIDRD_HEX_SNK_ERR_NONE;

    if (perr != NULL)
        *perr = strdup("");

    return true;
}


static bool
hidrd_hex_snk_initv(hidrd_snk *snk, char **perr, va_list ap)
{
    (void)ap;
    return hidrd_hex_snk_init(snk, perr);
}


static bool
hidrd_hex_snk_valid(const hidrd_snk *snk)
{
    const hidrd_hex_snk_inst  *hex_snk    =
                                    (const hidrd_hex_snk_inst *)snk;

    return (snk->type->size >= sizeof(hidrd_hex_snk_inst)) &&
           hidrd_buf_valid(&hex_snk->buf);
}


static char *
hidrd_hex_snk_errmsg(const hidrd_snk *snk)
{
    const hidrd_hex_snk_inst  *hex_snk    =
                                    (const hidrd_hex_snk_inst *)snk;
    const char                 *msg;

    switch (hex_snk->err)
    {
        case HIDRD_HEX_SNK_ERR_NONE:
            msg = "";
            break;
        case HIDRD_HEX_SNK_ERR_ALLOC:
            msg = "memory allocation failure";
            break;
        default:
            assert(!"Unknown error code");
            return NULL;
    }

    return strdup(msg);
}


static bool
hidrd_hex_snk_put(hidrd_snk *snk, const hidrd_item *item)
{
    hidrd_hex_snk_inst *hex_snk     = (hidrd_hex_snk_inst *)snk;
    size_t              n;
    const uint8_t      *p;

    assert(hidrd_item_valid(item));

    for (p = item, n = hidrd_item_get_size(item); n > 0; p++, n--) {
        if (!hidrd_buf_add_printf(&hex_snk->buf, " %.2hhx", *p) ||
            ((++hex_snk->bytes % HIDRD_HEX_SNK_COL_NUM == 0) &&
             !hidrd_buf_add_str(&hex_snk->buf, "\n"))) {
            hex_snk->err = HIDRD_HEX_SNK_ERR_ALLOC;
            return false;
        }
    }

    return true;
}


static bool
hidrd_hex_snk_flush(hidrd_snk *snk)
{
    hidrd_hex_snk_inst *hex_snk = (hidrd_hex_snk_inst *)snk;
    bool success                = false;
    bool terminated             = false;
    size_t new_size;
    void *new_buf               = NULL;

    if (hex_snk->bytes % HIDRD_HEX_SNK_COL_NUM != 0) {
        if (hidrd_buf_add_char(&hex_snk->buf, '\n'))
            terminated = true;
        else {
            hex_snk->err = HIDRD_HEX_SNK_ERR_ALLOC;
            goto cleanup;
        }
    }

    new_size = hex_snk->buf.len;

    if (snk->pbuf != NULL) {
        new_buf = malloc(new_size);
        if (new_size > 0 && new_buf == NULL) {
            hex_snk->err = HIDRD_HEX_SNK_ERR_ALLOC;
            goto cleanup;
        }
        memcpy(new_buf, hex_snk->buf.ptr, new_size);
        free(*snk->pbuf);
        *snk->pbuf = new_buf;
        new_buf = NULL;
    }

    if (snk->psize != NULL)
        *snk->psize = new_size;

    success = true;

cleanup:
    free(new_buf);
    if (terminated)
        hidrd_buf_del(&hex_snk->buf, 1);
    return success;
}


static void
hidrd_hex_snk_clnp(hidrd_snk *snk)
{
    hidrd_hex_snk_inst   *hex_snk   = (hidrd_hex_snk_inst *)snk;

    /* If the user owns the buffer */
    if (snk->pbuf != NULL)
        hidrd_buf_init(&hex_snk->buf);
    else
        hidrd_buf_clnp(&hex_snk->buf);

    hex_snk->bytes  = 0;
    hex_snk->err    = HIDRD_HEX_SNK_ERR_NONE;
}


const hidrd_snk_type hidrd_hex_snk = {
    .size   = sizeof(hidrd_hex_snk_inst),
    .initv  = hidrd_hex_snk_initv,
    .valid  = hidrd_hex_snk_valid,
    .errmsg = hidrd_hex_snk_errmsg,
    .put    = hidrd_hex_snk_put,
    .flush  = hidrd_hex_snk_flush,
    .clnp   = hidrd_hex_snk_clnp,
};



/** @file
 * @brief HID report descriptor - specification example sink
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

#include "hidrd/fmt/spec/snk.h"

static bool
init(hidrd_snk *snk, size_t indent)
{
    hidrd_spec_snk_inst    *spec_snk    = (hidrd_spec_snk_inst *)snk;
    hidrd_spec_snk_state   *state       = NULL;

    void   *buf     = (snk->pbuf != NULL) ? *snk->pbuf : NULL;
    size_t  size    = (snk->psize != NULL) ? *snk->psize : 0;

    /* Create item state table stack */
    state = malloc(sizeof(*state));
    if (state == NULL)
        goto failure;
    state->prev         = NULL;
    state->usage_page   = HIDRD_USAGE_PAGE_UNDEFINED;

    spec_snk->indent    = indent;

    spec_snk->depth     = 0;
    spec_snk->state     = 0;

    spec_snk->buf       = buf;
    spec_snk->size      = size;
    spec_snk->pos       = 0;

    return true;
}


static bool
hidrd_spec_snk_init(hidrd_snk *snk, va_list ap)
{
    size_t  indent  = va_arg(ap, size_t);

    return init(snk, indent);
}


#ifdef HIDRD_WITH_OPT
static const hidrd_opt_spec hidrd_spec_snk_opts_spec[] = {
    {.name  = "indent",
     .type  = HIDRD_OPT_TYPE_U32,
     .req   = false,
     .dflt  = {.u32 = 2},
     .desc  = "Number of indentation columns per nesting level"},
    {.name  = NULL}
};

static bool
hidrd_spec_snk_init_opts(hidrd_snk *snk, const hidrd_opt *list)
{
    return init(snk,
                hidrd_opt_list_get_u32(list, "indent"));
}
#endif /* HIDRD_WITH_OPT */


static bool
hidrd_spec_snk_valid(const hidrd_snk *snk)
{
    const hidrd_spec_snk_inst  *spec_snk    =
                                    (const hidrd_spec_snk_inst *)snk;

    return (snk->type->size >= sizeof(hidrd_spec_snk_inst)) &&
           xml_snk->state != NULL &&
           (spec_snk->size == 0 || spec_snk->buf != NULL) &&
           (spec_snk->pos <= spec_snk->size);
}


static bool
hidrd_spec_snk_put(hidrd_snk *snk, const hidrd_item *item)
{
    hidrd_spec_snk_inst    *spec_snk   = (hidrd_spec_snk_inst *)snk;

    assert(hidrd_item_valid(item));

    return true;
}


static bool
hidrd_spec_snk_flush(hidrd_snk *snk)
{
    hidrd_spec_snk_inst   *spec_snk   = (hidrd_spec_snk_inst *)snk;

    return true;
}


static void
hidrd_spec_snk_clnp(hidrd_snk *snk)
{
    hidrd_spec_snk_inst   *spec_snk   = (hidrd_spec_snk_inst *)snk;

    /* If the user owns the buffer */
    if (snk->pbuf != NULL)
        return;

    free(spec_snk->buf);
    spec_snk->buf      = NULL;
    spec_snk->size     = 0;
    spec_snk->pos      = 0;
}


const hidrd_snk_type hidrd_spec_snk = {
    .size       = sizeof(hidrd_spec_snk_inst),
    .init       = hidrd_spec_snk_init,
#ifdef HIDRD_WITH_OPT
    .init_opts  = hidrd_spec_snk_init_opts,
    .opts_spec  = hidrd_spec_snk_opts_spec,
#endif
    .valid      = hidrd_spec_snk_valid,
    .put        = hidrd_spec_snk_put,
    .flush      = hidrd_spec_snk_flush,
    .clnp       = hidrd_spec_snk_clnp,
};



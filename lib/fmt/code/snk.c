/** @file
 * @brief HID report descriptor - source code sink
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

#include "hidrd/cfg.h"
#include "hidrd/util/buf.h"
#include "hidrd/fmt/code/snk.h"

static bool
hidrd_code_snk_init(hidrd_snk *snk, char **perr,
                    size_t tabstop, bool comments, bool comments_comments)
{
    hidrd_code_snk_inst    *code_snk    = (hidrd_code_snk_inst *)snk;

    if (!hidrd_spec_snk_init(snk, perr, tabstop, false, comments_comments))
        return false;

    code_snk->comments = comments;

    return true;
}


static bool
hidrd_code_snk_initv(hidrd_snk *snk, char **perr, va_list ap)
{
    size_t  tabstop             = va_arg(ap, size_t);
    bool    comments            = (va_arg(ap, int) != 0);
    bool    comments_comments   = (va_arg(ap, int) != 0);

    return hidrd_code_snk_init(snk, perr,
                               tabstop, comments, comments_comments);
}


#ifdef HIDRD_WITH_OPT
static const hidrd_opt_spec hidrd_code_snk_opts_spec[] = {
    {.name  = "tabstop",
     .type  = HIDRD_OPT_TYPE_U32,
     .req   = false,
     .dflt  = {.u32 = 4},
     .desc  = "number of spaces per tab"},
    {.name  = "comments",
     .type  = HIDRD_OPT_TYPE_BOOLEAN,
     .req   = false,
     .dflt  = {.boolean = true},
     .desc  = "enable comments in specification example format"},
    {.name  = "comments_comments",
     .type  = HIDRD_OPT_TYPE_BOOLEAN,
     .req   = false,
     .dflt  = {.boolean = false},
     .desc  = "enable comments in specification example format comments"},
    {.name  = NULL}
};

static bool
hidrd_code_snk_init_opts(hidrd_snk *snk, char **perr, const hidrd_opt *list)
{
    return hidrd_code_snk_init(
                snk, perr,
                hidrd_opt_list_get_u32(list, "tabstop"),
                hidrd_opt_list_get_boolean(list, "comments"),
                hidrd_opt_list_get_boolean(list, "comments_comments"));
}
#endif /* HIDRD_WITH_OPT */


static bool
hidrd_code_snk_valid(const hidrd_snk *snk)
{
    return (snk->type->size >= sizeof(hidrd_code_snk_inst)) &&
           hidrd_spec_snk_valid(snk);
}


static bool
hidrd_code_snk_flush(hidrd_snk *snk)
{
    bool                            result      = false;
    hidrd_code_snk_inst            *code_snk    = (hidrd_code_snk_inst *)
                                                    snk;
    hidrd_spec_snk_inst            *spec_snk    = &code_snk->spec_snk;
    const hidrd_spec_snk_ent_list  *list        = &spec_snk->list;
    hidrd_spec_snk_ent             *p;
    size_t                          last_l      = 0;
    size_t                          l;
    hidrd_ttbl                     *tbl         = NULL;
    hidrd_buf                       buf         = HIDRD_BUF_EMPTY;
    uint8_t                        *item_p;
    size_t                          item_size;

    if (snk->pbuf != NULL)
    {
        free(*snk->pbuf);
        *snk->pbuf = NULL;
    }

    if (snk->psize != NULL)
        *snk->psize = 0;

    /* Find the last item */
    for (p = list->ptr, l = 0; l < list->len; p++, l++)
        if (p->name != NULL)
            last_l = l;

    /* If the comments are not requested */
    if (!code_snk->comments)
    {
        tbl = hidrd_ttbl_new();
        if (tbl == NULL)
            goto cleanup;
    }
    else
    {
        if (!hidrd_spec_snk_ent_list_to_tbl(&tbl, list,
                                            spec_snk->tabstop,
                                            spec_snk->dumps,
                                            spec_snk->comments))
            goto cleanup;

        /* Add comment end string column right after the spec comments */
        for (l = 0; l < list->len; l++)
            hidrd_ttbl_set(tbl, HIDRD_SPEC_SNK_ENT_LIST_CMNT_COL + 1, l,
                           "*/");
        /* Insert comment start column before the leftmost column */
        hidrd_ttbl_ins_cols(tbl, 0, 1);
        for (l = 0; l < list->len; l++)
            hidrd_ttbl_set(tbl, 0, l, "/*");

        /* Make room for our output */
        hidrd_ttbl_ins_cols(tbl, 0, 1);
    }

    /* Output the code */
    for (p = list->ptr, l = 0; l < list->len; p++, l++)
    {
        if (p->item == NULL)
            continue;

        for (item_size = hidrd_item_get_size(p->item), item_p = p->item;
             item_size > 0; item_size--, item_p++)
            if (!hidrd_buf_add_printf(&buf,
                                      (item_size == 1)
                                        ? ((l == last_l)
                                            ? "0x%.2hhX"
                                            : "0x%.2hhX,")
                                        : "0x%.2hhX, ",
                                      *item_p))
                goto cleanup;

        if (!hidrd_buf_add_span(&buf, '\0', 1))
            goto cleanup;
        hidrd_ttbl_set(tbl, 0, l, (const char *)buf.ptr);
        hidrd_buf_reset(&buf);
    }

    /* Render the table */
    result = hidrd_ttbl_render((char **)snk->pbuf, snk->psize, tbl,
                               spec_snk->tabstop);

cleanup:

    hidrd_buf_clnp(&buf);
    hidrd_ttbl_delete(tbl);

    spec_snk->err = result ? HIDRD_SPEC_SNK_ERR_NONE
                           : HIDRD_SPEC_SNK_ERR_ALLOC;

    return result;
}


const hidrd_snk_type hidrd_code_snk = {
    .size       = sizeof(hidrd_code_snk_inst),
    .initv      = hidrd_code_snk_initv,
#ifdef HIDRD_WITH_OPT
    .init_opts  = hidrd_code_snk_init_opts,
    .opts_spec  = hidrd_code_snk_opts_spec,
#endif
    .valid      = hidrd_code_snk_valid,
    .errmsg     = hidrd_spec_snk_errmsg,
    .put        = hidrd_spec_snk_put,
    .flush      = hidrd_code_snk_flush,
    .clnp       = hidrd_spec_snk_clnp,
};



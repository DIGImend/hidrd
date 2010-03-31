/** @file
 * @brief HID report descriptor - specification example sink - item entry
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
 * @(#) $Id: element.h 283 2010-03-20 12:58:33Z spb_nick $
 */

#include "item_ent.h"

bool
spec_snk_item_ent_nt_valid(spec_snk_item_ent_nt nt)
{
    switch (nt)
    {
        case SPEC_SNK_ITEM_ENT_NT_VALUE:
        case SPEC_SNK_ITEM_ENT_NT_COMMENT:
        case SPEC_SNK_ITEM_ENT_NT_NONE:
            return true;
        default:
            return false;
    }
}


bool
spec_snk_item_entvf(hidrd_spec_snk_inst    *spec_snk,
                    const char             *name_tkn,
                    va_list                 ap)
{
    bool    result  = false;
    bool    end     = false;
    char   *nl[2]   = {[SPEC_SNK_ITEM_ENT_NT_VALUE] = NULL,
                       [SPEC_SNK_ITEM_ENT_NT_COMMENT] = NULL};

    assert(hidrd_tkn_valid(name_tkn));
    assert(hidrd_tkn_hmnzbl(name_tkn));

    while (!end)
    {
        spec_snk_item_ent_nt    nt  = va_arg(ap, spec_snk_item_ent_nt);

        assert(spec_snk_item_ent_nt_valid(nt));

        if (nt == SPEC_SNK_ITEM_ENT_NT_NONE)
            end = true;
        else
        {
            hidrd_fmt_type  fmt = va_arg(ap, hidrd_fmt_type);
            char           *str;

            if (!hidrd_fmtpva(&str, fmt, &ap))
                goto cleanup;

            free(nl[nt]);
            nl[nt] = str;
        }
    }

    result = hidrd_spec_snk_ent_list_adda(
                &spec_snk->list,
                hidrd_spec_snk_ent_newa(
                    spec_snk->depth,
                    hidrd_tkn_ahmnz(name_tkn, HIDRD_TKN_HMNZ_CAP_WF),
                    nl[SPEC_SNK_ITEM_ENT_NT_VALUE],
                    nl[SPEC_SNK_ITEM_ENT_NT_COMMENT]));

    nl[SPEC_SNK_ITEM_ENT_NT_VALUE] = NULL;
    nl[SPEC_SNK_ITEM_ENT_NT_COMMENT] = NULL;

cleanup:

    while (!end)
    {
        spec_snk_item_ent_nt    nt  = va_arg(ap, spec_snk_item_ent_nt);

        assert(spec_snk_item_ent_nt_valid(nt));

        if (nt == SPEC_SNK_ITEM_ENT_NT_NONE)
            end = true;
        else
        {
            hidrd_fmt_type  fmt = va_arg(ap, hidrd_fmt_type);

            hidrd_fmtfreepv(fmt, &ap);
        }
    }

    free(nl[SPEC_SNK_ITEM_ENT_NT_VALUE]);
    free(nl[SPEC_SNK_ITEM_ENT_NT_COMMENT]);

    return result;
}


bool
spec_snk_item_entf(hidrd_spec_snk_inst *spec_snk,
                   const char          *name_tkn,
                   ...)
{
    va_list ap;
    bool    result;

    va_start(ap, name_tkn);
    result = spec_snk_item_entvf(spec_snk, name_tkn, ap);
    va_end(ap);

    return result;
}



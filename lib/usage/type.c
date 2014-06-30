/** @file
 * @brief HID report descriptor - usage types
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

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hidrd/cfg.h"
#include "hidrd/util/bit.h"
#include "hidrd/usage/type.h"


bool
hidrd_usage_type_valid(hidrd_usage_type type)
{
    uint8_t idx;
    
    if (type == 0)
        return false;

    for (idx = HIDRD_USAGE_TYPE_IDX_MIN;
         idx <= HIDRD_USAGE_TYPE_IDX_MAX;
         idx++)
    {
        if (type == 1)
            break;
        type >>= 1;
    }

    return false;
}


#ifdef HIDRD_WITH_NAMES
static const char *idx_name[HIDRD_USAGE_TYPE_IDX_NUM] = {
#define MAP(_TOKEN, _name) \
    [HIDRD_USAGE_TYPE_IDX_##_TOKEN] = _name
    MAP(LC,     "linear control"),
    MAP(OOC,    "on/off control"),
    MAP(MC,     "momentary control"),
    MAP(OSC,    "one-shot control"),
    MAP(RTC,    "re-trigger control"),
    MAP(SEL,    "selector"),
    MAP(SV,     "static value"),
    MAP(SF,     "static flag"),
    MAP(DV,     "dynamic value"),
    MAP(DF,     "dynamic flag"),
    MAP(NARY,   "named array"),
    MAP(CA,     "application collection"),
    MAP(CL,     "logical collection"),
    MAP(CP,     "physical collection"),
    MAP(US,     "usage switch"),
    MAP(UM,     "usage modifier")
#undef MAP
};

const char *
hidrd_usage_type_idx_name(hidrd_usage_type_idx idx)
{
    assert(hidrd_usage_type_idx_valid(idx));
    return idx_name[idx - HIDRD_USAGE_TYPE_IDX_MIN];
}

#endif

#ifdef HIDRD_WITH_TOKENS
/* Define type bit index <-> token conversion functions */
#define MAP(_N, _n) HIDRD_TKN_LINK(HIDRD_USAGE_TYPE_IDX_##_N, _n)
HIDRD_TKN_CONV_DEFS(usage_type_idx,
                    MAP(LC, LC),
                    MAP(OOC, OOC),
                    MAP(MC, MC),
                    MAP(OSC, OSC),
                    MAP(RTC, RTC),
                    MAP(SEL, Sel),
                    MAP(SV, SV),
                    MAP(SF, SF),
                    MAP(DV, DV),
                    MAP(DF, DF),
                    MAP(NARY, NAry),
                    MAP(CA, CA),
                    MAP(CL, CL),
                    MAP(CP, CP),
                    MAP(US, US),
                    MAP(UM, UM));
#undef MAP
#endif /* HIDRD_WITH_TOKENS */

#ifdef HIDRD_WITH_NAMES
char *
hidrd_usage_type_set_desc_str(hidrd_usage_type_set set)
{
    hidrd_usage_type_idx    i;
    char                   *str;
    char                   *new_str;

    assert(hidrd_usage_type_set_valid(set));

    str = strdup("");
    if (str == NULL)
        return NULL;

    for (i = HIDRD_USAGE_TYPE_IDX_MIN; i <= HIDRD_USAGE_TYPE_IDX_MAX; i++)
    {
        if (HIDRD_BIT_GET(set, i))
        {
            if (*str == '\0')
            {
                new_str = strdup(hidrd_usage_type_idx_name(i));
                if (new_str == NULL)
                    goto failure;
            }
            else if (asprintf(&new_str, "%s, %s", str, new_str) < 0)
                goto failure;
            free(str);
            str = new_str;
        }
    }

    return str;

failure:

    free(str);

    return NULL;
}
#endif /* HIDRD_WITH_NAMES */


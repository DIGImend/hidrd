/** @file
 * @brief HID report descriptor - unit value
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

#include "hidrd/util/dec.h"
#include "hidrd/util/str.h"
#include "hidrd/util/tkn.h"
#include "hidrd/util/unit.h"


char *
hidrd_unit_system_to_dec(hidrd_unit_system system)
{
    assert(hidrd_unit_system_valid(system));
    return hidrd_dec_u32_to_str(system);
}


bool
hidrd_unit_system_from_dec(hidrd_unit_system *psystem, const char *dec)
{
    uint32_t    system;

    assert(dec != NULL);

    if (!hidrd_dec_u32_from_str(&system, dec))
        return false;

    if (psystem != NULL)
        *psystem = system;

    return true;
}


char *
hidrd_unit_exp_to_str(hidrd_unit_exp exp)
{
    assert(hidrd_unit_exp_valid(exp));
    return hidrd_dec_s32_to_str(hidrd_unit_exp_to_int(exp));
}


bool
hidrd_unit_exp_from_str(hidrd_unit_exp *pexp, const char *str)
{
    int32_t exp_int;

    assert(str != NULL);

    if (!hidrd_dec_s32_from_str(&exp_int, str))
        return false;

    if (!hidrd_unit_exp_valid_int(exp_int))
        return false;

    if (pexp != NULL)
        *pexp = hidrd_unit_exp_from_int(exp_int);

    return true;
}


#ifdef HIDRD_WITH_TOKENS
const char *
hidrd_unit_system_to_token(hidrd_unit_system system)
{
    assert(hidrd_unit_system_valid(system));

    switch (system)
    {
#define MAP(_NAME, _name) \
    case HIDRD_UNIT_SYSTEM_##_NAME: \
        return #_name

        MAP(NONE, none);
        MAP(SI_LINEAR, si_linear);
        MAP(SI_ROTATION, si_rotation);
        MAP(ENGLISH_LINEAR, english_linear);
        MAP(ENGLISH_ROTATION, english_rotation);
        MAP(VENDOR, vendor);

#undef MAP
        default:
            return NULL;
    }
}


bool
hidrd_unit_system_from_token(hidrd_unit_system *psystem, const char *token)
{
    hidrd_unit_system   system;
    const char         *tkn;
    size_t              len;

    assert(token != NULL);

    if (!hidrd_tkn_strip(&tkn, &len, token))
        return false;

#define MAP(_NAME, _name) \
    do {                                                \
        if (hidrd_str_ncasecmpn(#_name, tkn, len) == 0) \
        {                                               \
            system = HIDRD_UNIT_SYSTEM_##_NAME;         \
            goto found;                                 \
        }                                               \
    } while (0)

    MAP(NONE, none);
    MAP(SI_LINEAR, si_linear);
    MAP(SI_ROTATION, si_rotation);
    MAP(ENGLISH_LINEAR, english_linear);
    MAP(ENGLISH_ROTATION, english_rotation);
    MAP(VENDOR, vendor);

#undef MAP

    return false;

found:

    if (psystem != NULL)
        *psystem = system;

    return true;
}


char *
hidrd_unit_system_to_token_or_dec(hidrd_unit_system system)
{
    const char *token;

    assert(hidrd_unit_system_valid(system));

    token = hidrd_unit_system_to_token(system);

    return (token != NULL)
            ? strdup(token)
            : hidrd_unit_system_to_dec(system);
}


bool
hidrd_unit_system_from_token_or_dec(hidrd_unit_system  *psystem,
                                    const char         *token_or_dec)
{
    assert(token_or_dec != NULL);

    return hidrd_unit_system_from_token(psystem, token_or_dec) ||
           hidrd_unit_system_from_dec(psystem, token_or_dec);
}
#endif /* HIDRD_WITH_TOKENS */



/** @file
 * @brief HID report descriptor - usage pages
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

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "hidrd/usage/page.h"

#ifdef HIDRD_WITH_TOKENS
char *
hidrd_usage_page_to_token(hidrd_usage_page page)
{
    assert(hidrd_usage_page_valid(page));

    /* Map single entries */
    switch (page)
    {
#define MAP(_NAME) \
    case HIDRD_USAGE_PAGE_##_NAME:  \
        return strdup(#_NAME)

        MAP(UNDEFINED);
        MAP(DESKTOP);
        MAP(SIMULATION);
        MAP(VR);
        MAP(SPORT);
        MAP(GAME);
        MAP(DEVICE);
        MAP(KEYBOARD);
        MAP(LED);
        MAP(BUTTON);
        MAP(ORDINAL);
        MAP(TELEPHONY);
        MAP(CONSUMER);
        MAP(DIGITIZER);
        MAP(PID);
        MAP(UNICODE);
        MAP(ALPHANUMERIC_DISPLAY);
        MAP(MEDICAL);
        MAP(POS_BCS);
        MAP(POS_SCALE);
        MAP(POS_MSR);
        MAP(POS_RESERVED);
        MAP(CAMERA);
        MAP(ARCADE);

#undef MAP
        default:

#define MAP(_name, _NAME) \
    do {                                                            \
        if (hidrd_usage_page_##_name(page))                         \
        {                                                           \
            char   *token;                                          \
                                                                    \
            if (asprintf(&token,                                    \
                         (page < 0x100) ? "%s_%.2X" : "%s_%.4X",    \
                         #_NAME, page) >= 0)                        \
                return token;                                       \
            else                                                    \
                return NULL;                                        \
        }                                                           \
    } while (0)

            MAP(reserved,   RESERVED);
            MAP(monitor,    MONITOR);
            MAP(power,      POWER);
            MAP(vendor,     VENDOR);

#undef MAP

            assert(!"Unknown usage page");

            return NULL;
    }
}
#endif /* HIDRD_WITH_TOKENS */



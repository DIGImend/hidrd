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

#if 0

#if defined HIDRD_WITH_TOKENS || defined HIDRD_WITH_NAMES
typedef page_desc {
    hidrd_usage_page    page;
#ifdef HIDRD_WITH_TOKENS
    const char         *token;
#endif
#ifdef HIDRD_WITH_NAMES
    const char         *name;
#endif
} page_desc;

static const page_desc page_list[] = {

#ifdef HIDRD_WITH_TOKENS
#define PAGE_TOKEN(_token)  .token = _token,
#else
#define PAGE_TOKEN(_token)
#endif

#ifdef HIDRD_WITH_NAMES
#define PAGE_NAME(_name)    .name = _name,
#else
#define PAGE_NAME(_name)
#endif

#define PAGE(_TOKEN, _token, _name) \
    {.page = HIDRD_USAGE_PAGE_##_TOKEN,     \
     PAGE_TOKEN(#_token) PAGE_NAME(_name)}

    PAGE(UNDEFINED, undefined, "undefined"),
    PAGE(DESKTOP, desktop, "generic desktop controls"),
    PAGE(SIMULATION, simulation, "simulation controls"),
    PAGE(VR, vr, "virtual reality controls"),
    PAGE(SPORT, sport, "sport controls"),
    PAGE(GAME, game, "game controls"),
    PAGE(DEVICE, device, "generic device controls"),
    PAGE(KEYBOARD, keyboard, "Keyboard/keypad"),
    PAGE(LED, led, "LEDs"),
    PAGE(BUTTON, button, "button"),
    PAGE(ORDINAL, ordinal, "ordinal"),
    PAGE(TELEPHONY, telephony, "telephony"),
    PAGE(CONSUMER, consumer, "consumer"),
    PAGE(DIGITIZER, digitizer, "digitizer"),
    PAGE(PID, pid, "physical interface device"),
    PAGE(UNICODE, unicode, "Unicode"),
    PAGE(ALPHANUMERIC_DISPLAY, alphanumeric_display,
        "alphanumeric display"),
    PAGE(MEDICAL, medical, "medical instruments"),
    PAGE(POS_BCS, pos_bcs, "bar code scanner (POS devices)"),
    PAGE(POS_SCALE, pos_scale, "scale (POS devices)"),
    PAGE(POS_MSR, pos_msr,
         "magnetic stripe reading device (POS devices)"),
    PAGE(CAMERA, camera, "camera control"),
    PAGE(ARCADE, arcade, "arcade/coinop-related device"),

#undef PAGE

    {.page  = HIDRD_USAGE_PAGE_UNDEFINED,
     .token = NULL,
     .name  = NULL}
};

#endif /* defined HIDRD_WITH_TOKENS || defined HIDRD_WITH_NAMES */

static 
char *
hidrd_usage_page_to_token(hidrd_usage_page page)
{
    assert(hidrd_usage_page_valid(page));

    /* Map single entries */

    switch (page)
    {
#define MAP(_NAME, _name) \
    case HIDRD_USAGE_PAGE_##_NAME:  \
        return strdup(#_NAME)


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

#endif


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

#ifndef __HIDRD_USAGE_PAGE_H__
#define __HIDRD_USAGE_PAGE_H__

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum hidrd_usage_page {
    /** Undefined */
    HIDRD_USAGE_PAGE_UNDEFINED              = 0x0000,
    /** Generic desktop controls */
    HIDRD_USAGE_PAGE_DESKTOP                = 0x0001,
    /** Simulation controls */
    HIDRD_USAGE_PAGE_SIMULATION             = 0x0002,
    /** Virtual reality controls */
    HIDRD_USAGE_PAGE_VR                     = 0x0003,
    /** Sport controls */
    HIDRD_USAGE_PAGE_SPORT                  = 0x0004,
    /** Game controls */
    HIDRD_USAGE_PAGE_GAME                   = 0x0005,
    /** Generic device controls */
    HIDRD_USAGE_PAGE_DEVICE                 = 0x0006,
    /** Keyboard/keypad */
    HIDRD_USAGE_PAGE_KEYBOARD               = 0x0007,
    /** LED */
    HIDRD_USAGE_PAGE_LED                    = 0x0008,
    /** Button */
    HIDRD_USAGE_PAGE_BUTTON                 = 0x0009,
    /** Ordinal */
    HIDRD_USAGE_PAGE_ORDINAL                = 0x000A,
    /** Telephony */
    HIDRD_USAGE_PAGE_TELEPHONY              = 0x000B,
    /** Consumer */
    HIDRD_USAGE_PAGE_CONSUMER               = 0x000C,
    /** Digitizer */
    HIDRD_USAGE_PAGE_DIGITIZER              = 0x000D,
    /** Reserved (0E) */
    HIDRD_USAGE_PAGE_RESERVED_0E            = 0x000E,
    /** Physical interface device */
    HIDRD_USAGE_PAGE_PID                    = 0x000F,
    /** Unicode */
    HIDRD_USAGE_PAGE_UNICODE                = 0x0010,
    /** Reserved (11-13) - start */
    HIDRD_USAGE_PAGE_RESERVED_11_13_MIN     = 0x0011,
    /** Reserved (11-13) - end */
    HIDRD_USAGE_PAGE_RESERVED_11_13_MAX     = 0x0013,
    /** Alphanumeric display */
    HIDRD_USAGE_PAGE_ALPHANUMERIC_DISPLAY   = 0x0014,
    /** Reserved (15-3F) - start */
    HIDRD_USAGE_PAGE_RESERVED_15_3F_MIN     = 0x0015,
    /** Reserved (15-3F) - end */
    HIDRD_USAGE_PAGE_RESERVED_15_3F_MAX     = 0x003F,
    /** Medical instruments */
    HIDRD_USAGE_PAGE_MEDICAL                = 0x0040,
    /** Reserved (41-7F) - start */
    HIDRD_USAGE_PAGE_RESERVED_41_7F_MIN     = 0x0041,
    /** Reserved (41-7F) - end */
    HIDRD_USAGE_PAGE_RESERVED_41_7F_MAX     = 0x007F,
    /** Monitor pages - start */
    HIDRD_USAGE_PAGE_MONITOR_MIN            = 0x0080,
    /** Monitor pages - end */
    HIDRD_USAGE_PAGE_MONITOR_MAX            = 0x0083,
    /** Power pages - start */
    HIDRD_USAGE_PAGE_POWER_MIN              = 0x0084,
    /** Power pages - end */
    HIDRD_USAGE_PAGE_POWER_MAX              = 0x0087,
    /** Reserved (88-8B) - start */
    HIDRD_USAGE_PAGE_RESERVED_88_8B_MIN     = 0x0088,
    /** Reserved (88-8B) - end */
    HIDRD_USAGE_PAGE_RESERVED_88_8B_MAX     = 0x008B,
    /** Point of sale devices - bar code scanner */
    HIDRD_USAGE_PAGE_POS_BCS                = 0x008C,
    /** Point of sale devices - scale */
    HIDRD_USAGE_PAGE_POS_SCALE              = 0x008D,
    /** Point of sale devices - magnetic stripe reading devices */
    HIDRD_USAGE_PAGE_POS_MSR                = 0x008E,
    /** Point of sale devices - reserved */
    HIDRD_USAGE_PAGE_POS_RESERVED           = 0x008F,
    /** Camera control */
    HIDRD_USAGE_PAGE_CAMERA                 = 0x0090,
    /** Arcade */
    HIDRD_USAGE_PAGE_ARCADE                 = 0x0091,
    /** Reserved (92-FEFF) - start */
    HIDRD_USAGE_PAGE_RESERVED_92_FEFF_MIN   = 0x0092,
    /** Reserved (92-FEFF) - end */
    HIDRD_USAGE_PAGE_RESERVED_92_FEFF_MAX   = 0xFEFF,
    /** Vendor-defined - start */
    HIDRD_USAGE_PAGE_VENDOR_MIN             = 0xFF00,
    /** Vendor-defined - end */
    HIDRD_USAGE_PAGE_VENDOR_MAX             = 0xFFFF,
    /** Invalid page */
    HIDRD_USAGE_PAGE_INVALID                = 0x10000
} hidrd_usage_page;

#define HIDRD_USAGE_PAGE_MIN    0x0000
#define HIDRD_USAGE_PAGE_MAX    0xFFFF

#define HIDRD_USAGE_PAGE_POS_MIN    HIDRD_USAGE_PAGE_POS_BCS
#define HIDRD_USAGE_PAGE_POS_MAX    HIDRD_USAGE_PAGE_POS_RESERVED

#define HIDRD_USAGE_PAGE_TOP_LEVEL_MIN  0x0001
#define HIDRD_USAGE_PAGE_TOP_LEVEL_MAX  0x001F

static inline bool
hidrd_usage_page_valid(hidrd_usage_page page)
{
    return page <= HIDRD_USAGE_PAGE_MAX;
}

static inline bool
hidrd_usage_page_defined(hidrd_usage_page page)
{
    return page != HIDRD_USAGE_PAGE_UNDEFINED;
}

static inline bool
hidrd_usage_page_top_level(hidrd_usage_page page)
{
    return page >= HIDRD_USAGE_PAGE_TOP_LEVEL_MIN &&
           page <= HIDRD_USAGE_PAGE_TOP_LEVEL_MAX;
}

static inline bool
hidrd_usage_page_reserved(hidrd_usage_page page)
{
    return page == HIDRD_USAGE_PAGE_RESERVED_0E ||
           (page >= HIDRD_USAGE_PAGE_RESERVED_11_13_MIN &&
            page <= HIDRD_USAGE_PAGE_RESERVED_11_13_MAX) ||
           (page >= HIDRD_USAGE_PAGE_RESERVED_15_3F_MIN &&
            page <= HIDRD_USAGE_PAGE_RESERVED_15_3F_MAX) ||
           (page >= HIDRD_USAGE_PAGE_RESERVED_41_7F_MIN &&
            page <= HIDRD_USAGE_PAGE_RESERVED_41_7F_MAX) ||
           (page >= HIDRD_USAGE_PAGE_RESERVED_88_8B_MIN &&
            page <= HIDRD_USAGE_PAGE_RESERVED_88_8B_MAX) ||
           page == HIDRD_USAGE_PAGE_POS_RESERVED ||
           (page >= HIDRD_USAGE_PAGE_RESERVED_92_FEFF_MIN &&
            page <= HIDRD_USAGE_PAGE_RESERVED_92_FEFF_MAX);
}

static inline bool
hidrd_usage_page_vendor(hidrd_usage_page page)
{
    return page >= HIDRD_USAGE_PAGE_VENDOR_MIN &&
           page <= HIDRD_USAGE_PAGE_VENDOR_MAX;
}

static inline bool
hidrd_usage_page_monitor(hidrd_usage_page page)
{
    return page >= HIDRD_USAGE_PAGE_MONITOR_MIN &&
           page <= HIDRD_USAGE_PAGE_MONITOR_MAX;
}

static inline bool
hidrd_usage_page_power(hidrd_usage_page page)
{
    return page >= HIDRD_USAGE_PAGE_POWER_MIN &&
           page <= HIDRD_USAGE_PAGE_POWER_MAX;
}

static inline bool
hidrd_usage_page_pos(hidrd_usage_page page)
{
    return page >= HIDRD_USAGE_PAGE_POS_MIN &&
           page <= HIDRD_USAGE_PAGE_POS_MAX;
}

/**
 * Convert a usage page code to a string token.
 *
 * @param page  Usage page code.
 *
 * @return Dynamically allocated usage page string token or NULL if failed
 *         to allocate.
 */
extern char *hidrd_usage_page_to_token(hidrd_usage_page page);

/**
 * Convert a usage page string token to a code.
 *
 * @param token Usage page string token (case insensitive).
 *
 * @return Usage page code; will be invalid if the token is not recognized.
 */
extern hidrd_usage_page hidrd_usage_page_from_token(const char *token);

/**
 * Retrieve usage page name string (close to specification).
 *
 * @param page  Usage page code.
 *
 * @return Usage page name string.
 */
extern const char *hidrd_usage_page_name(hidrd_usage_page page);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_USAGE_PAGE_H__ */

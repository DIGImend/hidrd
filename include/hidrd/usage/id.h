/** @file
 * @brief HID report descriptor - usage ID
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

#ifndef __HIDRD_USAGE_ID_H__
#define __HIDRD_USAGE_ID_H__

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint16_t hidrd_usage_id;

#define HIDRD_USAGE_ID_UNDEFINED    0

#define HIDRD_USAGE_ID_MIN  0
#define HIDRD_USAGE_ID_MAX  UINT16_MAX

/**
 * Check if a usage ID is valid.
 *
 * @param id    Usage ID to check.
 *
 * @return True if the usage ID is valid, false otherwise.
 */
static inline bool
hidrd_usage_id_valid(hidrd_usage_id id)
{
    (void)id;
    return true;
}

/**
 * Check if a usage ID is valid.
 *
 * @param id    Usage ID to check.
 *
 * @return True if the usage ID is valid, false otherwise.
 */
static inline bool
hidrd_usage_id_top_level(hidrd_usage_id id)
{
    assert(hidrd_usage_id_valid(id));
    return (id >= 0x01) && (id <= 0x1F);
}

/**
 * Convert a usage ID to a hexadecimal code string.
 *
 * @param id    Usage ID.
 *
 * @return Dynamically allocated hexadecimal code string, or NULL, if failed
 *         to allocate memory.
 */
extern char *hidrd_usage_id_to_hex(hidrd_usage_id id);

/**
 * Convert a usage ID hexadecimal code string to usage ID.
 *
 * @param pid   Location for the resulting usage ID; wil not be modified in
 *              case of error; could be NULL.
 * @param hex   Hexadecimal code string.
 *
 * @return True if the hexadecimal string valid, false otherwise.
 */
extern bool hidrd_usage_id_from_hex(hidrd_usage_id *pid, const char *hex);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_USAGE_ID */

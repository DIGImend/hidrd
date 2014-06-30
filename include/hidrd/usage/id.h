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
 */

#ifndef __HIDRD_USAGE_ID_H__
#define __HIDRD_USAGE_ID_H__

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "hidrd/util/num.h"

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
 * Check if a usage ID is top-level.
 *
 * @param id    Usage ID to check.
 *
 * @return True if the usage ID is top-level, false otherwise.
 */
static inline bool
hidrd_usage_id_top_level(hidrd_usage_id id)
{
    assert(hidrd_usage_id_valid(id));
    return (id >= 0x01) && (id <= 0x1F);
}

/* Declare usage ID to numeric string conversion functions */
HIDRD_NUM_CONV_DECLS(usage_id);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_USAGE_ID */

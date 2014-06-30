/** @file
 * @brief HID report descriptor - usage ID description
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

#ifndef __HIDRD_USAGE_ID_DESC_H__
#define __HIDRD_USAGE_ID_DESC_H__

#include "hidrd/cfg.h"
#include "hidrd/usage/id.h"
#include "hidrd/usage/type.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Usage ID description */
typedef struct hidrd_usage_id_desc {
    hidrd_usage_id          value;      /**< Usage ID value */
    hidrd_usage_type_set    type_set;   /**< Type set (bitmask) */
#ifdef HIDRD_WITH_TOKENS
    const char             *token;      /**< Token */
#endif
#ifdef HIDRD_WITH_NAMES
    const char             *name;       /**< Name */
#endif
} hidrd_usage_id_desc;

/**
 * Check if a usage ID description is valid.
 *
 * @param desc  Usage ID description to check.
 *
 * @return True if the description is valid, false otherwise.
 */
extern bool hidrd_usage_id_desc_valid(const hidrd_usage_id_desc *desc);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_USAGE_ID_DESC */

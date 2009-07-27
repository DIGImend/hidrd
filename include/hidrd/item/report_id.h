/** @file
 * @brief HID report descriptor - report ID item
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

#ifndef __HIDRD_ITEM_REPORT_ID_H__
#define __HIDRD_ITEM_REPORT_ID_H__

#include "hidrd/item/global.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline bool
hidrd_item_report_id_value_valid(uint32_t value)
{
    return (value > 0) && (value <= UINT8_MAX);
}

HIDRD_ITEM_GLOBAL_FUNCS(report_id, REPORT_ID,
                        unsigned, uint32_t, uint8_t)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_REPORT_ID_H__ */

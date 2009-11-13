/** @file
 * @brief HID report descriptor items.
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

#ifndef __HIDRD_ITEM_H__
#define __HIDRD_ITEM_H__

#include "hidrd/item/collection.h"
#include "hidrd/item/delimiter.h"
#include "hidrd/item/designator_index.h"
#include "hidrd/item/designator_maximum.h"
#include "hidrd/item/designator_minimum.h"
#include "hidrd/item/end_collection.h"
#include "hidrd/item/feature.h"
#include "hidrd/item/input.h"
#include "hidrd/item/logical_maximum.h"
#include "hidrd/item/logical_minimum.h"
#include "hidrd/item/output.h"
#include "hidrd/item/physical_maximum.h"
#include "hidrd/item/physical_minimum.h"
#include "hidrd/item/pop.h"
#include "hidrd/item/push.h"
#include "hidrd/item/report_count.h"
#include "hidrd/item/report_id.h"
#include "hidrd/item/report_size.h"
#include "hidrd/item/string_index.h"
#include "hidrd/item/string_maximum.h"
#include "hidrd/item/string_minimum.h"
#include "hidrd/item/unit.h"
#include "hidrd/item/unit_exponent.h"
#include "hidrd/item/usage.h"
#include "hidrd/item/usage_maximum.h"
#include "hidrd/item/usage_minimum.h"
#include "hidrd/item/usage_page.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HIDRD_ITEM_MIN_SIZE HIDRD_ITEM_LONG_MAX_SIZE
#define HIDRD_ITEM_MAX_SIZE HIDRD_ITEM_LONG_MAX_SIZE

extern bool hidrd_item_size_valid(const hidrd_item *item, size_t size);

extern bool hidrd_item_valid(const hidrd_item *item);

extern size_t hidrd_item_get_size(const hidrd_item *item);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_BASIC_H__ */


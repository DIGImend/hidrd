/** @file
 * @brief HID report descriptor - usage page description
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
 * @(#) $Id: id.h 331 2010-04-01 20:05:18Z spb_nick $
 */

#include "hidrd/cfg.h"
#ifdef HIDRD_WITH_TOKENS
#include "hidrd/util/tkn.h"
#endif
#include "hidrd/usage/id_desc_list.h"
#include "hidrd/usage/page_desc.h"


bool
hidrd_usage_page_desc_valid(const hidrd_usage_page_desc *desc)
{
    return desc != NULL &&
           hidrd_usage_page_valid(desc->value) &&
#ifdef HIDRD_WITH_TOKENS
           hidrd_tkn_valid(desc->token) &&
#endif
#ifdef HIDRD_WITH_NAMES
           desc->name != NULL &&
#endif
           hidrd_usage_id_desc_list_valid(desc->id_list, desc->id_num);
}



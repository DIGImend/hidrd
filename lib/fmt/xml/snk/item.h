/** @file
 * @brief HID report descriptor - XML sink - item output
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
 * @(#) $Id: element.h 283 2010-03-20 12:58:33Z spb_nick $
 */

#ifndef __SNK_ITEM_H__
#define __SNK_ITEM_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Put a basic item to an XML sink.
 *
 * @param xml_snk   XML sink.
 * @param item      Item to put.
 *
 * @return True if put successfully, false otherwise.
 */
extern bool xml_snk_item_basic(hidrd_xml_snk_inst  *xml_snk,
                               const hidrd_item    *item);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __SNK_ITEM_H__ */

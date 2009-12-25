/** @file
 * @brief HID report descriptor - XML stream type
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

#ifndef __HIDRD_STRM_XML_H__
#define __HIDRD_STRM_XML_H__

#include "hidrd/strm/type.h"
#include "hidrd/strm/inst.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const hidrd_strm_type    hidrd_strm_xml;

/**
 * Initialize global state of the XML parser.
 */
extern void hidrd_strm_xml_init_parser(void);

/**
 * Cleanup global state of the XML parser.
 */
extern void hidrd_strm_xml_clnp_parser(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_STRM_XML_H__ */


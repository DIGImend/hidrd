/** @file
 * @brief HID report descriptor - XML stream sink
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

#ifndef __HIDRD_FMT_XML_SNK_H__
#define __HIDRD_FMT_XML_SNK_H__

#include "libxml/tree.h"
#include "hidrd/strm/snk/inst.h"

#ifdef __cplusplus
extern "C" {
#endif

/** XML sink type */
extern const hidrd_snk_type hidrd_xml_snk;

/** XML sink item state table */
typedef struct hidrd_xml_snk_state hidrd_xml_snk_state;
struct hidrd_xml_snk_state {
    hidrd_xml_snk_state    *prev;       /**< Previous state */
    hidrd_usage_page        usage_page; /**< Usage page in effect */
};

/** XML sink instance */
typedef struct hidrd_xml_snk_inst {
    hidrd_snk               snk;    /**< Parent structure */
    bool                    format; /**< Format option flag */
    xmlDocPtr               doc;    /**< Document being built */
    xmlNodePtr              prnt;   /**< Current parent element */
    xmlNodePtr              cur;    /**< Current element */
    hidrd_xml_snk_state    *state;  /**< Item state table stack */
} hidrd_xml_snk_inst;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_FMT_XML_SNK_H__ */

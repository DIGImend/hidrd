/** @file
 * @brief HID report descriptor - XML stream source
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

#ifndef __HIDRD_FMT_XML_SRC_H__
#define __HIDRD_FMT_XML_SRC_H__

#include "libxml/tree.h"
#include "hidrd/strm/src/inst.h"

#ifdef __cplusplus
extern "C" {
#endif

/** XML source type */
extern const hidrd_src_type hidrd_xml_src;

/** XML source item state table */
typedef struct hidrd_xml_src_state hidrd_xml_src_state;
struct hidrd_xml_src_state {
    hidrd_xml_src_state    *prev;       /**< Previous state */
    hidrd_usage_page        usage_page; /**< Usage page in effect */
};

/** XML source instance */
typedef struct hidrd_xml_src_inst {
    hidrd_src               src;    /**< Parent structure */
    xmlDocPtr               doc;    /**< Document being read */
    xmlNodePtr              prnt;   /**< Current parent element */
    xmlNodePtr              cur;    /**< Current element */
    hidrd_xml_src_state    *state;  /**< Item state table stack */

    hidrd_item              item[HIDRD_ITEM_MAX_SIZE];  /**< Item
                                                             being
                                                             retrieved */
    char                   *err;    /**< Last error message */
} hidrd_xml_src_inst;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_FMT_XML_SRC_H__ */

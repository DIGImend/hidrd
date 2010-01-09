/** @file
 * @brief HID report descriptor - XML stream type - internal declarations
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


#ifndef __XML_H__
#define __XML_H__

#ifdef __cplusplus
extern "C" {
#endif

#define HIDRD_STRM_XML_NS \
    "http://digimend.sourceforge.net"
#define HIDRD_STRM_XML_NS_XSI \
    "http://www.w3.org/2001/XMLSchema-instance"
#define HIDRD_STRM_XML_XSI_SCHEMA_LOCATION \
    "http://digimend.sourceforge.net hidrd.xsd"

/** XML stream instance */
typedef struct hidrd_strm_xml_inst {
    hidrd_strm      strm;   /**< Parent structure */
    bool            format;

    void           *buf;
    size_t          size;
    xmlDocPtr       doc;
    xmlNodePtr      prnt;
    xmlNodePtr      cur;
    bool            changed;

    hidrd_item      item[HIDRD_ITEM_MAX_SIZE];
} hidrd_strm_xml_inst;

extern bool hidrd_strm_xml_being_read(const hidrd_strm *strm);

extern bool hidrd_strm_xml_being_written(const hidrd_strm *strm);

extern const hidrd_item *hidrd_strm_xml_read(hidrd_strm *strm);

extern bool hidrd_strm_xml_write(hidrd_strm        *strm,
                                 const hidrd_item  *item);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __XML_H__ */


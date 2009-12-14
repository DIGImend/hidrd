/** @file
 * @brief HID report descriptor - XML file stream type
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


#include <libxml/parser.h>
#include "hidrd/strm/xml.h"
#include "hidrd/strm/inst.h"

typedef struct hidrd_strm_xml_inst {
    hidrd_strm      strm;   /**< Parent structure */
    xmlDocPtr       doc;
} hidrd_strm_xml_inst;


static bool
hidrd_strm_xml_init(hidrd_strm *strm, va_list ap)
{
    hidrd_strm_xml_inst    *strm_xml    = (hidrd_strm_xml_inst *)strm;
    const char             *filename    = va_arg(ap, const char *);

    strm_xml->doc = xmlParseFile(filename);

    return (strm_xml->doc != NULL);
}


const hidrd_strm_type hidrd_strm_xml = {
    .size   = sizeof(hidrd_strm_xml_inst),
    .init   = hidrd_strm_xml_init,
#if 0
    .valid  = hidrd_strm_xml_valid,
    .read   = hidrd_strm_xml_read,
    .write  = hidrd_strm_xml_write,
    .flush  = hidrd_strm_xml_flush,
    .clnp   = hidrd_strm_xml_clnp,
#endif
};



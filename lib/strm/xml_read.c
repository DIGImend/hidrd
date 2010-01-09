/** @file
 * @brief HID report descriptor - XML stream type - reading
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


#include <string.h>
#include <libxml/parser.h>
#include "hidrd/strm/xml.h"
#include "xml.h"

static bool
hidrd_strm_xml_read_buf(hidrd_strm *strm)
{
    hidrd_strm_xml_inst    *strm_xml    = (hidrd_strm_xml_inst *)strm;

    assert(strm_xml->doc == NULL);
    assert(strm_xml->prnt == NULL);
    assert(strm_xml->cur == NULL);

    /* If there is no input */
    if (strm_xml->size == 0)
        return false;

    strm_xml->doc = xmlParseMemory(strm_xml->buf, strm_xml->size);
    if (strm_xml->doc == NULL)
    {
        strm->error = true;
        return false;
    }

    /* TODO XML schema validation with xmlSchemaValidateDoc */

    /* Retrieve the root */
    strm_xml->prnt = xmlDocGetRootElement(strm_xml->doc);

    /* Retrieve the first child */
    if (strm_xml->prnt != NULL)
        strm_xml->cur = strm_xml->prnt->children;

    return true;
}


const hidrd_item *
hidrd_strm_xml_read(hidrd_strm *strm)
{
    hidrd_strm_xml_inst    *strm_xml    = (hidrd_strm_xml_inst *)strm;
    xmlNodePtr              old_prnt;

    assert(!hidrd_strm_xml_being_written(strm));

    /* If the document hasn't been parsed yet */
    if (strm_xml->doc == NULL)
    {
        /* Parse the document and locate first node */
        if (!hidrd_strm_xml_read_buf(strm))
            return NULL;
    }

    /*
     * Get next element (go forward and up).
     */
    while (true)
    {
        while (strm_xml->cur == NULL)
        {
            if (strm_xml->prnt == NULL)
                return NULL;

            old_prnt = strm_xml->prnt;
            strm_xml->prnt = old_prnt->parent;
            if (strm_xml->prnt == NULL)
                return NULL;
            strm_xml->cur = old_prnt->next;
        }

        if (strm_xml->cur->type == XML_ELEMENT_NODE)
            break;

        strm_xml->cur = strm_xml->cur->next;
    }

    /*
     * Process element
     */

    return NULL;
}



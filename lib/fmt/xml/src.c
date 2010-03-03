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


#include "hidrd/fmt/xml/src.h"


static bool
init(hidrd_src *src)
{
    hidrd_xml_src_inst     *xml_src = (hidrd_xml_src_inst *)src;
    hidrd_xml_src_state    *state   = NULL;
    xmlDocPtr               doc     = NULL;
    xmlNodePtr              root;

    /* Create item state table stack */
    state = malloc(sizeof(*state));
    if (state == NULL)
        goto failure;
    state->prev         = NULL;
    state->usage_page   = HIDRD_USAGE_PAGE_UNDEFINED;

    /* Parse the document */
    doc = xmlParseMemory(src->buf, src->size);
    if (doc == NULL)
        goto failure;

    /* TODO XML schema validation with xmlSchemaValidateDoc */

    /* Retrieve the root element */
    root = xmlDocGetRootElement(xml_src->doc);
    if (root == NULL)
        goto failure;

    /* Initialize the source */
    xml_src->doc    = doc;
    xml_src->prnt   = root;
    xml_src->cur    = root->children;
    xml_src->state  = state;

    return true;

failure:

    if (doc != NULL)
        xmlFreeDoc(doc);

    free(state);

    return false;
}


static bool
hidrd_xml_src_init(hidrd_src *src, va_list ap)
{
    (void)ap;
    return init(src);
}


static bool
hidrd_xml_src_valid(const hidrd_src *src)
{
    const hidrd_xml_src_inst   *xml_src = (const hidrd_xml_src_inst *)src;

    return src->type->size >= sizeof(hidrd_xml_src_inst) &&
           xml_src->state != NULL &&
           xml_src->doc != NULL &&
           xml_src->prnt != NULL;
}


const hidrd_item *
hidrd_xml_src_get(hidrd_src *src)
{
    hidrd_xml_src_inst *xml_src     = (hidrd_xml_src_inst *)src;
    xmlNodePtr          old_prnt;

    /*
     * Get next element (go forward and up).
     */
    while (true)
    {
        while (xml_src->cur == NULL)
        {
            if (xml_src->prnt == NULL)
                return NULL;

            old_prnt = xml_src->prnt;
            xml_src->prnt = old_prnt->parent;
            if (xml_src->prnt == NULL)
                return NULL;
            xml_src->cur = old_prnt->next;
        }

        if (xml_src->cur->type == XML_ELEMENT_NODE)
            break;

        xml_src->cur = xml_src->cur->next;
    }

    /*
     * Process element
     */

    return NULL;
}


static void
hidrd_xml_src_clnp(hidrd_src *src)
{
    hidrd_xml_src_inst    *xml_src    = (hidrd_xml_src_inst *)src;
    hidrd_xml_src_state   *state;
    hidrd_xml_src_state   *prev_state;

    /* Free the document, if there is any */
    if (xml_src->doc != NULL)
    {
        xmlFreeDoc(xml_src->doc);
        xml_src->doc = NULL;
    }

    /* Free the state stack, if there is any */
    for (state = xml_src->state; state != NULL; state = prev_state)
    {
        prev_state = state->prev;
        free(state);
    }
    xml_src->state = NULL;
}


const hidrd_src_type hidrd_xml_src = {
    .size       = sizeof(hidrd_xml_src_inst),
    .init       = hidrd_xml_src_init,
    .valid      = hidrd_xml_src_valid,
    .get        = hidrd_xml_src_get,
    .clnp       = hidrd_xml_src_clnp,
};



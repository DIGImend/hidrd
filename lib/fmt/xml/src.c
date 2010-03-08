/** @file
 * @brief HID report descriptor - XML source
 *
 * Copyright (C) 2009-2010 Nikolai Kondrashov
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

#include "src_element.h"
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
    root = xmlDocGetRootElement(doc);
    if (root == NULL)
        goto failure;

    /* Initialize the source */
    xml_src->doc    = doc;
    xml_src->prnt   = NULL;
    xml_src->cur    = root;
    xml_src->state  = state;

    /* Own the resources */
    doc = NULL;
    state = NULL;

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
           (xml_src->prnt != NULL || xml_src->cur != NULL);
}

const hidrd_item *
hidrd_xml_src_get(hidrd_src *src)
{
    hidrd_xml_src_inst *xml_src     = (hidrd_xml_src_inst *)src;
    element_rc          rc;
    bool                enter;

    do {
        /*
         * Get next element (go forward and up).
         */
        while (true)
        {
            /* While we're at the end of the node list */
            while (xml_src->cur == NULL)
            {
                /* We don't go above the root element (only start there) */
                assert(xml_src->prnt != NULL);

                /* Handle the exit from an element */
                rc = element_exit(xml_src);
                /* If an error occurred */
                if (rc == ELEMENT_RC_ERROR)
                    xml_src->src.error = true;
                /* If we shouldn't stop here */
                if (rc != ELEMENT_RC_ERROR && rc != ELEMENT_RC_END)
                {
                    /* Go up (exit) */
                    xml_src->cur = xml_src->prnt->next;
                    xml_src->prnt = xml_src->prnt->parent;
                    /* We don't go above the root element (only start there) */
                    assert(xml_src->prnt != NULL);
                }
                /* If we have something to return */
                if (rc != ELEMENT_RC_NONE)
                    return (rc == ELEMENT_RC_ITEM) ? xml_src->item : NULL;
            }

            /* If this node is an element */
            if (xml_src->cur->type == XML_ELEMENT_NODE)
                break;

            /* Get next node */
            xml_src->cur = xml_src->cur->next;
        }

        /*
         * Process the element
         */
        enter = false;
        rc = element(xml_src, &enter);
        /* If an error occurred */
        if (rc == ELEMENT_RC_ERROR)
            xml_src->src.error = true;
        /* If we shouldn't stop here */
        if (rc != ELEMENT_RC_ERROR && rc != ELEMENT_RC_END)
        {
            if (enter)
            {
                xml_src->prnt = xml_src->cur;
                xml_src->cur = xml_src->prnt->children;
            }
            else
                xml_src->cur = xml_src->cur->next;
        }
    } while (rc == ELEMENT_RC_NONE); /* While we have nothing to return */

    return (rc == ELEMENT_RC_ITEM) ? xml_src->item : NULL;
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



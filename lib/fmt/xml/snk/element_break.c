/** @file
 * @brief HID report descriptor - XML sink - element breaking
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

#include "element_break.h"

bool
xml_snk_element_break(xmlNodePtr                    element,
                      xml_snk_element_create_fn    *create_start,
                      xml_snk_element_create_fn    *create_end)
{
    xmlNodePtr  sibling;
    xmlNodePtr  child;
    xmlNodePtr  next_child;
    xmlAttrPtr  prop;
    xmlAttrPtr  last_prop;

    assert(element != NULL);
    assert(element->parent != NULL);

    /* If starting element is NOT requested */
    if (create_start == NULL)
        sibling = element;
    else
    {
        /* Create starting element */
        sibling = create_start(element->doc, element->ns);
        if (sibling == NULL)
            return false;

        /* Add it right after the original one */
        sibling = xmlAddNextSibling(element, sibling);
        if (sibling == NULL)
            return false;

        /* Copy original element's property list, if not empty */
        if (element->properties != NULL)
        {
            prop = xmlCopyPropList(sibling, element->properties);
            if (prop == NULL)
                return false;

            /*
             * Attach copied property list to the created element property
             * list.
             */
            if (sibling->properties == NULL)
                sibling->properties = prop;
            else
            {
                /* Find the last property */
                for (last_prop = sibling->properties;
                     last_prop->next == NULL;
                     last_prop = last_prop->next);
                last_prop->next = prop;
                prop->prev = last_prop;
            }
        }
    }

    /* For each child of the original element */
    for (child = element->children;
         child != NULL; child = next_child)
    {
        /* Remember next child before this one is unlinked */
        next_child = child->next;
        /* Move the child after the new element */
        sibling = xmlAddNextSibling(sibling, child);
        if (sibling == NULL)
            return false;
    }

    /* If ending element is requested */
    if (create_end != NULL)
    {
        /* Create ending element */
        sibling = create_end(element->doc, element->ns);
        if (sibling == NULL)
            return false;

        /* Add it right after the contents */
        sibling = xmlAddNextSibling(element, sibling);
        if (sibling == NULL)
            return false;
    }

    /* Unlink original element */
    xmlUnlinkNode(element);

    /* Free original element */
    xmlFreeNode(element);

    return true;
}


bool
xml_snk_element_break_branch(xmlNodePtr                 parent,
                             xmlNodePtr                 element,
                             xml_snk_element_break_fn  *cb)
{
    xml_snk_element_create_fn  *create_start;
    xml_snk_element_create_fn  *create_end;
    xmlNodePtr                  element_parent;

    /* For each element in the stack until the target one */
    for (; element != parent; element = element_parent)
    {
        if (!(*cb)((const char *)element->name, &create_start, &create_end))
            return false;

        /* Remember parent element before this one is unlinked and freed */
        element_parent = element->parent;

        /* Break open the element - it is not finished */
        if (!xml_snk_element_break(element, create_start, create_end))
            return false;
    }

    return true;
}



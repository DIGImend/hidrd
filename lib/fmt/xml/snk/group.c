/** @file
 * @brief HID report descriptor - XML sink - element group handling
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

#include "element.h"
#include "element_break.h"
#include "group.h"

/** Group description */
typedef struct group {
    const char                 *name;           /**< Element name */
    xml_snk_element_create_fn  *create_start;   /**< Broken start element
                                                     creation function */
    xml_snk_element_create_fn  *create_end;     /**< Broken end element
                                                     creation function */
} group;

#ifndef NDEBUG
static bool
group_valid(const group *g)
{
    return g != NULL &&
           g->name != NULL &&
           *g->name != '\0' &&
           g->create_start != NULL &&
           g->create_end != NULL;
}
#endif

static xmlNodePtr
create_collection(xmlDocPtr doc, xmlNsPtr ns)
{
    return xmlNewDocNode(doc, ns, BAD_CAST "collection", NULL);
}

static xmlNodePtr
create_end_collection(xmlDocPtr doc, xmlNsPtr ns)
{
    return xmlNewDocNode(doc, ns, BAD_CAST "end_collection", NULL);
}

static xmlNodePtr
create_push(xmlDocPtr doc, xmlNsPtr ns)
{
    return xmlNewDocNode(doc, ns, BAD_CAST "push", NULL);
}

static xmlNodePtr
create_pop(xmlDocPtr doc, xmlNsPtr ns)
{
    return xmlNewDocNode(doc, ns, BAD_CAST "pop", NULL);
}

static xmlNodePtr
create_delimiter_open(xmlDocPtr doc, xmlNsPtr ns)
{
    xmlNodePtr  e;

    e = xmlNewDocNode(doc, ns, BAD_CAST "delimiter", NULL);
    if (e == NULL)
        return NULL;

    if (xmlSetProp(e, BAD_CAST "open", BAD_CAST "true") == NULL)
        return NULL;

    return e;
}

static xmlNodePtr
create_delimiter_close(xmlDocPtr doc, xmlNsPtr ns)
{
    xmlNodePtr  e;

    e = xmlNewDocNode(doc, ns, BAD_CAST "delimiter", NULL);
    if (e == NULL)
        return NULL;

    if (xmlSetProp(e, BAD_CAST "open", BAD_CAST "false") == NULL)
        return NULL;

    return e;
}


static const group group_list[] = {
    {.name          = "COLLECTION",
     .create_start  = create_collection,
     .create_end    = create_end_collection},
    {.name          = "PUSH",
     .create_start  = create_push,
     .create_end    = create_pop},
    {.name          = "SET",
     .create_start  = create_delimiter_open,
     .create_end    = create_delimiter_close},
    {.name = NULL}
};

static const group *
lookup_group(const char *name)
{
    const group    *g;
    for (g = group_list; g->name != NULL; g++)
        if (strcmp(g->name, name) == 0)
        {
            assert(group_valid(g));
            return g;
        }

    return NULL;
}

static xml_snk_element_break_fn group_break_cb;
static bool
group_break_cb(const char                  *name,
               xml_snk_element_create_fn  **pcreate_start,
               xml_snk_element_create_fn  **pcreate_end)
{
    const group    *g;

    assert(name != NULL);

    g = lookup_group(name);
    assert(g != NULL);

    if (g == NULL)
    {
        XML_ERR("unknown group element \"%s\"", name);
        return false;
    }

    if (pcreate_start != NULL)
        *pcreate_start = g->create_start;

    if (pcreate_end != NULL)
        *pcreate_end = NULL;

    return true;
}


bool
xml_snk_group_start(hidrd_xml_snk_inst *xml_snk,
                    const char         *name,
                    ...)
{
    va_list ap;
    bool    success;

    va_start(ap, name);
    success = xml_snk_element_addpv(xml_snk, true, name, &ap);
    va_end(ap);

    return success;
}


bool
xml_snk_group_end(hidrd_xml_snk_inst  *xml_snk,
                  const char           *name)
{
    const group    *target_group;
    xmlNodePtr      target_element;

    assert(xml_snk->cur == NULL);
    assert(name != NULL);

    target_group = lookup_group(name);
    /* There must be such group */
    assert(target_group != NULL);

    /* Look up an element with the same name up the parent stack */
    for (target_element = xml_snk->prnt;
         target_element != NULL && target_element->type == XML_ELEMENT_NODE;
         target_element = target_element->parent)
        if (strcmp((const char *)target_element->name, name) == 0)
            break;

    /* If not found */
    if (target_element == NULL || target_element->type != XML_ELEMENT_NODE)
    {
        xmlNodePtr  end_element;

        /* Insert closing element */
        end_element = target_group->create_end(xml_snk->doc, NULL);
        return xmlAddChild(xml_snk->prnt, end_element) != NULL;
    }
    else
    {
        /* Break open the branch up to the target element */
        if (!xml_snk_element_break_branch(target_element, xml_snk->prnt,
                                  group_break_cb))
            return false;

        /* Element done */
        xml_snk->prnt = target_element->parent;
    }

    return true;
}


bool
xml_snk_group_break_branch(hidrd_snk *snk)
{
    hidrd_xml_snk_inst *xml_snk = (hidrd_xml_snk_inst *)snk;
    xmlNodePtr          root;

    assert(xml_snk->doc != NULL);
    assert(xml_snk->prnt != NULL);

    root = xmlDocGetRootElement(xml_snk->doc);
    if (!xml_snk_element_break_branch(root, xml_snk->prnt, group_break_cb))
        return false;

    xml_snk->prnt = root;

    return true;
}



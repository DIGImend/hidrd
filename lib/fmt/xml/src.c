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
    xml_src->prnt   = NULL;
    xml_src->cur    = root;
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
           (xml_src->prnt != NULL || xml_src->cur != NULL);
}

/** Element processing result code */
typedef enum element_rc {
    ELEMENT_NONE,    /**< No item has been read, return */
    ELEMENT_SKIP,    /**< No item has been read, proceed */
    ELEMENT_ITEM,    /**< An item has been read, return */
} element_rc;

/**
 * Prototype for an element processing function.
 *
 * @param xml_src   XML source instance.
 * @param e         Element to handle (src->cur for element start, or src->prnt
 *                  for element end).
 * 
 * @return True if an item was read, false otherwise.
 */
typedef element_rc element_fn(hidrd_xml_src_inst *xml_src, xmlNodePtr e);

#define START(_name) \
    static element_rc                                                   \
    element_##_name##_start(hidrd_xml_src_inst *xml_src, xmlNodePtr e)

#define END(_name) \
    static element_rc                                                   \
    element_##_name##_end(hidrd_xml_src_inst *xml_src, xmlNodePtr e)

START(descriptor)
{
    (void)e;
    /* Go down */
    xml_src->prnt = xml_src->cur;
    xml_src->cur = xml_src->prnt->children;
    /* No item yet */
    return ELEMENT_SKIP;
}

END(descriptor)
{
    (void)xml_src;
    (void)e;
    /* No more items */
    return ELEMENT_NONE;
}

#undef END
#undef START

/** Element handler */
typedef struct element_handler {
    const char *name;   /**< Element name */
    element_fn *start;  /**< Element start processing function */
    element_fn *end;    /**< Element end processing function */
} element_handler;

/** Element handler list */
static const element_handler handler_list[] = {
#define IGNORE(_name)   {.name = #_name}
#define START(_name)    {.name = #_name, .start = element_##_name##_start}
#define END(_name)      {.name = #_name, .end = element_##_name##_end}
#define BOTH(_name)     {.name  = #_name, \
                         .start = element_##_name##_start,  \
                         .end   = element_##_name##_end}
    IGNORE(basic),
    IGNORE(short),
    IGNORE(main),
    IGNORE(input),
    IGNORE(output),
    IGNORE(feature),
    IGNORE(collection),
    IGNORE(end_collection),
    IGNORE(COLLECTION),
    IGNORE(global),
    IGNORE(usage_page),
    IGNORE(logical_minimum),
    IGNORE(logical_maximum),
    IGNORE(physical_minimum),
    IGNORE(physical_maximum),
    IGNORE(unit_exponent),
    IGNORE(unit),
    IGNORE(report_size),
    IGNORE(report_count),
    IGNORE(report_id),
    IGNORE(push),
    IGNORE(pop),
    IGNORE(PUSH),
    IGNORE(local),
    IGNORE(usage),
    IGNORE(usage_minimum),
    IGNORE(usage_maximum),
    IGNORE(designator_index),
    IGNORE(designator_minimum),
    IGNORE(designator_maximum),
    IGNORE(string_index),
    IGNORE(string_minimum),
    IGNORE(string_maximum),
    IGNORE(delimiter),
    IGNORE(SET),
    IGNORE(long),
    BOTH(descriptor),
#undef BOTH
#undef END
#undef START
#undef IGNORE
};


static element_rc
element_start(hidrd_xml_src_inst   *xml_src)
{
    const char             *name;
    size_t                  i;
    const element_handler  *handler;

    /* We have to process something */
    assert(xml_src->cur != NULL);
    /* We process elements only */
    assert(xml_src->cur->type == XML_ELEMENT_NODE);
    /* Either no parent or an element parent */
    assert(xml_src->prnt == NULL ||
           xml_src->prnt->type == XML_ELEMENT_NODE);

    name = (const char *)xml_src->cur->name;

    for (i = 0; i < sizeof(handler_list) / sizeof(*handler_list); i++)
    {
        handler = handler_list + i;

        if (strcmp(handler->name, name) == 0)
        {
            if (handler->start == NULL)
                return ELEMENT_SKIP;
#ifdef NDEBUG
            return (*handler->start)(xml_src, xml_src->cur);
#else
            xmlNodePtr  orig_prnt   = xml_src->prnt;
            xmlNodePtr  orig_cur    = xml_src->cur;
            element_rc  rc;

            rc = (*handler->start)(xml_src, xml_src->cur);

            /* We may stay or go one element deeper */
            assert(xml_src->prnt == orig_prnt || xml_src->prnt == orig_cur);

            return rc;
#endif /* !NDEBUG */
        }
    }

    xml_src->src.error = true;
    return false;
}


static element_rc
element_end(hidrd_xml_src_inst *xml_src)
{
    const char             *name;
    size_t                  i;
    const element_handler  *handler;

    /* We have to process something */
    assert(xml_src->prnt != NULL);
    /* We process elements only */
    assert(xml_src->prnt->type == XML_ELEMENT_NODE);
    /* We should be at the end of the node list */
    assert(xml_src->cur == NULL);

    name = (const char *)xml_src->prnt->name;

    for (i = 0; i < sizeof(handler_list) / sizeof(*handler_list); i++)
    {
        handler = handler_list + i;
        if (strcmp(handler->name, name) == 0)
        {
            if (handler->end == NULL)
                return ELEMENT_SKIP;
#ifdef NDEBUG
            return (*handler->end)(xml_src, xml_src->prnt);
#else
            xmlNodePtr  orig_prnt   = xml_src->prnt;
            element_rc  rc;

            rc = (*handler->end)(xml_src, xml_src->prnt);

            /* We shouldn't change anything */
            assert(xml_src->prnt == orig_prnt);
            assert(xml_src->cur == NULL);

            return rc;
#endif /* !NDEBUG */
        }
    }

    xml_src->src.error = true;
    return false;
}


const hidrd_item *
hidrd_xml_src_get(hidrd_src *src)
{
    hidrd_xml_src_inst *xml_src     = (hidrd_xml_src_inst *)src;
    element_rc          rc;

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
                /* We don't go down non-element nodes */
                assert(xml_src->prnt->type == XML_ELEMENT_NODE);

                /* Process element end */
                rc = element_end(xml_src);
                if (rc != ELEMENT_SKIP)
                    return (rc == ELEMENT_ITEM) ? xml_src->item : NULL;

                xml_src->cur = xml_src->prnt->next;
                xml_src->prnt = xml_src->prnt->parent;
                /* We don't go above the root element (only start there) */
                assert(xml_src->prnt != NULL);
            }

            /* If this node is an element */
            if (xml_src->cur->type == XML_ELEMENT_NODE)
                break;

            /* Get next node */
            xml_src->cur = xml_src->cur->next;
        }

        /*
         * Process element start
         */
        rc = element_start(xml_src);

    } while (rc == ELEMENT_SKIP);

    return (rc == ELEMENT_ITEM) ? xml_src->item : NULL;
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



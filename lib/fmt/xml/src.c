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

#include "hidrd/cfg.h"
#include "hidrd/fmt/xml/cfg.h"
#include "src/element.h"
#include "hidrd/fmt/xml/src.h"
#include "../xml.h"


static bool
init(hidrd_src *src, char **perr, const char *schema)
{
    bool                    result  = false;
    hidrd_xml_src_inst     *xml_src = (hidrd_xml_src_inst *)src;
    hidrd_xml_src_state    *state   = NULL;
    xmlDocPtr               doc     = NULL;
    xmlNodePtr              root;

    XML_ERR_FUNC_BACKUP_DECL;

    if (perr != NULL)
        *perr = strdup("");

    XML_ERR_FUNC_SET(perr);

    /* Create item state table stack */
    state = malloc(sizeof(*state));
    if (state == NULL)
        XML_ERR_CLNP("failed to allocate memory for the state table");
    state->prev         = NULL;
    state->usage_page   = HIDRD_USAGE_PAGE_UNDEFINED;

    /* Parse the document */
    doc = xmlParseMemory(src->buf, src->size);
    if (doc == NULL)
        goto cleanup;

    /* TODO XML schema validation with xmlSchemaValidateDoc */
    (void)schema;

    /* Retrieve the root element */
    root = xmlDocGetRootElement(doc);
    if (root == NULL)
        XML_ERR_CLNP("root element not found");

    /* Initialize the source */
    xml_src->doc    = doc;
    xml_src->prnt   = NULL;
    xml_src->cur    = root;
    xml_src->state  = state;
    xml_src->err    = strdup("");

    /* Own the resources */
    doc = NULL;
    state = NULL;

    /* Success */
    result = true;

cleanup:

    if (doc != NULL)
        xmlFreeDoc(doc);

    free(state);

    XML_ERR_FUNC_RESTORE;

    return result;
}


static bool
hidrd_xml_src_init(hidrd_src *src, char **perr, va_list ap)
{
    const char *schema  = va_arg(ap, const char *);

    return init(src, perr, schema);
}


#ifdef HIDRD_WITH_OPT
static const hidrd_opt_spec hidrd_xml_src_opts_spec[] = {
    {.name  = "schema",
     .type  = HIDRD_OPT_TYPE_STRING,
     .req   = false,
     .dflt  = {
         .string = HIDRD_XML_SCHEMA_PATH
     },
     .desc  = "path to a schema file for input validation"},
    {.name  = NULL}
};

static bool
hidrd_xml_src_init_opts(hidrd_src *src, char **perr, const hidrd_opt *list)
{
    return init(src, perr, hidrd_opt_list_get_string(list, "schema"));
}
#endif /* HIDRD_WITH_OPT */


static bool
hidrd_xml_src_valid(const hidrd_src *src)
{
    const hidrd_xml_src_inst   *xml_src = (const hidrd_xml_src_inst *)src;

    return src->type->size >= sizeof(hidrd_xml_src_inst) &&
           xml_src->state != NULL &&
           xml_src->doc != NULL &&
           (xml_src->prnt != NULL || xml_src->cur != NULL);
}


static size_t
hidrd_xml_src_getpos(const hidrd_src *src)
{
    const hidrd_xml_src_inst   *xml_src = (hidrd_xml_src_inst *)src;

    return xml_src->cur == NULL
            ? xml_src->prnt->line
            : xml_src->cur->line;
}


static char *
hidrd_xml_src_fmtpos(const hidrd_src *src, size_t pos)
{
    char   *str;

    (void)src;

    if (asprintf(&str, "line %zu", pos) < 0)
        return NULL;

    return str;
}


static char *
hidrd_xml_src_errmsg(const hidrd_src *src)
{
    const hidrd_xml_src_inst   *xml_src    =
                                    (const hidrd_xml_src_inst *)src;

    return strdup(xml_src->err);
}


static const hidrd_item *
hidrd_xml_src_get(hidrd_src *src)
{
    const hidrd_item   *result      = NULL;
    hidrd_xml_src_inst *xml_src     = (hidrd_xml_src_inst *)src;
    xml_src_element_rc  rc;
    bool                enter;

    XML_ERR_FUNC_BACKUP_DECL;

    free(xml_src->err);
    xml_src->err = strdup("");

    XML_ERR_FUNC_SET(&xml_src->err);

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
                rc = xml_src_element_exit(xml_src);
                /* If an error occurred */
                if (rc == XML_SRC_ELEMENT_RC_ERROR)
                    xml_src->src.error = true;
                /* If we shouldn't stop here */
                if (rc != XML_SRC_ELEMENT_RC_ERROR &&
                    rc != XML_SRC_ELEMENT_RC_END)
                {
                    /* Go up (exit) */
                    xml_src->cur = xml_src->prnt->next;
                    xml_src->prnt = xml_src->prnt->parent;
                    /*
                     * We don't go above the root element (only start there)
                     */
                    assert(xml_src->prnt != NULL);
                }
                /* If we have something to return */
                if (rc != XML_SRC_ELEMENT_RC_NONE)
                {
                    if (rc == XML_SRC_ELEMENT_RC_ITEM)
                        result = hidrd_item_validate(xml_src->item);
                    goto cleanup;
                }
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
        rc = xml_src_element(xml_src, &enter);
        /* If an error occurred */
        if (rc == XML_SRC_ELEMENT_RC_ERROR)
            xml_src->src.error = true;
        /* If we shouldn't stop here */
        if (rc != XML_SRC_ELEMENT_RC_ERROR && rc != XML_SRC_ELEMENT_RC_END)
        {
            if (enter)
            {
                xml_src->prnt = xml_src->cur;
                xml_src->cur = xml_src->prnt->children;
            }
            else
                xml_src->cur = xml_src->cur->next;
        }
    } while (rc == XML_SRC_ELEMENT_RC_NONE); /* While nothing to return */

    if (rc == XML_SRC_ELEMENT_RC_ITEM)
        result = hidrd_item_validate(xml_src->item);

cleanup:

    XML_ERR_FUNC_RESTORE;

    return result;
}


static void
hidrd_xml_src_clnp(hidrd_src *src)
{
    hidrd_xml_src_inst    *xml_src    = (hidrd_xml_src_inst *)src;
    hidrd_xml_src_state   *state;
    hidrd_xml_src_state   *prev_state;

    /* Free the error message */
    free(xml_src->err);
    xml_src->err = NULL;

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
#ifdef HIDRD_WITH_OPT
    .init_opts  = hidrd_xml_src_init_opts,
    .opts_spec  = hidrd_xml_src_opts_spec,
#endif
    .valid      = hidrd_xml_src_valid,
    .getpos     = hidrd_xml_src_getpos,
    .fmtpos     = hidrd_xml_src_fmtpos,
    .errmsg     = hidrd_xml_src_errmsg,
    .get        = hidrd_xml_src_get,
    .clnp       = hidrd_xml_src_clnp,
};



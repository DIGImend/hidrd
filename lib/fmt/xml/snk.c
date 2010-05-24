/** @file
 * @brief HID report descriptor - XML sink
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
#include "hidrd/fmt/xml/prop.h"
#include "hidrd/fmt/xml/snk.h"
#include "snk/group.h"
#include "snk/item.h"
#include "../xml.h"


static bool
hidrd_xml_snk_init(hidrd_snk *snk, char **perr, bool format, const char *schema)
{
    bool                    result      = false;
    hidrd_xml_snk_inst     *xml_snk     = (hidrd_xml_snk_inst *)snk;
    char                   *own_schema  = NULL;
    hidrd_xml_snk_state    *state       = NULL;
    xmlDocPtr               doc         = NULL;
    xmlNodePtr              root        = NULL;
    xmlNsPtr                ns;

    XML_ERR_FUNC_BACKUP_DECL;

    if (perr != NULL)
        *perr = strdup("");

    XML_ERR_FUNC_SET(perr);

    /* Copy schema file path */
    own_schema = strdup(schema);
    if (own_schema == NULL)
        XML_ERR_CLNP("failed to allocate memory for the schema file path");
        
    /* Create item state table stack */
    state = malloc(sizeof(*state));
    if (state == NULL)
        XML_ERR_CLNP("failed to allocate memory for the state table");
    state->prev         = NULL;
    state->usage_page   = HIDRD_USAGE_PAGE_UNDEFINED;

    /* Create the document */
    doc = xmlNewDoc(BAD_CAST "1.0");
    if (doc == NULL)
        goto cleanup;

    /* Create root node */
    root = xmlNewNode(NULL, BAD_CAST "descriptor");
    if (root == NULL)
        goto cleanup;

    /* Add and assign our namespace */
    ns = xmlNewNs(root, BAD_CAST HIDRD_XML_PROP_NS, NULL);
    if (ns == NULL)
        goto cleanup;
    xmlSetNs(root, ns);

    /* Add XML schema instance namespace */
    ns = xmlNewNs(root, BAD_CAST HIDRD_XML_PROP_NS_XSI, BAD_CAST "xsi");
    if (ns == NULL)
        goto cleanup;

    /* Add xsi:schemaLocation attribute */
    if (xmlSetNsProp(root, ns,
                     BAD_CAST "schemaLocation",
                     BAD_CAST HIDRD_XML_PROP_XSI_SCHEMA_LOCATION) == NULL)
        goto cleanup;

    /* Set root element */
    xmlDocSetRootElement(doc, root);

    /* Initialize the sink */
    xml_snk->schema = own_schema;
    xml_snk->format = format;
    xml_snk->state  = state;
    xml_snk->doc    = doc;
    xml_snk->prnt   = root;
    xml_snk->err    = strdup("");

    own_schema  = NULL;
    state       = NULL;
    doc         = NULL;
    root        = NULL;

    result = true;

cleanup:

    xmlFreeNode(root);

    if (doc != NULL)
        xmlFreeDoc(doc);

    free(state);
    free(own_schema);

    XML_ERR_FUNC_RESTORE;

    return result;
}


static bool
hidrd_xml_snk_initv(hidrd_snk *snk, char **perr, va_list ap)
{
    bool        format  = (va_arg(ap, int) != 0);
    const char *schema  = va_arg(ap, const char *);

    return hidrd_xml_snk_init(snk, perr, format, schema);
}


#ifdef HIDRD_WITH_OPT
static const hidrd_opt_spec hidrd_xml_snk_opts_spec[] = {
    {.name  = "format",
     .type  = HIDRD_OPT_TYPE_BOOLEAN,
     .req   = false,
     .dflt  = {
         .boolean = true
     },
     .desc  = "format XML output"},
    {.name  = "schema",
     .type  = HIDRD_OPT_TYPE_STRING,
     .req   = false,
     .dflt  = {
#ifdef NDEBUG
         .string = ""
#else
         .string = HIDRD_XML_SCHEMA_PATH
#endif
     },
     .desc  = "path to a schema file for output validation"},
    {.name  = NULL}
};

static bool
hidrd_xml_snk_init_opts(hidrd_snk *snk, char **perr, const hidrd_opt *list)
{
    return hidrd_xml_snk_init(
                snk, perr,
                hidrd_opt_list_get_boolean(list, "format"),
                hidrd_opt_list_get_string(list, "schema"));
}
#endif /* HIDRD_WITH_OPT */


static bool
hidrd_xml_snk_valid(const hidrd_snk *snk)
{
    const hidrd_xml_snk_inst   *xml_snk = (const hidrd_xml_snk_inst *)snk;

    return snk->type->size >= sizeof(hidrd_xml_snk_inst) &&
           xml_snk->state != NULL &&
           xml_snk->doc != NULL &&
           xml_snk->prnt != NULL;
}


static char *
hidrd_xml_snk_errmsg(const hidrd_snk *snk)
{
    const hidrd_xml_snk_inst   *xml_snk    =
                                    (const hidrd_xml_snk_inst *)snk;

    return strdup(xml_snk->err);
}


static bool
hidrd_xml_snk_flush(hidrd_snk *snk)
{
    bool                result      = false;
    hidrd_xml_snk_inst *xml_snk     = (hidrd_xml_snk_inst *)snk;
    bool                valid;
    xmlBufferPtr        xml_buf     = NULL;
    xmlOutputBufferPtr  xml_out_buf = NULL;
    void               *new_buf;
    size_t              new_size;

    XML_ERR_FUNC_BACKUP_DECL;

    free(xml_snk->err);
    xml_snk->err = strdup("");

    XML_ERR_FUNC_SET(&xml_snk->err);

    /* Break any unfinished groups */
    if (!xml_snk_group_break_branch(snk))
        goto cleanup;

    /* Validate the document, if the schema is specified */
    if (*xml_snk->schema != '\0' &&
        (!xml_validate(&valid, xml_snk->doc, xml_snk->schema) || !valid))
        goto cleanup;

    /* Create an XML buffer */
    xml_buf = xmlBufferCreate();
    if (xml_buf == NULL)
        goto cleanup;

    /* Create an XML output buffer from the generic buffer */
    xml_out_buf = xmlOutputBufferCreateBuffer(xml_buf, NULL);
    if (xml_out_buf == NULL)
        goto cleanup;

    /* Format XML from the document */
    if (xmlSaveFormatFileTo(xml_out_buf, xml_snk->doc,
                            NULL, xml_snk->format) < 0)
        goto cleanup;
    /* xml_out_buf is closed by xmlSaveFormatFileTo */
    xml_out_buf = NULL;

    /* Retrieve resulting size */
    new_size = xmlBufferLength(xml_buf);

    /* If we have a location for the buffer pointer */
    if (snk->pbuf != NULL)
    {
        /* Retension and update the buffer */
        new_buf = realloc(*snk->pbuf, new_size);
        if (new_size > 0 && new_buf == NULL)
            XML_ERR_CLNP("failed to retension the output buffer");
        memcpy(new_buf, xmlBufferContent(xml_buf), new_size);
        /* Update the buffer pointer */
        *snk->pbuf = new_buf;
    }

    /* Output size */
    if (snk->psize != NULL)
        *snk->psize = new_size;

    result = true;

cleanup:

    if (xml_out_buf != NULL)
        xmlOutputBufferClose(xml_out_buf);

    if (xml_buf != NULL)
        xmlBufferFree(xml_buf);

    XML_ERR_FUNC_RESTORE;

    return result;
}


static void
hidrd_xml_snk_clnp(hidrd_snk *snk)
{
    hidrd_xml_snk_inst    *xml_snk    = (hidrd_xml_snk_inst *)snk;
    hidrd_xml_snk_state   *state;
    hidrd_xml_snk_state   *prev_state;

    /* Free the error message */
    free(xml_snk->err);
    xml_snk->err = NULL;

    /* Free the document, if there is any */
    if (xml_snk->doc != NULL)
    {
        xmlFreeDoc(xml_snk->doc);
        xml_snk->doc = NULL;
    }

    /* Free the state stack, if there is any */
    for (state = xml_snk->state; state != NULL; state = prev_state)
    {
        prev_state = state->prev;
        free(state);
    }
    xml_snk->state = NULL;

    /* Free the schema file path */
    free(xml_snk->schema);
    xml_snk->schema = NULL;
}


static bool
hidrd_xml_snk_put(hidrd_snk *snk, const hidrd_item *item)
{
    bool                result;
    hidrd_xml_snk_inst *xml_snk = (hidrd_xml_snk_inst *)snk;

    XML_ERR_FUNC_BACKUP_DECL;

    free(xml_snk->err);
    xml_snk->err = strdup("");

    XML_ERR_FUNC_SET(&xml_snk->err);

    result = xml_snk_item_basic(xml_snk, item);

    XML_ERR_FUNC_RESTORE;

    return result;
}


const hidrd_snk_type hidrd_xml_snk = {
    .size       = sizeof(hidrd_xml_snk_inst),
    .initv      = hidrd_xml_snk_initv,
#ifdef HIDRD_WITH_OPT
    .init_opts  = hidrd_xml_snk_init_opts,
    .opts_spec  = hidrd_xml_snk_opts_spec,
#endif
    .valid      = hidrd_xml_snk_valid,
    .errmsg     = hidrd_xml_snk_errmsg,
    .put        = hidrd_xml_snk_put,
    .flush      = hidrd_xml_snk_flush,
    .clnp       = hidrd_xml_snk_clnp,
};



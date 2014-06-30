/** @file
 * @brief HID report descriptor - XML format
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
 */

#include <errno.h>
#include <libxml/parser.h>
#include <libxml/xmlschemas.h>
#include "hidrd/fmt/xml.h"
#include "xml.h"


void
xml_error(void *ctx, const char *fmt, ...)
{
    char      **perr    = (char **)ctx;
    va_list     ap;
    char       *chunk;
    char       *new_err;

    if (perr == NULL)
        return;

    va_start(ap, fmt);

    if (vasprintf(&chunk, fmt, ap) < 0)
    {
        if (asprintf(&chunk, "failed to format error message chunk: %s",
                     strerror(errno)) < 0)
        {
            assert(!"Failed to format formatting error message");
            chunk = NULL;
            goto cleanup;
        }
    }

    if (asprintf(&new_err, "%s%s", *perr,  chunk) < 0)
    {
        assert(!"Failed to format new error message");
        goto cleanup;
    }

    free(*perr);
    *perr = new_err;

cleanup:

    free(chunk);
    va_end(ap);
}


bool
xml_validate(bool          *pvalid,
             xmlDocPtr      doc,
             const char    *schema_path)
{
    bool                    result              = false;
    xmlDocPtr               schema_doc          = NULL;
    xmlSchemaParserCtxtPtr  schema_parser_ctxt  = NULL;
    xmlSchemaPtr            schema              = NULL;
    xmlSchemaValidCtxtPtr   schema_valid_ctxt   = NULL;
    int                     valid_rc;

    schema_doc = xmlReadFile(schema_path, NULL, XML_PARSE_NONET);
    if (schema_doc == NULL)
        goto cleanup;

    schema_parser_ctxt = xmlSchemaNewDocParserCtxt(schema_doc);
    if (schema_parser_ctxt == NULL)
        goto cleanup;

    schema = xmlSchemaParse(schema_parser_ctxt);
    if (schema == NULL)
        goto cleanup;

    schema_valid_ctxt = xmlSchemaNewValidCtxt(schema);
    if (schema_valid_ctxt == NULL)
        goto cleanup;

    valid_rc = xmlSchemaValidateDoc(schema_valid_ctxt, doc);
    if (valid_rc < 0)
        goto cleanup;

    if (pvalid != NULL)
        *pvalid = (valid_rc == 0);

    result = true;

cleanup:

    xmlSchemaFreeValidCtxt(schema_valid_ctxt);
    xmlSchemaFree(schema);
    xmlSchemaFreeParserCtxt(schema_parser_ctxt);
    if (schema_doc != NULL)
        xmlFreeDoc(schema_doc);

    return result;
}


static bool
hidrd_xml_init(void)
{
    xmlInitParser();
    return true;
}


static void
hidrd_xml_clnp(void)
{
    xmlCleanupParser();
}


const hidrd_fmt hidrd_xml  = {
    .name   = "xml",
    .desc   = "XML",
    .init   = hidrd_xml_init,
    .clnp   = hidrd_xml_clnp,
    .src    = &hidrd_xml_src,
    .snk    = &hidrd_xml_snk
};



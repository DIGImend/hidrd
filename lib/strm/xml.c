/** @file
 * @brief HID report descriptor - XML stream type
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
#ifdef HIDRD_WITH_OPT
#include "hidrd/opt/list.h"
#endif
#include "hidrd/strm/xml.h"
#include "xml.h"

void
hidrd_strm_xml_init_parser(void)
{
    xmlInitParser();
}


void
hidrd_strm_xml_clnp_parser(void)
{
    xmlCleanupParser();
}


static bool
init(hidrd_strm *strm, bool format)
{
    hidrd_strm_xml_inst    *strm_xml    = (hidrd_strm_xml_inst *)strm;

    strm_xml->format    = format;
    strm_xml->buf       = (strm->pbuf != NULL) ? *strm->pbuf : NULL;
    strm_xml->size      = (strm->psize != NULL) ? *strm->psize : 0;
    strm_xml->doc       = NULL;
    strm_xml->prnt      = NULL;
    strm_xml->cur       = NULL;
    strm_xml->changed   = false;

    return true;
}


static bool
hidrd_strm_xml_init(hidrd_strm *strm, va_list ap)
{
    bool    format  = (va_arg(ap, int) != 0);

    return init(strm, format);
}


#ifdef HIDRD_WITH_OPT
static bool
hidrd_strm_xml_opts_init(hidrd_strm *strm, const hidrd_opt *list)
{
    return init(strm, hidrd_opt_list_get_boolean(list, "format"));
}
#endif


bool
hidrd_strm_xml_being_read(const hidrd_strm *strm)
{
    const hidrd_strm_xml_inst  *strm_xml    =
                                    (const hidrd_strm_xml_inst *)strm;

    return strm_xml->doc != NULL && !strm_xml->changed;
}


bool
hidrd_strm_xml_being_written(const hidrd_strm *strm)
{
    const hidrd_strm_xml_inst  *strm_xml    =
                                    (const hidrd_strm_xml_inst *)strm;

    return strm_xml->doc != NULL && strm_xml->changed;
}


static bool
hidrd_strm_xml_valid(const hidrd_strm *strm)
{
    const hidrd_strm_xml_inst  *strm_xml    =
                                    (const hidrd_strm_xml_inst *)strm;

    if (strm_xml->doc == NULL)
        return strm_xml->prnt == NULL &&
               strm_xml->cur == NULL &&
               !strm_xml->changed;
    else
        return (strm_xml->prnt != NULL || strm_xml->cur == NULL);
}


static bool
hidrd_strm_xml_flush_doc(hidrd_strm *strm)
{
    bool                    result          = false;
    hidrd_strm_xml_inst    *strm_xml        = (hidrd_strm_xml_inst *)strm;
    xmlBufferPtr            xml_buf         = NULL;
    xmlOutputBufferPtr      xml_out_buf     = NULL;
    void                   *new_buf         = NULL;
    size_t                  new_size;

    if (!strm_xml->changed)
    {
        result = true;
        goto finish;
    }

    xml_buf = xmlBufferCreate();
    if (xml_buf == NULL)
        goto finish;

    xml_out_buf = xmlOutputBufferCreateBuffer(xml_buf, NULL);
    if (xml_out_buf == NULL)
        goto finish;

    if (xmlSaveFormatFileTo(xml_out_buf, strm_xml->doc,
                            NULL, strm_xml->format) < 0)
        goto finish;
    /* xml_out_buf is closed by xmlSaveFormatFileTo */
    xml_out_buf = NULL;

    new_size = xmlBufferLength(xml_buf);
    new_buf = realloc(strm_xml->buf, new_size);
    if (new_buf == NULL)
        goto finish;
    memcpy(new_buf, xmlBufferContent(xml_buf), new_size);

    strm_xml->buf = new_buf;
    if (strm->pbuf != NULL)
        *strm->pbuf = new_buf;
    strm_xml->size = new_size;

    new_buf = NULL;

    result = true;

finish:

    strm->error = (strm->error || !result);

#if 0
cleanup:
#endif

    free(new_buf);

    if (xml_out_buf != NULL)
        xmlOutputBufferClose(xml_out_buf);

    if (xml_buf != NULL)
        xmlBufferFree(xml_buf);

    return result;
}


static bool
hidrd_strm_xml_flush(hidrd_strm *strm)
{
    hidrd_strm_xml_inst    *strm_xml        = (hidrd_strm_xml_inst *)strm;

    if (!hidrd_strm_xml_being_written(strm))
        return true;

    /* Dump document to the buffer (updates *pbuf also) */
    if (!hidrd_strm_xml_flush_doc(strm))
        return false;

    /* Output size */
    if (strm->psize != NULL)
        *strm->psize = strm_xml->size;

    return true;
}


static void
hidrd_strm_xml_clnp(hidrd_strm *strm)
{
    hidrd_strm_xml_inst    *strm_xml    = (hidrd_strm_xml_inst *)strm;

    if (strm_xml->doc != NULL)
    {
        xmlFreeDoc(strm_xml->doc);
        strm_xml->doc = NULL;
    }
}


#ifdef HIDRD_WITH_OPT
const hidrd_opt_spec hidrd_strm_xml_opts_spec[] = {
    {.name  = "format",
     .type  = HIDRD_OPT_TYPE_BOOLEAN,
     .req   = false,
     .dflt  = {
         .boolean = true
     },
     .desc  = "Indent XML output"},
    {.name  = NULL}
};
#endif /* HIDRD_WITH_OPT */

const hidrd_strm_type hidrd_strm_xml = {
    .name       = "XML",
    .size       = sizeof(hidrd_strm_xml_inst),
    .init       = hidrd_strm_xml_init,
#ifdef HIDRD_WITH_OPT
    .opts_init  = hidrd_strm_xml_opts_init,
    .opts_spec  = hidrd_strm_xml_opts_spec,
#endif
    .valid      = hidrd_strm_xml_valid,
    .read       = hidrd_strm_xml_read,
    .write      = hidrd_strm_xml_write,
    .flush      = hidrd_strm_xml_flush,
    .clnp       = hidrd_strm_xml_clnp,
};



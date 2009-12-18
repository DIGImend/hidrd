/** @file
 * @brief HID report descriptor - XML file stream type
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
#include "hidrd/strm/inst.h"

typedef struct hidrd_strm_xml_inst {
    hidrd_strm      strm;   /**< Parent structure */
    void          **pbuf;
    size_t         *psize;
    bool            format;

    void           *buf;
    size_t          size;
    xmlDocPtr       doc;
    xmlNodePtr      prnt;
    xmlNodePtr      cur;
    bool            changed;

    hidrd_item      item[HIDRD_ITEM_MAX_SIZE];
} hidrd_strm_xml_inst;


static bool
hidrd_strm_xml_init(hidrd_strm *strm, va_list ap)
{
    hidrd_strm_xml_inst    *strm_xml    = (hidrd_strm_xml_inst *)strm;
    void                  **pbuf        = va_arg(ap, void **);
    size_t                 *psize       = va_arg(ap, size_t *);
    bool                    format      = (va_arg(ap, int) != 0);

    assert(pbuf == NULL ||  /* No input nor location for output buffer,
                               maybe location for output size */
           (
            pbuf != NULL && psize != NULL && /* Location for both output
                                                buffer and size, maybe
                                                input buffer or size */
            (*psize == 0 || *pbuf != NULL) /* Either input size of zero or
                                              buffer must be there */
           )
          );

    strm_xml->pbuf      = pbuf;
    strm_xml->psize     = psize;
    strm_xml->format    = format;

    strm_xml->buf       = (pbuf != NULL) ? *pbuf : NULL;
    strm_xml->size      = (psize != NULL) ? *psize : 0;
    strm_xml->doc       = NULL;
    strm_xml->prnt      = NULL;
    strm_xml->cur       = NULL;
    strm_xml->changed   = false;

    return true;
}


static bool
hidrd_strm_xml_being_read(const hidrd_strm *strm)
{
    const hidrd_strm_xml_inst  *strm_xml    =
                                    (const hidrd_strm_xml_inst *)strm;

    return strm_xml->doc != NULL && !strm_xml->changed;
}


static bool
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
hidrd_strm_xml_read_buf(hidrd_strm *strm)
{
    hidrd_strm_xml_inst    *strm_xml    = (hidrd_strm_xml_inst *)strm;

    assert(strm_xml->doc == NULL);
    assert(strm_xml->prnt == NULL);
    assert(strm_xml->cur == NULL);

    /* If there is no input */
    if (strm_xml->size == 0)
        return false;

    strm_xml->doc = xmlParseMemory(*strm_xml->pbuf, *strm_xml->psize);
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


static const hidrd_item *
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


static bool
hidrd_strm_xml_write(hidrd_strm *strm, const hidrd_item *item)
{
    hidrd_strm_xml_inst    *strm_xml    = (hidrd_strm_xml_inst *)strm;

    assert(!hidrd_strm_xml_being_read(strm));

    if (strm_xml->doc == NULL)
    {
        assert(strm_xml->prnt == NULL);
        assert(strm_xml->cur == NULL);

        strm_xml->doc = xmlNewDoc(BAD_CAST "1.1");
        if (strm_xml->doc == NULL)
        {
            strm->error = true;
            return false;
        }

        strm_xml->prnt = xmlNewNode(NULL, BAD_CAST "descriptor");
        if (strm_xml->prnt == NULL)
        {
            xmlFreeDoc(strm_xml->doc);
            strm_xml->doc = NULL;
            strm->error = true;
            return false;
        }

        xmlDocSetRootElement(strm_xml->doc, strm_xml->prnt);
    }

    assert(strm_xml->prnt != NULL);

    if (hidrd_item_usage_page_valid(item))
    {
        char        buf[6];
        int         rc;

        rc = snprintf(buf, sizeof(buf), "%hu",
                      hidrd_item_usage_page_get_value(item));
        assert(rc < (int)sizeof(buf));

        xmlNewTextChild(strm_xml->prnt, NULL,
                        BAD_CAST "usage_page",
                        BAD_CAST buf);
    }
    else if (hidrd_item_usage_valid(item))
    {
        char        buf[11];
        int         rc;

        rc = snprintf(buf, sizeof(buf), "%u",
                      hidrd_item_usage_get_value(item));
        assert(rc < (int)sizeof(buf));

        xmlNewTextChild(strm_xml->prnt, NULL,
                        BAD_CAST "usage",
                        BAD_CAST buf);
    }

    strm_xml->changed = true;

    return true;
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
    if (strm_xml->pbuf != NULL)
        *strm_xml->pbuf = new_buf;
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
    if (strm_xml->psize != NULL)
        *strm_xml->psize = strm_xml->size;

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


const hidrd_strm_type hidrd_strm_xml = {
    .size   = sizeof(hidrd_strm_xml_inst),
    .init   = hidrd_strm_xml_init,
    .valid  = hidrd_strm_xml_valid,
    .read   = hidrd_strm_xml_read,
    .write  = hidrd_strm_xml_write,
    .flush  = hidrd_strm_xml_flush,
    .clnp   = hidrd_strm_xml_clnp,
};



/** @file
 * @brief HID report descriptor - stream instance
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

#include <ctype.h>
#include <stdio.h>
#include "hidrd/strm/opt_list.h"
#include "hidrd/strm/inst.h"


bool
hidrd_strm_valid(const hidrd_strm *strm)
{
    return strm != NULL &&
           hidrd_strm_type_valid(strm->type) &&
           (strm->type->valid == NULL || (*strm->type->valid)(strm));
}


bool
hidrd_strm_writable(const hidrd_strm *strm)
{
    assert(hidrd_strm_valid(strm));

    return (strm->type->write != NULL);
}


bool
hidrd_strm_readable(const hidrd_strm *strm)
{
    assert(hidrd_strm_valid(strm));

    return (strm->type->read != NULL);
}


bool
hidrd_strm_error(const hidrd_strm *strm)
{
    assert(hidrd_strm_valid(strm));

    return strm->error;
}


hidrd_strm *
hidrd_strm_alloc(const hidrd_strm_type *type)
{
    hidrd_strm *strm;

    assert(hidrd_strm_type_valid(type));

    strm = calloc(1, type->size);
    if (strm != NULL)
        strm->type = type;

    return strm;
}


bool
hidrd_strm_initv(hidrd_strm *strm, void **pbuf, size_t *psize, va_list ap)
{
    assert(strm != NULL);
    assert(hidrd_strm_type_valid(strm->type));

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

    strm->pbuf  = pbuf;
    strm->psize = psize;
    strm->error = false;

    if (strm->type->init != NULL)
        if (!(*strm->type->init)(strm, ap))
            return false;

    assert(hidrd_strm_valid(strm));

    return true;
}


bool
hidrd_strm_init(hidrd_strm *strm, void **pbuf, size_t *psize, ...)
{
    bool    result;
    va_list ap;

    va_start(ap, psize);
    result = hidrd_strm_initv(strm, pbuf, psize, ap);
    va_end(ap);

    return result;
}


#ifdef HIDRD_STRM_WITH_OPTS
bool
hidrd_strm_opts_initf(hidrd_strm *strm,
                      void **pbuf, size_t *psize,
                      const char *opts_fmt, ...)
{
    va_list         ap;
    bool            result      = false;
    char           *opts_buf    = NULL;
    hidrd_strm_opt *opt_list    = NULL;

    assert(strm != NULL);
    assert(hidrd_strm_type_valid(strm->type));

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
    assert(opts_fmt != NULL);

    va_start(ap, opts_fmt);

    strm->pbuf  = pbuf;
    strm->psize = psize;
    strm->error = false;

    /* Format option string */
    if (vasprintf(&opts_buf, opts_fmt, ap) < 0)
        goto cleanup;

    /* Parse option string into option list */
    opt_list = hidrd_strm_opt_list_parse(opts_buf);
    if (opt_list == NULL)
        goto cleanup;

    /* If there is opts_init member */
    if (strm->type->opts_init != NULL)
    {
        /* Initialize with option list */
        if (!(*strm->type->opts_init)(strm, opt_list))
            return false;
    }
    else
    {
        /* If the option list is not empty */
        if (!hidrd_strm_opt_list_empty(opt_list))
            return false;
    }

    assert(hidrd_strm_valid(strm));

    result = true;

cleanup:

    free(opt_list);
    free(opts_buf);
    va_end(ap);

    return true;
}


bool
hidrd_strm_opts_init(hidrd_strm *strm,
                     void **pbuf, size_t *psize, const char *opts)
{
    return hidrd_strm_opts_initf(strm, pbuf, psize, "%s", opts);
}
#endif /* HIDRD_STRM_WITH_OPTS */


hidrd_strm *
hidrd_strm_open(const hidrd_strm_type  *type,
                void                  **pbuf,
                size_t                 *psize,
                ...)
{
    hidrd_strm *strm;
    bool        result;
    va_list     ap;

    /* Allocate */
    strm = hidrd_strm_alloc(type);
    if (strm == NULL)
        return NULL;

    /* Initialize */
    va_start(ap, psize);
    result = hidrd_strm_initv(strm, pbuf, psize, ap);
    va_end(ap);
    if (!result)
        return NULL;

    return strm;
}


const hidrd_item *
hidrd_strm_read(hidrd_strm *strm)
{
    assert(hidrd_strm_valid(strm));
    assert(hidrd_strm_readable(strm));

    return (*strm->type->read)(strm);
}


bool
hidrd_strm_write(hidrd_strm *strm, const hidrd_item *item)
{
    assert(hidrd_strm_valid(strm));
    assert(hidrd_strm_writable(strm));
    assert(hidrd_item_valid(item));

    return (*strm->type->write)(strm, item);
}


bool
hidrd_strm_flush(hidrd_strm *strm)
{
    assert(hidrd_strm_valid(strm));

    return (strm->type->flush == NULL) ||
           (*strm->type->flush)(strm);
}


void
hidrd_strm_free(hidrd_strm *strm)
{
    assert(strm == NULL || hidrd_strm_valid(strm));

    if (strm == NULL)
        return;

    if (strm->type->clnp != NULL)
        (*strm->type->clnp)(strm);

    free(strm);
}


bool
hidrd_strm_close(hidrd_strm *strm)
{
    assert(hidrd_strm_valid(strm));

    if (!hidrd_strm_flush(strm))
        return false;

    hidrd_strm_free(strm);

    return true;
}



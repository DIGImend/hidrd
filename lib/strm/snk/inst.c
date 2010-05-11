/** @file
 * @brief HID report descriptor - stream instance
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

#include <stdio.h>
#include "hidrd/opt/spec_list.h"
#include "hidrd/strm/snk/inst.h"


bool
hidrd_snk_valid(const hidrd_snk *snk)
{
    return snk != NULL &&
           hidrd_snk_type_valid(snk->type) &&
           (snk->type->valid == NULL || (*snk->type->valid)(snk));
}


char *
hidrd_snk_errmsg(const hidrd_snk *snk)
{
    assert(hidrd_snk_valid(snk));
    return (*snk->type->errmsg)(snk);
}


/**
 * Allocate (an uninitialized, but zeroed) sink instance of specified type
 * (set the type field).
 *
 * @param type  Sink type to allocate instance of.
 *
 * @return Uninitialized instance of the specified sink type, or NULL if
 *         failed to allocate memory.
 */
static hidrd_snk *
hidrd_snk_alloc(const hidrd_snk_type *type)
{
    hidrd_snk *snk;

    assert(hidrd_snk_type_valid(type));

    snk = calloc(1, type->size);
    if (snk != NULL)
        snk->type = type;

    return snk;
}


/**
 * Initialize sink instance (va_list version).
 *
 * @param snk   Sink instance to initialize.
 * @param perr  Location for a dynamically allocated error message pointer,
 *              in case the initialization failed, or for a dynamically
 *              allocated empty string otherwise; could be NULL.
 * @param pbuf  Location of sink buffer pointer.
 * @param psize Location of sink buffer size.
 * @param ap    Sink type-specific arguments.
 *
 * @return True if initialization succeeded, false otherwise.
 */
static bool
hidrd_snk_initv(hidrd_snk  *snk,
                char      **perr,
                void      **pbuf,
                size_t     *psize,
                va_list     ap)
{
    assert(snk != NULL);
    assert(hidrd_snk_type_valid(snk->type));

    assert(pbuf == NULL ||  /* No location of/for buffer,
                               maybe location of/for size */
           (
            pbuf != NULL && psize != NULL && /* Location of/for both
                                                buffer and size */
            (*psize == 0 || *pbuf != NULL) /* Either size of zero or
                                              buffer must be there */
           )
          );

    snk->pbuf  = pbuf;
    snk->psize = psize;

    if (snk->type->init != NULL)
    {
        if (!(*snk->type->init)(snk, perr, ap))
            return false;
    }
    else if (perr != NULL)
        *perr = strdup("");

    assert(hidrd_snk_valid(snk));

    return true;
}


/**
 * Initialize sink instance.
 *
 * @param snk   Sink instance to initialize.
 * @param perr  Location for a dynamically allocated error message pointer,
 *              in case the initialization failed, or for a dynamically
 *              allocated empty string otherwise; could be NULL.
 * @param pbuf  Location of sink buffer pointer.
 * @param psize Location of sink buffer size.
 * @param ...   Sink type-specific arguments.
 *
 * @return True if initialization succeeded, false otherwise.
 */
static bool
hidrd_snk_init(hidrd_snk   *snk,
               char       **perr,
               void       **pbuf,
               size_t      *psize,
               ...)
{
    bool    result;
    va_list ap;

    va_start(ap, psize);
    result = hidrd_snk_initv(snk, perr, pbuf, psize, ap);
    va_end(ap);

    return result;
}


#ifdef HIDRD_WITH_OPT
/**
 * Initialize sink instance with an option string, formatted using
 * sprintf.
 *
 * @param snk       Sink instance to initialize.
 * @param perr      Location for a dynamically allocated error message
 *                  pointer, in case the initialization failed, or for a
 *                  dynamically allocated empty string otherwise; could be
 *                  NULL.
 * @param pbuf      Location of sink buffer pointer.
 * @param psize     Location of sink buffer size.
 * @param opts_fmt  Option format string: each option is a name/value pair
 *                  separated by equals sign, with surrounding space
 *                  removed; options are separated by comma.
 * @param ...       Option format arguments.
 *
 * @return True if initialization succeeded, false otherwise.
 */
static bool
hidrd_snk_init_optsf(hidrd_snk     *snk,
                     char         **perr,
                     void         **pbuf,
                     size_t        *psize,
                     const char    *opts_fmt,
                     ...)
                     __attribute__((format(printf, 5, 6)));
static bool
hidrd_snk_init_optsf(hidrd_snk     *snk,
                     char         **perr,
                     void         **pbuf,
                     size_t        *psize,
                     const char    *opts_fmt,
                     ...)
{
    static const hidrd_opt_spec empty_spec_list[] = {{.name = NULL}};

    va_list                 ap;
    bool                    result      = false;
    char                   *opts_buf    = NULL;
    const hidrd_opt_spec   *spec_list;
    hidrd_opt              *opt_list    = NULL;

    assert(snk != NULL);
    assert(hidrd_snk_type_valid(snk->type));
    assert(pbuf == NULL ||  /* No location of/for buffer,
                               maybe location of/for size */
           (
            pbuf != NULL && psize != NULL && /* Location of/for both
                                                buffer and size */
            (*psize == 0 || *pbuf != NULL) /* Either size of zero or
                                              buffer must be there */
           )
          );
    assert(opts_fmt != NULL);

    va_start(ap, opts_fmt);

    /* Retrieve option specification list */
    spec_list = snk->type->opts_spec;
    if (spec_list == NULL)
        spec_list = empty_spec_list;

    /* Format option string */
    if (vasprintf(&opts_buf, opts_fmt, ap) < 0)
    {
        if (perr != NULL)
            *perr = strdup("failed to format options string");
        goto cleanup;
    }

    /* Parse option list */
    opt_list = hidrd_opt_list_parse(spec_list, opts_buf);
    if (opt_list == NULL)
    {
        if (perr != NULL)
            *perr = strdup("failed to parse options string");
        goto cleanup;
    }

    /* If there is init_opts member */
    if (snk->type->init_opts != NULL)
    {
        /* Initialize with option list */
        snk->pbuf  = pbuf;
        snk->psize = psize;

        if (!(*snk->type->init_opts)(snk, perr, opt_list))
            goto cleanup;
    }
    else
    {
        /* Do the regular initialization */
        if (!hidrd_snk_init(snk, perr, pbuf, psize))
            goto cleanup;
    }

    assert(hidrd_snk_valid(snk));

    result = true;

cleanup:

    free(opt_list);
    free(opts_buf);
    va_end(ap);

    return result;
}


/**
 * Initialize sink instance with an option string.
 *
 * @param snk   Sink instance to initialize.
 * @param perr  Location for a dynamically allocated error message pointer,
 *              in case the initialization failed, or for a dynamically
 *              allocated empty string otherwise; could be NULL.
 * @param pbuf  Location of sink buffer pointer.
 * @param psize Location of sink buffer size.
 * @param opts  Option string: each option is a name/value pair separated by
 *              equals sign, with surrounding space removed; options are
 *              separated by comma.
 *
 * @return True if initialization succeeded, false otherwise.
 */
static bool
hidrd_snk_init_opts(hidrd_snk      *snk,
                    char          **perr,
                    void          **pbuf,
                    size_t         *psize,
                    const char     *opts)
{
    return hidrd_snk_init_optsf(snk, perr, pbuf, psize, "%s", opts);
}


hidrd_snk *
hidrd_snk_new_opts(const hidrd_snk_type    *type,
                   char                   **perr,
                   void                   **pbuf,
                   size_t                  *psize,
                   const char              *opts)
{
    hidrd_snk *snk;

    assert(opts != NULL);

    /* Allocate */
    snk = hidrd_snk_alloc(type);
    if (snk == NULL)
    {
        if (perr != NULL)
            *perr = strdup("instance allocation failed");
        return NULL;
    }

    /* Initialize */
    if (!hidrd_snk_init_opts(snk, perr, pbuf, psize, opts))
        return NULL;

    return snk;
}
#endif /* HIDRD_WITH_OPT */


hidrd_snk *
hidrd_snk_new(const hidrd_snk_type     *type,
              char                    **perr,
              void                    **pbuf,
              size_t                   *psize,
              ...)
{
    hidrd_snk *snk;
    bool        result;
    va_list     ap;

    /* Allocate */
    snk = hidrd_snk_alloc(type);
    if (snk == NULL)
    {
        if (perr != NULL)
            *perr = strdup("instance allocation failed");
        return NULL;
    }

    /* Initialize */
    va_start(ap, psize);
    result = hidrd_snk_initv(snk, perr, pbuf, psize, ap);
    va_end(ap);
    if (!result)
        return NULL;

    return snk;
}


bool
hidrd_snk_put(hidrd_snk *snk, const hidrd_item *item)
{
    assert(hidrd_snk_valid(snk));
    assert(hidrd_item_valid(item));

    return (*snk->type->put)(snk, item);
}


bool
hidrd_snk_flush(hidrd_snk *snk)
{
    assert(hidrd_snk_valid(snk));

    return (snk->type->flush == NULL) ||
           (*snk->type->flush)(snk);
}


/**
 * Cleanup sink instance - free any internal data, but don't free the
 * sink itself.
 *
 * @param snk  Sink instance to cleanup.
 */
static void
hidrd_snk_clnp(hidrd_snk *snk)
{
    assert(hidrd_snk_valid(snk));

    if (snk->type->clnp != NULL)
        (*snk->type->clnp)(snk);
}


/**
 * Free sink instance without freeing any internal data.
 *
 * @param snk  Sink instance to free.
 */
static void
hidrd_snk_free(hidrd_snk *snk)
{
    if (snk == NULL)
        return;

    assert(hidrd_snk_type_valid(snk->type));

    free(snk);
}


void
hidrd_snk_delete(hidrd_snk *snk)
{
    assert(snk == NULL || hidrd_snk_valid(snk));
    if (snk == NULL)
        return;
    hidrd_snk_clnp(snk);
    hidrd_snk_free(snk);
}


bool
hidrd_snk_close(hidrd_snk *snk)
{
    assert(snk == NULL || hidrd_snk_valid(snk));

    if (snk == NULL)
        return true;

    if (!hidrd_snk_flush(snk))
        return false;

    hidrd_snk_delete(snk);

    return true;
}



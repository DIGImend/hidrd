/** @file
 * @brief HID report descriptor - stream source instance
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
#include "hidrd/strm/src/inst.h"


bool
hidrd_src_valid(const hidrd_src *src)
{
    return src != NULL &&
           hidrd_src_type_valid(src->type) &&
           (src->buf != NULL || src->size == 0) &&
           (src->type->valid == NULL || (*src->type->valid)(src));
}


bool
hidrd_src_error(const hidrd_src *src)
{
    assert(hidrd_src_valid(src));

    return src->error;
}


/**
 * Allocate (an uninitialized, but zeroed) source instance of specified
 * type and set the type field.
 *
 * @param type  Source type to create instance of.
 *
 * @return Uninitialized instance of the specified source type.
 */
static hidrd_src *
hidrd_src_alloc(const hidrd_src_type *type)
{
    hidrd_src *src;

    assert(hidrd_src_type_valid(type));

    src = calloc(1, type->size);
    if (src != NULL)
        src->type = type;

    return src;
}


/**
 * Initialize source instance (va_list version).
 *
 * @param src   Source instance to initialize.
 * @param buf   Source buffer pointer.
 * @param size  Source buffer size.
 * @param ap    Source type-specific arguments.
 *
 * @return True if initialization succeeded, false otherwise.
 */
static bool
hidrd_src_initv(hidrd_src *src, const void *buf, size_t size, va_list ap)
{
    assert(src != NULL);
    assert(hidrd_src_type_valid(src->type));
    assert(buf != NULL || size == 0);

    src->buf    = buf;
    src->size   = size;
    src->error  = false;

    if (src->type->init != NULL)
        if (!(*src->type->init)(src, ap))
            return false;

    assert(hidrd_src_valid(src));

    return true;
}


/**
 * Initialize source instance.
 *
 * @param src   Source instance to initialize.
 * @param buf   Source buffer pointer.
 * @param size  Source buffer size.
 * @param ...   Source type-specific arguments.
 *
 * @return True if initialization succeeded, false otherwise.
 */
static bool
hidrd_src_init(hidrd_src *src, const void *buf, size_t size, ...)
{
    bool    result;
    va_list ap;

    va_start(ap, size);
    result = hidrd_src_initv(src, buf, size, ap);
    va_end(ap);

    return result;
}


#ifdef HIDRD_WITH_OPT
/**
 * Initialize source instance with an option string, formatted using
 * sprintf.
 *
 * @param src       Source instance to initialize.
 * @param buf       Source buffer pointer.
 * @param size      Source buffer size.
 * @param opts_fmt  Option format string: each option is a name/value pair
 *                  separated by equals sign, with surrounding space
 *                  removed; options are separated by comma.
 * @param ...       Option format arguments.
 *
 * @return True if initialization succeeded, false otherwise.
 */
static bool
hidrd_src_init_optsf(hidrd_src *src,
                     const void *buf, size_t size,
                     const char *opts_fmt, ...)
                     __attribute__((format(printf, 4, 5)));
static bool
hidrd_src_init_optsf(hidrd_src *src,
                     const void *buf, size_t size,
                     const char *opts_fmt, ...)
{
    static const hidrd_opt_spec empty_spec_list[] = {{.name = NULL}};

    va_list                 ap;
    bool                    result      = false;
    char                   *opts_buf    = NULL;
    const hidrd_opt_spec   *spec_list;
    hidrd_opt              *opt_list    = NULL;

    assert(src != NULL);
    assert(hidrd_src_type_valid(src->type));
    assert(buf != NULL || size == 0);
    assert(opts_fmt != NULL);

    va_start(ap, opts_fmt);

    /* Retrieve option specification list */
    spec_list = src->type->opts_spec;
    if (spec_list == NULL)
        spec_list = empty_spec_list;

    /* Format option string */
    if (vasprintf(&opts_buf, opts_fmt, ap) < 0)
        goto cleanup;

    /* Parse option list */
    opt_list = hidrd_opt_list_parse(spec_list, opts_buf);
    if (opt_list == NULL)
        goto cleanup;

    /* If there is init_opts member */
    if (src->type->init_opts != NULL)
    {
        /* Initialize with option list */
        src->buf    = buf;
        src->size   = size;
        src->error  = false;

        if (!(*src->type->init_opts)(src, opt_list))
            goto cleanup;
    }
    else
    {
        /* Do the regular initialization */
        if (!hidrd_src_init(src, buf, size))
            goto cleanup;
    }

    assert(hidrd_src_valid(src));

    result = true;

cleanup:

    free(opt_list);
    free(opts_buf);
    va_end(ap);

    return result;
}


/**
 * Initialize source instance with an option string.
 *
 * @param src   Source instance to initialize.
 * @param buf   Source buffer pointer.
 * @param size  Source buffer size.
 * @param opts  Option string: each option is a name/value pair separated by
 *              equals sign, with surrounding space removed; options are
 *              separated by comma.
 *
 * @return True if initialization succeeded, false otherwise.
 */
static bool
hidrd_src_init_opts(hidrd_src *src,
                     const void *buf, size_t size, const char *opts)
{
    return hidrd_src_init_optsf(src, buf, size, "%s", opts);
}


hidrd_src *
hidrd_src_new_opts(const hidrd_src_type *type,
                   const void *buf, size_t size,
                   const char *opts)
{
    hidrd_src  *src;

    assert(opts != NULL);

    /* Allocate */
    src = hidrd_src_alloc(type);
    if (src == NULL)
        return NULL;

    /* Initialize */
    if (!hidrd_src_init_opts(src, buf, size, opts))
        return NULL;

    return src;
}
#endif /* HIDRD_WITH_OPT */


hidrd_src *
hidrd_src_new(const hidrd_src_type  *type,
              const void *buf, size_t size, ...)
{
    hidrd_src *src;
    bool        result;
    va_list     ap;

    /* Allocate */
    src = hidrd_src_alloc(type);
    if (src == NULL)
        return NULL;

    /* Initialize */
    va_start(ap, size);
    result = hidrd_src_initv(src, buf, size, ap);
    va_end(ap);
    if (!result)
        return NULL;

    return src;
}


const hidrd_item *
hidrd_src_get(hidrd_src *src)
{
    assert(hidrd_src_valid(src));

    return (*src->type->get)(src);
}


/**
 * Cleanup source instance - free any internal data, but don't free the
 * source itself.
 *
 * @param src  Source instance to cleanup.
 */
static void
hidrd_src_clnp(hidrd_src *src)
{
    assert(hidrd_src_valid(src));

    if (src->type->clnp != NULL)
        (*src->type->clnp)(src);
}


/**
 * Free source instance without freeing any internal data.
 *
 * @param src  Source instance to free.
 */
static void
hidrd_src_free(hidrd_src *src)
{
    if (src == NULL)
        return;

    assert(hidrd_src_type_valid(src->type));

    free(src);
}


void
hidrd_src_delete(hidrd_src *src)
{
    assert(hidrd_src_valid(src));
    hidrd_src_clnp(src);
    hidrd_src_free(src);
}



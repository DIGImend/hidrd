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


hidrd_src *
hidrd_src_alloc(const hidrd_src_type *type)
{
    hidrd_src *src;

    assert(hidrd_src_type_valid(type));

    src = calloc(1, type->size);
    if (src != NULL)
        src->type = type;

    return src;
}


bool
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


bool
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
bool
hidrd_src_opts_initf(hidrd_src *src,
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
    opt_list = hidrd_opt_spec_list_apply_parse(spec_list, opts_buf);
    if (opt_list == NULL)
        goto cleanup;

    /* If there is opts_init member */
    if (src->type->opts_init != NULL)
    {
        /* Initialize with option list */
        src->buf    = buf;
        src->size   = size;
        src->error  = false;

        if (!(*src->type->opts_init)(src, opt_list))
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

    return true;
}


bool
hidrd_src_opts_init(hidrd_src *src,
                     const void *buf, size_t size, const char *opts)
{
    return hidrd_src_opts_initf(src, buf, size, "%s", opts);
}


hidrd_src *
hidrd_src_opts_open(const hidrd_src_type *type,
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
    if (!hidrd_src_opts_init(src, buf, size, opts))
        return NULL;

    return src;
}
#endif /* HIDRD_WITH_OPT */


hidrd_src *
hidrd_src_open(const hidrd_src_type  *type,
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


void
hidrd_src_free(hidrd_src *src)
{
    assert(src == NULL || hidrd_src_valid(src));

    if (src == NULL)
        return;

    if (src->type->clnp != NULL)
        (*src->type->clnp)(src);

    /* Invalidate source */
    src->type = NULL;

    free(src);
}



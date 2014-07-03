/** @file
 * @brief HID report descriptor - utilities - growing buffer
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

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hidrd/util/buf.h"

void
hidrd_buf_init(hidrd_buf *buf)
{
    assert(buf != NULL);
    *buf = (hidrd_buf)HIDRD_BUF_EMPTY;
}


void
hidrd_buf_own(hidrd_buf *buf, void *ptr, size_t len, size_t size)
{
    assert(buf != NULL);
    assert(ptr != NULL || size == 0);
    assert(len <= size);
    buf->ptr = ptr;
    buf->len = len;
    buf->size = size;
}


bool
hidrd_buf_valid(const hidrd_buf *buf)
{
    return buf != NULL &&
           buf->len <= buf->size &&
           (buf->ptr != NULL || buf->size == 0);
}


void hidrd_buf_reset(hidrd_buf *buf)
{
    assert(hidrd_buf_valid(buf));

    buf->len = 0;
}


void
hidrd_buf_clnp(hidrd_buf *buf)
{
    if (buf == NULL)
        return;

    assert(hidrd_buf_valid(buf));

    free(buf->ptr);
    hidrd_buf_init(buf);
}


void
hidrd_buf_retention(hidrd_buf *buf)
{
    assert(hidrd_buf_valid(buf));

    buf->ptr = realloc(buf->ptr, buf->len);

    /* Well, this is a real disaster */
    assert(buf->ptr != NULL);

    buf->size = buf->len;
}


void
hidrd_buf_disown(hidrd_buf *buf, void **pptr, size_t *plen, size_t *psize)
{
    if (pptr != NULL)
        *pptr = buf->ptr;
    else
        free(buf->ptr);

    if (plen != NULL)
        *plen = buf->len;

    if (psize != NULL)
        *psize = buf->size;

    hidrd_buf_init(buf);
}


bool
hidrd_buf_grow(hidrd_buf *buf, size_t len)
{
    size_t  new_size;
    void   *new_ptr;

    assert(hidrd_buf_valid(buf));

    new_size = buf->size;

    /* A bit of optimization */
    if (len <= new_size)
        return true;

    /* Another bit of optimization */
    new_size = (new_size == 0)
                    ? HIDRD_BUF_MIN_SIZE
                    : (new_size + new_size / 2);

    /* XXX maybe it's not that efficient */
    while (len > new_size)
        new_size += new_size / 2;

    new_ptr = realloc(buf->ptr, new_size);
    if (new_ptr == NULL)
        return false;

    buf->ptr = new_ptr;
    buf->size = new_size;

    return true;
}


bool
hidrd_buf_add_span(hidrd_buf *buf, uint8_t val, size_t len)
{
    size_t  new_len;

    assert(hidrd_buf_valid(buf));

    new_len = buf->len + len;

    if (!hidrd_buf_grow(buf, new_len))
        return false;

    memset(buf->ptr + buf->len, val, len);
    buf->len = new_len;

    return true;
}


bool
hidrd_buf_add_vprintf(hidrd_buf *buf, const char *fmt, va_list ap)
{
    va_list ap_copy;
    int     str_len;
    size_t  new_len;

    assert(hidrd_buf_valid(buf));
    assert(fmt != NULL);

    va_copy(ap_copy, ap);
    str_len = vsnprintf(NULL, 0, fmt, ap_copy);
    va_end(ap_copy);
    if (str_len < 0)
        return false;

    new_len = buf->len + str_len;

    if (!hidrd_buf_grow(buf, new_len + 1))
        return false;

    vsnprintf(buf->ptr + buf->len, str_len + 1, fmt, ap);
    buf->len = new_len;

    return true;
}


bool
hidrd_buf_add_printf(hidrd_buf *buf, const char *fmt, ...)
{
    bool    result;
    va_list ap;

    assert(hidrd_buf_valid(buf));
    assert(fmt != NULL);

    va_start(ap, fmt);
    result = hidrd_buf_add_vprintf(buf, fmt, ap);
    va_end(ap);

    return result;
}


bool
hidrd_buf_add_ptr(hidrd_buf *buf, const void *ptr, size_t len)
{
    size_t  new_len;

    assert(hidrd_buf_valid(buf));
    assert(ptr != NULL || len == 0);

    new_len = buf->len + len;

    if (!hidrd_buf_grow(buf, new_len))
        return false;

    memcpy(buf->ptr + buf->len, ptr, len);
    buf->len = new_len;

    return true;
}


bool
hidrd_buf_add_str(hidrd_buf *buf, const char *str)
{
    assert(hidrd_buf_valid(buf));
    assert(str != NULL);

    return hidrd_buf_add_ptr(buf, str, strlen(str));
}


void
hidrd_buf_del(hidrd_buf *buf, size_t len)
{
    assert(hidrd_buf_valid(buf));
    assert(len <= buf->len);

    buf->len -= len;
}

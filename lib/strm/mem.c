/** @file
 * @brief HID report descriptor - memory stream
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

#include "hidrd/strm_mem.h"

typedef struct hidrd_strm_mem {
    hidrd_strm  strm;
    void       *buf;
    size_t      size;
    size_t      pos;
} hidrd_strm_mem;

bool
hidrd_strm_mem_init(hidrd_strm *strm, void *buf, size_t size)
{
    hidrd_strm_mem *strm_mem = (hidrd_strm_mem *)strm;

    assert(strm != NULL);

    if (buf == NULL && size != 0)
    {
        buf = malloc(size);
        if (buf == NULL)
            return false;
    }

    strm->buf = buf;
    strm->size = size;
    strm->pos = NULL;

    return true;
}

hidrd_strm *
hidrd_strm_mem_open(void *buf, size_t size)
{
    hidrd_strm *strm;

    strm = hidrd_strm_alloc(&hidrd_strm_type_mem);
    if (strm == NULL)
        return NULL;

    if (!hidrd_strm_mem_init(strm, buf, size))
    {
        hidrd_strm_free(strm);
        return false;
    }

    return strm;
}

const hidrd_strm_type hidrd_strm_type_mem {
    .size   = sizeof(hidrd_strm_mem),
    .init   = hidrd_strm_mem_init,
} hidrd_strm_type_mem;

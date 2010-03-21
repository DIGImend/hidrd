/** @file
 * @brief HID report descriptor - utilities - file descriptor operations
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
 * @(#) $Id: str.h 277 2010-03-15 21:04:04Z spb_nick $
 */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "hidrd/util/fd.h"

bool
hidrd_fd_read_whole(int fd, void **pbuf, size_t *psize)
{
    bool    result      = false;
    void   *buf         = NULL;
    void   *new_buf;
    size_t  alloc       = 0;
    size_t  new_alloc   = 4096;
    size_t  size        = 0;
    ssize_t read_size;

    new_buf = malloc(new_alloc);
    if (new_buf == NULL)
        goto cleanup;
    buf = new_buf;
    alloc = new_alloc;

    while ((read_size = read(fd, buf + size, alloc - size)) > 0)
    {
        size += read_size;

        if (size > alloc / 2)
        {
            new_alloc = alloc * 2;
            new_buf = realloc(buf, new_alloc);
            if (new_buf == NULL)
                goto cleanup;
            buf = new_buf;
            alloc = new_alloc;
        }
    }

    if (errno != 0)
        goto cleanup;

    new_buf = realloc(buf, size);
    if (size > 0 && new_buf == NULL)
        goto cleanup;
    buf = new_buf;
    alloc = size;

    if (pbuf != NULL)
    {
        *pbuf = buf;
        buf = NULL;
    }

    if (psize != NULL)
        *psize = size;

    result = true;

cleanup:

    free(buf);

    return result;
}


bool
hidrd_fd_write_whole(int fd, void *buf, size_t size)
{
    ssize_t write_size;

    while (size > 0)
    {
        write_size = write(fd, buf, size);
        if (write_size < 0)
            return false;
        size -= write_size;
        buf += write_size;
    }

    return true;
}



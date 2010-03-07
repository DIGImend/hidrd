/** @file
 * @brief HID report descriptor - utilities - hexadecimal conversions
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

#include <ctype.h>
#include <stdlib.h>
#include "hidrd/util/hex.h"


bool
hidrd_hex_buf_from_str(void        *buf,
                       size_t       size,
                       size_t      *plen,
                       const char  *str)
{
    bool        high;
    uint8_t     nibble;
    const char *p;
    char        c;
    uint8_t    *b;
    size_t      len;

    assert(buf != NULL || size == 0);
    assert(str != NULL);

    for (high = true, b = buf, len = 0, p = str; (c = *p) != '\0'; p++)
    {
        if (isspace(c))
            continue;

        if (c >= '0' && c <= '9')
            nibble = (uint8_t)c - '0';
        else if (c >= 'a' && c <= 'f')
            nibble = (uint8_t)c - 'a' + 0xA;
        else if (c >= 'A' && c <= 'F')
            nibble = (uint8_t)c - 'A' + 0xA;
        else
            return false;

        if (high)
        {
            if (len >= size)
                return false;
            *b = nibble << 4;
            high = false;
        }
        else
        {
            *b |= nibble;
            high = true;
            b++;
            len++;
        }
    }

    if (plen != NULL)
        *plen = len;

    return true;
}


char *
hidrd_hex_buf_to_str(void *buf, size_t size)
{
    static const char   map[16] = "0123456789ABCDEF";
    uint8_t            *bbuf    = (uint8_t *)buf;
    char               *str;
    char               *p;
    uint8_t             b;

    assert(buf != NULL || size == 0);

    str = malloc((size * 2) + 1);
    if (str == NULL)
        return NULL;

    for (p = str; size > 0; size--, bbuf++)
    {
        b = *bbuf;
        *p++ = map[b >> 4];
        *p++ = map[b & 0xF];
    }

    *p = '\0';

    return str;
}

/** @file
 * @brief HID report descriptor - hex dump source
 *
 * Copyright (C) 2014 Nikolai Kondrashov
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

#include <errno.h>
#include <string.h>
#include <ctype.h>
#include "hidrd/fmt/hex/src.h"

static bool
hidrd_hex_src_valid(const hidrd_src *src)
{
    const hidrd_hex_src_inst   *hex_src    =
                                        (const hidrd_hex_src_inst *)src;

    return (src->type->size >= sizeof(hidrd_hex_src_inst)) &&
           (hex_src->pos <= src->size) &&
           (hex_src->len <= sizeof(hex_src->buf));
}


static char *
hidrd_hex_src_errmsg(const hidrd_src *src)
{
    const hidrd_hex_src_inst   *hex_src =
                                    (const hidrd_hex_src_inst *)src;
    const char                 *msg;

    switch (hex_src->err)
    {
        case HIDRD_HEX_SRC_ERR_NONE:
            msg = "";
            break;
        case HIDRD_HEX_SRC_ERR_CHAR:
            msg = "invalid character";
            break;
        case HIDRD_HEX_SRC_ERR_NUM:
            msg = "invalid hexadecimal number";
            break;
        case HIDRD_HEX_SRC_ERR_SHORT:
            msg = "incomplete item";
            break;
        case HIDRD_HEX_SRC_ERR_INVALID:
            msg = "invalid item";
            break;
        default:
            assert(!"Unknown error code");
            return NULL;
    }

    return strdup(msg);
}


static size_t
hidrd_hex_src_getpos(const hidrd_src *src)
{
    const hidrd_hex_src_inst   *hex_src    = (hidrd_hex_src_inst *)src;

    return (hex_src->line > 0xFFFF ? 0xFFFF : (hex_src->line << 16)) |
           (hex_src->col > 0xFFFF ? 0xFFFF : hex_src->col);
}


static char *
hidrd_hex_src_fmtpos(const hidrd_src *src, size_t pos)
{
    char       *str;
    size_t      line    = (pos >> 16) & 0xFFFF;
    size_t      col     = pos & 0xFFFF;
    char        line_buf[16];
    char        col_buf[16];

    (void)src;

    if (line >= 0xFFFF)
        snprintf(line_buf, sizeof(line_buf), ">= 65536");
    else
        snprintf(line_buf, sizeof(line_buf), "%zu", line + 1);

    if (col >= 0xFFFF)
        snprintf(col_buf, sizeof(col_buf), ">= 65536");
    else
        snprintf(col_buf, sizeof(col_buf), "%zu", col + 1);

    if (asprintf(&str, "line %s, column %s", line_buf, col_buf) < 0)
        return NULL;

    return str;
}


/**
 * Read a byte from the source buffer into the decoded buffer.
 *
 * @param hex_src   The hex dump source instance to read the byte for.
 *
 * @return True if read successfully, false if end of buffer is reached or an
 *         error occurred. Error is set in the latter case.
 */
static bool
hidrd_hex_src_get_byte(hidrd_hex_src_inst *hex_src)
{
    hidrd_src  *src = &hex_src->src;
    size_t      pos     = hex_src->pos;
    uint8_t     byte    = 0;
    size_t      len     = 0;
    uint8_t     c;
    uint8_t     nibble;

    while (true) {
        if (pos >= src->size) {
            hex_src->pos = pos;
            if (len == 0)
                return false;
            else
                break;
        }
        c = ((uint8_t *)src->buf)[pos];
        if (isxdigit(c)) {
            if (len >= 8) {
                src->error = true;
                hex_src->err = HIDRD_HEX_SRC_ERR_NUM;
                return false;
            }
            if (c >= 'a') {
                nibble = c - 'a' + 10;
            } else if (c >= 'A') {
                nibble = c - 'A' + 10;
            } else {
                nibble = c - '0';
            }
            byte = (byte << 4) | nibble;
            len += 4;
            hex_src->col++;
        } else if (isspace(c)) {
            hex_src->pos = pos;
            if (c == '\n') {
                hex_src->line++;
                hex_src->col = 0;
            } else {
                hex_src->col++;
            }
            if (len > 0)
                break;
        } else {
            hex_src->pos = pos;
            src->error = true;
            hex_src->err = HIDRD_HEX_SRC_ERR_CHAR;
            return false;
        }
        pos++;
    }

    hex_src->buf[hex_src->len++] = byte;
    return true;
}


static const hidrd_item *
hidrd_hex_src_get(hidrd_src *src)
{
    hidrd_hex_src_inst *hex_src = (hidrd_hex_src_inst *)src;

    while (!hidrd_item_fits(hex_src->buf, hex_src->len, NULL)) {
        if (!hidrd_hex_src_get_byte(hex_src)) {
            if (hex_src->len > 0 && !src->error) {
                src->error = true;
                hex_src->err = HIDRD_HEX_SRC_ERR_SHORT;
            }
            return NULL;
        }
    }

    if (!hidrd_item_valid(hex_src->buf))
    {
        src->error = true;
        hex_src->err = HIDRD_HEX_SRC_ERR_INVALID;
        return NULL;
    }

    hex_src->len = 0;
    return hex_src->buf;
}


const hidrd_src_type hidrd_hex_src = {
    .size   = sizeof(hidrd_hex_src_inst),
    .valid  = hidrd_hex_src_valid,
    .getpos = hidrd_hex_src_getpos,
    .fmtpos = hidrd_hex_src_fmtpos,
    .errmsg = hidrd_hex_src_errmsg,
    .get    = hidrd_hex_src_get,
};



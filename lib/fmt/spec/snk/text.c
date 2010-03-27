/** @file
 * @brief HID report descriptor - specification example sink - text output
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
 * @(#) $Id: item.c 302 2010-03-23 12:44:41Z spb_nick $
 */

#include "text.h"

#define MIN_SIZE    1024

static bool
text_grow(hidrd_spec_snk_inst  *spec_snk, size_t new_pos)
{
    size_t  new_size;
    void   *new_buf;

    assert(spec_snk != NULL);

    new_size = spec_snk->size;

    /* A bit of optimization */
    if (new_pos < new_size)
        return true;

    /* Another bit of optimization */
    new_size = (new_size == 0) ? MIN_SIZE : new_size * 2;

    while (new_pos >= new_size)
        new_size *= 2;

    new_buf = realloc(spec_snk->buf, new_size);
    if (new_buf == NULL)
        return false;

    spec_snk->buf   = new_buf;
    spec_snk->size  = new_size;

    return true;
}


static bool
text_space(hidrd_spec_snk_inst  *spec_snk, size_t num)
{
    size_t  new_pos;

    assert(spec_snk != NULL);

    new_pos = spec_snk->pos + num;

    if (!text_grow(spec_snk, new_pos))
        return false;

    memset(spec_snk->buf + spec_snk->pos, ' ', num);
    spec_snk->pos = new_pos;

    return true;
}


static bool
text_indent(hidrd_spec_snk_inst    *spec_snk)
{
    assert(spec_snk != NULL);

    return text_space(spec_snk, spec_snk->indent * spec_snk->depth);
}


static bool
text_puts(hidrd_spec_snk_inst *spec_snk, const char *str)
{
    size_t  len;
    size_t  new_pos;

    assert(spec_snk != NULL);
    assert(str != NULL);

    len = strlen(str);
    new_pos = spec_snk->pos + len;

    if (!text_grow(spec_snk, new_pos))
        return false;

    memcpy(spec_snk->buf + spec_snk->pos, str, len);
    spec_snk->pos = new_pos;

    return true;
}


static bool
text_vprintf(hidrd_spec_snk_inst   *spec_snk,
             const char            *fmt,
             va_list                ap)
{
    va_list ap_copy;
    int     len;
    size_t  new_pos;

    assert(spec_snk != NULL);
    assert(fmt != NULL);

    va_copy(ap_copy, ap);
    len = vsnprintf(NULL, 0, fmt, ap_copy);
    va_end(ap_copy);
    if (len < 0)
        return false;

    new_pos = spec_snk->pos + len;

    if (!text_grow(spec_snk, new_pos + 1))
        return false;

    vsnprintf(spec_snk->buf + spec_snk->pos, len + 1, fmt, ap);
    spec_snk->pos = new_pos;

    return true;
}


static bool
text_printf(hidrd_spec_snk_inst    *spec_snk,
            const char             *fmt,
            ...)
           __attribute__((format(printf, 2, 3)));

static bool
text_printf(hidrd_spec_snk_inst    *spec_snk,
            const char             *fmt,
            ...)
{
    bool    result;
    va_list ap;

    assert(spec_snk != NULL);
    assert(fmt != NULL);

    va_start(ap, fmt);
    result = text_vprintf(spec_snk, fmt, ap);
    va_end(ap);

    return result;
}


bool
text_item(hidrd_spec_snk_inst  *spec_snk,
          const char           *name,
          const char           *value, 
          const char           *comment)
{
    return
        text_indent(spec_snk) &&
        (name == NULL ||
         text_puts(spec_snk, name)) &&
        (value == NULL ||
         text_printf(spec_snk,
                     ((name != NULL) ? " (%s)" : "(%s)"), value)) &&
        (comment == NULL ||
         text_printf(spec_snk,
                     ((name != NULL || value != NULL) ? " ; %s" : "; %s"),
                     comment)) &&
        text_puts(spec_snk, "\n");
}


bool
text_item_nt_valid(text_item_nt nt)
{
    switch (nt)
    {
        case TEXT_ITEM_NT_NONE:
        case TEXT_ITEM_NT_NAME:
        case TEXT_ITEM_NT_VALUE:
        case TEXT_ITEM_NT_COMMENT:
            return true;
        default:
            return false;
    }
}


static bool
text_itemvf(hidrd_spec_snk_inst *spec_snk, va_list ap)
{
    bool    result  = false;
    bool    end     = false;
    char   *nl[3]   = {[TEXT_ITEM_NT_NAME] = NULL,
                       [TEXT_ITEM_NT_VALUE] = NULL,
                       [TEXT_ITEM_NT_COMMENT] = NULL};

    while (!end)
    {
        text_item_nt    nt  = va_arg(ap, text_item_nt);

        assert(text_item_nt_valid(nt));

        if (nt == TEXT_ITEM_NT_NONE)
            end = true;
        else
        {
            hidrd_fmt_type  fmt = va_arg(ap, hidrd_fmt_type);
            char           *str;

            if (!hidrd_fmtpva(&str, fmt, &ap))
                goto cleanup;

            free(nl[nt]);
            nl[nt] = str;
        }
    }

    result = text_item(spec_snk,
                       nl[TEXT_ITEM_NT_NAME],
                       nl[TEXT_ITEM_NT_VALUE],
                       nl[TEXT_ITEM_NT_COMMENT]);

cleanup:

    while (!end)
    {
        text_item_nt    nt  = va_arg(ap, text_item_nt);

        assert(text_item_nt_valid(nt));

        if (nt == TEXT_ITEM_NT_NONE)
            end = true;
        else
        {
            hidrd_fmt_type  fmt = va_arg(ap, hidrd_fmt_type);

            hidrd_fmtfreepv(fmt, &ap);
        }
    }

    free(nl[TEXT_ITEM_NT_NAME]);
    free(nl[TEXT_ITEM_NT_VALUE]);
    free(nl[TEXT_ITEM_NT_COMMENT]);

    return result;
}


bool
text_itemf(hidrd_spec_snk_inst *spec_snk, ...)
{
    va_list ap;
    bool    result;

    va_start(ap, spec_snk);
    result = text_itemvf(spec_snk, ap);
    va_end(ap);

    return result;
}



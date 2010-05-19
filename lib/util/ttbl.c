/** @file
 * @brief HID report descriptor - utilities - text table
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

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "hidrd/util/buf.h"
#include "hidrd/util/ttbl.h"

#define obstack_chunk_alloc malloc
#define obstack_chunk_free  free

hidrd_ttbl *
hidrd_ttbl_new(void)
{
    hidrd_ttbl         *tbl;
    hidrd_ttbl_row     *row;
    hidrd_ttbl_cell    *cell;

    tbl = malloc(sizeof(*tbl));
    if (tbl == NULL)
        return NULL;

    obstack_init(&tbl->obstack);

    row = obstack_alloc(&tbl->obstack, sizeof(*row));
    row->next  = NULL;
    row->span  = SIZE_MAX;

    cell = obstack_alloc(&tbl->obstack, sizeof(*cell));
    cell->next = NULL;
    cell->span = SIZE_MAX;
    cell->text = NULL;

    row->cell = cell;

    tbl->row = row;

    return tbl;
}


/**
 * Set a table internally-allocated cell text, or remove the cell.
 *
 * @param tbl   Cell table to set the text into.
 * @param col   Cell column to set the text into.
 * @param line  Cell line to set the text into.
 * @param text  Text to set, or NULL to remove the cell.
 */
static void
hidrd_ttbl_seta(hidrd_ttbl  *tbl,
                size_t       col,
                size_t       line,
                char        *text)
{
    size_t              row_line;
    hidrd_ttbl_row     *row;
    hidrd_ttbl_row     *new_row;
    size_t              cell_col;
    hidrd_ttbl_cell    *cell;
    hidrd_ttbl_cell    *new_cell;

    assert(tbl != NULL);

    /* Lookup row */
    for (row_line = 0, row = tbl->row;
         line < row_line || line >= row_line + row->span;
         row_line += row->span, row = row->next);

    /* If it is not the exact row */
    if (line > row_line)
    {
        /* Insert a new row after the found one */
        new_row = obstack_alloc(&tbl->obstack, sizeof(*new_row));
        new_row->next = row->next;
        row->next = new_row;

        /* Split the original span */
        new_row->span = row->span - (line - row_line);
        row->span -= new_row->span;

        /* Add the cell */
        cell = obstack_alloc(&tbl->obstack, sizeof(*cell));
        cell->next = NULL;
        cell->span = SIZE_MAX;
        cell->text = NULL;
        new_row->cell = cell;

        /* Use the new row */
        row = new_row;
    }

    /* Lookup cell */
    for (cell_col = 0, cell = row->cell;
         col < cell_col || col >= cell_col + cell->span;
         cell_col += cell->span, cell = cell->next);

    /* If it is not the exact cell */
    if (col > cell_col)
    {
        /* Insert a new cell after the found one */
        new_cell = obstack_alloc(&tbl->obstack, sizeof(*new_cell));
        new_cell->next = cell->next;
        cell->next = new_cell;

        /* Split the original span */
        new_cell->span = cell->span - (col - cell_col);
        cell->span -= new_cell->span;

        /* Use the new cell */
        cell = new_cell;
    }

    /* Set the cell text */
    cell->text = text;
}

void
hidrd_ttbl_set(hidrd_ttbl  *tbl,
               size_t       col,
               size_t       line,
               const char  *text)
{
    hidrd_ttbl_set(tbl, col, line, 
                   (text == NULL)
                    ? NULL
                    : obstack_copy(&tbl->obstack, text, strlen(text) + 1));
}


bool
hidrd_ttbl_setvf(hidrd_ttbl    *tbl,
                 size_t         col,
                 size_t         line,
                 const char    *fmt,
                 va_list        ap)
{
    va_list     ap_copy;
    int         rc;
    size_t      size;
    char       *text;

    va_copy(ap_copy, ap);
    rc = vsnprintf(NULL, 0, fmt, ap_copy);
    va_end(ap_copy);
    if (rc < 0)
        return false;

    size = rc + 1;
    text = obstack_alloc(&tbl->obstack, size);

    vsnprintf(text, size, fmt, ap);

    hidrd_ttbl_seta(tbl, col, line, text);

    return true;
}


bool
hidrd_ttbl_setf(hidrd_ttbl  *tbl,
                size_t       col,
                size_t       line,
                const char  *fmt,
                ...)
{
    bool    result;
    va_list ap;

    va_start(ap, fmt);
    result = hidrd_ttbl_setvf(tbl, col, line, fmt, ap);
    va_end(ap);

    return result;
}

const char *
hidrd_ttbl_get(const hidrd_ttbl *tbl,
               size_t            col,
               size_t            line)
{
    size_t                  row_line;
    const hidrd_ttbl_row   *row;
    size_t                  cell_col;
    const hidrd_ttbl_cell  *cell;

    assert(tbl != NULL);

    /* Lookup the row */
    for (row_line = 0, row = tbl->row;
         line > row_line + row->span;
         row_line += row->span, row = row->next);

    if (line != row_line)
        return NULL;

    /* Lookup the cell */
    for (cell_col = 0, cell = row->cell;
         col > cell_col + cell->span;
         cell_col += cell->span, cell = cell->next);

    if (col != cell_col)
        return NULL;

    return cell->text;
}


void
hidrd_ttbl_delete(hidrd_ttbl *tbl)
{
    if (tbl == NULL)
        return;

    obstack_free(&tbl->obstack, tbl->row);
    tbl->row = NULL;

    free(tbl);
}


/** Column output strip */
typedef struct hidrd_ttbl_strip hidrd_ttbl_strip;
struct hidrd_ttbl_strip {
    hidrd_ttbl_strip   *next;       /**< Next strip */
    size_t              col;        /**< Column */
    size_t              max_len;    /**< Maximum length, characters */
    size_t              width;      /**< Strip width, characters */
};

static hidrd_ttbl_strip *
hidrd_ttbl_measure(struct obstack *obstack, const hidrd_ttbl *tbl)
{
    hidrd_ttbl_strip       *markup  = NULL;
    const hidrd_ttbl_row   *row;
    size_t                  col;
    const hidrd_ttbl_cell  *cell;
    hidrd_ttbl_strip      **pprev_next;
    hidrd_ttbl_strip       *strip;
    size_t                  len;

    for (row = tbl->row; row != NULL; row = row->next)
    {
        pprev_next = &markup;
        strip = markup;
        for (col = 0, cell = row->cell;
             cell != NULL;
             col += cell->span, cell = cell->next)
        {
            if (cell->text == NULL)
                continue;
            len = strlen(cell->text);

            /* Lookup the strip for the column */
            for (;strip != NULL && col > strip->col ;
                 pprev_next = &strip->next, strip = strip->next);

            if (strip != NULL && strip->col == col)
            {
                if (len > strip->max_len)
                    strip->max_len = len;
            }
            else
            {
                strip = obstack_alloc(obstack, sizeof(*strip));
                strip->next = *pprev_next;
                *pprev_next = strip;
                strip->col = col;
                strip->max_len = len;
            }
        }
    }

    return markup;
}


static hidrd_ttbl_strip *
hidrd_ttbl_distribute(hidrd_ttbl_strip *markup, size_t tabstop)
{
    for (; markup != NULL; markup = markup->next)
        markup->width =
            markup->max_len + (tabstop - markup->max_len % tabstop);

    return markup;
}


static bool
hidrd_ttbl_print(char **pbuf, size_t *psize,
                 const hidrd_ttbl *tbl, const hidrd_ttbl_strip *markup)
{
    bool                    result      = false;
    hidrd_buf               buf         = HIDRD_BUF_EMPTY;
    const hidrd_ttbl_row   *row;
    const hidrd_ttbl_strip *strip;
    size_t                  col;
    size_t                  pad;
    size_t                  len;
    const hidrd_ttbl_cell  *cell;
    bool                    got_text;

    for (row = tbl->row; row != NULL; row = row->next)
    {
        got_text = false;
        for (pad = 0, strip = markup, col = 0, cell = row->cell;
             cell != NULL;
             col += cell->span, cell = cell->next)
        {
            /* Lookup cell strip, adding to the field padding */
            for (; strip != NULL && strip->col < col;
                 pad += strip->width, strip = strip->next);

            if (cell->text == NULL)
                continue;

            got_text = true;

            /* Pad to the field start */
            if (!hidrd_buf_add_span(&buf, ' ', pad))
                goto cleanup;

            /* Output the text */
            len = strlen(cell->text);
            if (!hidrd_buf_add_ptr(&buf, cell->text, len))
                goto cleanup;

            /* Calculate padding to next field start */
            pad = strip->width - len;

            /* Move on to the next strip */
            strip = strip->next;
        }
        if (got_text && !hidrd_buf_add_span(&buf, '\n', 1))
            goto cleanup;
    }

    hidrd_buf_retension(&buf);
    hidrd_buf_detach(&buf, (void **)pbuf, psize);

    result = true;

cleanup:

    hidrd_buf_clnp(&buf);

    return result;
}


bool
hidrd_ttbl_render(char **pbuf, size_t *psize,
                  const hidrd_ttbl *tbl, size_t tabstop)
{
    struct obstack      obstack;
    hidrd_ttbl_strip   *markup;
    bool                result;

    obstack_init(&obstack);
    markup = hidrd_ttbl_measure(&obstack, tbl);
    hidrd_ttbl_distribute(markup, tabstop);
    result = hidrd_ttbl_print(pbuf, psize, tbl, markup);
    obstack_free(&obstack, markup);
    return result;
}

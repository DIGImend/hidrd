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

#ifndef __HIDRD_UTIL_TTBL_H__
#define __HIDRD_UTIL_TTBL_H__

#include <stdbool.h>
#include <stdarg.h>
#include <obstack.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Text table cell */
typedef struct hidrd_ttbl_cell hidrd_ttbl_cell;
struct hidrd_ttbl_cell {
    hidrd_ttbl_cell    *next;   /**< Next cell in the row */
    size_t              skip;   /**< Number of columns to skip after this
                                     cell */
    char               *text;   /**< Cell text; could be NULL */
};

/** Text table row */
typedef struct hidrd_ttbl_row hidrd_ttbl_row;
struct hidrd_ttbl_row {
    hidrd_ttbl_row     *next;   /**< Next row in the table */
    size_t              skip;   /**< Number of lines to skip after this
                                     row */
    hidrd_ttbl_cell    *cell;   /**< First cell; could be NULL */
};

/** Text table */
typedef struct hidrd_ttbl {
    struct obstack  obstack;    /**< Table data obstack */
    hidrd_ttbl_row *row;        /**< First row; could be NULL */
} hidrd_ttbl;

/**
 * Create an empty table.
 *
 * @return New empty table.
 */
extern hidrd_ttbl *hidrd_ttbl_new(void);

/**
 * Set a table cell text, or remove the cell.
 *
 * @param tbl   Cell table to set the text into.
 * @param col   Cell column to set the text into.
 * @param line  Cell line to set the text into.
 * @param text  Text to set, or NULL to remove the cell.
 */
extern void hidrd_ttbl_set(hidrd_ttbl  *tbl,
                           size_t       col,
                           size_t       line,
                           const char  *text);

/**
 * Set a table cell text, with printf formatting.
 *
 * @param tbl   Cell table to set the text into.
 * @param col   Cell column to set the text into.
 * @param line  Cell line to set the text into.
 * @param fmt   Format string for the text to set.
 * @param ...   Format arguments for the text to set.
 *
 * @return True if formatted successfully, false otherwise.
 */
extern bool hidrd_ttbl_setf(hidrd_ttbl *tbl,
                            size_t      col,
                            size_t      line,
                            const char *fmt,
                            ...);

/**
 * Set a table cell text, with printf formatting, va_list version.
 *
 * @param tbl   Cell table to set the text into.
 * @param col   Cell column to set the text into.
 * @param line  Cell line to set the text into.
 * @param fmt   Format string for the text to set.
 * @param ap    Format arguments for the text to set.
 *
 * @return True if formatted successfully, false otherwise.
 */
extern bool hidrd_ttbl_setvf(hidrd_ttbl    *tbl,
                             size_t         col,
                             size_t         line,
                             const char    *fmt,
                             va_list        ap);

/**
 * Get a table cell text.
 *
 * @param tbl   Cell table to set the text from.
 * @param col   Cell column to set the text from.
 * @param line  Cell line to set the text from.
 *
 * @return Cell text, or NULL, if there is no such cell.
 */
extern const char *hidrd_ttbl_get(const hidrd_ttbl *tbl,
                                  size_t            col,
                                  size_t            line);

/**
 * Destroy a table.
 *
 * @param tbl   The table to destroy.
 */
extern void hidrd_ttbl_delete(hidrd_ttbl *tbl);

/**
 * Render a table into a text.
 *
 * @param pbuf      Location for output text buffer pointer.
 * @param psize     Location for output text buffer size.
 * @param tbl       Table to render.
 * @param tabstop   Tabstop, characters.
 *
 * @return True if rendered successfully, false otherwise (on memory
 *         allocation failure).
 */
extern bool hidrd_ttbl_render(char **pbuf, size_t *psize,
                              const hidrd_ttbl *tbl, size_t tabstop);

/**
 * Insert empty columns into a table.
 *
 * @param tbl   Table to insert columns into.
 * @param col   Column number to insert columns at.
 * @param span  Number of columns to insert.
 */
extern void hidrd_ttbl_ins_cols(hidrd_ttbl *tbl, size_t col, size_t span);

/**
 * Insert empty rows into a table.
 *
 * @param tbl   Table to insert rows into.
 * @param line  Line number to insert rows at.
 * @param span  Number of rows to insert.
 */
extern void hidrd_ttbl_ins_rows(hidrd_ttbl *tbl, size_t line, size_t span);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_TTBL_H__ */

/** @file
 * @brief HID report descriptor - utilities - text table test
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
#include <errno.h>
#include <error.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hidrd/util/ttbl.h"

#define ERROR(_errno, _fmt, _args...) \
    error_at_line(1, _errno, __FILE__, __LINE__, _fmt, ##_args)

int
main(void)
{
    hidrd_ttbl *tbl;
    size_t      i;
    size_t      x;
    size_t      y;
    const char *str;
    size_t      val;
    char       *buf;
    size_t      size;
    const char *expected;

    hidrd_ttbl_delete(hidrd_ttbl_new());

    tbl = hidrd_ttbl_new();
    if (tbl == NULL)
        ERROR(errno, "Failed allocating the table");

    for (i = 0; i < 5; i++)
    {
        if (!hidrd_ttbl_setf(tbl,
                             i * 2 + 1,
                             i * 2 + 1,
                             "%zu", i * i))
            ERROR(errno, "Failed formatting cell value");
        if (!hidrd_ttbl_setf(tbl,
                             i * 2 + 1,
                             (4 - i) * 2 + 1,
                             "%zu", i * (4 - i)))
            ERROR(errno, "Failed formatting cell value");
    }

    for (y = 0; y < 5 * 2 + 1; y++)
        for (x = 0; x < 5 * 2 + 1; x++)
        {
            if (x == y && (x - 1) % 2 == 0)
            {
                str = hidrd_ttbl_get(tbl, x, y);
                if (str == NULL)
                    ERROR(0, "Unexpected NULL at (%zu, %zu)", x, y);
                val = strtoul(str, NULL, 10);
                if (val != ((x - 1) * (x - 1) / 4))
                    ERROR(0, "Unexpected value at (%zu, %zu): %zu", x, y, val);
            }
            else if ((10 - x) == y && (x - 1) % 2 == 0)
            {
                str = hidrd_ttbl_get(tbl, x, y);
                if (str == NULL)
                    ERROR(0, "Unexpected NULL at (%zu, %zu)", x, y);
                val = strtoul(str, NULL, 10);
                if (val != ((x - 1) * (y - 1) / 4))
                    ERROR(0, "Unexpected value at (%zu, %zu): %zu", x, y, val);
            }
            else
            {
                str = hidrd_ttbl_get(tbl, x, y);
                if (str != NULL)
                    ERROR(0, "Unexpected non-NULL value at (%zu, %zu): %s",
                          x, y, str);
            }
        }

    if (!hidrd_ttbl_render(&buf, &size, tbl, 4))
        ERROR(errno, "Failed rendering the table");

    expected =
        "0               0\n"
        "    1       3\n"
        "        4\n"
        "    3       9\n"
        "0               16\n";

    if (size != strlen(expected))
        ERROR(0, "Unexpected output length: %zu instead of %zu",
              size, strlen(expected));

    if (memcmp(buf, expected, size) != 0)
        ERROR(0, "Unexpected output:\n%.*s\ninstead of:\n%s",
              size, buf, expected);

    fprintf(stderr, "%.*s", size, buf);

    return 0;
}


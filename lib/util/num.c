/** @file
 * @brief HID report descriptor - utilities - number conversions
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
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "hidrd/util/dec.h"


bool
hidrd_num_u32_from_str(uint32_t *pnum, const char *str, hidrd_num_base base)
{
    /* Just to be safe on all archs */
    const unsigned long int     max     = UINT32_MAX;
    unsigned long int           num;
    const char                 *start;
    const char                 *end;

    assert(str != NULL);
    /* Only decimal and hexadecimal bases are supported */
    assert(base == HIDRD_NUM_BASE_DEC || base == HIDRD_NUM_BASE_HEX);

    /* Skip leading space ourselves */
    for (start = str; isspace(*start); start++);
    /* Defeat possible sign which strtoul interprets */
    if (!isdigit(*start))
        return false;

    /* Convert to number */
    errno = 0;
    num = strtoull(start, (char **)&end, base);
    /* Check for the conversion and range errors */
    if (errno != 0 || num > max)
        return false;

    /* Check that there is nothing left, but space */
    for (; isspace(*end); end++);
    if (*end != '\0')
        return false;

    /* All is OK */
    if (pnum != NULL)
        *pnum = (uint32_t)num;

    return true;
}


bool
hidrd_num_u16_from_str(uint16_t *pnum, const char *str, hidrd_num_base base)
{
    uint32_t    num;

    if (!hidrd_num_u32_from_str(&num, str, base))
        return false;

    if (num > UINT16_MAX)
        return false;

    if (pnum != NULL)
        *pnum = (uint16_t)num;

    return true;
}


bool
hidrd_num_u8_from_str(uint8_t *pnum, const char *str, hidrd_num_base base)
{
    uint32_t    num;

    if (!hidrd_num_u32_from_str(&num, str, base))
        return false;

    if (num > UINT8_MAX)
        return false;

    if (pnum != NULL)
        *pnum = (uint8_t)num;

    return true;
}


char *
hidrd_num_u32_to_str(uint32_t num, hidrd_num_base base)
{
    char   *str;

    /* Only decimal and hexadecimal bases are supported */
    assert(base == HIDRD_NUM_BASE_DEC || base == HIDRD_NUM_BASE_HEX);

    if (asprintf(&str, (base == HIDRD_NUM_BASE_DEC ? "%u" : "%X"), num) < 0)
        return NULL;

    return str;
}



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
#include <strings.h>
#include "hidrd/util/dec.h"


bool
hidrd_num_base_valid(hidrd_num_base base)
{
    return (base == HIDRD_NUM_BASE_DEC || base == HIDRD_NUM_BASE_HEX);
}


char
hidrd_num_base_to_char(hidrd_num_base base)
{
    assert(hidrd_num_base_valid(base));

    switch (base)
    {
        case HIDRD_NUM_BASE_DEC:
            return '\0';
        case HIDRD_NUM_BASE_HEX:
            return 'h';
        default:
            return '?';
    }
}


bool
hidrd_num_u32_from_str(uint32_t *pnum, const char *str, hidrd_num_base base)
{
    /* Just to be safe on all archs */
    const unsigned long int     max     = UINT32_MAX;
    unsigned long int           num;
    const char                 *start;
    const char                 *end;

    assert(str != NULL);
    assert(hidrd_num_base_valid(base));

    /* Skip leading space ourselves */
    for (start = str; isspace(*start); start++);
    /* Defeat possible sign which strtoul interprets */
    if (!((base == HIDRD_NUM_BASE_DEC)
                ? isdigit(*start)
                : isxdigit(*start)))
        return false;

    /* Convert to number */
    errno = 0;
    num = strtoul(start, (char **)&end, base);
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
hidrd_num_u32_from_bstr(uint32_t *pnum, const char *str)
{
    /* Just to be safe on all archs */
    const unsigned long int     max     = UINT32_MAX;
    const char                 *b;
    const char                 *b_end;
    hidrd_num_base              base;
    unsigned long int           num;
    const char                 *start;
    const char                 *end;

    assert(str != NULL);

    /* Lookup base character */
    for (b = index(str, '\0'); b > str && isspace(*b); b--)
    if (*b == 'h' || *b == 'H')
    {
        b_end = b;
        base = HIDRD_NUM_BASE_HEX;
    }
    else if (isdigit(*b))
    {
        b_end = b + 1;
        base = HIDRD_NUM_BASE_DEC;
    }
    else
        return false;

    /* Skip leading space ourselves */
    for (start = str; isspace(*start); start++);
    /* Defeat possible sign which strtoul interprets */
    if (!((base == HIDRD_NUM_BASE_DEC)
                ? isdigit(*start)
                : isxdigit(*start)))
        return false;

    /* Convert to number */
    errno = 0;
    num = strtoul(start, (char **)&end, base);
    /* Check for the conversion and range errors */
    if (errno != 0 || num > max)
        return false;

    /* Check that the number ends at the base character */
    if (end != b_end)
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

    assert(str != NULL);

    if (!hidrd_num_u32_from_str(&num, str, base))
        return false;

    if (num > UINT16_MAX)
        return false;

    if (pnum != NULL)
        *pnum = (uint16_t)num;

    return true;
}


bool
hidrd_num_u16_from_bstr(uint16_t *pnum, const char *str)
{
    uint32_t    num;

    assert(str != NULL);

    if (!hidrd_num_u32_from_bstr(&num, str))
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

    assert(str != NULL);

    if (!hidrd_num_u32_from_str(&num, str, base))
        return false;

    if (num > UINT8_MAX)
        return false;

    if (pnum != NULL)
        *pnum = (uint8_t)num;

    return true;
}


bool
hidrd_num_u8_from_bstr(uint8_t *pnum, const char *str)
{
    uint32_t    num;

    assert(str != NULL);

    if (!hidrd_num_u32_from_bstr(&num, str))
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

    assert(hidrd_num_base_valid(base));

    if (asprintf(&str, (base == HIDRD_NUM_BASE_DEC ? "%u" : "%X"), num) < 0)
        return NULL;

    return str;
}


char *
hidrd_num_u32_to_bstr(uint32_t num, hidrd_num_base base)
{
    char   *str;

    assert(hidrd_num_base_valid(base));

    if (asprintf(&str, (base == HIDRD_NUM_BASE_DEC ? "%u" : "%Xh"), num) < 0)
        return NULL;

    return str;
}


bool
hidrd_num_s32_from_str(int32_t *pnum, const char *str, hidrd_num_base base)
{
    /* Just to be safe on all archs */
    const long int  min     = INT32_MIN;
    /* Just to be safe on all archs */
    const long int  max     = INT32_MAX;
    long int        num;
    const char     *end;

    assert(str != NULL);
    assert(hidrd_num_base_valid(base));

    /* Convert to number */
    errno = 0;
    num = strtol(str, (char **)&end, base);
    /* Check for the conversion and range errors */
    if (errno != 0 || (num > max) || (num < min))
        return false;

    /* Check that there is nothing left, but space */
    for (; isspace(*end); end++);
    if (*end != '\0')
        return false;

    /* All is OK */
    if (pnum != NULL)
        *pnum = (int32_t)num;

    return true;
}


bool
hidrd_num_s32_from_bstr(int32_t *pnum, const char *str)
{
    /* Just to be safe on all archs */
    const long int  min     = INT32_MIN;
    /* Just to be safe on all archs */
    const long int  max     = INT32_MAX;
    const char     *b;
    const char     *b_end;
    hidrd_num_base  base;
    long int        num;
    const char     *end;

    assert(str != NULL);

    /* Lookup base character */
    for (b = index(str, '\0'); b > str && isspace(*b); b--)
    if (*b == 'h' || *b == 'H')
    {
        b_end = b;
        base = HIDRD_NUM_BASE_HEX;
    }
    else if (isdigit(*b))
    {
        b_end = b + 1;
        base = HIDRD_NUM_BASE_DEC;
    }
    else
        return false;

    /* Convert to number */
    errno = 0;
    num = strtol(str, (char **)&end, base);
    /* Check for the conversion and range errors */
    if (errno != 0 || (num > max) || (num < min))
        return false;

    /* Check that the number ends at the base character */
    if (end != b_end)
        return false;

    /* All is OK */
    if (pnum != NULL)
        *pnum = (int32_t)num;

    return true;
}


bool
hidrd_num_s16_from_str(int16_t *pnum, const char *str, hidrd_num_base base)
{
    int32_t num;

    assert(str != NULL);

    if (!hidrd_num_s32_from_str(&num, str, base))
        return false;

    if (num > INT16_MAX || num < INT16_MIN)
        return false;

    if (pnum != NULL)
        *pnum = (int16_t)num;

    return true;
}


bool
hidrd_num_s16_from_bstr(int16_t *pnum, const char *str)
{
    int32_t num;

    assert(str != NULL);

    if (!hidrd_num_s32_from_bstr(&num, str))
        return false;

    if (num > INT16_MAX || num < INT16_MIN)
        return false;

    if (pnum != NULL)
        *pnum = (int16_t)num;

    return true;
}


bool
hidrd_num_s8_from_str(int8_t *pnum, const char *str, hidrd_num_base base)
{
    int32_t num;

    assert(str != NULL);

    if (!hidrd_num_s32_from_str(&num, str, base))
        return false;

    if (num > INT8_MAX || num < INT8_MIN)
        return false;

    if (pnum != NULL)
        *pnum = (int8_t)num;

    return true;
}


bool
hidrd_num_s8_from_bstr(int8_t *pnum, const char *str)
{
    int32_t num;

    assert(str != NULL);

    if (!hidrd_num_s32_from_bstr(&num, str))
        return false;

    if (num > INT8_MAX || num < INT8_MIN)
        return false;

    if (pnum != NULL)
        *pnum = (int8_t)num;

    return true;
}


char *
hidrd_num_s32_to_str(int32_t num, hidrd_num_base base)
{
    char   *str;

    assert(hidrd_num_base_valid(base));

    if (asprintf(&str,
                 (base == HIDRD_NUM_BASE_DEC ? "%s%u" : "%s%X"),
                 (num >= 0 ? "" : "-"), (num >= 0 ? num : -num)) < 0)
        return NULL;

    return str;
}


char *
hidrd_num_s32_to_bstr(int32_t num, hidrd_num_base base)
{
    char   *str;

    assert(hidrd_num_base_valid(base));

    if (asprintf(&str,
                 (base == HIDRD_NUM_BASE_DEC ? "%s%u" : "%s%Xh"),
                 (num >= 0 ? "" : "-"), (num >= 0 ? num : -num)) < 0)
        return NULL;

    return str;
}


void
hidrd_num_u32_to_le(uint32_t *ple, uint32_t num)
{
    uint8_t *p  = (uint8_t *)ple;

    assert(ple != NULL);

    *p = num & 0xFF;
    p++;
    num >>= 8;
    *p = num & 0xFF;
    p++;
    num >>= 8;
    *p = num & 0xFF;
    p++;
    num >>= 8;
    *p = num & 0xFF;
}


uint32_t
hidrd_num_u32_from_le(const uint32_t *ple)
{
    const uint8_t  *p   = (const uint8_t *)ple;
    uint32_t        num;

    assert(ple != NULL);

    num = *p;
    num |= *++p << 8;
    num |= *++p << 16;
    num |= *++p << 24;

    return num;
}



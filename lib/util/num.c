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

#include <stdarg.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "hidrd/util/str.h"
#include "hidrd/util/num.h"


bool
hidrd_num_base_valid(hidrd_num_base base)
{
    switch (base)
    {
        case HIDRD_NUM_BASE_NONE:
        case HIDRD_NUM_BASE_DEC:
        case HIDRD_NUM_BASE_HEX:
            return true;
        default:
            return false;
    }
}


bool
hidrd_num_bmrk_valid(hidrd_num_bmrk bmrk)
{
    switch (bmrk)
    {
        case HIDRD_NUM_BMRK_NONE:
        case HIDRD_NUM_BMRK_SFX:
        case HIDRD_NUM_BMRK_PFX:
            return true;
        default:
            return false;
    }
}


/**
 * Find expected number end and base, if suffix base mark is expected.
 *
 * @param str       String to look through.
 * @param bmrk      Expected base mark type.
 * @param pbase     Location for base if suffix base mark is expected; could
 *                  be NULL.
 * @param pexp_end  Location for expected number end; could be NULL.
 *
 * @return True if the string is valid, false otherwise.
 */
static bool
find_exp_end_and_sfx_base(const char       *str,
                          hidrd_num_bmrk    bmrk,
                          hidrd_num_base   *pbase,
                          const char      **pexp_end)
{
    const char     *p;          /* Multi-purpose pointer */
    bool            text;       /* "Within text run" flag */
    const char     *exp_end;    /* Expected number end */
    hidrd_num_base  base    = HIDRD_NUM_BASE_NONE;

    assert(str != NULL);
    assert(hidrd_num_bmrk_valid(bmrk));

    /* Lookup right padding start */
    exp_end = NULL;
    text = false;
    p = str;
    while (true)
    {
        if (*p == '\0' || isspace(*p))
        {
            if (text)
            {
                exp_end = p;
                text = false;
            }
        }
        else
            text = true;

        if (*p == '\0')
            break;
        p++;
    }

    /* If there is nothing except padding (space) */
    if (exp_end == NULL)
        return false;

    /* If suffix base mark is expected */
    if (bmrk == HIDRD_NUM_BMRK_SFX)
    {
        p = exp_end - 1;
        if (*p == 'h' || *p == 'H')
        {
            exp_end = p;
            base = HIDRD_NUM_BASE_HEX;
        }
        else if (isdigit(*p))
            base = HIDRD_NUM_BASE_DEC;
        else
            return false;

        if (pbase != NULL)
            *pbase = base;
    }

    if (pexp_end != NULL)
        *pexp_end = exp_end;

    return true;
}


bool
hidrd_num_u32_from_str(uint32_t        *pnum,
                       const char      *str,
                       hidrd_num_bmrk   bmrk,
                       hidrd_num_base   base)
{
    /* Just to be safe on all archs */
    const unsigned long int     max         = UINT32_MAX;
    const char                 *exp_end;    /* Expected number end */
    const char                 *start;      /* Number start */;
    unsigned long int           num;        /* Converted number */;
    const char                 *end;        /* Number end strtoul reports */

    assert(str != NULL);
    assert(hidrd_num_bmrk_valid(bmrk));
    assert(hidrd_num_base_valid(base));
    assert(bmrk != HIDRD_NUM_BMRK_NONE || base != HIDRD_NUM_BASE_NONE);

    /* Lookup expected number end and base, if needed */
    if (!find_exp_end_and_sfx_base(str, bmrk, &base, &exp_end))
        return false;

    /* Skip leading space ourselves */
    for (start = str; isspace(*start); start++);
    /* Defeat possible negative sign which strtoul interprets */
    if (*start == '-')
        return false;

    /* Convert to number */
    errno = 0;
    num = strtoul(start, (char **)&end,
                  (bmrk == HIDRD_NUM_BMRK_PFX) ? 0 : base);
    /* Check for the conversion and range errors */
    if (errno != 0 || num > max)
        return false;

    /* Check that the number ends where expected */
    if (end != exp_end)
        return false;

    /* All is OK */
    if (pnum != NULL)
        *pnum = (uint32_t)num;

    return true;
}


bool
hidrd_num_s32_from_str(int32_t         *pnum,
                       const char      *str,
                       hidrd_num_bmrk   bmrk,
                       hidrd_num_base   base)
{
    /* Just to be safe on all archs */
    const long int  min     = INT32_MIN;
    /* Just to be safe on all archs */
    const long int  max     = INT32_MAX;

    const char     *exp_end;    /* Expected number end */
    long int        num;        /* Converted number */;
    const char     *end;        /* Number end strtoul reports */

    assert(str != NULL);
    assert(hidrd_num_bmrk_valid(bmrk));
    assert(hidrd_num_base_valid(base));
    assert(bmrk != HIDRD_NUM_BMRK_NONE || base != HIDRD_NUM_BASE_NONE);

    /* Lookup expected number end and base, if needed */
    if (!find_exp_end_and_sfx_base(str, bmrk, &base, &exp_end))
        return false;

    /* Convert to number */
    errno = 0;
    num = strtol(str, (char **)&end,
                 (bmrk == HIDRD_NUM_BMRK_PFX) ? 0 : base);
    /* Check for the conversion and range errors */
    if (errno != 0 || (num > max) || (num < min))
        return false;

    /* Check that the number ends where expected */
    if (end != exp_end)
        return false;

    /* All is OK */
    if (pnum != NULL)
        *pnum = (int32_t)num;

    return true;
}


char *
hidrd_num_u32_to_str(uint32_t num, hidrd_num_bmrk bmrk, hidrd_num_base base)
{
    char   *str;

    assert(hidrd_num_bmrk_valid(bmrk));
    assert(hidrd_num_base_valid(base));
    assert(base != HIDRD_NUM_BASE_NONE);

    if (base == HIDRD_NUM_BASE_HEX)
    {
        if (asprintf(&str,
                     ((bmrk == HIDRD_NUM_BMRK_NONE)
                        ? "%.*X"
                        : (bmrk == HIDRD_NUM_BMRK_SFX)
                            ? "%.*Xh"
                            : "0x%.*X"),
                     ((num == 0 && bmrk == HIDRD_NUM_BMRK_NONE)
                        ? 1
                        : num <= UINT8_MAX
                            ? 2
                            : num <= UINT16_MAX
                                ? 4
                                : 8),
                     (unsigned int)num) < 0)
            return NULL;
    }
    else
    {
        if (asprintf(&str, "%u", (unsigned int)num) < 0)
            return NULL;
    }

    return str;
}


char *
hidrd_num_s32_to_str(int32_t num, hidrd_num_bmrk bmrk, hidrd_num_base base)
{
    char   *str;

    assert(hidrd_num_bmrk_valid(bmrk));
    assert(hidrd_num_base_valid(base));
    assert(base != HIDRD_NUM_BASE_NONE);

    if (base == HIDRD_NUM_BASE_HEX)
    {
        const char *sgn;

        if (num >= 0)
            sgn = "";
        else
        {
            num = -num;
            sgn = "-";
        }

        if (asprintf(&str,
                     ((bmrk == HIDRD_NUM_BMRK_NONE)
                        ? "%s%.*X"
                        : (bmrk == HIDRD_NUM_BMRK_SFX)
                            ? "%s%.*Xh"
                            : "%s0x%.*X"),
                     sgn,
                     ((num == 0 && bmrk == HIDRD_NUM_BMRK_NONE)
                        ? 1
                        : num <= UINT8_MAX
                            ? 2
                            : num <= UINT16_MAX
                                ? 4
                                : 8),
                     (unsigned int)num) < 0)
            return NULL;
    }
    else
    {
        if (asprintf(&str, "%d", (int)num) < 0)
            return NULL;
    }

    return str;
}


#define U_FROM_STR_BODY(_b) \
    do {                                                    \
        uint32_t    num;                                    \
                                                            \
        assert(str != NULL);                                \
        assert(hidrd_num_bmrk_valid(bmrk));                 \
        assert(hidrd_num_base_valid(base));                 \
        assert(bmrk != HIDRD_NUM_BMRK_NONE ||               \
               base != HIDRD_NUM_BASE_NONE);                \
                                                            \
        if (!hidrd_num_u32_from_str(&num, str, bmrk, base)) \
            return false;                                   \
                                                            \
        if (num > UINT##_b##_MAX)                           \
            return false;                                   \
                                                            \
        if (pnum != NULL)                                   \
            *pnum = (uint##_b##_t)num;                      \
                                                            \
        return true;                                        \
    } while (0)


bool
hidrd_num_u16_from_str(uint16_t        *pnum,
                       const char      *str,
                       hidrd_num_bmrk   bmrk,
                       hidrd_num_base   base)
{
    U_FROM_STR_BODY(16);
}


bool
hidrd_num_u8_from_str(uint8_t          *pnum,
                      const char       *str,
                      hidrd_num_bmrk    bmrk,
                      hidrd_num_base    base)
{
    U_FROM_STR_BODY(8);
}


#define S_FROM_STR_BODY(_b) \
    do {                                                    \
        int32_t    num;                                     \
                                                            \
        assert(str != NULL);                                \
        assert(hidrd_num_bmrk_valid(bmrk));                 \
        assert(hidrd_num_base_valid(base));                 \
        assert(bmrk != HIDRD_NUM_BMRK_NONE ||               \
               base != HIDRD_NUM_BASE_NONE);                \
                                                            \
        if (!hidrd_num_s32_from_str(&num, str, bmrk, base)) \
            return false;                                   \
                                                            \
        if (num > INT##_b##_MAX || num < INT##_b##_MIN)     \
            return false;                                   \
                                                            \
        if (pnum != NULL)                                   \
            *pnum = (int##_b##_t)num;                       \
                                                            \
        return true;                                        \
    } while (0)


bool
hidrd_num_s16_from_str(int16_t         *pnum,
                       const char      *str,
                       hidrd_num_bmrk   bmrk,
                       hidrd_num_base   base)
{
    S_FROM_STR_BODY(16);
}


bool
hidrd_num_s8_from_str(int8_t           *pnum,
                      const char       *str,
                      hidrd_num_bmrk    bmrk,
                      hidrd_num_base    base)
{
    S_FROM_STR_BODY(8);
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


bool
hidrd_num_from_alt_str(void *pnum, const char *str, ...)
{
    va_list             ap;
    hidrd_num_parse_fn *fn;

    va_start(ap, str);

    while ((fn = va_arg(ap, hidrd_num_parse_fn *)) != NULL)
        if ((*fn)(pnum, str))
        {
            va_end(ap);
            return true;
        }

    va_end(ap);
    return false;
}


char *
hidrd_num_to_alt_str(size_t bits, ...)
{
    va_list             ap;
    char               *result      = NULL;
    unsigned int        n;
    char               *str         = NULL;
    void               *fmt_fn;
    hidrd_str_proc_fn  *proc_fn;
    char               *proc_str;

    assert(bits == 8 || bits == 16 || bits == 32);

    va_start(ap, bits);

    /*
     * This should handle smaller types since they are all promoted to int
     */
    n = va_arg(ap, unsigned int);

    while ((fmt_fn = va_arg(ap, void *)) != NULL)
    {
        errno = 0;

        switch (bits)
        {
            case 8:
                str = (*(hidrd_num_fmt8_fn *)fmt_fn)(n);
                break;
            case 16:
                str = (*(hidrd_num_fmt16_fn *)fmt_fn)(n);
                break;
            case 32:
                str = (*(hidrd_num_fmt32_fn *)fmt_fn)(n);
                break;
            default:
                errno = EINVAL;
                goto cleanup;
        }

        if (str == NULL)
        {
            if (errno != 0)
                goto cleanup;
            while ((proc_fn = va_arg(ap, hidrd_str_proc_fn *)) != NULL);
        }
        else
        {
            while ((proc_fn = va_arg(ap, hidrd_str_proc_fn *)) != NULL)
            {
                proc_str = (*proc_fn)(str);
                if (proc_str == NULL)
                {
                    errno = EINVAL;
                    goto cleanup;
                }
                str = proc_str;
            }
            break;
        }
    }

    result = str;
    str = NULL;

cleanup:

    free(str);
    va_end(ap);

    return result;
}



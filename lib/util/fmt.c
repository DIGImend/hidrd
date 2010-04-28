/** @file
 * @brief HID report descriptor - utilities - string formatting
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

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "hidrd/util/dec.h"
#include "hidrd/util/hex.h"
#include "hidrd/util/fmt.h"


bool
hidrd_fmtpva(char             **pstr,
             hidrd_fmt_type     type,
             va_list           *pap)
{
    char       *str;

    switch (type)
    {
        case HIDRD_FMT_TYPE_NULL:
            str = NULL;
            break;
        case HIDRD_FMT_TYPE_S32:
            str = HIDRD_DEC_TO_STR(s32, va_arg(*pap, int32_t));
            if (str == NULL)
                return false;
            break;
        case HIDRD_FMT_TYPE_U32:
            str = HIDRD_DEC_TO_STR(u32, va_arg(*pap, uint32_t));
            if (str == NULL)
                return false;
            break;
        case HIDRD_FMT_TYPE_STRDUP:
            {
                const char *arg = va_arg(*pap, const char *);

                assert(arg != NULL);

                str = strdup(arg);
                if (str == NULL)
                    return false;
            }
            break;
        case HIDRD_FMT_TYPE_STROWN:
            {
                char       *arg = va_arg(*pap, char *);

                assert(arg != NULL);

                str = arg;
            }
            break;
        case HIDRD_FMT_TYPE_HEX:
            {
                void   *buf     = va_arg(*pap, void *);
                size_t  size    = va_arg(*pap, size_t);

                assert(buf != NULL || size == 0);

                str = hidrd_hex_buf_to_str(buf, size);
                if (str == NULL)
                    return false;
            }
            break;
        case HIDRD_FMT_TYPE_BHEX:
            {
                void   *buf     = va_arg(*pap, void *);
                size_t  size    = va_arg(*pap, size_t);

                assert(buf != NULL || size == 0);

                str = hidrd_hex_buf_to_sstr(buf, size);
                if (str == NULL)
                    return false;
            }
            break;
        default:
            assert(!"Unknown string format");
            return false;
    }

    if (pstr != NULL)
        *pstr = str;
    else
        free(str);

    return true;
}


void
hidrd_fmtfreepv(hidrd_fmt_type  type,
                va_list        *pap)
{
    switch (type)
    {
        case HIDRD_FMT_TYPE_STROWN:
            {
                char   *arg = va_arg(*pap, char *);

                assert(arg != NULL);
                free(arg);
            }
            break;
        default:
            break;
    }
}



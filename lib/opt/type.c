/** @file
 * @brief HID report descriptor - option type
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
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include "hidrd/util/bool.h"
#include "hidrd/util/dec.h"
#include "hidrd/opt/type.h"


#define MAP_LIST \
    MAP(STRING, string);    \
    MAP(BOOLEAN, boolean);  \
    MAP(S32, s32);          \
    MAP(U32, u32)

bool
hidrd_opt_type_valid(hidrd_opt_type type)
{
    switch (type)
    {
#define MAP(_NAME, _name) \
    case HIDRD_OPT_TYPE_##_NAME:
        MAP_LIST;
            return true;
#undef MAP

        default:
            return false;
    }
}


bool
hidrd_opt_type_parse_string(const char **pval, const char *str)
{
    assert(pval != NULL);
    assert(str != NULL);

    *pval = str;

    return true;
}


bool
hidrd_opt_type_parse_boolean(bool *pval, const char *str)
{
    return hidrd_bool_from_str(pval, str);
}


bool
hidrd_opt_type_parse_s32(int32_t *pval, const char *str)
{
    return HIDRD_DEC_FROM_STR(s32, pval, str);
}


bool
hidrd_opt_type_parse_u32(uint32_t *pval, const char *str)
{
    return HIDRD_DEC_FROM_STR(u32, pval, str);
}


bool
hidrd_opt_type_parse_value(hidrd_opt_type   type,
                           hidrd_opt_value *pval,
                           const char      *str)
{
    assert(hidrd_opt_type_valid(type));
    assert(pval != NULL);
    assert(str != NULL);

    switch (type)
    {
#define MAP(_T, _t) \
    case HIDRD_OPT_TYPE_##_T:                               \
        return hidrd_opt_type_parse_##_t(&pval->_t, str)
        MAP_LIST;
#undef MAP

        default:
            assert(!"Unknown type");
            return false;
    }
}


char *
hidrd_opt_type_format_string(const char *val)
{
    assert(val != NULL);

    return strdup(val);
}


char *
hidrd_opt_type_format_boolean(bool val)
{
    return strdup(hidrd_bool_to_str(val));
}


char *
hidrd_opt_type_format_s32(int32_t val)
{
    return HIDRD_DEC_TO_STR(s32, val);
}


char *
hidrd_opt_type_format_u32(uint32_t val)
{
    return HIDRD_DEC_TO_STR(u32, val);
}


char *
hidrd_opt_type_format_value(hidrd_opt_type          type,
                            const hidrd_opt_value  *pval)
{
    assert(hidrd_opt_type_valid(type));
    assert(pval != NULL);

    switch (type)
    {
#define MAP(_T, _t) \
    case HIDRD_OPT_TYPE_##_T:                       \
        return hidrd_opt_type_format_##_t(pval->_t)
        MAP_LIST;
#undef MAP

        default:
            assert(!"Unknown type");
            return NULL;
    }
}


int
hidrd_opt_type_cmp_boolean(bool a, bool b)
{
    return ((a == false) == (b == false)) ? 0 : ((a == false) ? -1 : 1);
}


int
hidrd_opt_type_cmp_string(const char *a, const char *b)
{
    assert(a != NULL);
    assert(b != NULL);

    return strcmp(a, b);
}


int
hidrd_opt_type_cmp_s32(int32_t a, int32_t b)
{
    return (a > b) ? 1 : ((a < b) ? -1 : 0);
}


int
hidrd_opt_type_cmp_u32(uint32_t a, uint32_t b)
{
    return (a > b) ? 1 : ((a < b) ? -1 : 0);
}


int
hidrd_opt_type_cmp_value(hidrd_opt_type         type,
                         const hidrd_opt_value *a,
                         const hidrd_opt_value *b)
{
    assert(hidrd_opt_type_valid(type));
    assert(a != NULL);
    assert(b != NULL);

    switch (type)
    {
#define MAP(_T, _t) \
    case HIDRD_OPT_TYPE_##_T:                           \
        return hidrd_opt_type_cmp_##_t(a->_t, b->_t)
        MAP_LIST;
#undef MAP

        default:
            assert(!"Unknown type");
            return 0;
    }
}

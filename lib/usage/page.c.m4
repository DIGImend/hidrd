dnl
dnl lib/usage/page.c template.
dnl
dnl Copyright (C) 2010 Nikolai Kondrashov
dnl
dnl This file is part of hidrd.
dnl
dnl Hidrd is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.
dnl
dnl Hidrd is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with hidrd; if not, write to the Free Software
dnl Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
dnl
dnl
include(`m4/hidrd/util.m4')dnl
dnl
`/** @file
 * @brief HID report descriptor - usage pages
 *
 * Copyright (C) 2009 Nikolai Kondrashov
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
 * @(#) $Id: page.c 103 2010-01-18 21:04:26Z spb_nick $
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "hidrd/usage/page.h"

'define(`PAGE_SET',
`
define(`PAGE_SET_RANGE',
`ifelse('`$'`1, `$1',
        ifelse(eval(0x'`$'`2), eval(0x'`$'`3),dnl
    if (page == 0x'`$'`2)
        return true;
,dnl
    if (page >= 0x'`$'`2 && page <= 0x'`$'`3)
        return true;
))')dnl
bool
hidrd_usage_page_$1(hidrd_usage_page page)
{
include(`db/usage/page_set_range.m4')dnl
    return false;
}

undefine(`PAGE_SET_RANGE')dnl
')dnl
include(`db/usage/page_set.m4')dnl
undefine(`PAGE_SET')dnl
`
#if defined(HIDRD_WITH_TOKENS) || defined(HIDRD_WITH_NAMES)

typedef struct page_desc {
    hidrd_usage_page    page;
#ifdef HIDRD_WITH_TOKENS
    const char         *token;
#endif
#ifdef HIDRD_WITH_NAMES
    const char         *name;
#endif
} page_desc;

static const page_desc desc_list[] = {

#ifdef HIDRD_WITH_TOKENS
#define PAGE_TOKEN(_token)  .token = _token,
#else
#define PAGE_TOKEN(_token)
#endif

#ifdef HIDRD_WITH_NAMES
#define PAGE_NAME(_name)    .name = _name,
#else
#define PAGE_NAME(_name)
#endif

#define PAGE(_TOKEN, _name) \
    {.page = HIDRD_USAGE_PAGE_##_TOKEN,     \
     PAGE_TOKEN(#_TOKEN) PAGE_NAME(#_name)}

#undef PAGE

    {.page  = HIDRD_USAGE_PAGE_UNDEFINED,
     PAGE_TOKEN(NULL) PAGE_NAME(NULL)}
};

#ifdef HIDRD_WITH_TOKENS

const char *
hidrd_usage_page_to_token(hidrd_usage_page page)
{
    const page_desc    *desc;

    assert(hidrd_usage_page_valid(page));

    for (desc = desc_list; desc->page != HIDRD_USAGE_PAGE_UNDEFINED; desc++)
        if (desc->page == page)
            return desc->token;

    return NULL;
}

#endif /* HIDRD_WITH_TOKENS */

#endif /* defined HIDRD_WITH_TOKENS || defined HIDRD_WITH_NAMES */
'dnl

dnl
dnl hidrd/usage/page.h template.
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
 * Copyright (C) 2009-2010 Nikolai Kondrashov
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
 * @(#) $Id: page.h 103 2010-01-18 21:04:26Z spb_nick $
 */

#ifndef __HIDRD_USAGE_PAGE_H__
#define __HIDRD_USAGE_PAGE_H__

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum hidrd_usage_page {
    /** Undefined */
    HIDRD_USAGE_PAGE_UNDEFINED = 0x0000,
'dnl Delegated pages
pushdef(PAGE,dnl
    `/** capitalize_first(`$3') */'
    `HIDRD_USAGE_PAGE_`'translit($2, a-z, A-Z) = 0x$1,')dnl
include(`db/usage/page.m4')dnl
popdef(`PAGE')dnl
`} hidrd_usage_page;

#define HIDRD_USAGE_PAGE_MIN    0x0000
#define HIDRD_USAGE_PAGE_MAX    0xFFFF

static inline bool
hidrd_usage_page_valid(hidrd_usage_page page)
{
    return page <= HIDRD_USAGE_PAGE_MAX;
}

static inline bool
hidrd_usage_page_defined(hidrd_usage_page page)
{
    return page != HIDRD_USAGE_PAGE_UNDEFINED;
}

'define(`PAGE_SET',
`/**
 * Check if a page is $2.
 *
 * @param page  Page ID.
 *
 * @return True if the page is $2, false otherwise.
 */
ifelse(eval(PAGE_SET_RANGE_NUM($1) > 1), 1,
extern bool hidrd_usage_page_$1(hidrd_usage_page page);,
static inline bool hidrd_usage_page_$1(hidrd_usage_page page)
{
PAGE_SET_RANGE_CHECK($1)
}
)

')dnl
include(`db/usage/page_set.m4')dnl
undefine(`PAGE_SET')dnl
`#ifdef HIDRD_WITH_TOKENS

/**
 * Convert a usage page code to a string token.
 *
 * @param page  Usage page code.
 *
 * @return Usage page constant string token or NULL if not found.
 */
extern const char *hidrd_usage_page_to_token(hidrd_usage_page page);

/**
 * Convert a usage page string token to a code.
 *
 * @param token Usage page string token (case insensitive).
 *
 * @return Usage page code; will be HIDRD_USAGE_PAGE_UNDEFINED, if the token
 *         is not recognized.
 */
extern hidrd_usage_page hidrd_usage_page_from_token(const char *token);

#endif /* HIDRD_WITH_TOKENS */

#ifdef HIDRD_WITH_NAMES

/**
 * Retrieve usage page name string (close to specification).
 *
 * @param page  Usage page code.
 *
 * @return Usage page name string, or NULL if not found.
 */
extern const char *hidrd_usage_page_name(hidrd_usage_page page);

#endif /* HIDRD_WITH_NAMES */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_USAGE_PAGE_H__ */
'dnl

/** @file
 * @brief HID report descriptor - stream type
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
 * @(#) $Id$
 */

#ifndef __HIDRD_STRM_TYPE_H__
#define __HIDRD_STRM_TYPE_H__

#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef bool hidrd_strm_init_fn(hidrd_strm             *strm,
                                va_list                 ap);

typedef hidrd_item *hidrd_strm_read_fn(hidrd_strm  *strm);

typedef bool hidrd_strm_write_fn(hidrd_strm        *strm,
                                 const hidrd_item  *item);

typedef bool hidrd_strm_flush_fn(hidrd_strm    *strm);

typedef void hidrd_strm_clnp_fn(hidrd_strm     *strm);

typedef struct hidrd_strm_type {
    size_t              size;
    hidrd_strm_init_fn  init;
    hidrd_strm_init_fn  read;
    hidrd_strm_init_fn  write;
    hidrd_strm_init_fn  flush;
    hidrd_strm_init_fn  clnp;
} hidrd_strm_type;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_STRM_TYPE_H__ */



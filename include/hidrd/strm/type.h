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
#include <stdarg.h>
#include "hidrd/item.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declaration */
typedef struct hidrd_strm hidrd_strm;

/**
 * Prototype for a stream instance initialization function.
 *
 * @param strm  Stream instance to initialize.
 * @param ap    Type-specific variable argument list.
 *
 * @return True if the initialization succeeded, false otherwise.
 */
typedef bool hidrd_strm_type_init_fn(hidrd_strm    *strm,
                                     va_list        ap);

/**
 * Prototype for a stream instance validation function.
 *
 * @param strm  Stream instance to validate.
 *
 * @return True if the instance is valid, false otherwise.
 */
typedef bool hidrd_strm_type_valid_fn(const hidrd_strm  *strm);

/**
 * Prototype for a stream instance reading function.
 *
 * @param strm  Stream instance to read from.
 *
 * @return Pointer to an item read, or NULL in case of EOF or error.
 */
typedef const hidrd_item *hidrd_strm_type_read_fn(hidrd_strm   *strm);

/**
 * Prototype for a stream instance writing function.
 *
 * @param strm  Stream instance to write to.
 * @param item  Pointer to an item to write.
 *
 * @return True if wrote successfully, false otherwise.
 */
typedef bool hidrd_strm_type_write_fn(hidrd_strm       *strm,
                                      const hidrd_item *item);

/**
 * Flush a stream instance cached items (if any).
 *
 * @param strm  Stream instance to flush cached items from.
 *
 * @return True if flushed successfully, false otherwise.
 */
typedef bool hidrd_strm_type_flush_fn(hidrd_strm   *strm);

/**
 * Cleanup a stream instance (free associated resources).
 *
 * @param strm  Stream instance to cleanup.
 */
typedef void hidrd_strm_type_clnp_fn(hidrd_strm    *strm);

typedef struct hidrd_strm_type {
    size_t                      size;
    hidrd_strm_type_init_fn    *init;
    hidrd_strm_type_valid_fn   *valid;
    hidrd_strm_type_read_fn    *read;
    hidrd_strm_type_write_fn   *write;
    hidrd_strm_type_flush_fn   *flush;
    hidrd_strm_type_clnp_fn    *clnp;
} hidrd_strm_type;

extern bool hidrd_strm_type_valid(const hidrd_strm_type *type);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_STRM_TYPE_H__ */



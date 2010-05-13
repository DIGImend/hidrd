/** @file
 * @brief HID report descriptor - stream source type
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

#ifndef __HIDRD_STRM_SRC_TYPE_H__
#define __HIDRD_STRM_SRC_TYPE_H__

#include <assert.h>
#include <stdarg.h>
#include "hidrd/cfg.h"
#include "hidrd/item.h"

#ifdef HIDRD_WITH_OPT
#include "hidrd/opt.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declaration, see hidrd/strm/src/inst.h for definition */
typedef struct hidrd_src hidrd_src;

/**
 * Prototype for a source instance initialization function.
 *
 * @param src   Source instance to initialize.
 * @param perr  Location for a dynamically allocated error message pointer,
 *              in case the initialization failed, or for a dynamically
 *              allocated empty string otherwise; could be NULL.
 * @param ap    Type-specific variable argument list.
 *
 * @return True if the initialization succeeded, false otherwise.
 */
typedef bool hidrd_src_type_init_fn(hidrd_src  *src,
                                    char      **perr,
                                    va_list     ap);

#ifdef HIDRD_WITH_OPT
/**
 * Prototype for a source initialization function which uses options.
 *
 * @param src       Source instance to initialize.
 * @param perr      Location for a dynamically allocated error message
 *                  pointer, in case the initialization failed, or for a
 *                  dynamically allocated empty string otherwise; could be
 *                  NULL.
 * @param opt_list  Pointer to an option array, terminated with an option
 *                  having name set to NULL.
 *
 * @return  True if initialized successfully, false otherwise.
 */

typedef bool hidrd_src_type_init_opts_fn(hidrd_src         *src,
                                         char             **perr,
                                         const hidrd_opt   *opt_list);
#endif /* HIDRD_WITH_OPT */

/**
 * Prototype for a source instance validation function.
 *
 * @param src  Source instance to validate.
 *
 * @return True if the instance is valid, false otherwise.
 */
typedef bool hidrd_src_type_valid_fn(const hidrd_src  *src);

/**
 * Prototype for a function used to retrieve (abstract) current position in
 * a source stream.
 *
 * @param src   Source instance to retrieve position from.
 *
 * @return Abstract position in the source instance stream.
 */
typedef uint64_t hidrd_src_type_getpos_fn(const hidrd_src *src);

/**
 * Prototype for a function used to format a human-readable description of
 * an abstract position in a source stream.
 *
 * @param src   Source instance to format position description for.
 * @param pos   Abstract position in the source instance.
 *
 * @return Dynamically allocated position description string.
 */
typedef char *hidrd_src_type_fmtpos_fn(const hidrd_src *src, uint64_t pos);

/**
 * Prototype for a source instance error message retrieval function.
 *
 * @param src   Source instance to retrieve the error message from.
 *
 * @return Dynamically allocated error message string, empty string if no
 *         error occurred, or NULL if failed to allocate memory.
 */
typedef char *hidrd_src_type_errmsg_fn(const hidrd_src *src);

/**
 * Prototype for a function used to retrieve an item from a source instance.
 *
 * @param src   The source instance to retrieve the item from.
 *
 * @return The retrieved item, or NULL in case of end of source or error.
 */
typedef const hidrd_item *hidrd_src_type_get_fn(hidrd_src   *src);

/**
 * Cleanup a source instance (free associated resources).
 *
 * @param src  Source instance to cleanup.
 */
typedef void hidrd_src_type_clnp_fn(hidrd_src    *src);

/** Source type */
typedef struct hidrd_src_type {
    size_t                          size;       /**< Instance size */
    hidrd_src_type_init_fn         *init;
#ifdef HIDRD_WITH_OPT
    hidrd_src_type_init_opts_fn    *init_opts;
    const hidrd_opt_spec           *opts_spec;
#endif
    hidrd_src_type_valid_fn        *valid;
    hidrd_src_type_getpos_fn       *getpos;
    hidrd_src_type_fmtpos_fn       *fmtpos;
    hidrd_src_type_errmsg_fn       *errmsg;
    hidrd_src_type_get_fn          *get;
    hidrd_src_type_clnp_fn         *clnp;
} hidrd_src_type;

/**
 * Check if a source type is valid.
 *
 * @param type  Source type to check.
 *
 * @return True if the type is valid, false otherwise.
 */
extern bool hidrd_src_type_valid(const hidrd_src_type *type);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_STRM_SRC_TYPE_H__ */

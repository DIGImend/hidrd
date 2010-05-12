/** @file
 * @brief HID report descriptor - stream sink type
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

#ifndef __HIDRD_STRM_SNK_TYPE_H__
#define __HIDRD_STRM_SNK_TYPE_H__

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

/* Forward declaration, see hidrd/strm/snk/inst.h for definition */
typedef struct hidrd_snk hidrd_snk;

/**
 * Prototype for a sink instance initialization function.
 *
 * @param snk   Sink instance to initialize.
 * @param perr  Location for a dynamically allocated error message pointer,
 *              in case the initialization failed, or for a dynamically
 *              allocated empty string otherwise; could be NULL.
 * @param ap    Type-specific variable argument list.
 *
 * @return True if the initialization succeeded, false otherwise.
 */
typedef bool hidrd_snk_type_init_fn(hidrd_snk  *snk,
                                    char      **perr,
                                    va_list     ap);

#ifdef HIDRD_WITH_OPT
/**
 * Prototype for a sink initialization function which uses options.
 *
 * @param snk       Sink instance to initialize.
 * @param perr      Location for a dynamically allocated error message
 *                  pointer, in case the initialization failed, or for a
 *                  dynamically allocated empty string otherwise; could be
 *                  NULL.
 * @param opt_list  Pointer to an option array, terminated with an option
 *                  having name set to NULL.
 *
 * @return  True if initialized successfully, false otherwise.
 */
typedef bool hidrd_snk_type_init_opts_fn(hidrd_snk         *snk,
                                         char             **perr,
                                         const hidrd_opt   *opt_list);
#endif /* HIDRD_WITH_OPT */

/**
 * Prototype for a sink instance validation function.
 *
 * @param snk   Sink instance to validate.
 *
 * @return True if the instance is valid, false otherwise.
 */
typedef bool hidrd_snk_type_valid_fn(const hidrd_snk  *snk);

/**
 * Prototype for a sink instance error message retrieval function.
 *
 * @param snk   Sink instance to retrieve the error message from.
 *
 * @return Dynamically allocated error message string, empty string if no
 *         error occurred, or NULL if failed to allocate memory.
 */
typedef char *hidrd_snk_type_errmsg_fn(const hidrd_snk *snk);

/**
 * Prototype for a function used to put an item into a sink instance.
 *
 * @param snk   The sink instance to put the item into.
 * @param item  Pointer to the item to put.
 *
 * @return True if put successfully, false otherwise.
 */
typedef bool hidrd_snk_type_put_fn(hidrd_snk           *snk,
                                   const hidrd_item    *item);

/**
 * Flush a sink instance caches to the output.
 *
 * @param snk   Sink instance to flush caches from.
 *
 * @return True if flushed successfully, false otherwise.
 */
typedef bool hidrd_snk_type_flush_fn(hidrd_snk   *snk);

/**
 * Cleanup a sink instance (free associated resources).
 *
 * @param snk   Sink instance to cleanup.
 */
typedef void hidrd_snk_type_clnp_fn(hidrd_snk  *snk);

/** Sink type */
typedef struct hidrd_snk_type {
    size_t                          size;       /**< Instance size */
    hidrd_snk_type_init_fn         *init;
#ifdef HIDRD_WITH_OPT
    hidrd_snk_type_init_opts_fn    *init_opts;
    const hidrd_opt_spec           *opts_spec;
#endif
    hidrd_snk_type_valid_fn        *valid;
    hidrd_snk_type_errmsg_fn       *errmsg;
    hidrd_snk_type_put_fn          *put;
    hidrd_snk_type_flush_fn        *flush;
    hidrd_snk_type_clnp_fn         *clnp;
} hidrd_snk_type;

/**
 * Check if a sink type is valid.
 *
 * @param type  Sink type to check.
 *
 * @return True if the type is valid, false otherwise.
 */
extern bool hidrd_snk_type_valid(const hidrd_snk_type *type);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_STRM_SNK_TYPE_H__ */

/** @file
 * @brief HID report descriptor - stream sink instance
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

#ifndef __HIDRD_STRM_SNK_INST_H__
#define __HIDRD_STRM_SNK_INST_H__

#include "hidrd/cfg.h"
#include "hidrd/strm/snk/type.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Sink instance */
struct hidrd_snk {
    const hidrd_snk_type   *type;   /**< Type description */
    void                  **pbuf;   /**< Location of/for buffer pointer */
    size_t                 *psize;  /**< Location of/for buffer size */
};

/**
 * Check if a sink instance is valid.
 *
 * @param snk   Sink instance to validate.
 *
 * @return True if the instance is valid, false otherwise.
 */
extern bool hidrd_snk_valid(const hidrd_snk *snk);

/**
 * Create (allocate and initialize) an instance of specified sink type with
 * specified arguments.
 *
 * @param type  Sink type to create instance of.
 * @param perr  Location for a dynamically allocated error message pointer,
 *              in case the creation failed, or for a dynamically allocated
 *              empty string otherwise; could be NULL.
 * @param pbuf  Location of sink buffer pointer.
 * @param psize Location of sink buffer size.
 * @param ...   Sink type-specific initialization arguments.
 *
 * @return Opened (allocated and initialized) instance of specified sink
 *         type, or NULL, if failed to allocate or initialize.
 */
extern hidrd_snk *hidrd_snk_new(const hidrd_snk_type   *type,
                                char                  **perr,
                                void                  **pbuf,
                                size_t                 *psize,
                                ...);

#ifdef HIDRD_WITH_OPT
/**
 * Create (allocate and initialize) an instance of specified sink type with
 * specified options.
 *
 * @param type  Sink type to create instance of.
 * @param perr  Location for a dynamically allocated error message pointer,
 *              in case the creation failed, or for a dynamically allocated
 *              empty string otherwise; could be NULL.
 * @param pbuf  Location of sink buffer pointer.
 * @param psize Location of sink buffer size.
 * @param opts  Option string: each option is a name/value pair separated by
 *              equals sign, with surrounding space removed; options are
 *              separated by comma.
 *
 * @return Opened (allocated and initialized) instance of specified sink
 *         type, or NULL, if failed to allocate or initialize.
 */
extern hidrd_snk *hidrd_snk_new_opts(const hidrd_snk_type  *type,
                                     char                 **perr,
                                     void                 **pbuf,
                                     size_t                *psize,
                                     const char            *opts);
#endif /* HIDRD_WITH_OPT */

/**
 * Put an item to a sink instance.
 *
 * @param snk   The sink instance to put the item into.
 * @param item  The item to put.
 *
 * @return True if put succesfully, false otherwise.
 */
extern bool hidrd_snk_put(hidrd_snk *snk, const hidrd_item *item);

/**
 * Flush any cached data to sink output.
 *
 * @param snk   Sink instance to flush.
 *
 * @return True if flushed succesfully, false otherwise.
 */
extern bool hidrd_snk_flush(hidrd_snk *snk);

/**
 * Retrieve most recently occurred error message from a sink instance.
 *
 * @param snk   Sink instance to retrieve error message from.
 *
 * @return Dynamically allocated error message string, empty string if no
 *         error occurred, or NULL if failed to allocate memory.
 */
extern char *hidrd_snk_errmsg(const hidrd_snk *snk);

/**
 * Delete (cleanup and free) a sink instance.
 *
 * @param snk  Sink instance to delete.
 */
extern void hidrd_snk_delete(hidrd_snk *snk);

/**
 * Close (flush, cleanup and free) a sink instance.
 *
 * @param snk   Sink instance to close.
 *
 * @return True if closed (flushed) succesfully, false otherwise.
 */
extern bool hidrd_snk_close(hidrd_snk *snk);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_STRM_SNK_INST_H__ */

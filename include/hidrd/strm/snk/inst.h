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

#include "hidrd/strm/snk/type.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Sink instance */
struct hidrd_snk {
    const hidrd_snk_type   *type;   /**< Type description */
    void                  **pbuf;   /**< Location of/for buffer pointer */
    size_t                 *psize;  /**< Location of/for buffer size */
    bool                    error;  /**< Error indicator */
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
 * Check if a sink instance has error indicator.
 *
 * @param snk   Sink instance to check error indicator for.
 *
 * @return True if the error indicator is present, false otherwise.
 */
extern bool hidrd_snk_error(const hidrd_snk *snk);

/**
 * Allocate (an uninitialized, but zeroed) sink instance of specified type
 * (set the type field).
 *
 * @param type  Sink type to create instance of.
 *
 * @return Uninitialized instance of the specified sink type.
 */
extern hidrd_snk *hidrd_snk_alloc(const hidrd_snk_type *type);

/**
 * Initialize sink instance.
 *
 * @param snk   Sink instance to initialize.
 * @param pbuf  Location of sink buffer pointer.
 * @param psize Location of sink buffer size.
 * @param ...   Sink type-specific arguments.
 *
 * @return True if initialization succeeded, false otherwise.
 */
extern bool hidrd_snk_init(hidrd_snk *snk,
                           void **pbuf, size_t *psize, ...);

/**
 * Initialize sink instance (va_list version).
 *
 * @param snk   Sink instance to initialize.
 * @param pbuf  Location of sink buffer pointer.
 * @param psize Location of sink buffer size.
 * @param ap    Sink type-specific arguments.
 *
 * @return True if initialization succeeded, false otherwise.
 */
extern bool hidrd_snk_initv(hidrd_snk *snk,
                            void **pbuf, size_t *psize, va_list ap);

#ifdef HIDRD_WITH_OPT
/**
 * Initialize sink instance with an option string.
 *
 * @param snk   Sink instance to initialize.
 * @param pbuf  Location of sink buffer pointer.
 * @param psize Location of sink buffer size.
 * @param opts  Option string: each option is a name/value pair separated by
 *              equals sign, with surrounding space removed; options are
 *              separated by comma.
 *
 * @return True if initialization succeeded, false otherwise.
 */
extern bool hidrd_snk_opts_init(hidrd_snk *snk,
                                void **pbuf, size_t *psize,
                                const char *opts);

/**
 * Initialize sink instance with an option string, formatted using
 * sprintf.
 *
 * @param snk       Sink instance to initialize.
 * @param pbuf      Location of sink buffer pointer.
 * @param psize     Location of sink buffer size.
 * @param opts_fmt  Option format string: each option is a name/value pair
 *                  separated by equals sign, with surrounding space
 *                  removed; options are separated by comma.
 * @param ...       Option format arguments.
 *
 * @return True if initialization succeeded, false otherwise.
 */
extern bool hidrd_snk_opts_initf(hidrd_snk *snk,
                                 void **pbuf, size_t *psize,
                                 const char *opts_fmt, ...)
                                __attribute__((format(printf, 4, 5)));

/**
 * Open (allocate and initialize) an instance of specified sink type with
 * specified options.
 *
 * @param type  Sink type to open instance of.
 * @param pbuf  Location of sink buffer pointer.
 * @param psize Location of sink buffer size.
 * @param opts  Option string: each option is a name/value pair separated by
 *              equals sign, with surrounding space removed; options are
 *              separated by comma.
 *
 * @return Opened (allocated and initialized) instance of specified sink
 *         type, or NULL, if failed to allocate or initialize.
 */
extern hidrd_snk *hidrd_snk_opts_open(const hidrd_snk_type *type,
                                      void **pbuf, size_t *psize,
                                      const char *opts);

#endif /* HIDRD_WITH_OPT */

/**
 * Open (allocate and initialize) an instance of specified sink type with
 * specified arguments.
 *
 * @param type  Sink type to open instance of.
 * @param pbuf  Location of sink buffer pointer.
 * @param psize Location of sink buffer size.
 * @param ...   Sink type-specific initialization arguments.
 *
 * @return Opened (allocated and initialized) instance of specified sink
 *         type, or NULL, if failed to allocate or initialize.
 */
extern hidrd_snk *hidrd_snk_open(const hidrd_snk_type *type,
                                 void **pbuf, size_t *psize, ...);

/**
 * Flush any cached data to sink output.
 *
 * @param snk   Sink instance to flush.
 *
 * @return True if flushed succesfully, false otherwise.
 */
extern bool hidrd_snk_flush(hidrd_snk *snk);

/**
 * Free sink instance (without flushing any cached data).
 *
 * @param snk   Sink instance to free.
 */
extern void hidrd_snk_free(hidrd_snk *snk);

/**
 * Close (flush and free) a sink instance.
 *
 * @param snk   Sink instance to close.
 *
 * @return True if closed (flushed) succesfully, false otherwise.
 */
extern bool hidrd_snk_close(hidrd_snk *snk);

/**
 * Put an item to a sink instance.
 *
 * @param snk   The sink instance to put the item into.
 * @param item  The item to put.
 *
 * @return True if put succesfully, false otherwise.
 */
extern bool hidrd_snk_put(hidrd_snk *snk, const hidrd_item *item);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_STRM_SNK_INST_H__ */

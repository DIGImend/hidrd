/** @file
 * @brief HID report descriptor - stream source instance
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

#ifndef __HIDRD_STRM_SRC_INST_H__
#define __HIDRD_STRM_SRC_INST_H__

#include "hidrd/strm/src/type.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Source instance */
struct hidrd_src {
    const hidrd_src_type   *type;   /**< Type description */
    const void             *buf;    /**< Source buffer pointer */
    size_t                  size;   /**< Source buffer size */
    bool                    error;  /**< Error indicator */
};

/**
 * Check if a source instance is valid.
 *
 * @param src   Source instance to validate.
 *
 * @return True if the instance is valid, false otherwise.
 */
extern bool hidrd_src_valid(const hidrd_src *src);

/**
 * Check if a source instance has error indicator.
 *
 * @param src   Source instance to check error indicator for.
 *
 * @return True if the error indicator is present, false otherwise.
 */
extern bool hidrd_src_error(const hidrd_src *src);

/**
 * Allocate (an uninitialized) source instance of specified type.
 *
 * @param type  Source type to create instance of.
 *
 * @return Uninitialized instance of the specified source type.
 */
extern hidrd_src *hidrd_src_alloc(const hidrd_src_type *type);

/**
 * Initialize source instance.
 *
 * @param src   Source instance to initialize.
 * @param buf   Source buffer pointer.
 * @param size  Source buffer size.
 * @param ...   Source type-specific arguments.
 *
 * @return True if initialization succeeded, false otherwise.
 */
extern bool hidrd_src_init(hidrd_src *src,
                           const void *buf, size_t size, ...);

/**
 * Initialize source instance (va_list version).
 *
 * @param src   Source instance to initialize.
 * @param buf   Source buffer pointer.
 * @param size  Source buffer size.
 * @param ap    Source type-specific arguments.
 *
 * @return True if initialization succeeded, false otherwise.
 */
extern bool hidrd_src_initv(hidrd_src *src,
                            const void *buf, size_t size, va_list ap);

#ifdef HIDRD_WITH_OPT
/**
 * Initialize source instance with an option string.
 *
 * @param src   Source instance to initialize.
 * @param buf   Source buffer pointer.
 * @param size  Source buffer size.
 * @param opts  Option string: each option is a name/value pair separated by
 *              equals sign, with surrounding space removed; options are
 *              separated by comma.
 *
 * @return True if initialization succeeded, false otherwise.
 */
extern bool hidrd_src_opts_init(hidrd_src *src,
                                void *buf, size_t size,
                                const char *opts);

/**
 * Initialize source instance with an option string, formatted using
 * sprintf.
 *
 * @param src       Source instance to initialize.
 * @param buf       Source buffer pointer.
 * @param size      Source buffer size.
 * @param opts_fmt  Option format string: each option is a name/value pair
 *                  separated by equals sign, with surrounding space
 *                  removed; options are separated by comma.
 * @param ...       Option format arguments.
 *
 * @return True if initialization succeeded, false otherwise.
 */
extern bool hidrd_src_opts_initf(hidrd_src *src,
                                 void *buf, size_t size,
                                 const char *opts_fmt, ...)
                                __attribute__((format(printf, 4, 5)));

/**
 * Open (allocate and initialize) an instance of specified source type with
 * specified options.
 *
 * @param type  Source type to open instance of.
 * @param buf   Source buffer pointer.
 * @param size  Source buffer size.
 * @param opts  Option string: each option is a name/value pair separated by
 *              equals sign, with surrounding space removed; options are
 *              separated by comma.
 *
 * @return Opened (allocated and initialized) instance of specified source
 *         type, or NULL, if failed to allocate or initialize.
 */
extern hidrd_src *hidrd_src_opts_open(const hidrd_src_type *type,
                                      void *buf, size_t size,
                                      const char *opts);
#endif /* HIDRD_WITH_OPT */

/**
 * Open (allocate and initialize) an instance of specified source type with
 * specified arguments.
 *
 * @param type  Source type to open instance of.
 * @param buf   Source buffer pointer.
 * @param size  Source buffer size.
 * @param ...   Source type-specific initialization arguments.
 *
 * @return Opened (allocated and initialized) instance of specified source
 *         type, or NULL, if failed to allocate or initialize.
 */
extern hidrd_src *hidrd_src_open(const hidrd_src_type *type,
                                 void *buf, size_t size, ...);

/**
 * Free source instance (without flushing any cached data).
 *
 * @param src  Source instance to free.
 */
extern void hidrd_src_free(hidrd_src *src);

/**
 * Retrieve an item from a source instance.
 *
 * @param src   The source instance to retrieve the item from.
 *
 * @return The retrieved item, or NULL, if end of source or error.
 *
 * @see hidrd_src_error
 */
extern const hidrd_item *hidrd_src_get(hidrd_src *src);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_STRM_SRC_INST_H__ */

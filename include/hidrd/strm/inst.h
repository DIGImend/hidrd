/** @file
 * @brief HID report descriptor - stream instance
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

#ifndef __HIDRD_STRM_INST_H__
#define __HIDRD_STRM_INST_H__

#include "hidrd/strm/type.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Stream instance */
struct hidrd_strm {
    const hidrd_strm_type  *type;  /**< Type description */
    void                  **pbuf;  /**< Location of stream buffer pointer */
    size_t                 *psize; /**< Location of stream size */
    bool                    error; /**< Error indicator */
};

/**
 * Check if a stream instance is valid.
 *
 * @param strm  Stream instance to validate.
 *
 * @return True if the instance is valid, false otherwise.
 */
extern bool hidrd_strm_valid(const hidrd_strm *strm);

/**
 * Check if a stream instance is writable (the stream type has "write"
 * function).
 *
 * @param strm  Stream instance to check.
 *
 * @return True if the instance is writable, false otherwise.
 */
extern bool hidrd_strm_writable(const hidrd_strm *strm);

/**
 * Check if a stream instance is readable (the stream type has "read"
 * function).
 *
 * @param strm  Stream instance to check.
 *
 * @return True if the instance is writable, false otherwise.
 */
extern bool hidrd_strm_readable(const hidrd_strm *strm);

/**
 * Check if a stream instance has error indicator.
 *
 * @param strm  Stream instance to check error indicator for.
 *
 * @return True if the error indicator is present, false otherwise.
 */
extern bool hidrd_strm_error(const hidrd_strm *strm);

/**
 * Allocate (an uninitialized) stream instance of specified type.
 *
 * @param type  Stream type to create instance of.
 *
 * @return Uninitialized instance of the specified stream type.
 */
extern hidrd_strm *hidrd_strm_alloc(const hidrd_strm_type *type);

/**
 * Initialize stream instance.
 *
 * @param strm  Stream instance to initialize.
 * @param pbuf  Location of stream buffer pointer.
 * @param psize Location of stream size.
 * @param ...   Stream type-specific arguments.
 *
 * @return True if initialization succeeded, false otherwise.
 */
extern bool hidrd_strm_init(hidrd_strm *strm,
                            void **pbuf, size_t *psize, ...);

/**
 * Initialize stream instance (va_list version).
 *
 * @param strm  Stream instance to initialize.
 * @param pbuf  Location of stream buffer pointer.
 * @param psize Location of stream size.
 * @param ap    Stream type-specific arguments.
 *
 * @return True if initialization succeeded, false otherwise.
 */
extern bool hidrd_strm_initv(hidrd_strm *strm,
                             void **pbuf, size_t *psize, va_list ap);

#ifdef HIDD_STRM_WITH_OPTS
/**
 * Initialize stream instance with an option string.
 *
 * @param strm  Stream instance to initialize.
 * @param pbuf  Location of stream buffer pointer.
 * @param psize Location of stream size.
 * @param opts  Option string: each option is a name/value pair separated by
 *              equals sign, with surrounding space removed; options are
 *              separated by comma.
 *
 * @return True if initialization succeeded, false otherwise.
 */
extern bool hidrd_strm_opts_init(hidrd_strm *strm,
                                 void **pbuf, size_t *psize,
                                 const char *opts);

/**
 * Initialize stream instance with an option string, formatted using
 * sprintf.
 *
 * @param strm      Stream instance to initialize.
 * @param pbuf      Location of stream buffer pointer.
 * @param psize     Location of stream size.
 * @param opts_fmt  Option format string: each option is a name/value pair
 *                  separated by equals sign, with surrounding space
 *                  removed; options are separated by comma.
 * @param ...       Option format arguments.
 *
 * @return True if initialization succeeded, false otherwise.
 */
extern bool hidrd_strm_opts_initf(hidrd_strm *strm,
                                  void **pbuf, size_t *psize,
                                  const char *opts_fmt, ...)
                                 __attribute__((format(printf, 4, 5)));
#endif /* HIDRD_WITH_OPT */

/**
 * Open (allocate and initialize) an instance of specified stream type with
 * specified arguments.
 *
 * @param type  Stream type to open instance of.
 * @param pbuf  Location of stream buffer pointer.
 * @param psize Location of stream size.
 * @param ...   Stream type-specific initialization arguments.
 *
 * @return Opened (allocated and initialized) instance of specified stream
 *         type, or NULL, if failed to allocate or initialize.
 */
extern hidrd_strm *hidrd_strm_open(const hidrd_strm_type *type,
                                   void **pbuf, size_t *psize, ...);

/**
 * Flush any cached data to stream storage.
 *
 * @param strm  Stream instance to flush.
 *
 * @return True if flushed succesfully, false otherwise.
 */
extern bool hidrd_strm_flush(hidrd_strm *strm);

/**
 * Free stream instance (without flushing any cached data).
 *
 * @param strm  Stream instance to free.
 */
extern void hidrd_strm_free(hidrd_strm *strm);

/**
 * Close (flush and free) a stream instance.
 *
 * @param strm  Stream instance to close.
 *
 * @return True if closed (flushed) succesfully, false otherwise.
 */
extern bool hidrd_strm_close(hidrd_strm *strm);

/**
 * Read an item from a stream instance.
 *
 * @param strm  Stream instance to read from.
 *
 * @return An item read, or NULL, if end of stream or error.
 *
 * @see hidrd_strm_error
 */
extern const hidrd_item *hidrd_strm_read(hidrd_strm *strm);

/**
 * Write an item to a stream instance.
 *
 * @param strm  Stream instance to write to.
 * @param item  Item to write.
 *
 * @return True if written succesfully, false otherwise.
 */
extern bool hidrd_strm_write(hidrd_strm *strm, const hidrd_item *item);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_STRM_INST_H__ */

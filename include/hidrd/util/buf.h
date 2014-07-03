/** @file
 * @brief HID report descriptor - utilities - growing buffer
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
 */

#ifndef __HIDRD_UTIL_BUF_H__
#define __HIDRD_UTIL_BUF_H__

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Minimum allocated buffer size */
#define HIDRD_BUF_MIN_SIZE   256

/** Buffer */
typedef struct hidrd_buf {
    void   *ptr;    /**< Buffer pointer */
    size_t  len;    /**< Buffer contents length */
    size_t  size;   /**< Buffer allocated size */
} hidrd_buf;

/** Empty buffer initializer */
#define HIDRD_BUF_EMPTY {.ptr = NULL, .len = 0, .size = 0}

/**
 * Initialize a buffer.
 *
 * @param buf   Buffer to initialize.
 */
extern void hidrd_buf_init(hidrd_buf *buf);

/**
 * Initialize a buffer, taking ownership of a dynamically-allocated memory
 * chunk.
 *
 * @param buf   Buffer to initialize.
 * @param ptr   Memory chunk to own.
 * @param len   Memory chunk used length.
 * @param size  Memory chunk allocated size.
 */
extern void hidrd_buf_own(hidrd_buf *buf, void *ptr, size_t len, size_t size);

/**
 * Reset buffer contents
 *
 * @param buf   Buffer to reset.
 */
extern void hidrd_buf_reset(hidrd_buf *buf);

/**
 * Cleanup a buffer.
 *
 * @param buf   Buffer to cleanup.
 */
extern void hidrd_buf_clnp(hidrd_buf *buf);

/**
 * Check if a buffer is valid.
 *
 * @param buf   Buffer to check.
 *
 * @return True if the buffer is valid, false otherwise.
 */
extern bool hidrd_buf_valid(const hidrd_buf *buf);

/**
 * Retention a buffer: reallocate to contents size.
 *
 * @param buf   Buffer to retention.
 */
extern void hidrd_buf_retention(hidrd_buf *buf);

/**
 * Disown buffer contents.
 *
 * @param buf   Buffer to disown contents from.
 * @param pptr  Location for buffer contents pointer; can be NULL, in that
 *              case the buffer contents will be freed.
 * @param plen  Location for buffer contents length; can be NULL.
 * @param psize Location for buffer allocated length; can be NULL.
 */
extern void hidrd_buf_disown(hidrd_buf *buf,
                             void **pptr, size_t *plen, size_t *psize);

/**
 * Grow a buffer memory to fit specified contents length.
 *
 * @param buf   Buffer to grow.
 * @param len   Buffer contents length.
 *
 * @return True if grown successfully, false otherwise.
 */
extern bool hidrd_buf_grow(hidrd_buf *buf, size_t len);

/**
 * Append a byte span of specified value and length to a buffer.
 *
 * @param buf   Buffer to add to.
 * @param val   Byte value to fill the span with.
 * @param len   Span length in bytes.
 *
 * @return True if added successfully, false otherwise.
 */
extern bool hidrd_buf_add_span(hidrd_buf *buf, uint8_t val, size_t len);

/**
 * Append a character to a buffer.
 *
 * @param buf   Buffer to append to.
 * @param c     Character to append.
 *
 * @return True if added successfully, false otherwise.
 */
static inline bool hidrd_buf_add_char(hidrd_buf *buf, uint8_t c)
{
    return hidrd_buf_add_span(buf, c, 1);
}

/**
 * Append a printf-formatted string to a buffer.
 *
 * @param buf   Buffer to add to.
 * @param fmt   Format specification.
 * @param ...   Format arguments.
 *
 * @return True if added successfully, false otherwise.
 */
extern bool hidrd_buf_add_printf(hidrd_buf *buf, const char *fmt, ...)
                                __attribute__((format(printf, 2, 3)));

/**
 * Append a printf-formatted string to a buffer, va_list version.
 *
 * @param buf   Buffer to add to.
 * @param fmt   Format specification.
 * @param ap    Format arguments.
 *
 * @return True if added successfully, false otherwise.
 */
extern bool hidrd_buf_add_vprintf(hidrd_buf    *buf,
                                  const char   *fmt,
                                  va_list       ap);

/**
 * Append a memory chunk to a buffer.
 *
 * @param buf   Buffer to add to.
 * @param ptr   Pointer to the memory chunk to add.
 * @param len   Length of the memory chunk to add.
 *
 * @return True if added successfully, false otherwise.
 */
extern bool hidrd_buf_add_ptr(hidrd_buf    *buf,
                              const void   *ptr,
                              size_t        len);

/**
 * Append a string to a buffer.
 *
 * @param buf   Buffer to add to.
 * @param str   String to add.
 *
 * @return True if added successfully, false otherwise.
 */
extern bool hidrd_buf_add_str(hidrd_buf *buf, const char *str);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_BUF_H__ */

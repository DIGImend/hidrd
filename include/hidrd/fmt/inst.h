/** @file
 * @brief HID report descriptor - format instance
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

#ifndef __HIDRD_FMT_INST_H__
#define __HIDRD_FMT_INST_H__

#include "hidrd/strm/src/inst.h"
#include "hidrd/strm/snk/inst.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Prototype for a function used to initialize format support.
 *
 * @return True if initialized successfully, false otherwise.
 */
typedef bool hidrd_fmt_init_fn(void);

/**
 * Prototype for a function used to cleanup format support.
 */
typedef void hidrd_fmt_clnp_fn(void);

/** Format */
typedef struct hidrd_fmt {
    const char             *name;
    hidrd_fmt_init_fn      *init;
    hidrd_fmt_clnp_fn      *clnp;
    const hidrd_src_type   *src;
    const hidrd_snk_type   *snk;
} hidrd_fmt;

/**
 * Check if a format is valid.
 *
 * @param fmt   Format to check.
 *
 * @return True if the format is valid, false otherwise.
 */
extern bool hidrd_fmt_valid(const hidrd_fmt *fmt);

/**
 * Check if a format is readable.
 *
 * @param fmt   Format to check.
 *
 * @return True if the format is readable, false otherwise.
 */
static inline bool
hidrd_fmt_readable(const hidrd_fmt *fmt)
{
    assert(hidrd_fmt_valid(fmt));
    return fmt->src != NULL;
}

/**
 * Check if a format is writable.
 *
 * @param fmt   Format to check.
 *
 * @return True if the format is writable, false otherwise.
 */
static inline bool
hidrd_fmt_writable(const hidrd_fmt *fmt)
{
    assert(hidrd_fmt_valid(fmt));
    return fmt->snk != NULL;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_FMT_INST_H__ */

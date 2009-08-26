/** @file
 * @brief HID report descriptor - stream
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

#ifndef __HIDRD_STRM_H__
#define __HIDRD_STRM_H__

#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hidrd_strm {
    const hidrd_strm_type  *type;
    bool                    eof;
    int                     error;
} hidrd_strm;

/**
 * Allocate (uninitialized) instance of specified stream type.
 *
 * @param type  Stream type.
 *
 * @return Stream instance with type-specific part uninitialized.
 *
 * @alg Basically, allocates memory of size specified in the type
 * description, initializes generic part, the rest of the memory is filled
 * with zeroes.
 *
 * @sa hidrd_strm_free
 */
extern hidrd_strm *hidrd_strm_alloc(const hidrd_strm_type *type);

extern hidrd_strm *hidrd_strm_open(const hidrd_strm_type *type, ...);

extern bool hidrd_strm_flush(hidrd_strm *strm);

extern void hidrd_strm_free(hidrd_strm *strm);

static inline bool
hidrd_strm_close(hidrd_strm *strm)
{
    if (!hidrd_strm_flush(strm))
        return false;

    hidrd_strm_free(strm);
    return true;
}

extern hidrd_item *hidrd_strm_read(hidrd_strm *strm);

extern bool hidrd_strm_write(hidrd_strm *strm, const hidrd_item *item);

extern bool hidrd_strm_eof(const hidrd_strm *strm);
extern int hidrd_strm_error(const hidrd_strm *strm);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_STRM_H__ */


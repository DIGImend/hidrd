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

typedef struct hidrd_strm {
    const hidrd_strm_type  *type;
    bool                    error;
} hidrd_strm;

extern bool hidrd_strm_valid(const hidrd_strm *strm);

extern bool hidrd_strm_writable(const hidrd_strm *strm);

extern bool hidrd_strm_readable(const hidrd_strm *strm);

extern bool hidrd_strm_error(const hidrd_strm *strm);

extern hidrd_strm *hidrd_strm_alloc(const hidrd_strm_type *type);

extern bool hidrd_strm_initv(hidrd_strm *strm, va_list ap);

extern bool hidrd_strm_init(hidrd_strm *strm, ...);

extern hidrd_strm *hidrd_strm_open(const hidrd_strm_type *type, ...);

extern bool hidrd_strm_flush(hidrd_strm *strm);

extern void hidrd_strm_free(hidrd_strm *strm);

extern bool hidrd_strm_close(hidrd_strm *strm);

extern const hidrd_item *hidrd_strm_read(hidrd_strm *strm);

extern bool hidrd_strm_write(hidrd_strm *strm, const hidrd_item *item);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_STRM_INST_H__ */

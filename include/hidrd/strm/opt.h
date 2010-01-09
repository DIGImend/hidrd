/** @file
 * @brief HID report descriptor - stream initialization option
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

#ifndef __HIDRD_STRM_OPT_H__
#define __HIDRD_STRM_OPT_H__

#include <stdbool.h>
#include "hidrd/strm/opt.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Stream initialization option */
typedef struct hidrd_strm_opt {
    const char *name;
    const char *value;
} hidrd_strm_opt;

/**
 * Get a boolean value.
 *
 * @param opt   Option pointer.
 * @param dflt  Default value.
 *
 * @return Option value, or @e dflt, if there is no value.
 */
extern bool hidrd_strm_opt_get_bool(const hidrd_strm_opt *opt, bool dflt);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_STRM_OPT_H__ */


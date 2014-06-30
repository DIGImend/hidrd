/** @file
 * @brief HID report descriptor - native stream source
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

#ifndef __HIDRD_FMT_NATV_SRC_H__
#define __HIDRD_FMT_NATV_SRC_H__

#include "hidrd/strm/src/inst.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Native source type */
extern const hidrd_src_type hidrd_natv_src;

/** Native source error code */
typedef enum hidrd_natv_src_err {
    HIDRD_NATV_SRC_ERR_NONE,    /**< No error */
    HIDRD_NATV_SRC_ERR_SHORT,   /**< Item buffer ended prematurely */
    HIDRD_NATV_SRC_ERR_INVALID  /**< Invalid item encountered */
} hidrd_natv_src_err;

/** Native source instance */
typedef struct hidrd_natv_src_inst {
    hidrd_src           src;    /**< Parent structure */
    size_t              pos;    /**< Stream position in bytes */
    hidrd_natv_src_err  err;    /**< Last error code */
} hidrd_natv_src_inst;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_FMT_NATV_SRC_H__ */

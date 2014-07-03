/** @file
 * @brief HID report descriptor - hex stream sink
 *
 * Copyright (C) 2014 Nikolai Kondrashov
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

#ifndef __HIDRD_FMT_HEX_SNK_H__
#define __HIDRD_FMT_HEX_SNK_H__

#include "hidrd/strm/snk/inst.h"
#include "hidrd/util/buf.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Number of columns in hex dump */
#define HIDRD_HEX_SNK_COL_NUM   16

/** Hex sink type */
const hidrd_snk_type    hidrd_hex_snk;

/** Hex sink error code */
typedef enum hidrd_hex_snk_err {
    HIDRD_HEX_SNK_ERR_NONE,     /**< No error */
    HIDRD_HEX_SNK_ERR_ALLOC     /**< Memory allocation failure */
} hidrd_hex_snk_err;

/** Hex sink instance */
typedef struct hidrd_hex_snk_inst {
    hidrd_snk           snk;    /**< Parent structure */
    hidrd_buf           buf;    /**< Output buffer */
    size_t              bytes;  /**< Number of output bytes */
    hidrd_hex_snk_err   err;    /**< Last error code */
} hidrd_hex_snk_inst;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_FMT_HEX_SNK_H__ */

/** @file
 * @brief HID report descriptor - native stream sink
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

#ifndef __HIDRD_FMT_NATV_SNK_H__
#define __HIDRD_FMT_NATV_SNK_H__

#include "hidrd/strm/snk/inst.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Native sink type */
extern const hidrd_snk_type hidrd_natv_snk;

/** Native sink error code */
typedef enum hidrd_natv_snk_err {
    HIDRD_NATV_SNK_ERR_NONE,    /**< No error */
    HIDRD_NATV_SNK_ERR_ALLOC    /**< Memory allocation failure */
} hidrd_natv_snk_err;

/** Native sink instance */
typedef struct hidrd_natv_snk_inst {
    hidrd_snk           snk;    /**< Parent structure */
    void               *buf;    /**< Buffer pointer */
    size_t              size;   /**< Stream size in bytes */
    size_t              alloc;  /**< Buffer size in bytes */
    size_t              pos;    /**< Stream position in bytes */
    hidrd_natv_snk_err  err;    /**< Last error code */
} hidrd_natv_snk_inst;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_FMT_NATV_SNK_H__ */

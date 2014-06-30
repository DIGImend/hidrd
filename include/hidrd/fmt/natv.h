/** @file
 * @brief HID report descriptor - native format
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

#ifndef __HIDRD_FMT_NATV_H__
#define __HIDRD_FMT_NATV_H__

#include "hidrd/fmt/inst.h"
#include "hidrd/fmt/natv/src.h"
#include "hidrd/fmt/natv/snk.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Native format */
extern const hidrd_fmt  hidrd_natv;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_FMT_NATV_H__ */

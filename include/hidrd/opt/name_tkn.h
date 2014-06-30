/** @file
 * @brief HID report descriptor - option name token
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

#ifndef __HIDRD_OPT_NAME_TKN_H__
#define __HIDRD_OPT_NAME_TKN_H__

#include "hidrd/opt/tkn.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check if an option name token is valid.
 *
 * @param name  Option name token to check.
 *
 * @return True if the name token is valid, false otherwise.
 */
extern bool hidrd_opt_name_tkn_valid(const char *name);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_OPT_NAME_TKN_H__ */

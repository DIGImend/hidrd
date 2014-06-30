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
 */

#include "hidrd/fmt/inst.h"

bool
hidrd_fmt_valid(const hidrd_fmt *fmt)
{
    return fmt != NULL &&
           fmt->name != NULL && *fmt->name != '\0' &&
           fmt->desc != NULL && *fmt->desc != '\0' &&
           ((fmt->init == NULL && fmt->clnp == NULL) ||
            (fmt->init != NULL && fmt->clnp != NULL)) &&
           (fmt->src != NULL || fmt->snk != NULL) &&
           (fmt->src == NULL || hidrd_src_type_valid(fmt->src)) &&
           (fmt->snk == NULL || hidrd_snk_type_valid(fmt->snk));
}

/** @file
 * @brief HID report descriptor - stream type
 *
 * Copyright (C) 2009-2010 Nikolai Kondrashov
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

#include "hidrd/strm/opt_spec_list.h"
#include "hidrd/strm/type.h"
#include "hidrd/strm/inst.h"

bool
hidrd_strm_type_valid(const hidrd_strm_type *type)
{
    return type != NULL &&
           type->name != NULL && *type->name != '\0' &&
           type->size >= sizeof(hidrd_strm) &&
#ifdef HIDRD_STRM_WITH_OPTS
           (type->init != NULL || type->opts_init == NULL) &&
           (type->opts_init == NULL ||
            hidrd_strm_opt_spec_list_valid(type->opts_spec)) &&
#endif
           (type->read != NULL || type->write != NULL);
}



/** @file
 * @brief HID report descriptor - stream sink type
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

#include "hidrd/cfg.h"
#ifdef HIDRD_WITH_OPT
#include "hidrd/opt/spec_list.h"
#endif
#include "hidrd/strm/snk/type.h"
#include "hidrd/strm/snk/inst.h"

bool
hidrd_snk_type_valid(const hidrd_snk_type *type)
{
    return type != NULL &&
           type->size >= sizeof(hidrd_snk) &&
#ifdef HIDRD_WITH_OPT
           (type->init != NULL || type->init_opts == NULL) &&
           (type->init_opts == NULL ||
            hidrd_opt_spec_list_valid(type->opts_spec)) &&
#endif
           type->put != NULL &&
           type->errmsg != NULL;
}



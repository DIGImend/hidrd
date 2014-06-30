/** @file
 * @brief HID report descriptor - supported format list
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

#include <strings.h>
#include "hidrd/fmt/cfg.h"
#include "hidrd/fmt/natv.h"
#ifdef HIDRD_FMT_WITH_XML
#include "hidrd/fmt/xml.h"
#endif
#ifdef HIDRD_FMT_WITH_SPEC
#include "hidrd/fmt/spec.h"
#endif
#ifdef HIDRD_FMT_WITH_CODE
#include "hidrd/fmt/code.h"
#endif
#include "hidrd/fmt/list.h"

/** Supported format list, terminated by NULL */
const hidrd_fmt *hidrd_fmt_list[]  = {
    &hidrd_natv,
#ifdef HIDRD_FMT_WITH_XML
    &hidrd_xml,
#endif
#ifdef HIDRD_FMT_WITH_SPEC
    &hidrd_spec,
#endif
#ifdef HIDRD_FMT_WITH_CODE
    &hidrd_code,
#endif
    NULL
};


const hidrd_fmt *
hidrd_fmt_list_lkp(const char *name)
{
    const hidrd_fmt   **pfmt;

    for (pfmt = hidrd_fmt_list; *pfmt != NULL; pfmt++)
        if (strcasecmp((*pfmt)->name, name) == 0)
            return *pfmt;

    return NULL;
}

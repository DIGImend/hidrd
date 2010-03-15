/** @file
 * @brief HID report descriptor - XML source - bitmap-based element handling
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
 * @(#) $Id: src_element.h 244 2010-03-08 19:13:53Z spb_nick $
 */

#ifndef __SRC_ELEMENT_BITMAP_H__
#define __SRC_ELEMENT_BITMAP_H__

#include "element.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Process input element. */
extern ELEMENT(input);
/** Process output element. */
extern ELEMENT(output);
/** Process feature element. */
extern ELEMENT(feature);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __SRC_ELEMENT_BITMAP_H__ */

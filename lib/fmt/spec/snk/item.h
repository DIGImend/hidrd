/** @file
 * @brief HID report descriptor - specification example sink - item output
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
 * @(#) $Id: element.h 283 2010-03-20 12:58:33Z spb_nick $
 */

#ifndef __SPEC_SNK_ITEM_H__
#define __SPEC_SNK_ITEM_H__

#include "hidrd/fmt/spec/snk.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Put a basic item to a specification example sink.
 *
 * @param spec_snk  Specification example sink instance.
 * @param item      Item to put.
 *
 * @return True if put successfully, false otherwise.
 */
extern bool spec_snk_item_basic(hidrd_spec_snk_inst    *spec_snk,
                                const hidrd_item       *item);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __SPEC_SNK_ITEM_H__ */

/** @file
 * @brief HID report descriptor - specification example sink - text output
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

#ifndef __SPEC_SNK_TEXT_H__
#define __SPEC_SNK_TEXT_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Output an item text to a specification example sink.
 *
 * @param spec_snk  Specification example sink.
 * @param name      Item name to output; could be NULL.
 * @param value     Item value to output; could be NULL.
 * @param comment   Item comment to output; could be NULL.
 *
 * @return True if output successfully, false if failed to allocate memory.
 */
extern bool text_item(hidrd_spec_snk_inst  *spec_snk,
                      const char           *name,
                      const char           *value, 
                      const char           *comment);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __SPEC_SNK_TEXT_H__ */

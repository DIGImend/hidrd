/** @file
 * @brief HID report descriptor - XML sink - element breaking
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

#ifndef __SNK_ELEMENT_BREAK_H__
#define __SNK_ELEMENT_BREAK_H__

#include "element.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Break open an element.
 *
 * @alg Add a starting element next to the original element, with
 *      specified name, and the original element's properties. Move the
 *      contents of the original element right after the new element. Add an
 *      ending element with specified name next to the moved original
 *      contents. Remove the original element.
 *
 * @param element       The element to break.
 * @param create_start  Starting element creation function, could be NULL,
 *                      if starting element is not needed.
 * @param create_end    Ending element creation function, could be NULL,
 *                      if ending element is not needed.
 *
 * @return True if broken successfully, false otherwise.
 */
extern bool element_break(xmlNodePtr            element,
                          element_create_fn    *create_start,
                          element_create_fn    *create_end);

/**
 * Prototype for a function used to retrieve starting and
 * ending element creation functions when breaking.
 *
 * @param name          Element name to break.
 * @param pcreate_start Location for a pointer to the start element creation
 *                      function.
 * @param pcreate_end   Location for a pointer to the end element creation
 *                      function.
 *
 * @return True if element is known, false otherwise.
 */
typedef bool element_break_fn(const char *name,
                              element_create_fn **pcreate_start,
                              element_create_fn **pcreate_end);

/**
 * Break open an element branch up to the specified parent.
 *
 * @alg Break open the specified element and all its parent elements up to
 *      but not including the specified parent element.
 *
 * @param parent    Parent element to stop at.
 * @param element   Element to start breaking from.
 * @param cb        Break function - used to retrieve starting and ending
 *                  element creation functions when breaking.
 *
 * @return True if broken successfuly, false otherwise.
 */
extern bool element_break_branch(xmlNodePtr         parent,
                                 xmlNodePtr         element,
                                 element_break_fn  *cb);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __SNK_ELEMENT_BREAK_H__ */



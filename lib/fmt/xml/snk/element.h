/** @file
 * @brief HID report descriptor - XML sink - element handling
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

#ifndef __SNK_ELEMENT_H__
#define __SNK_ELEMENT_H__

#include "hidrd/util/fmt.h"
#include "hidrd/fmt/xml/snk.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Prototype for a function used to create and setup an element.
 *
 * @param doc       Document.
 * @param ns        Namespace.
 *
 * @return Created element, or NULL if failed.
 */
typedef xmlNodePtr element_create_fn(xmlDocPtr doc, xmlNsPtr ns);

/**
 * Create a new element and make it current.
 *
 * @param xml_snk   XML sink.
 * @param name      Element name to create.
 *
 * @return True if created successfully, false otherwise.
 */
extern bool element_new(hidrd_xml_snk_inst *xml_snk,
                        const char         *name);

/**
 * Set attribute of the current element.
 *
 * @param xml_snk   XML sink.
 * @param fmt       Attribute value format type.
 * @param pap       Pointer to a variable argument list (va_list) containing
 *                  format arguments.
 *
 * @return True if set successfully, false otherwise.
 */
extern bool element_set_attrpv(hidrd_xml_snk_inst  *xml_snk,
                               const char          *name,
                               hidrd_fmt_type       fmt,
                               va_list             *pap);

/**
 * Add content to the current element.
 *
 * @param xml_snk   XML sink.
 * @param fmt       Content format type.
 * @param pap       Pointer to a variable argument list (va_list) containing
 *                  format arguments.
 *
 * @return True if added successfully, false otherwise.
 */
extern bool element_add_contentpv(hidrd_xml_snk_inst   *xml_snk,
                                  hidrd_fmt_type        fmt,
                                  va_list              *pap);

/**
 * Add a comment node to the current element.
 *
 * @param xml_snk   XML sink.
 * @param fmt       Comment format type.
 * @param pap       Pointer to a variable argument list (va_list) containing
 *                  format arguments.
 *
 * @return True if added successfully, false otherwise.
 */
extern bool element_add_commentpv(hidrd_xml_snk_inst   *xml_snk,
                                  hidrd_fmt_type        fmt,
                                  va_list              *pap);

/**
 * Commit the current element.
 *
 * @param xml_snk   XML sink.
 * @param container "Container" flag - should be true if the current element
 *                  should become a parent.
 */
extern void element_commit(hidrd_xml_snk_inst  *xml_snk,
                           bool                 container);

/** Element sub-node type */
typedef enum element_nt {
    ELEMENT_NT_NONE,
    ELEMENT_NT_CONTENT,
    ELEMENT_NT_COMMENT,
    ELEMENT_NT_ATTR
} element_nt;

/**
 * Add element with a contents.
 *
 * @param xml_snk   XML sink.
 * @param container "Container" flag - should be true if the created element
 *                  should become a parent.
 * @param name      Element name.
 * @param ...       Contents specification - a list of node type/node
 *                  parameter sequences, terminated by ELEMENT_NT_NONE.
 *
 * @return True if added successfully, false otherwise.
 */
extern bool element_add(hidrd_xml_snk_inst *xml_snk,
                        bool                container,
                        const char         *name,
                        ...);

/**
 * Add element with a contents, va_list pointer version.
 *
 * @param xml_snk   XML sink.
 * @param container "Container" flag - should be true if the created element
 *                  should become a parent.
 * @param name      Element name.
 * @param pap       Pointer to a variable arguments list (va_list) with
 *                  contents specification - a list of node type/node
 *                  parameter sequences, terminated by ELEMENT_NT_NONE.
 *
 * @return True if added successfully, false otherwise.
 */
extern bool element_addpv(hidrd_xml_snk_inst   *xml_snk,
                          bool                  container,
                          const char           *name,
                          va_list              *pap);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __SNK_ELEMENT_H__ */

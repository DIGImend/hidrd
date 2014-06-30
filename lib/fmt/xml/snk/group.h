/** @file
 * @brief HID report descriptor - XML sink - element group handling
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

#ifndef __XML_SNK_GROUP_H__
#define __XML_SNK_GROUP_H__

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Start a group.
 *
 * @param xml_snk   XML sink.
 * @param name      Group element name.
 * @param ...       Contents specification - a list of node type/node
 *                  parameter sequences, terminated by ELEMENT_NT_NONE.
 *
 * @return True if started successfully, false otherwise.
 */
extern bool xml_snk_group_start(hidrd_xml_snk_inst *xml_snk,
                                const char         *name,
                                ...);

/**
 * End a group.
 *
 * @param xml_snk   XML sink.
 * @param name      Group element name.
 *
 * @return True if ended successfully, false otherwise.
 */
extern bool xml_snk_group_end(hidrd_xml_snk_inst   *xml_snk,
                              const char           *name);

/**
 * Break groups from the current element up to the root.
 *
 * @param xml_snk   XML sink.
 *
 * @return True if broken successfully, false otherwise.
 */
extern bool xml_snk_group_break_branch(hidrd_snk *snk);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __XML_SNK_GROUP_H__ */

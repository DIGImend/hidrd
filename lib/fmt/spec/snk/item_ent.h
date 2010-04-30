/** @file
 * @brief HID report descriptor - specification example sink - item entry
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

#ifndef __SPEC_SNK_ITEM_ENT_H__
#define __SPEC_SNK_ITEM_ENT_H__

#include <limits.h>
#include "hidrd/util/fmt.h"
#include "hidrd/fmt/spec/snk.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Item entry node type */
typedef enum spec_snk_item_ent_nt {
    SPEC_SNK_ITEM_ENT_NT_VALUE   = 0,       /**< Value */
    SPEC_SNK_ITEM_ENT_NT_COMMENT = 1,       /**< Comment */
    SPEC_SNK_ITEM_ENT_NT_NONE    = UINT_MAX /**< None - for EOL */
} spec_snk_item_ent_nt;

/**
 * Check if a item entry node type is valid.
 *
 * @param nt    Node type to check.
 *
 * @return True if node type is valid, false otherwise.
 */
extern bool spec_snk_item_ent_nt_valid(spec_snk_item_ent_nt nt);

/**
 * Output an item entry to a specification example sink.
 *
 * @param spec_snk  Specification example sink.
 * @param name_tkn  Item name token.
 * @param ...       List of node type, format type & arguments sequences;
 *                  terminated with SPEC_SNK_ITEM_ENT_NT_NONE.
 *
 * @return True if output successfully, false if failed to allocate memory.
 */
extern bool spec_snk_item_entf(hidrd_spec_snk_inst *spec_snk,
                               const char          *name_tkn,
                               ...);

/**
 * Output an item entry to a specification example sink; va_list pointer
 * version.
 *
 * @param spec_snk  Specification example sink.
 * @param name_tkn  Item name token.
 * @param pap       Pointer to list of node type, format type & arguments
 *                  sequences; terminated with SPEC_SNK_ITEM_ENT_NT_NONE.
 *
 * @return True if output successfully, false if failed to allocate memory.
 */
extern bool spec_snk_item_entpvf(hidrd_spec_snk_inst   *spec_snk,
                                 const char            *name_tkn,
                                 va_list               *pap);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __SPEC_SNK_ITEM_ENT_H__ */

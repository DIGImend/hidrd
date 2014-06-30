/** @file
 * @brief HID report descriptor - specification example sink - entry list
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

#ifndef __HIDRD_FMT_SPEC_SNK_ENT_LIST_H__
#define __HIDRD_FMT_SPEC_SNK_ENT_LIST_H__

#include <stddef.h>
#include "hidrd/util/ttbl.h"
#include "hidrd/fmt/spec/snk/ent.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HIDRD_SPEC_SNK_ENT_LIST_MIN_SIZE   128

/** Entry list */
typedef struct hidrd_spec_snk_ent_list {
    hidrd_spec_snk_ent *ptr;    /**< Array pointer */
    size_t              len;    /**< List length, in entries */
    size_t              size;   /**< Allocated memory, in entries */
} hidrd_spec_snk_ent_list;

/** Empty entry list initializer */
#define HIDRD_SPEC_SNK_ENT_LIST_EMPTY {.ptr = NULL, .len = 0, .size = 0}

/**
 * Initialize (empty) entry list.
 *
 * @param list  Entry list to initialize.
 */
extern void hidrd_spec_snk_ent_list_init(hidrd_spec_snk_ent_list *list);

/**
 * Add an entry to a list.
 *
 * @param list  Entry list to add to.
 * @param ent   Entry to add.
 *
 * @return True if added successfully, false otherwise.
 */
extern bool hidrd_spec_snk_ent_list_add(hidrd_spec_snk_ent_list    *list,
                                        const hidrd_spec_snk_ent   *ent);

/**
 * Add an entry to a list, freeing the original entry.
 *
 * @param list  Entry list to add to.
 * @param ent   Entry to add and free afterwards.
 *
 * @return True if added successfully, false otherwise.
 */
extern bool hidrd_spec_snk_ent_list_adda(hidrd_spec_snk_ent_list   *list,
                                         hidrd_spec_snk_ent        *ent);

/**
 * Check if an entry list is valid.
 *
 * @param list  Entry list to check.
 *
 * @return True if the list is valid, false otherwise.
 */
extern bool hidrd_spec_snk_ent_list_valid(
                                    const hidrd_spec_snk_ent_list  *list);

/**
 * Find minimum entry depth of a list.
 *
 * @param list  Entry list to find minimum depth in.
 *
 * @return Minimum entry depth, or INT_MAX, if there are no entries.
 */
extern int hidrd_spec_snk_ent_list_min_depth(
                                    const hidrd_spec_snk_ent_list *list);

/** Code column number in table output */
#define HIDRD_SPEC_SNK_ENT_LIST_CODE_COL    0
/** Item dump column number in table output */
#define HIDRD_SPEC_SNK_ENT_LIST_DUMP_COL    1
/** Comment column number in table output */
#define HIDRD_SPEC_SNK_ENT_LIST_CMNT_COL    2

/**
 * Render entry list as a text table.
 *
 * @param psize     Location for output text table.
 * @param list      Entry list to render.
 * @param tabstop   Number of spaces per tab.
 * @param dumps     "Output item dumps" flag.
 * @param comments  "Output item comments" flag.
 *
 * @return True if rendered successfully, false otherwise (on memory
 *         allocation failure).
 */
extern bool hidrd_spec_snk_ent_list_to_tbl(
                                hidrd_ttbl                    **ptbl,
                                const hidrd_spec_snk_ent_list  *list,
                                size_t                          tabstop,
                                bool                            dumps,
                                bool                            comments);

/**
 * Render entry list text.
 *
 * @param pbuf      Location for output text buffer pointer.
 * @param psize     Location for output text buffer size.
 * @param list      Entry list to render.
 * @param tabstop   Number of spaces per tab.
 * @param dumps     "Output item dumps" flag.
 * @param comments  "Output item comments" flag.
 *
 * @return True if rendered successfully, false otherwise (on memory
 *         allocation failure).
 */
extern bool hidrd_spec_snk_ent_list_render(
                                void                          **pbuf,
                                size_t                         *psize,
                                const hidrd_spec_snk_ent_list  *list,
                                size_t                          tabstop,
                                bool                            dumps,
                                bool                            comments);

/**
 * Cleanup an entry list.
 *
 * @param list  List to cleanup.
 */
extern void hidrd_spec_snk_ent_list_clnp(hidrd_spec_snk_ent_list   *list);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_FMT_SPEC_SNK_ENT_LIST_H__ */

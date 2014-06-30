/** @file
 * @brief HID report descriptor - specification example sink - entry
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

#ifndef __HIDRD_FMT_SPEC_SNK_ENT_H__
#define __HIDRD_FMT_SPEC_SNK_ENT_H__

#include "hidrd/item.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Specification example format entry */
typedef struct hidrd_spec_snk_ent {
    int         depth;      /**< Nesting depth */
    hidrd_item *item;       /**< Native item; could be NULL,
                                 if name and value are NULL */
    char       *name;       /**< Item name; could be NULL,
                                 if item and value are NULL */
    char       *value;      /**< Item value; could be NULL */
    char       *comment;    /**< Comment; could be NULL */
} hidrd_spec_snk_ent;

/**
 * Check if an entry name is valid.
 *
 * @param name  Entry name to check.
 *
 * @return True if the name is valid, false otherwise.
 */
extern bool hidrd_spec_snk_ent_name_valid(const char *name);

/**
 * Check if an entry value is valid.
 *
 * @param value Entry value to check.
 *
 * @return True if the value is valid, false otherwise.
 */
extern bool hidrd_spec_snk_ent_value_valid(const char *value);

/**
 * Check if an entry comment is valid.
 *
 * @param comment   Entry comment to check.
 *
 * @return True if the comment is valid, false otherwise.
 */
extern bool hidrd_spec_snk_ent_comment_valid(const char *comment);

/**
 * Check if an entry is valid.
 *
 * @param ent   Entry to check.
 *
 * @return True if the entry is valid, false otherwise.
 */
extern bool hidrd_spec_snk_ent_valid(const hidrd_spec_snk_ent *ent);

/**
 * Initialize an entry, copying native item, name, value and comment, if
 * specified.
 *
 * @param ent       Entry to initialize.
 * @param depth     Depth.
 * @param item      Native item; could be NULL if name and value are NULL.
 * @param name      Item name; could be NULL if item and value are NULL.
 * @param value     Item value; could be NULL.
 * @param comment   Comment; could be NULL.
 *
 * @return Initialized entry.
 */
extern hidrd_spec_snk_ent *hidrd_spec_snk_ent_init(
                                    hidrd_spec_snk_ent *ent,
                                    int                 depth,
                                    const hidrd_item   *item,
                                    const char         *name,
                                    const char         *value,
                                    const char         *comment);

/**
 * Allocate and initialize an entry, copying native item, name, value and
 * comment, if specified.
 *
 * @param ent       Entry to initialize.
 * @param depth     Depth.
 * @param item      Native item; could be NULL if name and value are NULL.
 * @param name      Item name; could be NULL if item and value are NULL.
 * @param value     Item value; could be NULL.
 * @param comment   Comment; could be NULL.
 *
 * @return Dynamically allocated and initialized entry.
 */
extern hidrd_spec_snk_ent *hidrd_spec_snk_ent_new(
                                    int                 depth,
                                    const hidrd_item   *item,
                                    const char         *name,
                                    const char         *value,
                                    const char         *comment);

/**
 * Initialize an entry, taking over native item, name, value and comment, if
 * specified.
 *
 * @param ent       Entry to initialize.
 * @param depth     Depth.
 * @param item      Native item; could be NULL if name and value are NULL.
 * @param name      Item name; could be NULL if item and value are NULL.
 * @param value     Item value; could be NULL.
 * @param comment   Comment; could be NULL.
 *
 * @return Initialized entry.
 */
extern hidrd_spec_snk_ent *hidrd_spec_snk_ent_inita(
                                    hidrd_spec_snk_ent *ent,
                                    int                 depth,
                                    hidrd_item         *item,
                                    char               *name,
                                    char               *value,
                                    char               *comment);

/**
 * Allocated and initialize an entry, taking over native item, name, value
 * and comment, if specified.
 *
 * @param ent       Entry to initialize.
 * @param depth     Depth.
 * @param item      Native item; could be NULL if name and value are NULL.
 * @param name      Item name; could be NULL if item and value are NULL.
 * @param value     Item value; could be NULL.
 * @param comment   Comment; could be NULL.
 *
 * @return Dynamically allocated and initialized entry.
 */
extern hidrd_spec_snk_ent *hidrd_spec_snk_ent_newa(
                                    int                 depth,
                                    hidrd_item         *item,
                                    char               *name,
                                    char               *value,
                                    char               *comment);

/**
 * Cleanup an entry.
 *
 * @param ent   Entry to cleanup.
 */
extern void hidrd_spec_snk_ent_clnp(hidrd_spec_snk_ent *ent);

/**
 * Cleanup and free an entry.
 *
 * @param ent   Entry to cleanup and free.
 */
extern void hidrd_spec_snk_ent_delete(hidrd_spec_snk_ent *ent);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_FMT_SPEC_SNK_ENT_H__ */

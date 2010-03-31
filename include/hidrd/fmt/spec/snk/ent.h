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
 *
 * @(#) $Id: element.h 283 2010-03-20 12:58:33Z spb_nick $
 */

#ifndef __HIDRD_FMT_SPEC_SNK_ENT_H__
#define __HIDRD_FMT_SPEC_SNK_ENT_H__

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Specification example format entry */
typedef struct hidrd_spec_snk_ent {
    int     depth;      /**< Nesting depth */
    char   *name;       /**< Item name; could be NULL, if value is NULL */
    char   *value;      /**< Item value; could be NULL */
    char   *comment;    /**< Comment; could be NULL */
} hidrd_spec_snk_ent;

extern bool hidrd_spec_snk_ent_name_valid(const char *name);

extern bool hidrd_spec_snk_ent_value_valid(const char *value);

extern bool hidrd_spec_snk_ent_comment_valid(const char *comment);

extern bool hidrd_spec_snk_ent_valid(const hidrd_spec_snk_ent *ent);

extern hidrd_spec_snk_ent *hidrd_spec_snk_ent_init(
                                    hidrd_spec_snk_ent *ent,
                                    int                 depth,
                                    const char         *name,
                                    const char         *value,
                                    const char         *comment);

extern hidrd_spec_snk_ent *hidrd_spec_snk_ent_new(
                                    int                 depth,
                                    const char         *name,
                                    const char         *value,
                                    const char         *comment);

extern hidrd_spec_snk_ent *hidrd_spec_snk_ent_inita(
                                    hidrd_spec_snk_ent *ent,
                                    int                 depth,
                                    char               *name,
                                    char               *value,
                                    char               *comment);

extern hidrd_spec_snk_ent *hidrd_spec_snk_ent_newa(
                                    int                 depth,
                                    char               *name,
                                    char               *value,
                                    char               *comment);

extern void hidrd_spec_snk_ent_clnp(hidrd_spec_snk_ent *ent);

extern void hidrd_spec_snk_ent_delete(hidrd_spec_snk_ent *ent);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_FMT_SPEC_SNK_ENT_H__ */

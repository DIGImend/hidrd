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
 * @(#) $Id$
 */

#include "hidrd/util/str.h"
#include "hidrd/item.h"
#include "item_ent.h"
#include "item.h"

#define ITEM(_name_tkn, _args...) \
    spec_snk_item_entf(spec_snk, #_name_tkn,                \
                       ##_args, SPEC_SNK_ITEM_ENT_NT_NONE)

#define VALUE(_fmt, _args...) \
    SPEC_SNK_ITEM_ENT_NT_VALUE, HIDRD_FMT_TYPE_##_fmt, ##_args

#define COMMENT(_fmt, _args...) \
    SPEC_SNK_ITEM_ENT_NT_COMMENT, HIDRD_FMT_TYPE_##_fmt, ##_args

#define CASE_ITEM_S32(_TYPE, _NAME, _name) \
    case HIDRD_ITEM_##_TYPE##_TAG_##_NAME:                              \
        return                                                          \
            ITEM(_name,                                                 \
                 VALUE(S32,                                             \
                       (int32_t)hidrd_item_##_name##_get_value(item)))

#define CASE_ITEM_U32(_TYPE, _NAME, _name) \
    case HIDRD_ITEM_##_TYPE##_TAG_##_NAME:                              \
        return                                                          \
            ITEM(_name,                                                 \
                 VALUE(U32,                                             \
                       (uint32_t)hidrd_item_##_name##_get_value(item)))


static bool
spec_snk_item_main(hidrd_spec_snk_inst *spec_snk,
                   const hidrd_item    *item)
{
    assert(hidrd_item_main_valid(item));

    switch (hidrd_item_main_get_tag(item))
    {
        case HIDRD_ITEM_MAIN_TAG_COLLECTION:
            if (!ITEM(collection,
                      VALUE(STROWN,
                           hidrd_tkn_hmnz(
                            hidrd_item_collection_type_to_token_or_dec(
                                hidrd_item_collection_get_type(item)),
                            HIDRD_TKN_HMNZ_CAP_WF))))
                return false;

            spec_snk->depth++;
            return true;

        case HIDRD_ITEM_MAIN_TAG_END_COLLECTION:
            spec_snk->depth--;
            return ITEM(end_collection);

        default:
            /* TODO add contents value */
            return ITEM(main);
    }
}


static bool
spec_snk_item_global(hidrd_spec_snk_inst *spec_snk,
                     const hidrd_item    *item)
{
    assert(hidrd_item_global_valid(item));

    switch (hidrd_item_global_get_tag(item))
    {
        CASE_ITEM_S32(GLOBAL, LOGICAL_MINIMUM, logical_minimum);
        CASE_ITEM_S32(GLOBAL, LOGICAL_MAXIMUM, logical_maximum);
        CASE_ITEM_S32(GLOBAL, PHYSICAL_MINIMUM, physical_minimum);
        CASE_ITEM_S32(GLOBAL, PHYSICAL_MAXIMUM, physical_maximum);
        CASE_ITEM_S32(GLOBAL, UNIT_EXPONENT, unit_exponent);
        CASE_ITEM_U32(GLOBAL, REPORT_SIZE, report_size);
        CASE_ITEM_U32(GLOBAL, REPORT_ID, report_id);
        CASE_ITEM_U32(GLOBAL, REPORT_COUNT, report_count);

        case HIDRD_ITEM_GLOBAL_TAG_USAGE_PAGE:
            spec_snk->state->usage_page =
                hidrd_item_usage_page_get_value(item);
            return
                ITEM(usage_page,
                     VALUE(STROWN,
                           hidrd_tkn_hmnz(
                            hidrd_usage_page_to_token_or_hex(
                                hidrd_item_usage_page_get_value(item)),
                            HIDRD_TKN_HMNZ_CAP_WF)),
                     COMMENT(STROWN,
                             hidrd_str_uc_first(
                                hidrd_usage_page_desc(
                                    hidrd_item_usage_page_get_value(
                                        item)))));

        case HIDRD_ITEM_GLOBAL_TAG_PUSH:
            {
                hidrd_spec_snk_state   *new_state;

                if (!ITEM(push))
                    return false;

                /* Push state */
                new_state = malloc(sizeof(*new_state));
                if (new_state == NULL)
                    return false;
                memcpy(new_state, spec_snk->state, sizeof(*new_state));
                new_state->prev = spec_snk->state;
                spec_snk->state = new_state;

                return true;
            }

        case HIDRD_ITEM_GLOBAL_TAG_POP:
            {
                hidrd_spec_snk_state   *prev_state;

                /* Pop state, if possible */
                prev_state = spec_snk->state->prev;
                if (prev_state != NULL)
                {
                    free(spec_snk->state);
                    spec_snk->state = prev_state;
                }

                return ITEM(pop);
            }

        default:
            /* TODO add contents value */
            return ITEM(global);
    }
}


static bool
spec_snk_item_local(hidrd_spec_snk_inst *spec_snk,
                    const hidrd_item    *item)
{
    assert(hidrd_item_local_valid(item));

    switch (hidrd_item_local_get_tag(item))
    {
        CASE_ITEM_U32(LOCAL, DESIGNATOR_INDEX, designator_index);
        CASE_ITEM_U32(LOCAL, DESIGNATOR_MINIMUM, designator_minimum);
        CASE_ITEM_U32(LOCAL, DESIGNATOR_MAXIMUM, designator_maximum);
        CASE_ITEM_U32(LOCAL, STRING_INDEX, string_index);
        CASE_ITEM_U32(LOCAL, STRING_MINIMUM, string_minimum);
        CASE_ITEM_U32(LOCAL, STRING_MAXIMUM, string_maximum);

        case HIDRD_ITEM_LOCAL_TAG_DELIMITER:
            return ITEM(delimiter,
                        VALUE(STRDUP,
                              (hidrd_item_delimiter_get_value(item) ==
                               HIDRD_ITEM_DELIMITER_SET_OPEN)
                                ? "Open"
                                : "Close"));

        default:
            /* TODO add contents value */
            return ITEM(local);
    }
}


static bool
spec_snk_item_short(hidrd_spec_snk_inst    *spec_snk,
                    const hidrd_item       *item)
{
    hidrd_item_short_type   type;

    assert(hidrd_item_short_valid(item));

    switch (type = hidrd_item_short_get_type(item))
    {
        case HIDRD_ITEM_SHORT_TYPE_MAIN:
            return spec_snk_item_main(spec_snk, item);
        case HIDRD_ITEM_SHORT_TYPE_GLOBAL:
            return spec_snk_item_global(spec_snk, item);
        case HIDRD_ITEM_SHORT_TYPE_LOCAL:
            return spec_snk_item_local(spec_snk, item);
        default:
            /* TODO add contents value */
            return ITEM(short);
    }
}


static bool
spec_snk_item_long(hidrd_spec_snk_inst *spec_snk,
                   const hidrd_item    *item)
{
    assert(hidrd_item_long_valid(item));
    (void)item;

    /* TODO add contents value */
    return ITEM(long);
                
}


bool
spec_snk_item_basic(hidrd_spec_snk_inst    *spec_snk,
                    const hidrd_item       *item)
{
    switch (hidrd_item_basic_get_format(item))
    {
        case HIDRD_ITEM_BASIC_FORMAT_SHORT:
            return spec_snk_item_short(spec_snk, item);
        case HIDRD_ITEM_BASIC_FORMAT_LONG:
            return spec_snk_item_long(spec_snk, item);
        default:
            /* Unknown basic format */
            return false;
    }
}



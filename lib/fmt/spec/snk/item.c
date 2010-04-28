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
#include "hidrd/util/hex.h"
#include "hidrd/util/buf.h"
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

#define RETURN_ITEM_SHORT_GENERIC(_type) \
    do {                                                                \
        char   *data_str;                                               \
        char   *value;                                                  \
                                                                        \
        data_str = hidrd_hex_buf_to_str(                                \
                    /* We won't change it, we promise */                \
                    hidrd_item_short_get_data((hidrd_item *)item),      \
                    hidrd_item_short_get_data_bytes(item));             \
        if (data_str == NULL)                                           \
            return false;                                               \
                                                                        \
        if (asprintf(&value,                                            \
                     ((hidrd_item_short_get_data_size(item) ==          \
                        HIDRD_ITEM_SHORT_DATA_SIZE_0B)                  \
                            ? "tag:%u"                                  \
                            : "tag:%u data:%sh"),                       \
                     (unsigned int)hidrd_item_##_type##_get_tag(item),  \
                     data_str) < 0)                                     \
        {                                                               \
            free(data_str);                                             \
            return false;                                               \
        }                                                               \
        free(data_str);                                                 \
                                                                        \
        return ITEM(_type, VALUE(STROWN, value));                       \
    } while (0)

static bool
spec_snk_item_main_bitmap(hidrd_spec_snk_inst  *spec_snk,
                          const hidrd_item     *item)
{
    bool        result          = false;
    bool        first           = true;
    hidrd_buf   buf             = HIDRD_BUF_EMPTY;
    char        name_buf[32];
    uint8_t     bit;

    assert(hidrd_item_input_valid(item) ||
           hidrd_item_output_valid(item) ||
           hidrd_item_feature_valid(item));

#define BIT(_idx, _off_name, _on_name) \
    do {                                                            \
        if (hidrd_item_main_get_bit(item, _idx))                    \
        {                                                           \
            if (snprintf(name_buf, sizeof(name_buf),                \
                         "%s", #_on_name) >= (int)sizeof(name_buf)) \
                goto cleanup;                                       \
            hidrd_tkn_hmnz(name_buf, HIDRD_TKN_HMNZ_CAP_WF);        \
                                                                    \
            if (!hidrd_buf_add_printf(&buf,                         \
                                      (first ? "%s" : ", %s"),      \
                                      name_buf))                    \
                goto cleanup;                                       \
                                                                    \
            first = false;                                          \
        }                                                           \
    } while (0)

    BIT(0, data, constant);
    BIT(1, array, variable);
    BIT(2, absolute, relative);
    BIT(3, no_wrap, wrap);
    BIT(4, linear, non_linear);
    BIT(5, preferred_state, no_preferred);
    BIT(6, no_null_position, null_state);
    if (hidrd_item_main_get_tag(item) == HIDRD_ITEM_MAIN_TAG_INPUT)
        BIT(7, no_bit7, bit7);
    else
        BIT(7, non_volatile, volatile);
    BIT(8, bit_field, buffered_bytes);

#undef BIT

    for (bit = 9; bit < 32; bit++)
        if (hidrd_item_main_get_bit(item, bit))
        {
            if (snprintf(name_buf, sizeof(name_buf), "bit%hhu", bit) >=
                (int)sizeof(name_buf))
                goto cleanup;
            hidrd_tkn_hmnz(name_buf, HIDRD_TKN_HMNZ_CAP_WF);

            if (!hidrd_buf_add_printf(&buf,
                                      (first ? "%s" : ", %s"),
                                      name_buf))
                goto cleanup;

            first = false;
        }

    hidrd_buf_add_span(&buf, '\0', 1);
    hidrd_buf_retension(&buf);

    result = spec_snk_item_entf(spec_snk,
                                hidrd_item_main_tag_to_token(
                                    hidrd_item_main_get_tag(item)),
                                VALUE(STROWN, buf.ptr),
                                SPEC_SNK_ITEM_ENT_NT_NONE);
    hidrd_buf_init(&buf);

cleanup:

    hidrd_buf_clnp(&buf);

    return result;
}


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
                            HIDRD_NUM_TO_ALT_STRCD(
                                item_collection_type,
                                hidrd_item_collection_get_type(item),
                                token, dec),
                            HIDRD_TKN_HMNZ_CAP_WF))))
                return false;

            spec_snk->depth++;
            return true;

        case HIDRD_ITEM_MAIN_TAG_END_COLLECTION:
            spec_snk->depth--;
            return ITEM(end_collection);

        case HIDRD_ITEM_MAIN_TAG_INPUT:
        case HIDRD_ITEM_MAIN_TAG_OUTPUT:
        case HIDRD_ITEM_MAIN_TAG_FEATURE:
            return spec_snk_item_main_bitmap(spec_snk, item);

        default:
            RETURN_ITEM_SHORT_GENERIC(main);
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
                            HIDRD_NUM_TO_ALT_STRCD(
                                usage_page,
                                hidrd_item_usage_page_get_value(item),
                                token, shex),
                            HIDRD_TKN_HMNZ_CAP_WF)),
                     COMMENT(STROWN,
                             hidrd_str_uc_first(
                                hidrd_usage_page_fmt_desc(
                                    hidrd_item_usage_page_get_value(
                                        item)))));

        case HIDRD_ITEM_GLOBAL_TAG_UNIT:
            {
                hidrd_unit  unit    = hidrd_item_unit_get_value(item);

                if (unit == HIDRD_UNIT_NONE)
                    return ITEM(unit);
                else if (!hidrd_unit_void(unit) && hidrd_unit_known(unit) &&
                         hidrd_unit_system_known(
                             hidrd_unit_get_system(unit)))
                    return
                        ITEM(unit,
                             VALUE(STROWN,
                                   hidrd_unit_to_expr(
                                      unit, HIDRD_TKN_HMNZ_CAP_WF)));

                return
                    ITEM(unit,
                        VALUE(BHEX,
                              hidrd_item_short_get_data((hidrd_item *)item),
                              hidrd_item_short_get_data_bytes(item)));
            }
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
            RETURN_ITEM_SHORT_GENERIC(global);
    }
}


static char *
hidrd_usage_to_shex_id(hidrd_usage usage)
{
    return hidrd_usage_id_to_shex(hidrd_usage_get_id(usage));
}


static bool
spec_snk_item_usage(hidrd_spec_snk_inst    *spec_snk,
                    const char             *name_tkn,
                    hidrd_usage             usage)
{
    bool    result          = false;
    char   *token_or_bhex   = NULL;
    char   *desc            = NULL;

    if (!hidrd_usage_defined_page(usage))
        usage = hidrd_usage_set_page(usage, spec_snk->state->usage_page);

    if (hidrd_usage_get_page(usage) == spec_snk->state->usage_page)
    {
        token_or_bhex = HIDRD_NUM_TO_ALT_STR2D(usage, usage,
                                               token, shex_id);
        if (token_or_bhex == NULL)
            goto cleanup;
        desc = hidrd_usage_fmt_desc_id(usage);
        if (desc == NULL)
            goto cleanup;
    }
    else
    {
        token_or_bhex = HIDRD_NUM_TO_ALT_STR2D(usage, usage, token, shex);
        if (token_or_bhex == NULL)
            goto cleanup;
        desc = hidrd_usage_fmt_desc(usage);
        if (desc == NULL)
            goto cleanup;
    }

    hidrd_tkn_hmnz(token_or_bhex, HIDRD_TKN_HMNZ_CAP_WF);

    result = spec_snk_item_entf(spec_snk,
                                name_tkn,
                                VALUE(STROWN, token_or_bhex),
                                COMMENT(STROWN, desc),
                                SPEC_SNK_ITEM_ENT_NT_NONE);
    token_or_bhex = NULL;
    desc = NULL;

cleanup:

    free(desc);
    free(token_or_bhex);

    return result;
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

        case HIDRD_ITEM_LOCAL_TAG_USAGE:
            return spec_snk_item_usage(spec_snk, "usage",
                                       hidrd_item_usage_get_value(item));

        case HIDRD_ITEM_LOCAL_TAG_USAGE_MINIMUM:
            return spec_snk_item_usage(
                        spec_snk, "usage_minimum",
                        hidrd_item_usage_minimum_get_value(item));

        case HIDRD_ITEM_LOCAL_TAG_USAGE_MAXIMUM:
            return spec_snk_item_usage(
                        spec_snk, "usage_maximum",
                        hidrd_item_usage_maximum_get_value(item));

        case HIDRD_ITEM_LOCAL_TAG_DELIMITER:
        {
            char   *value;

            value = strdup((hidrd_item_delimiter_get_value(item) ==
                               HIDRD_ITEM_DELIMITER_SET_OPEN)
                                ? "open"
                                : "close");
            if (value == NULL)
                return false;

            hidrd_tkn_hmnz(value, HIDRD_TKN_HMNZ_CAP_WF);

            return ITEM(delimiter, VALUE(STROWN, value));
        }

        default:
            RETURN_ITEM_SHORT_GENERIC(local);
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
            {
                char   *data_str;
                char   *value;

                data_str = hidrd_hex_buf_to_str(
                            /* We won't change it, we promise */
                            hidrd_item_short_get_data((hidrd_item *)item),
                            hidrd_item_short_get_data_bytes(item));
                if (data_str == NULL)
                    return false;

                if (asprintf(&value,
                             ((hidrd_item_short_get_data_size(item) == 
                                HIDRD_ITEM_SHORT_DATA_SIZE_0B)
                                    ? "type:%u tag:%u"
                                    : "type:%u tag:%u data:%sh"),
                             (unsigned int)hidrd_item_short_get_type(item),
                             (unsigned int)hidrd_item_short_get_tag(item),
                             data_str) < 0)
                {
                    free(data_str);
                    return false;
                }
                free(data_str);

                return ITEM(short, VALUE(STROWN, value));
            }
    }
}


static bool
spec_snk_item_long(hidrd_spec_snk_inst *spec_snk,
                   const hidrd_item    *item)
{
    char   *data_str;
    char   *value;

    assert(hidrd_item_long_valid(item));

    data_str = hidrd_hex_buf_to_str(
                    /* We won't change it, we promise */
                    hidrd_item_long_get_data((hidrd_item *)item),
                    hidrd_item_long_get_data_size(item));
    if (data_str == NULL)
        return false;

    if (asprintf(&value,
                 ((hidrd_item_long_get_data_size(item) == 0)
                    ? "tag:%u"
                    : "tag:%u data:%sh"),
                 (unsigned int)hidrd_item_long_get_tag(item),
                 data_str) < 0)
    {
        free(data_str);
        return false;
    }
    free(data_str);

    return ITEM(long, VALUE(STROWN, value));
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



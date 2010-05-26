/** @file
 * @brief HID report descriptor - XML sink - item output
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

#include <errno.h>
#include "hidrd/util/str.h"
#include "element.h"
#include "group.h"
#include "item.h"


#define ATTR(_name, _fmt, _args...) \
    XML_SNK_ELEMENT_NT_ATTR, #_name, HIDRD_FMT_TYPE_##_fmt, ##_args

#define CONTENT(_fmt, _args...) \
    XML_SNK_ELEMENT_NT_CONTENT, HIDRD_FMT_TYPE_##_fmt, ##_args

#define COMMENT(_fmt, _args...) \
    XML_SNK_ELEMENT_NT_COMMENT, HIDRD_FMT_TYPE_##_fmt, ##_args

#define ADD_SIMPLE(_name, _args...) \
    xml_snk_element_add(xml_snk, false, #_name, ##_args,    \
                        XML_SNK_ELEMENT_NT_NONE)

#define GROUP_START(_name, _args...) \
    xml_snk_group_start(xml_snk, #_name, ##_args, XML_SNK_ELEMENT_NT_NONE)

#define GROUP_END(_name) \
    xml_snk_group_end(xml_snk, #_name)

#define CASE_SIMPLE_S32(_TYPE, _NAME, _name) \
    case HIDRD_ITEM_##_TYPE##_TAG_##_NAME:                              \
        return ADD_SIMPLE(                                              \
                _name,                                                  \
                CONTENT(S32,                                            \
                        (int32_t)hidrd_item_##_name##_get_value(item)))

#define CASE_SIMPLE_U32(_TYPE, _NAME, _name) \
    case HIDRD_ITEM_##_TYPE##_TAG_##_NAME:                          \
        return ADD_SIMPLE(                                          \
                _name,                                              \
                CONTENT(U32,                                        \
                        (uint32_t)                                  \
                            hidrd_item_##_name##_get_value(item)))


static bool
xml_snk_item_main_bitmap(hidrd_xml_snk_inst    *xml_snk,
                         const hidrd_item      *item)
{
    uint8_t bit;
    char    name[6];

    assert(xml_snk->cur == NULL);
    assert(hidrd_item_main_valid(item));
    assert(hidrd_item_input_valid(item) ||
           hidrd_item_output_valid(item) ||
           hidrd_item_feature_valid(item));

#define BIT(_idx, _on_name) \
    do {                                            \
        if (hidrd_item_main_get_bit(item, _idx) &&  \
            !ADD_SIMPLE(_on_name))                  \
            return false;                           \
    } while (0)

    BIT(0, constant);
    BIT(1, variable);
    BIT(2, relative);
    BIT(3, wrap);
    BIT(4, non_linear);
    BIT(5, no_preferred);
    BIT(6, null_state);
    if (hidrd_item_main_get_tag(item) == HIDRD_ITEM_MAIN_TAG_INPUT)
        BIT(7, bit7);
    else
        BIT(7, volatile);
    BIT(8, buffered_bytes);

#undef BIT

    for (bit = 9; bit < 32; bit++)
        if (hidrd_item_main_get_bit(item, bit))
        {
            if (snprintf(name, sizeof(name), "bit%hhu", bit) >=
                (int)sizeof(name))
                return false;

            if (!xml_snk_element_add(xml_snk, false, name,
                                     XML_SNK_ELEMENT_NT_NONE))
                return false;
        }

    return true;
}

static bool
xml_snk_item_main(hidrd_xml_snk_inst   *xml_snk,
                  const hidrd_item     *item)
{
    hidrd_item_main_tag tag;

    assert(hidrd_item_main_valid(item));

    switch (tag = hidrd_item_main_get_tag(item))
    {
        case HIDRD_ITEM_MAIN_TAG_COLLECTION:
            return GROUP_START(
                    COLLECTION,
                    ATTR(type, STROWN,
                         HIDRD_NUM_TO_ALT_STR2_1(
                             item_collection_type,
                             hidrd_item_collection_get_type(item),
                             token, lc, dec)));
        case HIDRD_ITEM_MAIN_TAG_END_COLLECTION:
            return GROUP_END(COLLECTION);

        case HIDRD_ITEM_MAIN_TAG_INPUT:
        case HIDRD_ITEM_MAIN_TAG_OUTPUT:
        case HIDRD_ITEM_MAIN_TAG_FEATURE:
            {
                char   *token;
                bool    result;

                assert(hidrd_item_main_tag_known(tag));

                token = hidrd_item_main_tag_to_token(tag);
                assert(token != NULL || errno != 0);
                if (token == NULL)
                {
                    XML_ERR("failed to allocate a main tag token");
                    return false;
                }
                token = hidrd_str_lc(token);
                result = xml_snk_element_add(xml_snk, true, token,
                                             XML_SNK_ELEMENT_NT_NONE);
                free(token);
                if (!result)
                    return false;

                if (!xml_snk_item_main_bitmap(xml_snk, item))
                    return false;

                xml_snk->prnt = xml_snk->prnt->parent;

                return true;
            }
        default:
            return ADD_SIMPLE(
                    main,
                    ATTR(tag, STROWN,
                         HIDRD_NUM_TO_ALT_STR2_1(
                             item_main_tag, tag, token, lc, dec)),
                    CONTENT(
                        HEX,
                        /* We promise we won't change it */
                        hidrd_item_short_get_data((hidrd_item *)item)),
                        hidrd_item_short_get_data_bytes(item));
    }
}


static bool
xml_snk_item_unit_generic(hidrd_xml_snk_inst   *xml_snk,
                          hidrd_unit            unit)
{
    bool            success = false;
    bool            inside  = false;
    hidrd_unit_exp  exp;

    if (!xml_snk_element_add(xml_snk, true, "generic",
                     ATTR(system, STROWN,
                          HIDRD_NUM_TO_ALT_STR2_1(
                              unit_system,
                              hidrd_unit_get_system(unit),
                              token, lc, dec)),
                     XML_SNK_ELEMENT_NT_NONE))
        goto cleanup;

    inside = true;

#define EXP(_name) \
    do {                                                                \
        exp = hidrd_unit_get_##_name(unit);                             \
        if (exp != HIDRD_UNIT_EXP_0)                                    \
        {                                                               \
            if (exp == HIDRD_UNIT_EXP_1)                                \
            {                                                           \
                if (!ADD_SIMPLE(_name))                                 \
                    goto cleanup;                                       \
            }                                                           \
            else                                                        \
            {                                                           \
                if (!ADD_SIMPLE(_name,                                  \
                        CONTENT(S32,                                    \
                                (int32_t)hidrd_unit_exp_to_int(exp))))  \
                    goto cleanup;                                       \
            }                                                           \
        }                                                               \
    } while (0)

    EXP(length);
    EXP(mass);
    EXP(time);
    EXP(temperature);
    EXP(current);
    EXP(luminous_intensity);

#undef EXP

    success = true;

cleanup:

    if (inside)
        xml_snk->prnt = xml_snk->prnt->parent;

    return success;
}


static bool
xml_snk_item_unit_specific(hidrd_xml_snk_inst  *xml_snk,
                           hidrd_unit           unit)
{
    bool                success = false;
    hidrd_unit_system   system;
    char               *token;
    bool                inside  = false;
    hidrd_unit_exp      exp;

    assert(hidrd_unit_valid(unit));
    system = hidrd_unit_get_system(unit);
    assert(hidrd_unit_system_known(system));

    token = hidrd_unit_system_to_token(system);
    assert(token != NULL || errno != 0);
    if (token == NULL)
        XML_ERR_CLNP("failed to allocate unit system token");
    token = hidrd_str_lc(token);

    if (!xml_snk_element_add(xml_snk, true,
                             token,
                             XML_SNK_ELEMENT_NT_NONE))
        goto cleanup;

    free(token);
    token = NULL;

    inside = true;

#define EXP(_gen_name, _spec_expr) \
    do {                                                                \
        exp = hidrd_unit_get_##_gen_name(unit);                         \
        if (exp != HIDRD_UNIT_EXP_0)                                    \
        {                                                               \
            const char *_spec_name = (_spec_expr);                      \
                                                                        \
            if (exp == HIDRD_UNIT_EXP_1)                                \
            {                                                           \
                if (!xml_snk_element_add(xml_snk, false, _spec_name,    \
                                         XML_SNK_ELEMENT_NT_NONE))      \
                    goto cleanup;                                       \
            }                                                           \
            else                                                        \
            {                                                           \
                if (!xml_snk_element_add(                               \
                        xml_snk, false, _spec_name,                     \
                        CONTENT(S32,                                    \
                                (int32_t)hidrd_unit_exp_to_int(exp)),   \
                        XML_SNK_ELEMENT_NT_NONE))                       \
                    goto cleanup;                                       \
            }                                                           \
        }                                                               \
    } while (0)

    EXP(length,
        (system == HIDRD_UNIT_SYSTEM_SI_LINEAR)
            ? "centimeter"
            : (system == HIDRD_UNIT_SYSTEM_SI_ROTATION)
                ? "radians"
                : (system == HIDRD_UNIT_SYSTEM_ENGLISH_LINEAR)
                    ? "inch"
                    : "degrees");
    EXP(mass,
        (system == HIDRD_UNIT_SYSTEM_SI_LINEAR ||
         system == HIDRD_UNIT_SYSTEM_SI_ROTATION)
            ? "gram"
            : "slug");
    EXP(time, "seconds");
    EXP(temperature,
        (system == HIDRD_UNIT_SYSTEM_SI_LINEAR ||
         system == HIDRD_UNIT_SYSTEM_SI_ROTATION)
            ? "kelvin"
            : "fahrenheit");
    EXP(current, "ampere");
    EXP(luminous_intensity, "candela");

#undef EXP

    success = true;

cleanup:

    if (inside)
        xml_snk->prnt = xml_snk->prnt->parent;
    free(token);

    return success;
}


static bool
xml_snk_item_unit(hidrd_xml_snk_inst   *xml_snk,
                  const hidrd_item     *item)
{
    hidrd_unit  unit;
    bool        success     = false;
    bool        inside      = false;

    assert(hidrd_item_unit_valid(item));

    unit = hidrd_item_unit_get_value(item);

    if (!xml_snk_element_add(xml_snk, true, "unit",
                             XML_SNK_ELEMENT_NT_NONE))
        goto cleanup;
    inside = true;

    /*
     * If the unit value could be interpreted with our API and it does
     * contain something meaningful.
     */
    /* If the unit is "none" - i.e. there is no units */
    if (unit == HIDRD_UNIT_NONE)
        success = ADD_SIMPLE(none);
    /*
     * If the unit is void (indicates no particular units) or 
     * unknown, (cannot be interpreted by our API)
     */
    else if (hidrd_unit_void(unit) || !hidrd_unit_known(unit))
        success =
            ADD_SIMPLE(
                value,
                CONTENT(HEX,
                        /* We promise we won't change it */
                        hidrd_item_short_get_data((hidrd_item *)item),
                        hidrd_item_short_get_data_bytes(item)));
    else
        /* If the unit system is known to us */
        success = hidrd_unit_system_known(hidrd_unit_get_system(unit))
                    ? xml_snk_item_unit_specific(xml_snk, unit)
                    : xml_snk_item_unit_generic(xml_snk, unit);

cleanup:

    if (inside)
        xml_snk->prnt = xml_snk->prnt->parent;

    return success;
}


static bool
xml_snk_item_global(hidrd_xml_snk_inst *xml_snk,
                    const hidrd_item   *item)
{
    hidrd_item_global_tag   tag;

    assert(hidrd_item_global_valid(item));

    switch (tag = hidrd_item_global_get_tag(item))
    {
        CASE_SIMPLE_S32(GLOBAL, LOGICAL_MINIMUM, logical_minimum);
        CASE_SIMPLE_S32(GLOBAL, LOGICAL_MAXIMUM, logical_maximum);
        CASE_SIMPLE_S32(GLOBAL, PHYSICAL_MINIMUM, physical_minimum);
        CASE_SIMPLE_S32(GLOBAL, PHYSICAL_MAXIMUM, physical_maximum);
        CASE_SIMPLE_S32(GLOBAL, UNIT_EXPONENT, unit_exponent);
        CASE_SIMPLE_U32(GLOBAL, REPORT_SIZE, report_size);
        CASE_SIMPLE_U32(GLOBAL, REPORT_ID, report_id);
        CASE_SIMPLE_U32(GLOBAL, REPORT_COUNT, report_count);

        case HIDRD_ITEM_GLOBAL_TAG_UNIT:
            return xml_snk_item_unit(xml_snk, item);

        case HIDRD_ITEM_GLOBAL_TAG_USAGE_PAGE:
            xml_snk->state->usage_page =
                hidrd_item_usage_page_get_value(item);
            return ADD_SIMPLE(
                    usage_page,
                    CONTENT(STROWN,
                            HIDRD_NUM_TO_ALT_STR2_1(
                                usage_page,
                                hidrd_item_usage_page_get_value(item),
                                token, lc, hex)),
                    COMMENT(STROWN,
                            hidrd_str_apada(
                                hidrd_str_uc_first(
                                    hidrd_usage_page_desc_str(
                                        hidrd_item_usage_page_get_value(
                                            item))))));

        case HIDRD_ITEM_GLOBAL_TAG_PUSH:
            {
                hidrd_xml_snk_state   *new_state;

                /* Push state */
                new_state = malloc(sizeof(*new_state));
                if (new_state == NULL)
                {
                    XML_ERR("failed to allocate a state table");
                    return false;
                }
                memcpy(new_state, xml_snk->state, sizeof(*new_state));
                new_state->prev = xml_snk->state;
                xml_snk->state = new_state;

                return GROUP_START(PUSH);
            }
        case HIDRD_ITEM_GLOBAL_TAG_POP:
            {
                hidrd_xml_snk_state   *prev_state;

                /* Pop state, if possible */
                prev_state = xml_snk->state->prev;
                if (prev_state != NULL)
                {
                    free(xml_snk->state);
                    xml_snk->state = prev_state;
                }
                return GROUP_END(PUSH);
            }
        default:
            return ADD_SIMPLE(
                    global,
                    ATTR(tag, STROWN,
                         HIDRD_NUM_TO_ALT_STR2_1(
                             item_global_tag, tag, token, lc, dec)),
                    CONTENT(HEX,
                            /* We promise we won't change it */
                            hidrd_item_short_get_data((hidrd_item *)item)),
                            hidrd_item_short_get_data_bytes(item));
    }
}


static char *
hidrd_usage_to_id_hex(hidrd_usage usage)
{
    return hidrd_usage_id_to_hex(hidrd_usage_get_id(usage));
}


static bool
xml_snk_item_usage(hidrd_xml_snk_inst  *xml_snk,
                   const char          *name,
                   hidrd_usage          usage)
{
    bool    success         = false;
    char   *token_or_hex    = NULL;
    char   *desc            = NULL;

    if (!hidrd_usage_defined_page(usage))
        usage = hidrd_usage_set_page(usage, xml_snk->state->usage_page);

    if (hidrd_usage_get_page(usage) == xml_snk->state->usage_page)
    {
        token_or_hex = HIDRD_NUM_TO_ALT_STR2_1(usage, usage,
                                               token, lc, id_hex);
        if (token_or_hex == NULL)
            XML_ERR_CLNP("failed to convert usage to string");
        desc = hidrd_usage_desc_id_str(usage);
        if (desc == NULL)
            XML_ERR_CLNP("failed to format usage description");
    }
    else
    {
        token_or_hex = HIDRD_NUM_TO_ALT_STR2_1(usage, usage,
                                               token, lc, hex);
        if (token_or_hex == NULL)
            XML_ERR_CLNP("failed to convert usage to string");
        desc = hidrd_usage_desc_str(usage);
        if (desc == NULL)
            XML_ERR_CLNP("failed to format usage description");
    }

    if (*desc == '\0')
    {
        success = xml_snk_element_add(xml_snk, false, name,
                                      CONTENT(STROWN, token_or_hex),
                                      XML_SNK_ELEMENT_NT_NONE);
        token_or_hex = NULL;
    }
    else
    {
        success = xml_snk_element_add(xml_snk, false, name,
                                      CONTENT(STROWN, token_or_hex),
                                      COMMENT(STROWN,
                                              hidrd_str_apada(
                                                hidrd_str_uc_first(desc))),
                                      XML_SNK_ELEMENT_NT_NONE);
        token_or_hex = NULL;
        desc = NULL;
    }

cleanup:

    free(desc);
    free(token_or_hex);

    return success;
}


static bool
xml_snk_item_local(hidrd_xml_snk_inst  *xml_snk,
                   const hidrd_item    *item)
{
    hidrd_item_local_tag    tag;

    assert(hidrd_item_local_valid(item));

    switch (tag = hidrd_item_local_get_tag(item))
    {
        CASE_SIMPLE_U32(LOCAL, DESIGNATOR_INDEX, designator_index);
        CASE_SIMPLE_U32(LOCAL, DESIGNATOR_MINIMUM, designator_minimum);
        CASE_SIMPLE_U32(LOCAL, DESIGNATOR_MAXIMUM, designator_maximum);
        CASE_SIMPLE_U32(LOCAL, STRING_INDEX, string_index);
        CASE_SIMPLE_U32(LOCAL, STRING_MINIMUM, string_minimum);
        CASE_SIMPLE_U32(LOCAL, STRING_MAXIMUM, string_maximum);

        case HIDRD_ITEM_LOCAL_TAG_USAGE:
            return xml_snk_item_usage(xml_snk, "usage",
                                      hidrd_item_usage_get_value(item));

        case HIDRD_ITEM_LOCAL_TAG_USAGE_MINIMUM:
            return xml_snk_item_usage(
                        xml_snk, "usage_minimum",
                        hidrd_item_usage_minimum_get_value(item));

        case HIDRD_ITEM_LOCAL_TAG_USAGE_MAXIMUM:
            return xml_snk_item_usage(
                        xml_snk, "usage_maximum",
                        hidrd_item_usage_maximum_get_value(item));

        case HIDRD_ITEM_LOCAL_TAG_DELIMITER:
            return (hidrd_item_delimiter_get_value(item) ==
                    HIDRD_ITEM_DELIMITER_SET_OPEN)
                        ? GROUP_START(SET)
                        : GROUP_END(SET);

        default:
            return ADD_SIMPLE(
                    local,
                    ATTR(tag, STROWN,
                         HIDRD_NUM_TO_ALT_STR2_1(
                             item_local_tag, tag, token, lc, dec)),
                    CONTENT(HEX,
                            /* We promise we won't change it */
                            hidrd_item_short_get_data((hidrd_item *)item)),
                            hidrd_item_short_get_data_bytes(item));
    }
}


static bool
xml_snk_item_short(hidrd_xml_snk_inst  *xml_snk,
                   const hidrd_item    *item)
{
    assert(hidrd_item_short_valid(item));

    switch (hidrd_item_short_get_type(item))
    {
        case HIDRD_ITEM_SHORT_TYPE_MAIN:
            return xml_snk_item_main(xml_snk, item);
        case HIDRD_ITEM_SHORT_TYPE_GLOBAL:
            return xml_snk_item_global(xml_snk, item);
        case HIDRD_ITEM_SHORT_TYPE_LOCAL:
            return xml_snk_item_local(xml_snk, item);
        default:
            return ADD_SIMPLE(short,
                    ATTR(type, STROWN,
                         HIDRD_NUM_TO_ALT_STR2_1(
                             item_short_type,
                             hidrd_item_short_get_type(item),
                             token, lc, dec)),
                    ATTR(tag, STROWN,
                         hidrd_item_short_tag_to_dec(
                             hidrd_item_short_get_tag(item))),
                    CONTENT(HEX,
                            /* We promise we won't change it */
                            hidrd_item_short_get_data((hidrd_item *)item)),
                            hidrd_item_short_get_data_bytes(item));
    }
}


bool
xml_snk_item_basic(hidrd_xml_snk_inst  *xml_snk,
                   const hidrd_item    *item)
{
    switch (hidrd_item_basic_get_format(item))
    {
        case HIDRD_ITEM_BASIC_FORMAT_LONG:
            return ADD_SIMPLE(
                        long,
                        ATTR(tag, U32,
                             (uint32_t)hidrd_item_long_get_tag(item)),
                        CONTENT(
                            HEX,
                            /* We promise we won't change it */
                            hidrd_item_long_get_data((hidrd_item *)item)),
                            (size_t)hidrd_item_long_get_data_size(item));

        case HIDRD_ITEM_BASIC_FORMAT_SHORT:
            return xml_snk_item_short(xml_snk, item);
        default:
            return ADD_SIMPLE(basic,
                    ATTR(type, STROWN,
                         HIDRD_NUM_TO_ALT_STR2_1(
                             item_basic_type,
                             hidrd_item_basic_get_type(item),
                             token, lc, dec)),
                    ATTR(tag, STROWN,
                         hidrd_item_basic_tag_to_dec(
                             hidrd_item_basic_get_tag(item))),
                    ATTR(tag, U32,
                         (uint32_t)hidrd_item_basic_get_data_bytes(item)),
                    CONTENT(HEX,
                            /* We promise we won't change it */
                            hidrd_item_basic_get_data((hidrd_item *)item)),
                            hidrd_item_basic_get_data_bytes(item));
    }
}



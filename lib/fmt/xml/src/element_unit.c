/** @file
 * @brief HID report descriptor - XML source - unit element handling
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
 * @(#) $Id: src_element.h 244 2010-03-08 19:13:53Z spb_nick $
 */

#include "hidrd/util/hex.h"
#include "hidrd/util/str.h"
#include "element_unit.h"

typedef const char *unit_system_desc[HIDRD_UNIT_NIBBLE_INDEX_EXP_NUM];

static const unit_system_desc  generic_usd = {
    "length", "mass", "time", "temperature", "current", "luminous_intensity"
};
static const unit_system_desc  si_linear_usd = {
    "centimeter", "gram", "seconds", "kelvin", "ampere", "candela"
};
static const unit_system_desc  si_rotation_usd = {
    "radians", "gram", "seconds", "kelvin", "ampere", "candela"
};
static const unit_system_desc  english_linear_usd = {
    "inch", "slug", "seconds", "fahrenheit", "ampere", "candela"
};
static const unit_system_desc  english_rotation_usd = {
    "degrees", "slug", "seconds", "fahrenheit", "ampere", "candela"
};

static bool
parse_unit_system_element(hidrd_unit               *punit,
                          const unit_system_desc    usd,
                          xmlNodePtr                e)
{
    bool            result  = false;
    hidrd_unit      unit    = HIDRD_UNIT_NONE;
    size_t          i;
    bool            matched;
    char           *exp_str = NULL;
    hidrd_unit_exp  exp;

    for (i = 0, e = e->children; e != NULL; e = e->next)
    {
        if (e->type != XML_ELEMENT_NODE)
            continue;

        for (matched = false; !matched; i++)
        {
            if (i > sizeof(unit_system_desc) / sizeof(*usd))
                /* Unknown element name */
                goto cleanup;

            if (strcmp(usd[i], (const char *)e->name) != 0)
                continue;

            exp_str = (char *)xmlNodeGetContent(e);
            if (exp_str == NULL)
                goto cleanup;
            if (hidrd_str_isblank(exp_str))
                exp = HIDRD_UNIT_EXP_1;
            else if (!hidrd_unit_exp_from_dec(&exp, exp_str))
                goto cleanup;
            xmlFree(exp_str);
            exp_str = NULL;

            unit = hidrd_unit_set_nibble(
                            unit,
                            i + HIDRD_UNIT_NIBBLE_INDEX_EXP_MIN,
                            exp);
            matched = true;
        }
    }

    if (punit != NULL)
        *punit = unit;

    result = true;

cleanup:

    xmlFree(exp_str);

    return result;
}


static bool
parse_unit_system_gen_element(hidrd_unit *punit, xmlNodePtr e)
{
    bool        result  = false;
    hidrd_unit  unit;
    
    ELEMENT_PROP_DECL(unit_system, system);

    ELEMENT_PROP_RETR_ALT2(unit_system, system, token, dec);

    if (!parse_unit_system_element(&unit, generic_usd, e))
        goto cleanup;

    unit = hidrd_unit_set_system(unit, system);

    if (punit != NULL)
        *punit = unit;

    result = true;

cleanup:

    ELEMENT_PROP_CLNP(system);

    return result;
}


static const unit_system_desc
                *known_system_list[HIDRD_UNIT_SYSTEM_KNOWN_NUM] = {
#define MAP(_NAME, _name) \
    [HIDRD_UNIT_SYSTEM_##_NAME - HIDRD_UNIT_SYSTEM_KNOWN_MIN] = &_name##_usd
    MAP(SI_LINEAR, si_linear),
    MAP(SI_ROTATION, si_rotation),
    MAP(ENGLISH_LINEAR, english_linear),
    MAP(ENGLISH_ROTATION, english_rotation)
#undef MAP
};

static bool
parse_unit_system_spec_element(hidrd_unit          *punit,
                               hidrd_unit_system    system,
                               xmlNodePtr           e)
{
    hidrd_unit  unit;

    assert(hidrd_unit_system_valid(system));
    assert(hidrd_unit_system_known(system));

    if (!parse_unit_system_element(
                &unit,
                *known_system_list[system - HIDRD_UNIT_SYSTEM_KNOWN_MIN],
                e))
        return false;

    unit = hidrd_unit_set_system(unit, system);

    if (punit != NULL)
        *punit = unit;

    return true;
}


static bool
parse_unit_value_element(hidrd_unit *punit, xmlNodePtr e)
{
    bool        result      = false;
    uint32_t    unit        = 0;
    char       *data_str    = NULL;

    data_str = (char *)xmlNodeGetContent(e);
    if (data_str == NULL)
        goto cleanup;
    if (!hidrd_hex_buf_from_str(&unit, sizeof(unit),
                                NULL, data_str))
        goto cleanup;

    if (punit != NULL)
        *punit = hidrd_num_u32_from_le(&unit);

    result = true;

cleanup:

    xmlFree(data_str);

    return result;
}


ELEMENT(unit)
{
    hidrd_unit          unit;

    /* Lookup first element */
    for (e = e->children;
         e != NULL && e->type != XML_ELEMENT_NODE;
         e = e->next);
    /* If none */
    if (e == NULL)
        return XML_SRC_ELEMENT_RC_ERROR;

#define MATCH(_name) (strcmp((const char *)e->name, #_name) == 0)
    if (MATCH(none))
    {
        unit = HIDRD_UNIT_NONE;
        goto finish;
    }
    else if (MATCH(value))
    {
        if (parse_unit_value_element(&unit, e))
            goto finish;
    }
    else if (MATCH(generic))
    {
        if (parse_unit_system_gen_element(&unit, e))
            goto finish;
    }
#define MAP(_NAME, _name) \
    else if (MATCH(_name))                                              \
    {                                                                   \
        if (parse_unit_system_spec_element(&unit,                       \
                                           HIDRD_UNIT_SYSTEM_##_NAME,   \
                                           e))                          \
            goto finish;                                                \
    }
    MAP(SI_LINEAR, si_linear)
    MAP(SI_ROTATION, si_rotation)
    MAP(ENGLISH_LINEAR, english_linear)
    MAP(ENGLISH_ROTATION, english_rotation)
#undef MAP
#undef MATCH

    return XML_SRC_ELEMENT_RC_ERROR;

finish:

    /* Lookup extra element */
    for (e = e->next;
         e != NULL && e->type != XML_ELEMENT_NODE;
         e = e->next);
    /* If any */
    if (e != NULL)
        return XML_SRC_ELEMENT_RC_ERROR;

    hidrd_item_unit_init(item, unit);

    return XML_SRC_ELEMENT_RC_ITEM;
}

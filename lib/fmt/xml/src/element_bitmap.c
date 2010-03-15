/** @file
 * @brief HID report descriptor - XML source - bitmap-based element handling
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

#include "hidrd/util/str.h"
#include "element_bitmap.h"

typedef struct main_bit_desc {
    const char *off;
    const char *on;
} main_bit_desc;

#define MBD(_num, _off, _on) \
    static const main_bit_desc mbd##_num = {.off = #_off, .on = #_on}

MBD(0, data, constant);
MBD(1, array, variable);
MBD(2, absolute, relative);
MBD(3, no_wrap, wrap);
MBD(4, linear, non_linear);
MBD(5, preferred_state, no_preferred);
MBD(6, no_null_position, null_state);
MBD(7, non_volatile, volatile);
MBD(8, bit_field, buffered_bytes);

#undef MBD

typedef const main_bit_desc    *main_bitmap_desc[32];

#define MBMD(_name, _fields...) \
    static const main_bitmap_desc   _name##_bmd = {_fields}

MBMD(input,  &mbd0, &mbd1, &mbd2, &mbd3, &mbd4, &mbd5, &mbd6, NULL,  &mbd8);
MBMD(output, &mbd0, &mbd1, &mbd2, &mbd3, &mbd4, &mbd5, &mbd6, &mbd7, &mbd8);
#define feature_bmd output_bmd

static bool parse_bitmap_element(uint32_t                  *pbitmap,
                                 xmlNodePtr                 e,
                                 const main_bitmap_desc     bmd)
{
    bool        result      = false;
    uint32_t    bitmap      = 0;
    char       *data_str    = NULL;
    bool        data;
    bool        matched;
    size_t      i;
    char        i_name[6]   = "bit";

    for (i = 0, e = e->children; e != NULL; e = e->next)
    {
        if (e->type != XML_ELEMENT_NODE)
            continue;

        data_str = (char *)xmlNodeGetContent(e);
        if (data_str == NULL)
            goto cleanup;
        if (hidrd_str_isblank(data_str))
            data = true;
        else if (!hidrd_bool_from_str(&data, data_str))
            goto cleanup;
        xmlFree(data_str);
        data_str = NULL;

        for (matched = false; !matched; i++)
        {
            if (i > 31)
                /* Unkown element name */
                goto cleanup;
            if (bmd[i] != NULL &&
                strcmp(bmd[i]->off, (const char *)e->name) == 0)
                bitmap = HIDRD_BIT_SET(bitmap, i, !data);
            else if (bmd[i] != NULL &&
                     strcmp(bmd[i]->on, (const char *)e->name) == 0)
                bitmap = HIDRD_BIT_SET(bitmap, i, data);
            else
            {
                snprintf(i_name + 3, sizeof(i_name) - 3, "%zu", i);
                if (strcmp(i_name, (const char *)e->name) == 0)
                    bitmap = HIDRD_BIT_SET(bitmap, i, data);
                else
                    continue;
            }
            matched = true;
        }
    }

    if (pbitmap != NULL)
        *pbitmap = bitmap;

    result = true;

cleanup:

    xmlFree(data_str);

    return result;
}

#define BITMAP_ELEMENT(_name) \
    ELEMENT(_name)                                          \
    {                                                       \
        uint32_t    bitmap;                                 \
                                                            \
        if (!parse_bitmap_element(&bitmap, e, _name##_bmd)) \
            return ELEMENT_RC_ERROR;                        \
                                                            \
        hidrd_item_##_name##_init(xml_src->item, bitmap);   \
                                                            \
        return ELEMENT_RC_ITEM;                             \
    }

BITMAP_ELEMENT(input)
BITMAP_ELEMENT(output)
BITMAP_ELEMENT(feature)



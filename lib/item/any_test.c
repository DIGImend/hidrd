/** @file
 * @brief HID report descriptor item - universal methods test.
 *
 * Copyright (C) 2009 Nikolai Kondrashov
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


#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include "hidrd/item.h"

#define V_U32_TYPE  uint32_t
#define V_U32_FMT   "%u"
#define V_U16_TYPE  uint16_t
#define V_U16_FMT   "%hu"
#define V_U8_TYPE   uint8_t
#define V_U8_FMT    "%hhu"
#define V_S32_TYPE  int32_t
#define V_S32_FMT   "%d"
#define V_S16_TYPE  int16_t
#define V_S16_FMT   "%hd"
#define V_S8_TYPE   int8_t
#define V_S8_FMT    "%hhd"

#define ITEM_ERROR(_fmt, _args...) \
    error_at_line(1, 0, __FILE__, __LINE__,                 \
                  "Item %s " _fmt ".", item_desc, ##_args)

#define BEGIN_ITEM(_name, _desc, _byte...) \
    do {                                                                \
        const char         *item_desc   = _desc;                        \
        const uint8_t       orig_buf[]  = {_byte};                      \
        const hidrd_item   *orig_item   = orig_buf;                     \
        const size_t        orig_size   = sizeof(orig_buf);             \
        size_t              test_size   = 0;                            \
                                                                        \
        if (!hidrd_item_fits(orig_item, orig_size, &test_size))         \
            ITEM_ERROR("doesn't fit (%u != %u)", test_size, orig_size); \
        if (test_size != orig_size)                                     \
            ITEM_ERROR("fits, but size is invalid (%u != %u)",          \
                       test_size, orig_size);                           \
                                                                        \
        test_size = hidrd_item_get_size(orig_item);                     \
        if (test_size != orig_size)                                     \
            ITEM_ERROR("size invalid (%u != %u)",                       \
                       test_size, orig_size);                           \
                                                                        \
        if (!hidrd_item_valid(orig_item))                               \
            ITEM_ERROR("considered invalid by the generic check");      \
                                                                        \
        if (!hidrd_item_##_name##_valid(orig_item))                     \
            ITEM_ERROR("considered invalid by the specific check");

#define END_ITEM \
    } while (0)

#define ITEM(_name, _desc, _byte...) \
    BEGIN_ITEM(_name, _desc, ##_byte);  \
    END_ITEM;

#define ITEM_EMPTY(_name, _desc, _byte...) \
    BEGIN_ITEM(_name, _desc, ##_byte);  \
    END_ITEM;

#define ITEM_WVALUE(_name, _desc, _type, _orig_value, _byte...) \
    BEGIN_ITEM(_name, _desc, ##_byte);                                  \
        V_##_type##_TYPE test_value;                                    \
                                                                        \
        test_value = hidrd_item_##_name##_get_value(orig_item);         \
        if (test_value != _orig_value)                                  \
            ITEM_ERROR("value is invalid "                              \
                       "(" V_##_type##_FMT " != " V_##_type##_FMT ")",  \
                       test_value, _orig_value);                        \
        if (!hidrd_item_##_name##_value_valid(test_value))              \
            ITEM_ERROR("value %u is considered invalid", test_value);   \
    END_ITEM

#define ITEM_WTYPE(_name, _desc, _orig_type, _byte...) \
    BEGIN_ITEM(_name, _desc, ##_byte);                              \
        uint32_t    test_type;                                      \
                                                                    \
        test_type = hidrd_item_##_name##_get_type(orig_item);       \
        if (test_type != _orig_type)                                \
            ITEM_ERROR("type is invalid (%u != %u)",                \
                       test_type, _orig_type);                      \
        if (!hidrd_item_##_name##_type_valid(test_type))            \
            ITEM_ERROR("type %u is considered invalid", test_type); \
    END_ITEM

#define BEGIN_ITEM_WBITS(_name, _desc, _byte...) \
    BEGIN_ITEM(_name, _desc, ##_byte)

#define ITEM_BIT(_on_name, _off_name) \
    do {                                                        \
        if (!hidrd_item_input_is_##_on_name(orig_item))         \
            ITEM_ERROR("is not %s unexpectedly", #_on_name);    \
        if (hidrd_item_input_is_##_off_name(orig_item))         \
            ITEM_ERROR("is %s unexpectedly", #_off_name);       \
    } while (0)

#define END_ITEM_WBITS \
    END_ITEM


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    /*
     * WP8060U report descriptor
     */
    ITEM_WVALUE(usage_page,     "USAGE_PAGE (Digitizers)",          U16, 0x0d, 0x05, 0x0d);
    ITEM_WVALUE(usage,          "USAGE (Pen)",                      U32, 0x02, 0x09, 0x02);
    ITEM_WTYPE(collection,      "COLLECTION (Application)",         0x01, 0xa1, 0x01);
    ITEM_WVALUE(report_id,        "REPORT_ID (7)",                  U8, 0x07, 0x85, 0x07);
    ITEM_WVALUE(usage,            "USAGE (Stylus)",                 U32, 0x20, 0x09, 0x20);
    ITEM_WTYPE(collection,        "COLLECTION (Physical)",          0x00, 0xa1, 0x00);
    ITEM_WVALUE(usage,              "USAGE (Tip Switch)",           U32, 0x42, 0x09, 0x42);
    ITEM_WVALUE(usage,              "USAGE (Barrel Switch)",        U32, 0x44, 0x09, 0x44);
    ITEM_WVALUE(usage,              "USAGE (Eraser)",               U32, 0x45, 0x09, 0x45);
    ITEM_WVALUE(logical_minimum,    "LOGICAL_MINIMUM (0)",          S32, 0x00, 0x15, 0x00);
    ITEM_WVALUE(logical_maximum,    "LOGICAL_MAXIMUM (1)",          S32, 0x01, 0x25, 0x01);
    ITEM_WVALUE(report_size,        "REPORT_SIZE (1)",              U32, 0x01, 0x75, 0x01);
    ITEM_WVALUE(report_count,       "REPORT_COUNT (3)",             U32, 0x03, 0x95, 0x03);
    BEGIN_ITEM_WBITS(input,         "INPUT (Data,Var,Abs)",         0x81, 0x02);
        ITEM_BIT(data, /* not */ constant);
        ITEM_BIT(variable, /* not */ array);
        ITEM_BIT(absolute, /* not */ relative);
        ITEM_BIT(no_wrap, /* not */ wrap);
        ITEM_BIT(linear, /* not */ non_linear);
        ITEM_BIT(preferred_state, /* not */ no_preferred);
        ITEM_BIT(no_null_position, /* not */ null_state);
        ITEM_BIT(bit_field, /* not */ buffered_bytes);
    END_ITEM_WBITS;
    ITEM_WVALUE(report_count,       "REPORT_COUNT (3)",             U32, 0x03, 0x95, 0x03);
    BEGIN_ITEM_WBITS(input,         "INPUT (Cnst,Var,Abs)",         0x81, 0x03);
        ITEM_BIT(constant, /* not */ data);
        ITEM_BIT(variable, /* not */ array);
        ITEM_BIT(absolute, /* not */ relative);
        ITEM_BIT(no_wrap, /* not */ wrap);
        ITEM_BIT(linear, /* not */ non_linear);
        ITEM_BIT(preferred_state, /* not */ no_preferred);
        ITEM_BIT(no_null_position, /* not */ null_state);
        ITEM_BIT(bit_field, /* not */ buffered_bytes);
    END_ITEM_WBITS;
    ITEM_WVALUE(usage,              "USAGE (In Range)",             U32, 0x32, 0x09, 0x32);
    ITEM_WVALUE(report_count,       "REPORT_COUNT (1)",             U32, 0x01, 0x95, 0x01);
    BEGIN_ITEM_WBITS(input,         "INPUT (Data,Var,Abs)",         0x81, 0x02);
        ITEM_BIT(data, /* not */ constant);
        ITEM_BIT(variable, /* not */ array);
        ITEM_BIT(absolute, /* not */ relative);
        ITEM_BIT(no_wrap, /* not */ wrap);
        ITEM_BIT(linear, /* not */ non_linear);
        ITEM_BIT(preferred_state, /* not */ no_preferred);
        ITEM_BIT(no_null_position, /* not */ null_state);
        ITEM_BIT(bit_field, /* not */ buffered_bytes);
    END_ITEM_WBITS;
    ITEM_WVALUE(report_count,       "REPORT_COUNT (1)",             U32, 0x01, 0x95, 0x01);
    BEGIN_ITEM_WBITS(input,         "INPUT (Cnst,Var,Abs)",         0x81, 0x03);
        ITEM_BIT(constant, /* not */ data);
        ITEM_BIT(variable, /* not */ array);
        ITEM_BIT(absolute, /* not */ relative);
        ITEM_BIT(no_wrap, /* not */ wrap);
        ITEM_BIT(linear, /* not */ non_linear);
        ITEM_BIT(preferred_state, /* not */ no_preferred);
        ITEM_BIT(no_null_position, /* not */ null_state);
        ITEM_BIT(bit_field, /* not */ buffered_bytes);
    END_ITEM_WBITS;
    ITEM_WVALUE(usage_page,         "USAGE_PAGE (Generic Desktop)", U16, 0x01, 0x05, 0x01);
    ITEM_WVALUE(usage,              "USAGE (X)",                    U32, 0x30, 0x09, 0x30);
    ITEM_WVALUE(report_size,        "REPORT_SIZE (16)",             U32, 0x10, 0x75, 0x10);
    ITEM_WVALUE(report_count,       "REPORT_COUNT (1)",             U32, 0x01, 0x95, 0x01);
    ITEM_EMPTY(push,                "PUSH",                         0xa4);
    ITEM_WVALUE(unit_exponent,      "UNIT_EXPONENT (-3)",           U32, 0x0d, 0x55, 0x0d);
    ITEM_WVALUE(unit,               "UNIT (Eng Lin:0x33)",          U32, 0x33, 0x65, 0x33);
    ITEM_WVALUE(physical_minimum,   "PHYSICAL_MINIMUM (0)",         S32, 0x00, 0x35, 0x00);
    ITEM_WVALUE(physical_maximum,   "PHYSICAL_MAXIMUM (8000)",      S32, 8000, 0x46, 0x40, 0x1f);
    ITEM_WVALUE(logical_maximum,    "LOGICAL_MAXIMUM (16000)",      S32, 16000, 0x26, 0x80, 0x3e);
    BEGIN_ITEM_WBITS(input,         "INPUT (Data,Var,Abs)",         0x81, 0x02);
        ITEM_BIT(data, /* not */ constant);
        ITEM_BIT(variable, /* not */ array);
        ITEM_BIT(absolute, /* not */ relative);
        ITEM_BIT(no_wrap, /* not */ wrap);
        ITEM_BIT(linear, /* not */ non_linear);
        ITEM_BIT(preferred_state, /* not */ no_preferred);
        ITEM_BIT(no_null_position, /* not */ null_state);
        ITEM_BIT(bit_field, /* not */ buffered_bytes);
    END_ITEM_WBITS;
    ITEM_WVALUE(usage,              "USAGE (Y)",                    U32, 0x31, 0x09, 0x31);
    ITEM_WVALUE(physical_maximum,   "PHYSICAL_MAXIMUM (6000)",      S32, 6000, 0x46, 0x70, 0x17);
    ITEM_WVALUE(logical_maximum,    "LOGICAL_MAXIMUM (12000)",      S32, 12000, 0x26, 0xe0, 0x2e);
    BEGIN_ITEM_WBITS(input,         "INPUT (Data,Var,Abs)",         0x81, 0x02);
        ITEM_BIT(data, /* not */ constant);
        ITEM_BIT(variable, /* not */ array);
        ITEM_BIT(absolute, /* not */ relative);
        ITEM_BIT(no_wrap, /* not */ wrap);
        ITEM_BIT(linear, /* not */ non_linear);
        ITEM_BIT(preferred_state, /* not */ no_preferred);
        ITEM_BIT(no_null_position, /* not */ null_state);
        ITEM_BIT(bit_field, /* not */ buffered_bytes);
    END_ITEM_WBITS;
    ITEM_EMPTY(pop,                 "POP",                          0xb4);
    ITEM_WVALUE(usage_page,         "USAGE_PAGE (Digitizers)",      U16, 0x0d, 0x05, 0x0d);
    ITEM_WVALUE(usage,              "USAGE (Tip Pressure)",         U32, 0x30, 0x09, 0x30);
    ITEM_WVALUE(logical_maximum,    "LOGICAL_MAXIMUM (1023)",       S32, 1023, 0x26, 0xff, 0x03);
    BEGIN_ITEM_WBITS(input,         "INPUT (Data,Var,Abs)",         0x81, 0x02);
        ITEM_BIT(data, /* not */ constant);
        ITEM_BIT(variable, /* not */ array);
        ITEM_BIT(absolute, /* not */ relative);
        ITEM_BIT(no_wrap, /* not */ wrap);
        ITEM_BIT(linear, /* not */ non_linear);
        ITEM_BIT(preferred_state, /* not */ no_preferred);
        ITEM_BIT(no_null_position, /* not */ null_state);
        ITEM_BIT(bit_field, /* not */ buffered_bytes);
    END_ITEM_WBITS;
    ITEM_WVALUE(report_size,        "REPORT_SIZE (16)",             U32, 0x10, 0x75, 0x10);
    ITEM_EMPTY(end_collection,    "END_COLLECTION",                 0xc0);
    ITEM_EMPTY(end_collection,  "END_COLLECTION",                   0xc0);
    ITEM_WVALUE(usage_page,     "USAGE_PAGE (Generic Desktop)",     U16, 0x01, 0x05, 0x01);
    ITEM_WVALUE(usage,          "USAGE (Mouse)",                    U32, 0x02, 0x09, 0x02);
    ITEM_WTYPE(collection,      "COLLECTION (Application)",         0x01, 0xa1, 0x01);
    ITEM_WVALUE(report_id,        "REPORT_ID (8)",                  U8, 0x08, 0x85, 0x08);
    ITEM_WVALUE(usage,            "USAGE (Pointer)",                U32, 0x01, 0x09, 0x01);
    ITEM_WTYPE(collection,        "COLLECTION (Physical)",          0x00, 0xa1, 0x00);
    ITEM_WVALUE(usage_page,         "USAGE_PAGE (Button)",          U16, 0x09, 0x05, 0x09);
    ITEM_WVALUE(usage_minimum,      "USAGE_MINIMUM (Undefined)",    U32, 0x01, 0x19, 0x01);
    ITEM_WVALUE(usage_maximum,      "USAGE_MAXIMUM (Undefined)",    U32, 0x03, 0x29, 0x03);
    ITEM_WVALUE(logical_minimum,    "LOGICAL_MINIMUM (0)",          S32, 0x00, 0x15, 0x00);
    ITEM_WVALUE(logical_maximum,    "LOGICAL_MAXIMUM (1)",          S32, 0x01, 0x25, 0x01);
    ITEM_WVALUE(report_count,       "REPORT_COUNT (3)",             U32, 0x03, 0x95, 0x03);
    ITEM_WVALUE(report_size,        "REPORT_SIZE (1)",              U32, 0x01, 0x75, 0x01);
    BEGIN_ITEM_WBITS(input,         "INPUT (Data,Var,Abs)",         0x81, 0x02);
        ITEM_BIT(data, /* not */ constant);
        ITEM_BIT(variable, /* not */ array);
        ITEM_BIT(absolute, /* not */ relative);
        ITEM_BIT(no_wrap, /* not */ wrap);
        ITEM_BIT(linear, /* not */ non_linear);
        ITEM_BIT(preferred_state, /* not */ no_preferred);
        ITEM_BIT(no_null_position, /* not */ null_state);
        ITEM_BIT(bit_field, /* not */ buffered_bytes);
    END_ITEM_WBITS;
    ITEM_WVALUE(report_count,       "REPORT_COUNT (5)",             U32, 0x05, 0x95, 0x05);
    BEGIN_ITEM_WBITS(input,         "INPUT (Cnst,Ary,Abs)",         0x81, 0x01);
        ITEM_BIT(constant, /* not */ data);
        ITEM_BIT(array, /* not */ variable);
        ITEM_BIT(absolute, /* not */ relative);
        ITEM_BIT(no_wrap, /* not */ wrap);
        ITEM_BIT(linear, /* not */ non_linear);
        ITEM_BIT(preferred_state, /* not */ no_preferred);
        ITEM_BIT(no_null_position, /* not */ null_state);
        ITEM_BIT(bit_field, /* not */ buffered_bytes);
    END_ITEM_WBITS;
    ITEM_WVALUE(usage_page,         "USAGE_PAGE (Generic Desktop)", U16, 0x01, 0x05, 0x01);
    ITEM_WVALUE(usage,              "USAGE (X)",                    U32, 0x30, 0x09, 0x30);
    ITEM_WVALUE(usage,              "USAGE (Y)",                    U32, 0x31, 0x09, 0x31);
    ITEM_WVALUE(usage,              "USAGE (Wheel)",                U32, 0x38, 0x09, 0x38);
    ITEM_WVALUE(usage,              "USAGE (Undefined)",            U32, 0x00, 0x09, 0x00);
    ITEM_WVALUE(logical_minimum,    "LOGICAL_MINIMUM (-127)",       S32, -127, 0x15, 0x81);
    ITEM_WVALUE(logical_maximum,    "LOGICAL_MAXIMUM (127)",        S32, 127, 0x25, 0x7f);
    ITEM_WVALUE(report_size,        "REPORT_SIZE (8)",              U32, 0x08, 0x75, 0x08);
    ITEM_WVALUE(report_count,       "REPORT_COUNT (4)",             U32, 0x04, 0x95, 0x04);
    BEGIN_ITEM_WBITS(input,         "INPUT (Data,Var,Rel)",         0x81, 0x06);
        ITEM_BIT(data, /* not */ constant);
        ITEM_BIT(variable, /* not */ array);
        ITEM_BIT(relative, /* not */ absolute);
        ITEM_BIT(no_wrap, /* not */ wrap);
        ITEM_BIT(linear, /* not */ non_linear);
        ITEM_BIT(preferred_state, /* not */ no_preferred);
        ITEM_BIT(no_null_position, /* not */ null_state);
        ITEM_BIT(bit_field, /* not */ buffered_bytes);
    END_ITEM_WBITS;
    ITEM_EMPTY(end_collection,    "END_COLLECTION",                 0xc0);
    ITEM_EMPTY(end_collection,  "END_COLLECTION",                   0xc0);
    ITEM_WVALUE(usage_page,     "USAGE_PAGE (Generic Desktop)",     U16, 0x01, 0x05, 0x01);
    ITEM_WVALUE(usage,          "USAGE (Mouse)",                    U32, 0x02, 0x09, 0x02);
    ITEM_WTYPE(collection,      "COLLECTION (Application)",         0x01, 0xa1, 0x01);
    ITEM_WVALUE(report_id,        "REPORT_ID (9)",                  U8, 0x09, 0x85, 0x09);
    ITEM_WVALUE(usage,            "USAGE (Pointer)",                U32, 0x01, 0x09, 0x01);
    ITEM_WTYPE(collection,        "COLLECTION (Physical)",          0x00, 0xa1, 0x00);
    ITEM_WVALUE(usage_page,       "USAGE_PAGE (Button)",            U16, 0x09, 0x05, 0x09);
    ITEM_WVALUE(usage_minimum,    "USAGE_MINIMUM (Button 1)",       U32, 0x01, 0x19, 0x01);
    ITEM_WVALUE(usage_maximum,    "USAGE_MAXIMUM (Button 3)",       U32, 0x03, 0x29, 0x03);
    ITEM_WVALUE(logical_minimum,  "LOGICAL_MINIMUM (0)",            S32, 0x00, 0x15, 0x00);
    ITEM_WVALUE(logical_maximum,  "LOGICAL_MAXIMUM (1)",            S32, 0x01, 0x25, 0x01);
    ITEM_WVALUE(report_count,     "REPORT_COUNT (3)",               U32, 0x03, 0x95, 0x03);
    ITEM_WVALUE(report_size,        "REPORT_SIZE (1)",              U32, 0x01, 0x75, 0x01);
    BEGIN_ITEM_WBITS(input,         "INPUT (Data,Var,Abs)",         0x81, 0x02);
        ITEM_BIT(data, /* not */ constant);
        ITEM_BIT(variable, /* not */ array);
        ITEM_BIT(absolute, /* not */ relative);
        ITEM_BIT(no_wrap, /* not */ wrap);
        ITEM_BIT(linear, /* not */ non_linear);
        ITEM_BIT(preferred_state, /* not */ no_preferred);
        ITEM_BIT(no_null_position, /* not */ null_state);
        ITEM_BIT(bit_field, /* not */ buffered_bytes);
    END_ITEM_WBITS;
    ITEM_WVALUE(report_count,     "REPORT_COUNT (5)",               U32, 0x05, 0x95, 0x05);
    BEGIN_ITEM_WBITS(input,         "INPUT (Cnst,Ary,Abs)",         0x81, 0x01);
        ITEM_BIT(constant, /* not */ data);
        ITEM_BIT(array, /* not */ variable);
        ITEM_BIT(absolute, /* not */ relative);
        ITEM_BIT(no_wrap, /* not */ wrap);
        ITEM_BIT(linear, /* not */ non_linear);
        ITEM_BIT(preferred_state, /* not */ no_preferred);
        ITEM_BIT(no_null_position, /* not */ null_state);
        ITEM_BIT(bit_field, /* not */ buffered_bytes);
    END_ITEM_WBITS;
    ITEM_WVALUE(usage_page,       "USAGE_PAGE (Generic Desktop)",   U16, 0x01, 0x05, 0x01);
    ITEM_WVALUE(usage,            "USAGE (X)",                      U32, 0x30, 0x09, 0x30);
    ITEM_WVALUE(usage,            "USAGE (Y)",                      U32, 0x31, 0x09, 0x31);
    ITEM_WVALUE(logical_minimum,  "LOGICAL_MINIMUM (0)",            S32, 0x00, 0x15, 0x00);
    ITEM_WVALUE(logical_maximum,  "LOGICAL_MAXIMUM (32767)",        S32, 32767, 0x26, 0xff, 0x7f);
    ITEM_WVALUE(physical_minimum, "PHYSICAL_MINIMUM (0)",           S32, 0x00, 0x35, 0x00);
    ITEM_WVALUE(physical_maximum, "PHYSICAL_MAXIMUM (32767)",       S32, 32767, 0x46, 0xff, 0x7f);
    ITEM_WVALUE(report_count,     "REPORT_COUNT (2)",               U32, 0x02, 0x95, 0x02);
    ITEM_WVALUE(report_size,      "REPORT_SIZE (16)",               U32, 0x10, 0x75, 0x10);
    BEGIN_ITEM_WBITS(input,         "INPUT (Data,Var,Abs)",         0x81, 0x02);
        ITEM_BIT(data, /* not */ constant);
        ITEM_BIT(variable, /* not */ array);
        ITEM_BIT(absolute, /* not */ relative);
        ITEM_BIT(no_wrap, /* not */ wrap);
        ITEM_BIT(linear, /* not */ non_linear);
        ITEM_BIT(preferred_state, /* not */ no_preferred);
        ITEM_BIT(no_null_position, /* not */ null_state);
        ITEM_BIT(bit_field, /* not */ buffered_bytes);
    END_ITEM_WBITS;
    ITEM_WVALUE(usage_page,         "USAGE_PAGE (Digitizers)",      U16, 0x0d, 0x05, 0x0d);
    ITEM_WVALUE(usage,              "USAGE (Tip Pressure)",         U32, 0x30, 0x09, 0x30);
    ITEM_WVALUE(logical_maximum,  "LOGICAL_MAXIMUM (1023)",         S32, 1023, 0x26, 0xff, 0x03);
    ITEM_WVALUE(report_count,     "REPORT_COUNT (1)",               U32, 0x01, 0x95, 0x01);
    ITEM_WVALUE(report_size,      "REPORT_SIZE (16)",               U32, 0x10, 0x75, 0x10);
    BEGIN_ITEM_WBITS(input,       "INPUT (Data,Var,Abs)",           0x81, 0x02);
        ITEM_BIT(data, /* not */ constant);
        ITEM_BIT(variable, /* not */ array);
        ITEM_BIT(absolute, /* not */ relative);
        ITEM_BIT(no_wrap, /* not */ wrap);
        ITEM_BIT(linear, /* not */ non_linear);
        ITEM_BIT(preferred_state, /* not */ no_preferred);
        ITEM_BIT(no_null_position, /* not */ null_state);
        ITEM_BIT(bit_field, /* not */ buffered_bytes);
    END_ITEM_WBITS;
    ITEM_EMPTY(end_collection,    "END_COLLECTION",                 0xc0);
    ITEM_EMPTY(end_collection,  "END_COLLECTION",                   0xc0);

    return 0;
}



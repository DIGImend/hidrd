/** @file
 * @brief HID report descriptor - utilities - numbers test
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

#include <assert.h>
#include <error.h>
#include <stdlib.h>
#include <string.h>
#include "hidrd/util/num.h"

#define FMT_u32 "%u"
#define FMT_s32 "%d"
#define FMT_u16 "%hu"
#define FMT_s16 "%hd"
#define FMT_u8  "%hhu"
#define FMT_s8  "%hhd"

#define ERROR(_fmt, _args...) \
    error_at_line(1, 0, __FILE__, __LINE__, _fmt, ##_args)

#define PASS_FROM_STR(_t, _v, _s, _m, _b) \
    do {                                                        \
        HIDRD_NUM_##_t##_TYPE   num;                            \
                                                                \
        if (!HIDRD_NUM_FROM_STR(_t, &num, _s, _m, _b))          \
            ERROR("Failed parsing string \"%s\" "               \
                  "unexpectedly", _s);                          \
        if (num != _v)                                          \
            ERROR("Unexpected parsing result: "                 \
                  FMT_##_t " instead of " FMT_##_t, num, _v);   \
    } while (0)


#define PASS_TO_STR(_t, _v, _s, _m, _b) \
    do {                                                        \
        char                   *str;                            \
                                                                \
        str = HIDRD_NUM_TO_STR(_t, _v, _m, _b);                 \
        if (strcmp(str, _s) != 0)                               \
            ERROR("Unexpected printing result: "                \
                  "%s instead of %s", str, _s);                 \
        free(str);                                              \
    } while (0)


#define PASS_BOTH(_t, _v, _s, _m, _b) \
    do {                                    \
        PASS_FROM_STR(_t, _v, _s, _m, _b);  \
        PASS_TO_STR(_t, _v, _s, _m, _b);    \
    } while (0)


#define FAIL_FROM_STR(_t, _s, _m, _b) \
    do {                                                        \
        HIDRD_NUM_##_t##_TYPE   num;                            \
                                                                \
        if (HIDRD_NUM_FROM_STR(_t, &num, _s, _m, _b))           \
            ERROR("Unexpected success parsing string \"%s\", "  \
                  "result: " FMT_##_t, _s, num);                \
    } while (0);

#define TEST_TYPE(_t) \
    typedef HIDRD_NUM_##_t##_TYPE hidrd_test_##_t;  \
                                                    \
    bool                                            \
    hidrd_test_##_t##_valid(hidrd_test_##_t _t)     \
    {                                               \
        (void)_t;                                   \
        return true;                                \
    }                                               \
                                                    \
    const char *                                    \
    hidrd_test_##_t##_to_null(hidrd_test_##_t _t)   \
    {                                               \
        (void)_t;                                   \
        return NULL;                                \
    }                                               \
                                                    \
    HIDRD_NUM_CONV_DEFS(test_##_t, _t)

TEST_TYPE(s8);
TEST_TYPE(u8);
TEST_TYPE(s16);
TEST_TYPE(u16);
TEST_TYPE(s32);
TEST_TYPE(u32);

#define PASS_TO_ALT_STR1_1(_res, _t, _n, _c, _d) \
    do {                                                        \
        char   *str;                                            \
                                                                \
        str = HIDRD_NUM_TO_ALT_STR1_1(_t, _n, _c, _d);          \
        if (str == NULL)                                        \
            ERROR("Formatting result is NULL unexpectedly");    \
        if (strcmp(str, _res) != 0)                             \
            ERROR("Unexpected formatting result: "              \
                  "%s instead of %s", str, _res);               \
        free(str);                                              \
    } while (0)

int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    PASS_BOTH(u32,  UINT32_MAX, "4294967295",   NONE,   DEC);
    PASS_BOTH(u32,  UINT16_MAX, "65535",        NONE,   DEC);
    PASS_BOTH(u32,  UINT8_MAX,  "255",          NONE,   DEC);
    PASS_BOTH(u32,  0,          "0",            NONE,   DEC);
    PASS_BOTH(u16,  UINT16_MAX, "65535",        NONE,   DEC);
    PASS_BOTH(u16,  UINT8_MAX,  "255",          NONE,   DEC);
    PASS_BOTH(u16,  0,          "0",            NONE,   DEC);
    PASS_BOTH(u8,   UINT8_MAX,  "255",          NONE,   DEC);
    PASS_BOTH(u8,   0,          "0",            NONE,   DEC);

    PASS_BOTH(u32,  UINT32_MAX, "4294967295",   PFX,    DEC);
    PASS_BOTH(u32,  UINT16_MAX, "65535",        PFX,    DEC);
    PASS_BOTH(u32,  UINT8_MAX,  "255",          PFX,    DEC);
    PASS_BOTH(u32,  0,          "0",            PFX,    DEC);
    PASS_BOTH(u16,  UINT16_MAX, "65535",        PFX,    DEC);
    PASS_BOTH(u16,  UINT8_MAX,  "255",          PFX,    DEC);
    PASS_BOTH(u16,  0,          "0",            PFX,    DEC);
    PASS_BOTH(u8,   UINT8_MAX,  "255",          PFX,    DEC);
    PASS_BOTH(u8,   0,          "0",            PFX,    DEC);

    PASS_BOTH(u32,  UINT32_MAX, "4294967295",   SFX,    DEC);
    PASS_BOTH(u32,  UINT16_MAX, "65535",        SFX,    DEC);
    PASS_BOTH(u32,  UINT8_MAX,  "255",          SFX,    DEC);
    PASS_BOTH(u32,  0,          "0",            SFX,    DEC);
    PASS_BOTH(u16,  UINT16_MAX, "65535",        SFX,    DEC);
    PASS_BOTH(u16,  UINT8_MAX,  "255",          SFX,    DEC);
    PASS_BOTH(u16,  0,          "0",            SFX,    DEC);
    PASS_BOTH(u8,   UINT8_MAX,  "255",          SFX,    DEC);
    PASS_BOTH(u8,   0,          "0",            SFX,    DEC);

    PASS_BOTH(u32,  UINT32_MAX, "FFFFFFFF",     NONE,   HEX);
    PASS_BOTH(u32,  UINT16_MAX, "FFFF",         NONE,   HEX);
    PASS_BOTH(u32,  UINT8_MAX,  "FF",           NONE,   HEX);
    PASS_BOTH(u32,  0,          "0",            NONE,   HEX);
    PASS_BOTH(u16,  UINT16_MAX, "FFFF",         NONE,   HEX);
    PASS_BOTH(u16,  UINT8_MAX,  "FF",           NONE,   HEX);
    PASS_BOTH(u16,  0,          "0",            NONE,   HEX);
    PASS_BOTH(u8,   UINT8_MAX,  "FF",           NONE,   HEX);
    PASS_BOTH(u8,   0,          "0",            NONE,   HEX);

    PASS_BOTH(u32,  UINT32_MAX, "0xFFFFFFFF",   PFX,    HEX);
    PASS_BOTH(u32,  UINT16_MAX, "0xFFFF",       PFX,    HEX);
    PASS_BOTH(u32,  UINT8_MAX,  "0xFF",         PFX,    HEX);
    PASS_BOTH(u32,  0,          "0x00",         PFX,    HEX);
    PASS_BOTH(u16,  UINT16_MAX, "0xFFFF",       PFX,    HEX);
    PASS_BOTH(u16,  UINT8_MAX,  "0xFF",         PFX,    HEX);
    PASS_BOTH(u16,  0,          "0x00",         PFX,    HEX);
    PASS_BOTH(u8,   UINT8_MAX,  "0xFF",         PFX,    HEX);
    PASS_BOTH(u8,   0,          "0x00",         PFX,    HEX);

    PASS_BOTH(u32,  UINT32_MAX, "FFFFFFFFh",    SFX,    HEX);
    PASS_BOTH(u32,  UINT16_MAX, "FFFFh",        SFX,    HEX);
    PASS_BOTH(u32,  UINT8_MAX,  "FFh",          SFX,    HEX);
    PASS_BOTH(u32,  0,          "00h",          SFX,    HEX);
    PASS_BOTH(u16,  UINT16_MAX, "FFFFh",        SFX,    HEX);
    PASS_BOTH(u16,  UINT8_MAX,  "FFh",          SFX,    HEX);
    PASS_BOTH(u16,  0,          "00h",          SFX,    HEX);
    PASS_BOTH(u8,   UINT8_MAX,  "FFh",          SFX,    HEX);
    PASS_BOTH(u8,   0,          "00h",          SFX,    HEX);

    PASS_BOTH(s32,  INT32_MIN,  "-2147483648",  NONE,   DEC);
    PASS_BOTH(s32,  INT16_MIN,  "-32768",       NONE,   DEC);
    PASS_BOTH(s32,  INT8_MIN,   "-128",         NONE,   DEC);
    PASS_BOTH(s32,  0,          "0",            NONE,   DEC);
    PASS_BOTH(s32,  INT8_MAX,   "127",          NONE,   DEC);
    PASS_BOTH(s32,  INT16_MAX,  "32767",        NONE,   DEC);
    PASS_BOTH(s32,  INT32_MAX,  "2147483647",   NONE,   DEC);
    PASS_BOTH(s16,  INT16_MIN,  "-32768",       NONE,   DEC);
    PASS_BOTH(s16,  INT8_MIN,   "-128",         NONE,   DEC);
    PASS_BOTH(s16,  0,          "0",            NONE,   DEC);
    PASS_BOTH(s16,  INT8_MAX,   "127",          NONE,   DEC);
    PASS_BOTH(s16,  INT16_MAX,  "32767",        NONE,   DEC);
    PASS_BOTH(s8,   INT8_MIN,   "-128",         NONE,   DEC);
    PASS_BOTH(s8,   0,          "0",            NONE,   DEC);
    PASS_BOTH(s8,   INT8_MAX,   "127",          NONE,   DEC);

    PASS_BOTH(s32,  INT32_MIN,  "-2147483648",  PFX,    DEC);
    PASS_BOTH(s32,  INT16_MIN,  "-32768",       PFX,    DEC);
    PASS_BOTH(s32,  INT8_MIN,   "-128",         PFX,    DEC);
    PASS_BOTH(s32,  0,          "0",            PFX,    DEC);
    PASS_BOTH(s32,  INT8_MAX,   "127",          PFX,    DEC);
    PASS_BOTH(s32,  INT16_MAX,  "32767",        PFX,    DEC);
    PASS_BOTH(s32,  INT32_MAX,  "2147483647",   PFX,    DEC);
    PASS_BOTH(s16,  INT16_MIN,  "-32768",       PFX,    DEC);
    PASS_BOTH(s16,  INT8_MIN,   "-128",         PFX,    DEC);
    PASS_BOTH(s16,  0,          "0",            PFX,    DEC);
    PASS_BOTH(s16,  INT8_MAX,   "127",          PFX,    DEC);
    PASS_BOTH(s16,  INT16_MAX,  "32767",        PFX,    DEC);
    PASS_BOTH(s8,   INT8_MIN,   "-128",         PFX,    DEC);
    PASS_BOTH(s8,   0,          "0",            PFX,    DEC);
    PASS_BOTH(s8,   INT8_MAX,   "127",          PFX,    DEC);

    PASS_BOTH(s32,  INT32_MIN,  "-2147483648",  SFX,    DEC);
    PASS_BOTH(s32,  INT16_MIN,  "-32768",       SFX,    DEC);
    PASS_BOTH(s32,  INT8_MIN,   "-128",         SFX,    DEC);
    PASS_BOTH(s32,  0,          "0",            SFX,    DEC);
    PASS_BOTH(s32,  INT8_MAX,   "127",          SFX,    DEC);
    PASS_BOTH(s32,  INT16_MAX,  "32767",        SFX,    DEC);
    PASS_BOTH(s32,  INT32_MAX,  "2147483647",   SFX,    DEC);
    PASS_BOTH(s16,  INT16_MIN,  "-32768",       SFX,    DEC);
    PASS_BOTH(s16,  INT8_MIN,   "-128",         SFX,    DEC);
    PASS_BOTH(s16,  0,          "0",            SFX,    DEC);
    PASS_BOTH(s16,  INT8_MAX,   "127",          SFX,    DEC);
    PASS_BOTH(s16,  INT16_MAX,  "32767",        SFX,    DEC);
    PASS_BOTH(s8,   INT8_MIN,   "-128",         SFX,    DEC);
    PASS_BOTH(s8,   0,          "0",            SFX,    DEC);
    PASS_BOTH(s8,   INT8_MAX,   "127",          SFX,    DEC);

    PASS_BOTH(s32,  INT32_MIN,  "-80000000",    NONE,   HEX);
    PASS_BOTH(s32,  INT16_MIN,  "-8000",        NONE,   HEX);
    PASS_BOTH(s32,  INT8_MIN,   "-80",          NONE,   HEX);
    PASS_BOTH(s32,  0,          "0",            NONE,   HEX);
    PASS_BOTH(s32,  INT8_MAX,   "7F",           NONE,   HEX);
    PASS_BOTH(s32,  INT16_MAX,  "7FFF",         NONE,   HEX);
    PASS_BOTH(s32,  INT32_MAX,  "7FFFFFFF",     NONE,   HEX);
    PASS_BOTH(s16,  INT16_MIN,  "-8000",        NONE,   HEX);
    PASS_BOTH(s16,  INT8_MIN,   "-80",          NONE,   HEX);
    PASS_BOTH(s16,  0,          "0",            NONE,   HEX);
    PASS_BOTH(s16,  INT8_MAX,   "7F",           NONE,   HEX);
    PASS_BOTH(s16,  INT16_MAX,  "7FFF",         NONE,   HEX);
    PASS_BOTH(s8,   INT8_MIN,   "-80",          NONE,   HEX);
    PASS_BOTH(s8,   0,          "0",            NONE,   HEX);
    PASS_BOTH(s8,   INT8_MAX,   "7F",           NONE,   HEX);

    PASS_BOTH(s32,  INT32_MIN,  "-0x80000000",  PFX,    HEX);
    PASS_BOTH(s32,  INT16_MIN,  "-0x8000",      PFX,    HEX);
    PASS_BOTH(s32,  INT8_MIN,   "-0x80",        PFX,    HEX);
    PASS_BOTH(s32,  0,          "0x00",         PFX,    HEX);
    PASS_BOTH(s32,  INT8_MAX,   "0x7F",         PFX,    HEX);
    PASS_BOTH(s32,  INT16_MAX,  "0x7FFF",       PFX,    HEX);
    PASS_BOTH(s32,  INT32_MAX,  "0x7FFFFFFF",   PFX,    HEX);
    PASS_BOTH(s16,  INT16_MIN,  "-0x8000",      PFX,    HEX);
    PASS_BOTH(s16,  INT8_MIN,   "-0x80",        PFX,    HEX);
    PASS_BOTH(s16,  0,          "0x00",         PFX,    HEX);
    PASS_BOTH(s16,  INT8_MAX,   "0x7F",         PFX,    HEX);
    PASS_BOTH(s16,  INT16_MAX,  "0x7FFF",       PFX,    HEX);
    PASS_BOTH(s8,   INT8_MIN,   "-0x80",        PFX,    HEX);
    PASS_BOTH(s8,   0,          "0x00",         PFX,    HEX);
    PASS_BOTH(s8,   INT8_MAX,   "0x7F",         PFX,    HEX);

    PASS_BOTH(s32,  INT32_MIN,  "-80000000h",   SFX,    HEX);
    PASS_BOTH(s32,  INT16_MIN,  "-8000h",       SFX,    HEX);
    PASS_BOTH(s32,  INT8_MIN,   "-80h",         SFX,    HEX);
    PASS_BOTH(s32,  0,          "00h",          SFX,    HEX);
    PASS_BOTH(s32,  INT8_MAX,   "7Fh",          SFX,    HEX);
    PASS_BOTH(s32,  INT16_MAX,  "7FFFh",        SFX,    HEX);
    PASS_BOTH(s32,  INT32_MAX,  "7FFFFFFFh",    SFX,    HEX);
    PASS_BOTH(s16,  INT16_MIN,  "-8000h",       SFX,    HEX);
    PASS_BOTH(s16,  INT8_MIN,   "-80h",         SFX,    HEX);
    PASS_BOTH(s16,  0,          "00h",          SFX,    HEX);
    PASS_BOTH(s16,  INT8_MAX,   "7Fh",          SFX,    HEX);
    PASS_BOTH(s16,  INT16_MAX,  "7FFFh",        SFX,    HEX);
    PASS_BOTH(s8,   INT8_MIN,   "-80h",         SFX,    HEX);
    PASS_BOTH(s8,   0,          "00h",          SFX,    HEX);
    PASS_BOTH(s8,   INT8_MAX,   "7Fh",          SFX,    HEX);

    FAIL_FROM_STR(u32,  "-1",           NONE,   DEC);
    FAIL_FROM_STR(u32,  "4294967296",   NONE,   DEC);
    FAIL_FROM_STR(u16,  "-1",           NONE,   DEC);
    FAIL_FROM_STR(u16,  "65536",        NONE,   DEC);
    FAIL_FROM_STR(u8,   "-1",           NONE,   DEC);
    FAIL_FROM_STR(u8,   "256",          NONE,   DEC);

    FAIL_FROM_STR(s32,  "-2147483649",  NONE,   DEC);
    FAIL_FROM_STR(s32,  "2147483648",   NONE,   DEC);
    FAIL_FROM_STR(s16,  "-32769",       NONE,   DEC);
    FAIL_FROM_STR(s16,  "32768",        NONE,   DEC);
    FAIL_FROM_STR(s8,   "-129",         NONE,   DEC);
    FAIL_FROM_STR(s8,   "128",          NONE,   DEC);

    PASS_FROM_STR(u32,  10, " 10 ",     NONE,   DEC);

    FAIL_FROM_STR(u32,  "a1",           NONE,   DEC);
    FAIL_FROM_STR(u32,  "1a",           NONE,   DEC);

    FAIL_FROM_STR(u32,  "a 1",          NONE,   DEC);
    FAIL_FROM_STR(u32,  "1 a",          NONE,   DEC);

    FAIL_FROM_STR(u32,  "",             NONE,   DEC);
    FAIL_FROM_STR(u32,  " ",            NONE,   DEC);

    PASS_FROM_STR(u32,  0xA,    "ah",   SFX,    HEX);
    FAIL_FROM_STR(u32,  "a h",          SFX,    HEX);
    FAIL_FROM_STR(u32,  "0x a",         PFX,    HEX);
    PASS_FROM_STR(u32,  0xA,    "0xa",  PFX,    HEX);

    PASS_TO_ALT_STR1_1("0",          test_u8,    0,          null, dec);
    PASS_TO_ALT_STR1_1("255",        test_u8,    UINT8_MAX,  null, dec);
    PASS_TO_ALT_STR1_1("0",          test_u16,   0,          null, dec);
    PASS_TO_ALT_STR1_1("65535",      test_u16,   UINT16_MAX, null, dec);
    PASS_TO_ALT_STR1_1("0",          test_u32,   0,          null, dec);
    PASS_TO_ALT_STR1_1("4294967295", test_u32,   UINT32_MAX, null, dec);

    PASS_TO_ALT_STR1_1("-128",           test_s8,    INT8_MIN,   null, dec);
    PASS_TO_ALT_STR1_1("127",            test_s8,    INT8_MAX,   null, dec);
    PASS_TO_ALT_STR1_1("-32768",         test_s32,   INT16_MIN,  null, dec);
    PASS_TO_ALT_STR1_1("32767",          test_s32,   INT16_MAX,  null, dec);
    PASS_TO_ALT_STR1_1("-2147483648",    test_s32,   INT32_MIN,  null, dec);
    PASS_TO_ALT_STR1_1("2147483647",     test_s32,   INT32_MAX,  null, dec);

    return 0;
}

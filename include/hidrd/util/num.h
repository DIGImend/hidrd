/** @file
 * @brief HID report descriptor - utilities - number conversions
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

#ifndef __HIDRD_UTIL_NUM_H__
#define __HIDRD_UTIL_NUM_H__

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** The type behind convenience type name "u32" (used in macros) */
#define HIDRD_NUM_u32_TYPE  uint32_t
/** The type behind convenience type name "s32" (used in macros) */
#define HIDRD_NUM_s32_TYPE  int32_t
/** The type behind convenience type name "u16" (used in macros) */
#define HIDRD_NUM_u16_TYPE  uint16_t
/** The type behind convenience type name "s16" (used in macros) */
#define HIDRD_NUM_s16_TYPE  int16_t
/** The type behind convenience type name "u8" (used in macros) */
#define HIDRD_NUM_u8_TYPE   uint8_t
/** The type behind convenience type name "s8" (used in macros) */
#define HIDRD_NUM_s8_TYPE   int8_t

/** Number base */
typedef enum hidrd_num_base {
    HIDRD_NUM_BASE_NONE = 0,    /**< None, not specified */
    HIDRD_NUM_BASE_DEC  = 10,   /**< Decimal */
    HIDRD_NUM_BASE_HEX  = 16    /**< Hexadecimal */
} hidrd_num_base;

/** A lowercase version of HIDRD_NUM_BASE_DEC - for macro convenience */
#define HIDRD_NUM_BASE_dec  HIDRD_NUM_BASE_DEC
/** A lowercase version of HIDRD_NUM_BASE_HEX - for macro convenience */
#define HIDRD_NUM_BASE_hex  HIDRD_NUM_BASE_HEX

/**
 * Check if a number base is valid.
 *
 * @param base  Base to check.
 *
 * @return True if the base is valid, false otherwise.
 */
extern bool hidrd_num_base_valid(hidrd_num_base base);

/** Number base mark type */
typedef enum hidrd_num_bmrk {
    HIDRD_NUM_BMRK_NONE = 0,    /**< No base mark, explicit base required */
    HIDRD_NUM_BMRK_SFX,         /**< Suffix (h, b, etc) */
    HIDRD_NUM_BMRK_PFX,         /**< Prefix (0x, 0, etc) */
} hidrd_num_bmrk;

/**
 * Check if a number base mark type is valid.
 *
 * @param bmrk  Base mark type to check.
 *
 * @return True if the base mark type is valid, false otherwise.
 */
extern bool hidrd_num_bmrk_valid(hidrd_num_bmrk bmrk);

/**
 * Convert a string to an unsigned 32-bit integer.
 *
 * @param pnum  Location for the converted number; could be NULL.
 * @param str   String to convert from.
 * @param bmrk  Number base mark type; if HIDRD_NUM_BMRK_NONE, @e base must
 *              be specified (not HIDRD_NUM_BASE_NONE).
 * @param base  Number base to convert from; only applicable if @e bmrk is
 *              HIDRD_NUM_BMRK_NONE.
 *
 * @return True if the string was valid and converted successfully, false
 *         otherwise.
 */
extern bool hidrd_num_u32_from_str(uint32_t        *pnum,
                                   const char      *str,
                                   hidrd_num_bmrk   bmrk,
                                   hidrd_num_base   base);

/**
 * Convert a string to a signed 32-bit integer.
 *
 * @param pnum  Location for the converted number; could be NULL.
 * @param str   String to convert from.
 * @param bmrk  Number base mark type; if HIDRD_NUM_BMRK_NONE, @e base must
 *              be specified (not HIDRD_NUM_BASE_NONE).
 * @param base  Number base to convert from; only applicable if @e bmrk is
 *              HIDRD_NUM_BMRK_NONE.
 *
 * @return True if the string was valid and converted successfully, false
 *         otherwise.
 */
extern bool hidrd_num_s32_from_str(int32_t         *pnum,
                                   const char      *str,
                                   hidrd_num_bmrk   bmrk,
                                   hidrd_num_base   base);

/**
 * Convert a string to an unsigned 16-bit integer.
 *
 * @param pnum  Location for the converted number; could be NULL.
 * @param str   String to convert from.
 * @param bmrk  Number base mark type; if HIDRD_NUM_BMRK_NONE, @e base must
 *              be specified (not HIDRD_NUM_BASE_NONE).
 * @param base  Number base to convert from; only applicable if @e bmrk is
 *              HIDRD_NUM_BMRK_NONE.
 *
 * @return True if the string was valid and converted successfully, false
 *         otherwise.
 */
extern bool hidrd_num_u16_from_str(uint16_t        *pnum,
                                   const char      *str,
                                   hidrd_num_bmrk   bmrk,
                                   hidrd_num_base   base);

/**
 * Convert a string to a signed 16-bit integer.
 *
 * @param pnum  Location for the converted number; could be NULL.
 * @param str   String to convert from.
 * @param bmrk  Number base mark type; if HIDRD_NUM_BMRK_NONE, @e base must
 *              be specified (not HIDRD_NUM_BASE_NONE).
 * @param base  Number base to convert from; only applicable if @e bmrk is
 *              HIDRD_NUM_BMRK_NONE.
 *
 * @return True if the string was valid and converted successfully, false
 *         otherwise.
 */
extern bool hidrd_num_s16_from_str(int16_t         *pnum,
                                   const char      *str,
                                   hidrd_num_bmrk   bmrk,
                                   hidrd_num_base   base);

/**
 * Convert a string to an unsigned 8-bit integer.
 *
 * @param pnum  Location for the converted number; could be NULL.
 * @param str   String to convert from.
 * @param bmrk  Number base mark type; if HIDRD_NUM_BMRK_NONE, @e base must
 *              be specified (not HIDRD_NUM_BASE_NONE).
 * @param base  Number base to convert from; only applicable if @e bmrk is
 *              HIDRD_NUM_BMRK_NONE.
 *
 * @return True if the string was valid and converted successfully, false
 *         otherwise.
 */
extern bool hidrd_num_u8_from_str(uint8_t          *pnum,
                                  const char       *str,
                                  hidrd_num_bmrk    bmrk,
                                  hidrd_num_base    base);

/**
 * Convert a string to a signed 8-bit integer.
 *
 * @param pnum  Location for the converted number; could be NULL.
 * @param str   String to convert from.
 * @param bmrk  Number base mark type; if HIDRD_NUM_BMRK_NONE, @e base must
 *              be specified (not HIDRD_NUM_BASE_NONE).
 * @param base  Number base to convert from; only applicable if @e bmrk is
 *              HIDRD_NUM_BMRK_NONE.
 *
 * @return True if the string was valid and converted successfully, false
 *         otherwise.
 */
extern bool hidrd_num_s8_from_str(int8_t           *pnum,
                                  const char       *str,
                                  hidrd_num_bmrk    bmrk,
                                  hidrd_num_base    base);

/**
 * Convert an unsigned 32-bit integer to a string.
 *
 * @param num   The number to convert.
 * @param bmrk  Number base mark type.
 * @param base  Number base to convert to, must be specified (not
 *              HIDRD_NUM_BASE_NONE).
 *
 * @return Dynamically allocated string, or NULL if failed to allocate
 *         memory.
 */
extern char *hidrd_num_u32_to_str(uint32_t          num,
                                  hidrd_num_bmrk    bmrk,
                                  hidrd_num_base    base);

/**
 * Convert a signed 32-bit integer to a string.
 *
 * @param num   The number to convert.
 * @param bmrk  Number base mark type.
 * @param base  Number base to convert to, must be specified (not
 *              HIDRD_NUM_BASE_NONE).
 *
 * @return Dynamically allocated string, or NULL if failed to allocate
 *         memory.
 */
extern char *hidrd_num_s32_to_str(int32_t           num,
                                  hidrd_num_bmrk    bmrk,
                                  hidrd_num_base    base);

/**
 * Convert an unsigned 16-bit integer to a string.
 *
 * @param num   The number to convert.
 * @param bmrk  Number base mark type.
 * @param base  Number base to convert to, must be specified (not
 *              HIDRD_NUM_BASE_NONE).
 *
 * @return Dynamically allocated string, or NULL if failed to allocate
 *         memory.
 */
static inline char *
hidrd_num_u16_to_str(uint16_t num, hidrd_num_bmrk bmrk, hidrd_num_base base)
{
    return hidrd_num_u32_to_str(num, bmrk, base);
}

/**
 * Convert a signed 16-bit integer to a string.
 *
 * @param num   The number to convert.
 * @param bmrk  Number base mark type.
 * @param base  Number base to convert to, must be specified (not
 *              HIDRD_NUM_BASE_NONE).
 *
 * @return Dynamically allocated string, or NULL if failed to allocate
 *         memory.
 */
static inline char *
hidrd_num_s16_to_str(int16_t num, hidrd_num_bmrk bmrk, hidrd_num_base base)
{
    return hidrd_num_s32_to_str(num, bmrk, base);
}

/**
 * Convert an unsigned 8-bit integer to a string.
 *
 * @param num   The number to convert.
 * @param bmrk  Number base mark type.
 * @param base  Number base to convert to, must be specified (not
 *              HIDRD_NUM_BASE_NONE).
 *
 * @return Dynamically allocated string, or NULL if failed to allocate
 *         memory.
 */
static inline char *
hidrd_num_u8_to_str(uint8_t num, hidrd_num_bmrk bmrk, hidrd_num_base base)
{
    return hidrd_num_u32_to_str(num, bmrk, base);
}

/**
 * Convert a signed 8-bit integer to a string.
 *
 * @param num   The number to convert.
 * @param bmrk  Number base mark type.
 * @param base  Number base to convert to, must be specified (not
 *              HIDRD_NUM_BASE_NONE).
 *
 * @return Dynamically allocated string, or NULL if failed to allocate
 *         memory.
 */
static inline char *
hidrd_num_s8_to_str(int8_t num, hidrd_num_bmrk bmrk, hidrd_num_base base)
{
    return hidrd_num_s32_to_str(num, bmrk, base);
}


/**
 * Convert a specified integer number type to a string.
 *
 * @param _t    Short integer number type name (u32/s32/u16/s16/u8/s8).
 * @param _n    Number.
 * @param _m    Short base mark type name (without HIDRD_NUM_BMRK_ prefix).
 * @param _b    Short base name (without HIDRD_NUM_BASE_ prefix); cannot be
 *              NONE.
 *
 * @return Dynamically allocated string, or NULL, if failed to allocate
 *         memory.
 */
#define HIDRD_NUM_TO_STR(_t, _n, _m, _b) \
    hidrd_num_##_t##_to_str(_n, HIDRD_NUM_BMRK_##_m, HIDRD_NUM_BASE_##_b)


/**
 * Convert a string to a specified integer type.
 *
 * @param _t    Short integer number type name (u32/s32/u16/s16/u8/s8).
 * @param _pn   Location for resulting number.
 * @param _s    String to parse.
 * @param _m    Short base mark type name (without HIDRD_NUM_BMRK_ prefix);
 *              if not specified (NONE), @e _b must be specified (not NONE).
 * @param _b    Short base name (without HIDRD_NUM_BASE_ prefix); only
 *              applicable if @e _m is specified (not NONE).
 *
 * @return True if the string was valid and parsed successfully, false
 *         otherwise.
 */
#define HIDRD_NUM_FROM_STR(_t, _pn, _s, _m, _b) \
    hidrd_num_##_t##_from_str(_pn, _s,                                  \
                              HIDRD_NUM_BMRK_##_m, HIDRD_NUM_BASE_##_b)


/**
 * Declare a function set for converting a number type to/from a string.
 *
 * @param _t    Name of the type being converted, without hidrd_ prefix.
 */
#define HIDRD_NUM_CONV_DECLS(_t) \
    extern char *hidrd_##_t##_to_dec(hidrd_##_t v);                     \
    extern char *hidrd_##_t##_to_hex(hidrd_##_t v);                     \
    extern char *hidrd_##_t##_to_phex(hidrd_##_t v);                    \
    extern char *hidrd_##_t##_to_shex(hidrd_##_t v);                    \
    extern bool hidrd_##_t##_from_dec(hidrd_##_t *pv, const char *s);   \
    extern bool hidrd_##_t##_from_hex(hidrd_##_t *pv, const char *s);   \
    extern bool hidrd_##_t##_from_pstr(hidrd_##_t *pv, const char *s);  \
    extern bool hidrd_##_t##_from_sstr(hidrd_##_t *pv, const char *s)


/**
 * Define a function set for converting a number type to/from a string.
 *
 * @param _t    Name of the type being converted, without hidrd_ prefix.
 * @param _n    Short (convenience) name of the number type (like s8).
 */
#define HIDRD_NUM_CONV_DEFS(_t, _n) \
    char *                                                  \
    hidrd_##_t##_to_dec(hidrd_##_t v)                       \
    {                                                       \
        assert(hidrd_##_t##_valid(v));                      \
        return HIDRD_NUM_TO_STR(_n, v, NONE, DEC);          \
    }                                                       \
                                                            \
                                                            \
    char *                                                  \
    hidrd_##_t##_to_hex(hidrd_##_t v)                       \
    {                                                       \
        assert(hidrd_##_t##_valid(v));                      \
        return HIDRD_NUM_TO_STR(_n, v, NONE, HEX);          \
    }                                                       \
                                                            \
                                                            \
    char *                                                  \
    hidrd_##_t##_to_phex(hidrd_##_t v)                      \
    {                                                       \
        assert(hidrd_##_t##_valid(v));                      \
        return HIDRD_NUM_TO_STR(_n, v, PFX, HEX);           \
    }                                                       \
                                                            \
                                                            \
    char *                                                  \
    hidrd_##_t##_to_shex(hidrd_##_t v)                      \
    {                                                       \
        assert(hidrd_##_t##_valid(v));                      \
        return HIDRD_NUM_TO_STR(_n, v, SFX, HEX);           \
    }                                                       \
                                                            \
                                                            \
    bool                                                    \
    hidrd_##_t##_from_dec(hidrd_##_t *pv, const char *s)    \
    {                                                       \
        HIDRD_NUM_##_n##_TYPE   v;                          \
                                                            \
        assert(s != NULL);                                  \
                                                            \
        if (!HIDRD_NUM_FROM_STR(_n, &v, s, NONE, DEC) ||    \
            !hidrd_##_t##_valid(v))                         \
            return false;                                   \
                                                            \
        if (pv != NULL)                                     \
            *pv = v;                                        \
                                                            \
        return true;                                        \
    }                                                       \
                                                            \
                                                            \
    bool                                                    \
    hidrd_##_t##_from_hex(hidrd_##_t *pv, const char *s)    \
    {                                                       \
        HIDRD_NUM_##_n##_TYPE   v;                          \
                                                            \
        assert(s != NULL);                                  \
                                                            \
        if (!HIDRD_NUM_FROM_STR(_n, &v, s, NONE, HEX) ||    \
            !hidrd_##_t##_valid(v))                         \
            return false;                                   \
                                                            \
        if (pv != NULL)                                     \
            *pv = v;                                        \
                                                            \
        return true;                                        \
    }                                                       \
                                                            \
                                                            \
    bool                                                    \
    hidrd_##_t##_from_pstr(hidrd_##_t *pv, const char *s)   \
    {                                                       \
        HIDRD_NUM_##_n##_TYPE   v;                          \
                                                            \
        assert(s != NULL);                                  \
                                                            \
        if (!HIDRD_NUM_FROM_STR(_n, &v, s, PFX, NONE) ||    \
            !hidrd_##_t##_valid(v))                         \
            return false;                                   \
                                                            \
        if (pv != NULL)                                     \
            *pv = v;                                        \
                                                            \
        return true;                                        \
    }                                                       \
                                                            \
                                                            \
    bool                                                    \
    hidrd_##_t##_from_sstr(hidrd_##_t *pv, const char  *s)  \
    {                                                       \
        HIDRD_NUM_##_n##_TYPE   v;                          \
                                                            \
        assert(s != NULL);                                  \
                                                            \
        if (!HIDRD_NUM_FROM_STR(_n, &v, s, SFX, NONE) ||    \
            !hidrd_##_t##_valid(v))                         \
            return false;                                   \
                                                            \
        if (pv != NULL)                                     \
            *pv = v;                                        \
                                                            \
        return true;                                        \
    }

/**
 * Prototype for a function used to parse a number string.
 *
 * This prototype is not meant to be used to define functions, but to
 * describe hidrd_num_from_alt_str function parameters.
 *
 * @param pnum  Location for the output number.
 * @param str   The string to parse.
 *
 * @return True if the string was valid and parsed successfully.
 */
typedef bool hidrd_num_parse_fn(void *pnum, const char *str);

/**
 * Convert a number from alternate string formats.
 *
 * @param pnum  Location for the output number; could be NULL.
 * @param str   The string to parse.
 * @param ...   List of @e hidrd_num_parse_fn functions to try to parse the
 *              string with; terminated with NULL.
 *
 * @return True if at least one function succeeded parsing the string.
 */
extern bool hidrd_num_from_alt_str(void *pnum, const char *str, ...);


/**
 * Convert a number from a string representations.
 *
 * @param _type     Number type name token (used to generate parsing
 *                  function names).
 * @param _pnum     Location for the output number; could be NULL.
 * @param _str      The string to parse.
 * @param _rerp     Representation name token (used to generate parsing
 *                  function name).
 *
 * @return True if the function succeeded parsing the string.
 */
#define HIDRD_NUM_FROM_ALT_STR1(_type, _pnum, _str, _repr) \
    hidrd_num_from_alt_str(_pnum, _str,                     \
                           hidrd_##_type##_from_##_repr,    \
                           NULL)

/**
 * Convert a number from two alternate string representations.
 *
 * @param _type     Number type name token (used to generate parsing
 *                  function names).
 * @param _pnum     Location for the output number; could be NULL.
 * @param _str      The string to parse.
 * @param _rerp1    First representation name token (used to generate
 *                  first parsing function name).
 * @param _rerp2    Second representation name token (used to generate
 *                  second parsing function name).
 *
 * @return True if at least one function succeeded parsing the string.
 */
#define HIDRD_NUM_FROM_ALT_STR2(_type, _pnum, _str, \
                                _repr1, _repr2)             \
    hidrd_num_from_alt_str(_pnum, _str,                     \
                           hidrd_##_type##_from_##_repr1,   \
                           hidrd_##_type##_from_##_repr2,   \
                           NULL)

/**
 * Convert a number from three alternate string representations.
 *
 * @param _type     Number type name token (used to generate parsing
 *                  function names).
 * @param _pnum     Location for the output number; could be NULL.
 * @param _str      The string to parse.
 * @param _rerp1    First representation name token (used to generate
 *                  first parsing function name).
 * @param _rerp2    Second representation name token (used to generate
 *                  second parsing function name).
 * @param _rerp3    Third representation name token (used to generate
 *                  third parsing function name).
 *
 * @return True if at least one function succeeded parsing the string.
 */
#define HIDRD_NUM_FROM_ALT_STR3(_type, _pnum, _str, \
                                _repr1, _repr2, _repr3)     \
    hidrd_num_from_alt_str(_pnum, _str,                     \
                           hidrd_##_type##_from_##_repr1,   \
                           hidrd_##_type##_from_##_repr2,   \
                           hidrd_##_type##_from_##_repr3,   \
                           NULL)

/**
 * Convert a number from four alternate string representations.
 *
 * @param _type     Number type name token (used to generate parsing
 *                  function names).
 * @param _pnum     Location for the output number; could be NULL.
 * @param _str      The string to parse.
 * @param _rerp1    First representation name token (used to generate
 *                  first parsing function name).
 * @param _rerp2    Second representation name token (used to generate
 *                  second parsing function name).
 * @param _rerp3    Third representation name token (used to generate
 *                  third parsing function name).
 * @param _rerp4    Fourth representation name token (used to generate
 *                  fourth parsing function name).
 *
 * @return True if at least one function succeeded parsing the string.
 */
#define HIDRD_NUM_FROM_ALT_STR4(_type, _pnum, _str, \
                                _repr1, _repr2,             \
                                _repr3, _repr4)             \
    hidrd_num_from_alt_str(_pnum, _str,                     \
                           hidrd_##_type##_from_##_repr1,   \
                           hidrd_##_type##_from_##_repr2,   \
                           hidrd_##_type##_from_##_repr3,   \
                           hidrd_##_type##_from_##_repr4,   \
                           NULL)


/**
 * Prototype for a function used to format an 8-bit number string (either
 * signed or unsigned).
 *
 * This prototype is not meant to be used to define functions, but to
 * describe hidrd_num_to_alt_str function parameters.
 *
 * @param num   The number to convert.
 *
 * @return Dynamically allocated string, or NULL if the match is not found
 *         or an error occurred; check errno for the latter.
 */
typedef char *hidrd_num_fmt8_fn(uint8_t num);

/**
 * Prototype for a function used to format an 16-bit number string (either
 * signed or unsigned).
 *
 * This prototype is not meant to be used to define functions, but to
 * describe hidrd_num_to_alt_str function parameters.
 *
 * @param num   The number to convert.
 *
 * @return Dynamically allocated string, or NULL if the match is not found
 *         or an error occurred; check errno for the latter.
 */
typedef char *hidrd_num_fmt16_fn(uint16_t num);

/**
 * Prototype for a function used to format an 32-bit number string (either
 * signed or unsigned).
 *
 * This prototype is not meant to be used to define functions, but to
 * describe hidrd_num_to_alt_str function parameters.
 *
 * @param num   The number to convert.
 *
 * @return Dynamically allocated string, or NULL if the match is not found
 *         or an error occurred; check errno for the latter.
 */
typedef char *hidrd_num_fmt32_fn(uint32_t num);

/**
 * Convert a number to a string of alternate formats.
 *
 * @param bits  Size of the number in bits; only 8, 16 and 32 accepted.
 * @param ...   A succession of arguments:
 *              - the number to convert;
 *              - conversion functions (hidrd_num_fmtX_fn),
 *                terminated by NULL;
 *
 * @return Dynamically allocated string, or NULL if failed to find a match,
 *         or an error occurred; check errno for the latter.
 *
 * @note Always resets errno.
 */
char *hidrd_num_to_alt_str(size_t bits, ...);

/**
 * Convert a number to a string of two alternate formats.
 *
 * @param _t    The number type name token.
 * @param _n    The number to convert.
 * @param _r1   First converter representation token.
 * @param _r2   Second converter representation token.
 *
 * @return Dynamically allocated string, or NULL if failed to find a match
 *         or an error occurred; check errno for the latter.
 */
#define HIDRD_NUM_TO_ALT_STR2(_t, _n, _r1, _r2) \
    hidrd_num_to_alt_str(sizeof(hidrd_##_t) * 8, _n,    \
                         hidrd_##_t##_to_##_r1,         \
                         hidrd_##_t##_to_##_r2,         \
                         NULL)

/**
 * Convert a 32-bit unsigned number to little-endian order.
 *
 * @param ple   Location for the output number in little-endian order.
 * @param num   Input number in host order.
 */
extern void hidrd_num_u32_to_le(uint32_t *ple, uint32_t num);

/**
 * Convert a 32-bit unsigned number from little-endian order.
 *
 * @param ple   Location of the input number in little-endian order.
 *
 * @return Output number in host order.
 */
extern uint32_t hidrd_num_u32_from_le(const uint32_t *ple);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_NUM_H__ */

/** @file
 * @brief HID report descriptor - utilities - unit value
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

#ifndef __HIDRD_UTIL_UNIT_H__
#define __HIDRD_UTIL_UNIT_H__

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include "hidrd/cfg.h"
#if HAVE_CONFIG_H
# include <config.h>
#endif

#ifdef HIDRD_WITH_TOKENS
#include "hidrd/util/tkn.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** Unit system */
typedef enum hidrd_unit_system {
    HIDRD_UNIT_SYSTEM_NONE              = 0x0,
    HIDRD_UNIT_SYSTEM_SI_LINEAR         = 0x1,
    HIDRD_UNIT_SYSTEM_SI_ROTATION       = 0x2,
    HIDRD_UNIT_SYSTEM_ENGLISH_LINEAR    = 0x3,
    HIDRD_UNIT_SYSTEM_ENGLISH_ROTATION  = 0x4,
    HIDRD_UNIT_SYSTEM_VENDOR            = 0xF
} hidrd_unit_system;

#define HIDRD_UNIT_SYSTEM_MIN   HIDRD_UNIT_SYSTEM_NONE
#define HIDRD_UNIT_SYSTEM_MAX   HIDRD_UNIT_SYSTEM_VENDOR

#define HIDRD_UNIT_SYSTEM_KNOWN_MIN HIDRD_UNIT_SYSTEM_SI_LINEAR
#define HIDRD_UNIT_SYSTEM_KNOWN_MAX HIDRD_UNIT_SYSTEM_ENGLISH_ROTATION
#define HIDRD_UNIT_SYSTEM_KNOWN_NUM \
            (HIDRD_UNIT_SYSTEM_KNOWN_MAX - HIDRD_UNIT_SYSTEM_KNOWN_MIN + 1)

#define HIDRD_UNIT_SYSTEM_RESERVED_MIN  0x5
#define HIDRD_UNIT_SYSTEM_RESERVED_MAX  0xE

/**
 * Check if a unit system is valid.
 *
 * @param system    Unit system to check.
 *
 * @return True if the system is valid, false otherwise.
 */
static inline bool
hidrd_unit_system_valid(hidrd_unit_system system)
{
    return system <= HIDRD_UNIT_SYSTEM_MAX;
}


/* Declare unit system to numeric string conversion functions */
HIDRD_NUM_CONV_DECLS(unit_system);


#ifdef HIDRD_WITH_TOKENS
/* Declare unit system <-> token conversion functions */
HIDRD_TKN_CONV_DECLS(unit_system);
#endif /* HIDRD_WITH_TOKENS */

/**
 * Check if a unit system is known.
 *
 * @param system    Unit system to check.
 *
 * @return True if the system is known, false otherwise.
 */
static inline bool
hidrd_unit_system_known(hidrd_unit_system system)
{ return (system >= HIDRD_UNIT_SYSTEM_KNOWN_MIN) &&
           (system <= HIDRD_UNIT_SYSTEM_KNOWN_MAX);
}

/**
 * Check if a unit system is reserved.
 *
 * @param system    Unit system to check.
 *
 * @return True if the system is reserved, false otherwise.
 */
static inline bool
hidrd_unit_system_reserved(hidrd_unit_system system)
{
    return (system >= HIDRD_UNIT_SYSTEM_RESERVED_MIN) &&
           (system <= HIDRD_UNIT_SYSTEM_RESERVED_MAX);
}

/** Unit exponent */
typedef enum hidrd_unit_exp {
    HIDRD_UNIT_EXP_0        = 0x0,
    HIDRD_UNIT_EXP_1        = 0x1,
    HIDRD_UNIT_EXP_2        = 0x2,
    HIDRD_UNIT_EXP_3        = 0x3,
    HIDRD_UNIT_EXP_4        = 0x4,
    HIDRD_UNIT_EXP_5        = 0x5,
    HIDRD_UNIT_EXP_6        = 0x6,
    HIDRD_UNIT_EXP_7        = 0x7,
    HIDRD_UNIT_EXP_MINUS_8  = 0x8,
    HIDRD_UNIT_EXP_MINUS_7  = 0x9,
    HIDRD_UNIT_EXP_MINUS_6  = 0xA,
    HIDRD_UNIT_EXP_MINUS_5  = 0xB,
    HIDRD_UNIT_EXP_MINUS_4  = 0xC,
    HIDRD_UNIT_EXP_MINUS_3  = 0xD,
    HIDRD_UNIT_EXP_MINUS_2  = 0xE,
    HIDRD_UNIT_EXP_MINUS_1  = 0xF,
} hidrd_unit_exp;

#define HIDRD_UNIT_EXP_MIN  HIDRD_UNIT_EXP_0
#define HIDRD_UNIT_EXP_MAX  HIDRD_UNIT_EXP_MINUS_1

/**
 * Check if a unit exponent is valid.
 *
 * @param exp   Unit exponent to check.
 *
 * @return True if the unit exponent is valid, false otherwise.
 */
static inline bool
hidrd_unit_exp_valid(hidrd_unit_exp exp)
{
    return exp <= HIDRD_UNIT_EXP_MAX;
}


/**
 * Validate a unit exponent.
 *
 * @param exp   Unit exponent to validate.
 *
 * @return Validated exponent.
 */
static inline hidrd_unit_exp
hidrd_unit_exp_validate(hidrd_unit_exp exp)
{
    assert(hidrd_unit_exp_valid(exp));
    return exp;
}


/**
 * Convert a unit exponent to (a decimal) string.
 *
 * @param exp   Unit exponent to convert.
 *
 * @return Dynamically allocated (integer) string representing unit
 *         exponent, or NULL, if failed to allocate memory.
 */
extern char *hidrd_unit_exp_to_dec(hidrd_unit_exp exp);

/**
 * Convert (a decimal) string to a unit exponent.
 *
 * @param pexp  Location for the resulting unit exponent.
 * @param str   The string to convert.
 *
 * @return True if converted successfully, false otherwise.
 */
extern bool hidrd_unit_exp_from_dec(hidrd_unit_exp *pexp, const char *str);

#define HIDRD_UNIT_EXP_MIN_INT  -8
#define HIDRD_UNIT_EXP_MAX_INT  7

/**
 * Check if an integer number representation of a unit exponent is valid.
 *
 * @param i Unit exponent integer to check.
 *
 * @return True if the integer is valid, false otherwise.
 */
static inline bool
hidrd_unit_exp_valid_int(int i)
{
    return (i >= HIDRD_UNIT_EXP_MIN_INT) &&
           (i <= HIDRD_UNIT_EXP_MAX_INT);
}


/**
 * Validate an integer number representation of a unit exponent.
 *
 * @param i Unit exponent integer to validate.
 *
 * @return Validated integer.
 */
static inline int
hidrd_unit_exp_validate_int(int i)
{
    assert(hidrd_unit_exp_valid_int(i));
    return i;
}


/**
 * Convert a unit exponent code to an integer number.
 *
 * @param exp   Exponent to convert from.
 *
 * @return Integer number representation of the exponent.
 */
static inline int
hidrd_unit_exp_to_int(hidrd_unit_exp exp)
{
    assert(hidrd_unit_exp_valid(exp));
    return (exp & 0x8) ? ((int)exp - 0x10) : (int)exp;
}


/**
 * Convert an integer number representation of unit exponent to a unit
 * exponent code.
 *
 * @param i Integer number representation to convert from.
 *
 * @return Unit exponent code corresponding to the integer.
 */
static inline hidrd_unit_exp
hidrd_unit_exp_from_int(int i)
{
    assert(hidrd_unit_exp_valid_int(i));
    return (i < 0) ? (i + 0x10) : i;
}

/** Unit nibble (4-bit field) index */
typedef enum hidrd_unit_nibble_index {
    HIDRD_UNIT_NIBBLE_INDEX_SYSTEM              = 0x0,
    HIDRD_UNIT_NIBBLE_INDEX_LENGTH,
    HIDRD_UNIT_NIBBLE_INDEX_MASS,
    HIDRD_UNIT_NIBBLE_INDEX_TIME,
    HIDRD_UNIT_NIBBLE_INDEX_TEMPERATURE,
    HIDRD_UNIT_NIBBLE_INDEX_CURRENT,
    HIDRD_UNIT_NIBBLE_INDEX_LUMINOUS_INTENSITY,
    HIDRD_UNIT_NIBBLE_INDEX_RESERVED,
} hidrd_unit_nibble_index;

/**< Minimum index of an exponent nibble */
#define HIDRD_UNIT_NIBBLE_INDEX_EXP_MIN \
    HIDRD_UNIT_NIBBLE_INDEX_LENGTH
/**< Maximum index of an exponent nibble */
#define HIDRD_UNIT_NIBBLE_INDEX_EXP_MAX \
    HIDRD_UNIT_NIBBLE_INDEX_LUMINOUS_INTENSITY
/**< Number of exponent nibble indexes */
#define HIDRD_UNIT_NIBBLE_INDEX_EXP_NUM \
    (HIDRD_UNIT_NIBBLE_INDEX_EXP_MAX - HIDRD_UNIT_NIBBLE_INDEX_EXP_MIN + 1)

/**
 * Check if a unit nibble index is valid.
 *
 * @param i Nibble index to check.
 *
 * @return True if the index is valid, false otherwise.
 */
static inline bool
hidrd_unit_nibble_index_valid(hidrd_unit_nibble_index i)
{
    return (i <= 7);
}


/** Unit value type */
typedef uint32_t hidrd_unit;

/** The "none" unit - indicates absence of particular units */
#define HIDRD_UNIT_NONE 0

/**
 * Check if a unit is valid (currently a stub - always true).
 *
 * @param unit  Unit to check.
 *
 * @return True if the unit is valid, false otherwise.
 */
static inline bool
hidrd_unit_valid(hidrd_unit unit)
{
    (void)unit;
    return true;
}


/**
 * Retrieve a unit nibble (4-bit field) value, specified by index.
 *
 * @param unit  Unit to retrieve nibble from.
 * @param i     Nibble index to retrieve from.
 *
 * @return The retrieved nibble value.
 */
static inline uint8_t
hidrd_unit_get_nibble(hidrd_unit unit, hidrd_unit_nibble_index i)
{
    assert(hidrd_unit_valid(unit));
    assert(hidrd_unit_nibble_index_valid(i));

    return (unit >> (i * 4)) & 0xF;
}


/**
 * Set a unit nibble (4-bit field) value, specified by index.
 *
 * @param unit  Unit to set nibble to.
 * @param i     Nibble index to set to.
 * @param value Nibble value to set.
 *
 * @return The unit with the nibble set.
 */
static inline hidrd_unit
hidrd_unit_set_nibble(hidrd_unit unit, uint8_t i, uint8_t value)
{
    assert(hidrd_unit_valid(unit));
    assert(hidrd_unit_nibble_index_valid(i));
    assert(value <= 0xF);

    return (unit & ~(hidrd_unit)(0xF << (i * 4))) | (value << (i * 4));
}


#define HIDRD_UNIT_NIBBLE_ACCESSOR_PAIR(_type, _name, _NAME) \
    static inline hidrd_unit_##_type                                    \
    hidrd_unit_get_##_name(hidrd_unit unit)                             \
    {                                                                   \
        assert(hidrd_unit_valid(unit));                                 \
        return hidrd_unit_get_nibble(unit,                              \
                                     HIDRD_UNIT_NIBBLE_INDEX_##_NAME);  \
    }                                                                   \
                                                                        \
    static inline hidrd_unit                                            \
    hidrd_unit_set_##_name(hidrd_unit unit, hidrd_unit_##_type value)   \
    {                                                                   \
        assert(hidrd_unit_valid(unit));                                 \
        assert(hidrd_unit_##_type##_valid(value));                      \
        return hidrd_unit_set_nibble(unit,                              \
                                     HIDRD_UNIT_NIBBLE_INDEX_##_NAME,   \
                                     value);                            \
    }


HIDRD_UNIT_NIBBLE_ACCESSOR_PAIR(system, system, SYSTEM)
HIDRD_UNIT_NIBBLE_ACCESSOR_PAIR(exp, length, LENGTH)
HIDRD_UNIT_NIBBLE_ACCESSOR_PAIR(exp, mass, MASS)
HIDRD_UNIT_NIBBLE_ACCESSOR_PAIR(exp, time, TIME)
HIDRD_UNIT_NIBBLE_ACCESSOR_PAIR(exp, temperature, TEMPERATURE)
HIDRD_UNIT_NIBBLE_ACCESSOR_PAIR(exp, current, CURRENT)
HIDRD_UNIT_NIBBLE_ACCESSOR_PAIR(exp, luminous_intensity, LUMINOUS_INTENSITY)

/**
 * Check if a unit value is known (in effect if it could be interpreted
 * using the functions and constants provided in this module).
 *
 * @param unit  Unit value to check.
 *
 * @return True if the unit value is known, false otherwise.
 */
static inline bool
hidrd_unit_known(hidrd_unit unit)
{
    /* The only problem we have is the reserved nibble */
    return hidrd_unit_get_nibble(unit,
                                 HIDRD_UNIT_NIBBLE_INDEX_RESERVED) == 0;
}

/**
 * Check if a unit value is void.
 *
 * @param unit  Unit value to check.
 *
 * @return True if the unit value is void, false otherwise.
 */
static inline bool
hidrd_unit_void(hidrd_unit unit)
{
    /*
     * If there is no system or all the exponents (including reserved) are
     * zeroes.
     */
    return hidrd_unit_get_system(unit) == HIDRD_UNIT_SYSTEM_NONE ||
           /* May you forgive us for using an obscure constant :) */
           ((unit & 0xFFFFFFF0) == 0);
}

#ifdef HIDRD_WITH_TOKENS

/**
 * Convert a known unit with known system to an expression string.
 *
 * @param unit  Unit to convert.
 * @param cap   Capitalization type for token humanization.
 *
 * @return Dynamically allocated expression string, or NULL if failed to
 *         allocate memory.
 */
extern char *hidrd_unit_to_expr(hidrd_unit unit, hidrd_tkn_hmnz_cap cap);

#endif /* HIDRD_WITH_TOKENS */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_UNIT_H__ */

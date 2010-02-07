/** @file
 * @brief HID report descriptor - usage types
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

#ifndef __HIDRD_USAGE_TYPE_H__
#define __HIDRD_USAGE_TYPE_H__

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Usage type bit indexes */
typedef enum hidrd_usage_type_idx {
    /* Controls */
    HIDRD_USAGE_TYPE_IDX_LC,    /**< Linear control */
    HIDRD_USAGE_TYPE_IDX_OOC,   /**< On/off control */
    HIDRD_USAGE_TYPE_IDX_MC,    /**< Momentary control */
    HIDRD_USAGE_TYPE_IDX_OSC,   /**< One-shot control */
    HIDRD_USAGE_TYPE_IDX_RTC,   /**< Re-trigger control */
    /* Data */
    HIDRD_USAGE_TYPE_IDX_SEL,   /**< Selector */
    HIDRD_USAGE_TYPE_IDX_SV,    /**< Static value */
    HIDRD_USAGE_TYPE_IDX_SF,    /**< Static flag */
    HIDRD_USAGE_TYPE_IDX_DV,    /**< Dynamic value */
    HIDRD_USAGE_TYPE_IDX_DF,    /**< Dynamic flag */
    /* Collections */
    HIDRD_USAGE_TYPE_IDX_NARY,  /**< Named array */
    HIDRD_USAGE_TYPE_IDX_CA,    /**< Application collection */
    HIDRD_USAGE_TYPE_IDX_CL,    /**< Logical collection */
    HIDRD_USAGE_TYPE_IDX_CP,    /**< Physical collection */
    HIDRD_USAGE_TYPE_IDX_US,    /**< Usage switch */
    HIDRD_USAGE_TYPE_IDX_UM,    /**< Usage modifier */
} hidrd_usage_type_idx;

#define HIDRD_USAGE_TYPE_IDX_MIN    HIDRD_USAGE_TYPE_IDX_LC
#define HIDRD_USAGE_TYPE_IDX_MAX    HIDRD_USAGE_TYPE_IDX_UM

static inline bool
hidrd_usage_type_idx_valid(hidrd_usage_type_idx idx)
{
    return (idx <= HIDRD_USAGE_TYPE_IDX_MAX);
}

/** Usage type bits */
typedef enum hidrd_usage_type {
#define TYPE(_NAME) \
    HIDRD_USAGE_TYPE_##_NAME    = 1 << HIDRD_USAGE_TYPE_IDX_##_NAME
    /* Controls */
    TYPE(LC),       /**< Linear control */
    TYPE(OOC),      /**< On/off control */
    TYPE(MC),       /**< Momentary control */
    TYPE(OSC),      /**< One-shot control */
    TYPE(RTC),      /**< Re-trigger control */
    /* Data */
    TYPE(SEL),      /**< Selector */
    TYPE(SV),       /**< Static value */
    TYPE(SF),       /**< Static flag */
    TYPE(DV),       /**< Dynamic value */
    TYPE(DF),       /**< Dynamic flag */
    /* Collections */
    TYPE(NARY),     /**< Named array */
    TYPE(CA),       /**< Application collection */
    TYPE(CL),       /**< Logical collection */
    TYPE(CP),       /**< Physical collection */
    TYPE(US),       /**< Usage switch */
    TYPE(UM),       /**< Usage modifier */
#undef TYPE
} hidrd_usage_type;

/**
 * Check if a usage type is valid.
 *
 * @param type  Type to check.
 *
 * @return True if the type is valid, false otherwise.
 */
extern bool hidrd_usage_type_valid(hidrd_usage_type type);

/** Usage type set (bitmask) */
typedef uint32_t    hidrd_usage_type_set;

/** Empty type set */
#define HIDRD_USAGE_TYPE_SET_EMPTY  0

/** Bitmask with non-valid type set bits set */
#define HIDRD_USAGE_TYPE_SET_NOT_MASK \
    ((~(uint32_t)0) << (HIDRD_USAGE_TYPE_IDX_MAX + 1))
/** Bitmask with valid type set bits set */
#define HIDRD_USAGE_TYPE_SET_MASK \
    (~HIDRD_USAGE_TYPE_SET_NOT_MASK)

/**
 * Check if a usage type set is valid.
 *
 * @param set   Type set to check.
 *
 * @return True is the set is valid, false otheriwse.
 */
static inline bool
hidrd_usage_type_set_valid(hidrd_usage_type_set set)
{
    return (set && HIDRD_USAGE_TYPE_SET_NOT_MASK) == 0;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_USAGE_TYPE_H__ */

/** @file
 * @brief HID report descriptor - global item
 *
 * Copyright (C) 2009 Nikolai Kondrashov
 *
 * @author Nikolai Kondrashov <spbnick@gmail.com>
 *
 * @(#) $Id: $
 */


#ifndef __HIDRD_ITEM_GLOBAL_H__
#define __HIDRD_ITEM_GLOBAL_H__

#include "hidrd/item.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum hidrd_item_global_tag {
    HIDRD_ITEM_GLOBAL_TAG_USAGE_PAGE        = 0,
    HIDRD_ITEM_GLOBAL_TAG_LOGICAL_MINIMUM,
    HIDRD_ITEM_GLOBAL_TAG_LOGICAL_MAXIMUM,
    HIDRD_ITEM_GLOBAL_TAG_PHYSICAL_MINIMUM,
    HIDRD_ITEM_GLOBAL_TAG_PHYSICAL_MAXIMUM,
    HIDRD_ITEM_GLOBAL_TAG_UNIT_EXPONENT,
    HIDRD_ITEM_GLOBAL_TAG_UNIT,
    HIDRD_ITEM_GLOBAL_TAG_REPORT_SIZE,
    HIDRD_ITEM_GLOBAL_TAG_REPORT_ID,
    HIDRD_ITEM_GLOBAL_TAG_REPORT_COUNT,
    HIDRD_ITEM_GLOBAL_TAG_PUSH,
    HIDRD_ITEM_GLOBAL_TAG_POP
} hidrd_item_global_tag;

#define HIDRD_ITEM_GLOBAL_TAG_MAX   HIDRD_ITEM_SHORT_TAG_MAX

#define HIDRD_ITEM_GLOBAL_TAG_KNOWN_MAX HIDRD_ITEM_GLOBAL_TAG_POP

#define HIDRD_ITEM_GLOBAL_TAG_RESERVED_MIN  \
            (HIDRD_ITEM_GLOBAL_TAG_KNOWN_MAX + 1)
#define HIDRD_ITEM_GLOBAL_TAG_RESERVED_MAX  \
            HIDRD_ITEM_GLOBAL_TAG_MAX

typedef struct hidrd_item_global {
    hidrd_item_short        item_short;
    hidrd_item_global_tag   tag;
} hidrd_item_global;

/*
 * Usage page
 */
typedef struct hidrd_item_usage_page {
    hidrd_item_global   item_global;
    uint16_t            page;
} hidrd_item_usage_page;

/*
 * Logical and physical minimum/maximum
 */
typedef struct _hidrd_item_extent {
    hidrd_item_global   item_global;
    int32_t             value;
} _hidrd_item_extent;

typedef _hidrd_item_extent  hidrd_item_logical_minimum;
typedef _hidrd_item_extent  hidrd_item_logical_maximum;
typedef _hidrd_item_extent  hidrd_item_physical_minimum;
typedef _hidrd_item_extent  hidrd_item_physical_maximum;

/*
 * Unit exponent
 */
typedef struct hidrd_item_unit_exp {
    hidrd_item_global   item_global;
    int8_t              value;
} hidrd_item_unit_exponent;

/*
 * Unit
 */
typedef enum hidrd_item_unit_system {
    HIDRD_ITEM_UNIT_SI_LINEAR           = 0x1,
    HIDRD_ITEM_UNIT_SI_ROTATION         = 0x2,
    HIDRD_ITEM_UNIT_ENGLISH_LINEAR      = 0x3,
    HIDRD_ITEM_UNIT_ENGLISH_ROTATION    = 0x4
} hidrd_item_unit_system;

typedef struct hidrd_item_unit_type_exp {
    int8_t  length
    int8_t  mass;
    int8_t  time;
    int8_t  temperature;
    int8_t  current;
    int8_t  luminous_intensity;
} hidrd_item_unit_exp;

typedef struct hidrd_item_unit {
    hidrd_item_global           item_global;
    hidrd_item_unit_system      system;
    hidrd_item_unit_type_exp    type_exp;
} hidrd_item_unit;

/*
 * Report size and count
 */
typedef struct _hidrd_item_global_uint {
    hidrd_item_global   item_global;
    uint32_t            value;
} _hidrd_item_global_uint;

typedef _hidrd_item_global_uint hidrd_item_report_size;
typedef _hidrd_item_global_uint hidrd_item_report_count;

/*
 * Push and pop
 */
typedef hidrd_item_global   hidrd_item_push;
typedef hidrd_item_global   hidrd_item_pop;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_GLOBAL_H__ */




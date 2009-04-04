/** @file
 * @brief HID report descriptor - item
 *
 * Copyright (C) 2009 Nikolai Kondrashov
 *
 * @author Nikolai Kondrashov <spbnick@gmail.com>
 *
 * @(#) $Id: $
 */


#ifndef __HIDRD_ITEM_H__
#define __HIDRD_ITEM_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum hidrd_item_type {
    HIDRD_ITEM_TYPE_MAIN    = 0,
    HIDRD_ITEM_TYPE_GLOBAL,
    HIDRD_ITEM_TYPE_LOCAL
} hidrd_item_type;

typedef struct hidrd_item {
    hidrd_item_type type;
} hidrd_item;


/***********************************************************
 * Main item
 ***********************************************************/
typedef enum hidrd_item_main_tag {
    HIDRD_ITEM_MAIN_TAG_INPUT           = 0x8,
    HIDRD_ITEM_MAIN_TAG_OUTPUT          = 0x9,
    HIDRD_ITEM_MAIN_TAG_COLLECTION      = 0xA
    HIDRD_ITEM_MAIN_TAG_FEATURE         = 0xB,
    HIDRD_ITEM_MAIN_TAG_END_COLLECTION  = 0xC,
} hidrd_item_main_tag;

typedef struct hidrd_item_main {
    hidrd_item          item;
    hidrd_item_main_tag tag;
} hidrd_item_main;

typedef struct hidrd_item_input {
    hidrd_item_main item_main;
    bool            constant;       /**< Data/Constant */
    bool            variable;       /**< Array/Variable */
    bool            relative;       /**< Absolute/Relative */
    bool            wrap;           /**< No Wrap/Wrap */
    bool            non_linear;     /**< Linear/Non Linear */
    bool            no_preferred;   /**< Preferred State/No Preferred */
    bool            null_state;     /**< No Null position/Null state */
    bool            buffered_bytes; /**< Bit Field/Buffered Bytes */
} hidrd_item_input;

typedef struct hidrd_item_output {
    hidrd_item_main item_main;
    bool            constant;       /**< Data/Constant */
    bool            variable;       /**< Array/Variable */
    bool            relative;       /**< Absolute/Relative */
    bool            wrap;           /**< No Wrap/Wrap */
    bool            non_linear;     /**< Linear/Non Linear */
    bool            no_preferred;   /**< Preferred State/No Preferred */
    bool            null_state;     /**< No Null position/Null state */
    bool            is_volatile;    /**< Non volatile/volatile */
    bool            buffered_bytes; /**< Bit Field/Buffered Bytes */
} hidrd_item_output;

typedef enum hidrd_item_coll_type {
    HIDRD_ITEM_COLL_TYPE_PHYSICAL       = 0,
    HIDRD_ITEM_COLL_TYPE_APPLICATION,
    HIDRD_ITEM_COLL_TYPE_LOGICAL,
    HIDRD_ITEM_COLL_TYPE_REPORT,
    HIDRD_ITEM_COLL_TYPE_NAMED_ARRAY,
    HIDRD_ITEM_COLL_TYPE_USAGE_SWITCH,
    HIDRD_ITEM_COLL_TYPE_USAGE_MODIFIER
} hidrd_item_coll_type;

typedef struct hidrd_item_coll {
    hidrd_item_main         item_main;
    hidrd_item_coll_type    type;
} hidrd_item_coll;

typedef hidrd_item_main hidrd_item_end_coll;

/***********************************************************
 * Global item
 ***********************************************************/
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

typedef struct hidrd_item_global {
    hidrd_item              item;
    hidrd_item_global_tag   tag;
} hidrd_item_global;

typedef struct hidrd_item_usage_page {
    hidrd_item_global   item_global;
    uint16_t            page;
} hidrd_item_usage_page;

typedef struct _hidrd_item_extent {
    hidrd_item_global   item_global;
    int32_t             value;
} _hidrd_item_extent;

typedef _hidrd_item_extent  hidrd_item_logical_minimum;
typedef _hidrd_item_extent  hidrd_item_logical_maximum;
typedef _hidrd_item_extent  hidrd_item_physical_minimum;
typedef _hidrd_item_extent  hidrd_item_physical_maximum;

typedef struct hidrd_item_unit_exp {
    hidrd_item_global   item_global;
    int8_t              value;
} hidrd_item_unit_exponent;

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

typedef struct _hidrd_item_global_uint {
    hidrd_item_global   item_global;
    uint32_t            value;
} _hidrd_item_global_uint;

typedef _hidrd_item_global_uint hidrd_item_report_size;
typedef _hidrd_item_global_uint hidrd_item_report_count;

typedef hidrd_item_global   hidrd_item_push;
typedef hidrd_item_global   hidrd_item_pop;

/***********************************************************
 * Local item
 ***********************************************************/
typedef enum hidrd_item_local_tag {
    HIDRD_ITEM_LOCAL_TAG_USAGE                  = 0,
    HIDRD_ITEM_LOCAL_TAG_USAGE_MINIMUM,
    HIDRD_ITEM_LOCAL_TAG_USAGE_MAXIMUM,
    HIDRD_ITEM_LOCAL_TAG_DESIGNATOR_INDEX,
    HIDRD_ITEM_LOCAL_TAG_DESIGNATOR_MINIMUM,
    HIDRD_ITEM_LOCAL_TAG_DESIGNATOR_MAXIMUM,
    HIDRD_ITEM_LOCAL_TAG_STRING_INDEX,
    HIDRD_ITEM_LOCAL_TAG_STRING_MINIMUM,
    HIDRD_ITEM_LOCAL_TAG_STRING_MAXIMUM,
    HIDRD_ITEM_LOCAL_TAG_DELIMITER
} hidrd_item_global_tag;

typedef struct hidrd_item_local {
    hidrd_item              item;
    hidrd_item_local_tag    tag;
} hidrd_item_local;

typedef struct _hidrd_item_local_uint {
    hidrd_item_local    item_local;
    uint32_t            value;
} _hidrd_item_local_uint;

typedef _hidrd_item_local_uint  hidrd_item_usage;
typedef _hidrd_item_local_uint  hidrd_item_usage_minimum;
typedef _hidrd_item_local_uint  hidrd_item_usage_maximum;
typedef _hidrd_item_local_uint  hidrd_item_designator_index;
typedef _hidrd_item_local_uint  hidrd_item_designator_minimum;
typedef _hidrd_item_local_uint  hidrd_item_designator_maximum;
typedef _hidrd_item_local_uint  hidrd_item_string_index;
typedef _hidrd_item_local_uint  hidrd_item_string_minimum;
typedef _hidrd_item_local_uint  hidrd_item_string_maximum;
typedef _hidrd_item_local_uint  hidrd_item_delimiter;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_H__ */


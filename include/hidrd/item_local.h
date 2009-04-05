/** @file
 * @brief HID report descriptor - local item
 *
 * Copyright (C) 2009 Nikolai Kondrashov
 *
 * @author Nikolai Kondrashov <spbnick@gmail.com>
 *
 * @(#) $Id: $
 */


#ifndef __HIDRD_ITEM_LOCAL_H__
#define __HIDRD_ITEM_LOCAL_H__

#include "hidrd/item.h"

#ifdef __cplusplus
extern "C" {
#endif

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
    hidrd_item_short        item_short;
    hidrd_item_local_tag    tag;
} hidrd_item_local;

/*
 * Usage/designator/string index(ID)/minimum/maximum, delimiter
 */
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

#endif /* __HIDRD_ITEM_LOCAL_H__ */





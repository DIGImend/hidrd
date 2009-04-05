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

typedef struct hidrd_item {
    bool    long_item;
} hidrd_item;

/*
 * Short item
 */
typedef enum hidrd_item_short_type {
    HIDRD_ITEM_SHORT_TYPE_MAIN    = 0,
    HIDRD_ITEM_SHORT_TYPE_GLOBAL,
    HIDRD_ITEM_SHORT_TYPE_LOCAL
} hidrd_item_short_type;

#define HIDRD_ITEM_SHORT_TYPE_KNOWN_MAX HIDRD_ITEM_SHORT_TYPE_LOCAL
#define HIDRD_ITEM_SHORT_TYPE_RESERVED  0x3
#define HIDRD_ITEM_SHORT_TYPE_MAX   HIDRD_ITEM_SHORT_TYPE_RESERVED

static inline bool
hidrd_item_short_type_valid(hidrd_item_short_type type)
{
    return (type <= HIDRD_ITEM_SHORT_TYPE_MAX);
}

static inline bool
hidrd_item_short_type_known(hidrd_item_short_type type)
{
    assert(hidrd_item_short_type_valid(type));
    return (type <= HIDRD_ITEM_SHORT_TYPE_KNOWN_MAX);
}

static inline bool
hidrd_item_short_type_reserved(hidrd_item_short_type type)
{
    assert(hidrd_item_short_type_valid(type));
    return (type == HIDRD_ITEM_SHORT_TYPE_RESERVED);
}

typedef struct hidrd_item_short {
    hidrd_item              item;
    hidrd_item_short_type   type;
} hidrd_item_short;

static inline bool
hidrd_item_short_valid(const hidrd_item_short *item_short)
{
    return !item_short->item.long_item &&
           hidrd_item_short_type_valid(item_short->type);
}

#define HIDRD_ITEM_SHORT_TAG_MAX    0xF

static inline bool
hidrd_item_short_tag_valid(uint8_t tag)
{
    return (tag <= HIDRD_ITEM_SHORT_TAG_MAX);
}

/*
 * Long item
 */
typedef struct hidrd_item_long {
    hidrd_item  item;
    uint8_t     tag;
    uint8_t     size;
    uint8_t     data[255];
}

static inline bool
hidrd_item_long_valid(const hidrd_item_long *item_long)
{
    return item_long->item.long_item;
}


/***********************************************************
 * Reserved item type
 ***********************************************************/
typedef struct hidrd_item_short_reserved {
    hidrd_item_short    item_short;
    uint8_t             tag;
    uint32_t            data;
} hidrd_item_short_reserved;

static inline bool
hidrd_item_short_reserved_valid(const hidrd_item_short_reserved *reserved)
{
    return hidrd_item_short_valid(&reserved->item_short) &&
           hidrd_item_short_type_reserved(reserved->item_short.type) &&
           hidrd_item_short_tag_valid(reserved->tag);
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_H__ */


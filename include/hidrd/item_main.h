/** @file
 * @brief HID report descriptor - main item
 *
 * Copyright (C) 2009 Nikolai Kondrashov
 *
 * @author Nikolai Kondrashov <spbnick@gmail.com>
 *
 * @(#) $Id: $
 */


#ifndef __HIDRD_ITEM_MAIN_H__
#define __HIDRD_ITEM_MAIN_H__

#include "hidrd/item.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HIDRD_ITEM_MAIN_TAG_MIN 0x8

typedef enum hidrd_item_main_tag {
    HIDRD_ITEM_MAIN_TAG_INPUT           = HIDRD_ITEM_MAIN_TAG_MIN,
    HIDRD_ITEM_MAIN_TAG_OUTPUT,
    HIDRD_ITEM_MAIN_TAG_COLLECTION,
    HIDRD_ITEM_MAIN_TAG_FEATURE,
    HIDRD_ITEM_MAIN_TAG_END_COLLECTION
} hidrd_item_main_tag;

#define HIDRD_ITEM_MAIN_TAG_MAX HIDRD_ITEM_SHORT_TAG_MAX

#define HIDRD_ITEM_MAIN_TAG_KNOWN_MAX   HIDRD_ITEM_MAIN_TAG_END_COLLECTION

#define HIDRD_ITEM_MAIN_TAG_RESERVED_MIN \
            (HIDRD_ITEM_MAIN_TAG_KNOWN_MAX + 1)
#define HIDRD_ITEM_MAIN_TAG_RESERVED_MAX \
            HIDRD_ITEM_MAIN_TAG_MAX


static inline bool
hidrd_item_main_tag_valid(hidrd_item_main_tag tag)
{
    return (tag >= HIDRD_ITEM_MAIN_TAG_MIN) &&
           (tag <= HIDRD_ITEM_MAIN_TAG_MAX);
}

static inline bool
hidrd_item_main_tag_known(hidrd_item_main_tag tag)
{
    assert(hidrd_item_main_tag_valid(tag));

    return (tag <= HIDRD_ITEM_MAIN_TAG_KNOWN_MAX);
}

static inline bool
hidrd_item_main_tag_reserved(hidrd_item_main_tag tag)
{
    return (tag >= HIDRD_ITEM_MAIN_TAG_RESERVED_MIN) &&
           (tag <= HIDRD_ITEM_MAIN_TAG_RESERVED_MAX);
}

typedef struct hidrd_item_main {
    hidrd_item_short    item_short;
    hidrd_item_main_tag tag;
} hidrd_item_main;

static inline bool
hidrd_item_main_valid(const hidrd_item_main *main)
{
    return hidrd_item_short_valid(&main->item_short) &&
           main->item_short.type == HIDRD_ITEM_SHORT_TYPE_MAIN &&
           hidrd_item_main_tag_valid(main->tag);
}

/*
 * Input
 */
typedef struct hidrd_item_input {
    hidrd_item_main item_main;
    union {
        bool    number[32];
        struct {
            bool            constant;       /**< Data/Constant */
            bool            variable;       /**< Array/Variable */
            bool            relative;       /**< Absolute/Relative */
            bool            wrap;           /**< No Wrap/Wrap */
            bool            non_linear;     /**< Linear/Non Linear */
            bool            no_preferred;   /**< Preferred State/
                                                 No Preferred */
            bool            null_state;     /**< No Null position/
                                                 Null state */
            bool            reserved7;
            bool            buffered_bytes; /**< Bit Field/Buffered Bytes */
            bool            reserved9;
            bool            reserved10;
            bool            reserved11;
            bool            reserved12;
            bool            reserved13;
            bool            reserved14;
            bool            reserved15;
            bool            reserved16;
            bool            reserved17;
            bool            reserved18;
            bool            reserved19;
            bool            reserved20;
            bool            reserved21;
            bool            reserved22;
            bool            reserved23;
            bool            reserved24;
            bool            reserved25;
            bool            reserved26;
            bool            reserved27;
            bool            reserved28;
            bool            reserved29;
            bool            reserved30;
            bool            reserved31;
        }       name;
    } bit;
} hidrd_item_input;

static inline bool
hidrd_item_input_valid(const hidrd_item_input *input)
{
    return hidrd_item_main_valid(&input->item_main) &&
           input->item_main.tag == HIDRD_ITEM_MAIN_TAG_INPUT;
}

/*
 * Output
 */
typedef struct hidrd_item_output {
    hidrd_item_main item_main;
    union {
        bool    number[32];
        struct {
            bool            constant;       /**< Data/Constant */
            bool            variable;       /**< Array/Variable */
            bool            relative;       /**< Absolute/Relative */
            bool            wrap;           /**< No Wrap/Wrap */
            bool            non_linear;     /**< Linear/Non Linear */
            bool            no_preferred;   /**< Preferred State/
                                                 No Preferred */
            bool            null_state;     /**< No Null position/
                                                 Null state */
            bool            is_volatile;    /**< Non volatile/volatile */
            bool            buffered_bytes; /**< Bit Field/Buffered Bytes */
            bool            reserved9;
            bool            reserved10;
            bool            reserved11;
            bool            reserved12;
            bool            reserved13;
            bool            reserved14;
            bool            reserved15;
            bool            reserved16;
            bool            reserved17;
            bool            reserved18;
            bool            reserved19;
            bool            reserved20;
            bool            reserved21;
            bool            reserved22;
            bool            reserved23;
            bool            reserved24;
            bool            reserved25;
            bool            reserved26;
            bool            reserved27;
            bool            reserved28;
            bool            reserved29;
            bool            reserved30;
            bool            reserved31;
        }       name;
    } bit;
} hidrd_item_output;

static inline bool
hidrd_item_output_valid(const hidrd_item_input *input)
{
    return hidrd_item_main_valid(&input->item_main) &&
           input->item_main.tag == HIDRD_ITEM_MAIN_TAG_OUTPUT;
}

/*
 * Feature
 */
typedef struct hidrd_item_feature {
    hidrd_item_main item_main;
    union {
        bool    number[32];
        struct {
            bool            constant;       /**< Data/Constant */
            bool            variable;       /**< Array/Variable */
            bool            relative;       /**< Absolute/Relative */
            bool            wrap;           /**< No Wrap/Wrap */
            bool            non_linear;     /**< Linear/Non Linear */
            bool            no_preferred;   /**< Preferred State/
                                                 No Preferred */
            bool            null_state;     /**< No Null position/
                                                 Null state */
            bool            is_volatile;    /**< Non volatile/volatile */
            bool            buffered_bytes; /**< Bit Field/Buffered Bytes */
            bool            reserved9;
            bool            reserved10;
            bool            reserved11;
            bool            reserved12;
            bool            reserved13;
            bool            reserved14;
            bool            reserved15;
            bool            reserved16;
            bool            reserved17;
            bool            reserved18;
            bool            reserved19;
            bool            reserved20;
            bool            reserved21;
            bool            reserved22;
            bool            reserved23;
            bool            reserved24;
            bool            reserved25;
            bool            reserved26;
            bool            reserved27;
            bool            reserved28;
            bool            reserved29;
            bool            reserved30;
            bool            reserved31;
        }       name;
    } bit;
} hidrd_item_feature;

static inline bool
hidrd_item_feature_valid(const hidrd_item_input *input)
{
    return hidrd_item_main_valid(&input->item_main) &&
           input->item_main.tag == HIDRD_ITEM_MAIN_TAG_FEATURE;
}

/*
 * Collection
 */
typedef enum hidrd_item_coll_type {
    HIDRD_ITEM_COLL_TYPE_PHYSICAL       = 0x00,
    HIDRD_ITEM_COLL_TYPE_APPLICATION    = 0x01,
    HIDRD_ITEM_COLL_TYPE_LOGICAL        = 0x02,
    HIDRD_ITEM_COLL_TYPE_REPORT         = 0x03,
    HIDRD_ITEM_COLL_TYPE_NAMED_ARRAY    = 0x04,
    HIDRD_ITEM_COLL_TYPE_USAGE_SWITCH   = 0x05,
    HIDRD_ITEM_COLL_TYPE_USAGE_MODIFIER = 0x06,
} hidrd_item_coll_type;

#define HIDRD_ITEM_COLL_TYPE_KNOWN_MAX  HIDRD_ITEM_COLL_TYPE_USAGE_MODIFIER

#define HIDRD_ITEM_COLL_TYPE_RESERVED_MIN   0x07
#define HIDRD_ITEM_COLL_TYPE_RESERVED_MAX   0x7F

#define HIDRD_ITEM_COLL_TYPE_VENDOR_MIN     0x80
#define HIDRD_ITEM_COLL_TYPE_VENDOR_MAX     0xFF

#define HIDRD_ITEM_COLL_TYPE_MAX        HIDRD_ITEM_COLL_TYPE_VENDOR_MAX

static inline bool
hidrd_item_coll_type_valid(hidrd_item_coll_type type)
{
    return (type <= HIDRD_ITEM_COLL_TYPE_MAX);
}

static inline bool
hidrd_item_coll_type_known(hidrd_item_coll_type type)
{
    assert(hidrd_item_coll_type_valid(type));
    return (type <= HIDRD_ITEM_COLL_TYPE_KNOWN_MAX);
}

static inline bool
hidrd_item_coll_type_reserved(hidrd_item_coll_type type)
{
    assert(hidrd_item_coll_type_valid(type));
    return (type >= HIDRD_ITEM_COLL_TYPE_RESERVED_MIN) &&
           (type <= HIDRD_ITEM_COLL_TYPE_RESERVED_MAX);
}

static inline bool
hidrd_item_coll_type_vendor(hidrd_item_coll_type type)
{
    assert(hidrd_item_coll_type_valid(type));
    return (type >= HIDRD_ITEM_COLL_TYPE_VENDOR_MIN) &&
           (type <= HIDRD_ITEM_COLL_TYPE_VENDOR_MAX);
}

typedef struct hidrd_item_coll {
    hidrd_item_main         item_main;
    hidrd_item_coll_type    type;
} hidrd_item_coll;

static inline bool
hidrd_item_coll_valid(const hidrd_item_coll *coll)
{
    return hidrd_item_main_valid(&coll->item_main) &&
           input->item_main.tag == HIDRD_ITEM_MAIN_TAG_COLLECTION &&
           hidrd_item_coll_type_valid(coll->type);
}

/*
 * End collection
 */
typedef struct hidrd_item_end_coll {
    hidrd_item_main         item_main;
} hidrd_item_end_coll;

static inline bool
hidrd_item_end_coll_valid(const hidrd_item_end_coll *end_coll)
{
    return hidrd_item_main_valid(&end_coll->item_main) &&
           input->item_main.tag == HIDRD_ITEM_MAIN_TAG_END_COLLECTION;
}

/*
 * Reserved
 */
typedef struct hidrd_item_main_reserved {
    hidrd_item_main         item_main;
    uint32_t                data;
} hidrd_item_main_reserved;

static inline bool
hidrd_item_main_reserved_valid(const hidrd_item_main_reserved *reserved)
{
    return hidrd_item_main_valid(&reserved->item_main) &&
           hidrd_item_main_tag_reserved(reserved->item_main.tag);
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_MAIN_H__ */



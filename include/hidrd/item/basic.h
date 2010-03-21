/** @file
 * @brief HID report descriptor - basic item.
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

#ifndef __HIDRD_ITEM_BASIC_H__
#define __HIDRD_ITEM_BASIC_H__

#include <assert.h>
#include "hidrd/util/dec.h"
#ifdef HIDRD_WITH_TOKENS
#include "hidrd/util/tkn.h"
#endif
#include "hidrd/item/type.h"
#include "hidrd/item/pfx.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Minimum size of a basic item */
#define HIDRD_ITEM_BASIC_MIN_SIZE   HIDRD_ITEM_SHORT_MIN_SIZE
/** Maximum size of a basic item */
#define HIDRD_ITEM_BASIC_MAX_SIZE   HIDRD_ITEM_LONG_MAX_SIZE

/** Basic item prefix' type bitfield value */
typedef hidrd_item_pfx_type hidrd_item_basic_type;
#define HIDRD_ITEM_BASIC_TYPE_MAIN      HIDRD_ITEM_PFX_TYPE_MAIN
#define HIDRD_ITEM_BASIC_TYPE_GLOBAL    HIDRD_ITEM_PFX_TYPE_GLOBAL
#define HIDRD_ITEM_BASIC_TYPE_LOCAL     HIDRD_ITEM_PFX_TYPE_LOCAL
#define HIDRD_ITEM_BASIC_TYPE_RESERVED  HIDRD_ITEM_PFX_TYPE_RESERVED

#define HIDRD_ITEM_BASIC_TYPE_LONG      HIDRD_ITEM_PFX_TYPE_LONG

/**
 * Check if a basic item prefix' type value is valid.
 *
 * @param type  Basic item type to check.
 *
 * @return True if the type value is valid, false otherwise.
 */
static inline bool
hidrd_item_basic_type_valid(hidrd_item_basic_type type)
{
    return hidrd_item_pfx_type_valid(type);
}


/* Declare type decimal string conversion functions */
HIDRD_DEC_CONV_DECLS(item_basic_type, type);

#ifdef HIDRD_WITH_TOKENS
/* Declare type token conversion functions */
HIDRD_TKN_CONV_DECLS(item_basic_type, type, dec);
#endif /* HIDRD_WITH_TOKENS */

/** Basic item prefix' tag bitfield value */
typedef hidrd_item_pfx_tag hidrd_item_basic_tag;
#define HIDRD_ITEM_BASIC_TAG_MIN    HIDRD_ITEM_PFX_TAG_MIN
#define HIDRD_ITEM_BASIC_TAG_MAX    HIDRD_ITEM_PFX_TAG_MAX
#define HIDRD_ITEM_BASIC_TAG_LONG   HIDRD_ITEM_PFX_TAG_LONG

/**
 * Check if a basic item prefix' tag value is valid.
 *
 * @param tag   Basic item tag to check.
 *
 * @return True if the tag value is valid, false otherwise.
 */
static inline bool
hidrd_item_basic_tag_valid(hidrd_item_basic_tag tag)
{
    return hidrd_item_pfx_tag_valid(tag);
}

/* Declare tag decimal string conversion functions */
HIDRD_DEC_CONV_DECLS(item_basic_tag, tag);

/** Basic item data size value */
typedef hidrd_item_pfx_size hidrd_item_basic_data_size;
#define HIDRD_ITEM_BASIC_DATA_SIZE_0B   HIDRD_ITEM_PFX_SIZE_0B
#define HIDRD_ITEM_BASIC_DATA_SIZE_1B   HIDRD_ITEM_PFX_SIZE_1B
#define HIDRD_ITEM_BASIC_DATA_SIZE_2B   HIDRD_ITEM_PFX_SIZE_2B
#define HIDRD_ITEM_BASIC_DATA_SIZE_4B   HIDRD_ITEM_PFX_SIZE_4B
#define HIDRD_ITEM_BASIC_DATA_SIZE_LONG HIDRD_ITEM_PFX_SIZE_LONG

/**
 * Check if a basic item prefix' data size code is valid.
 *
 * @param size  Basic item data size code to check.
 *
 * @return True if the data size code is valid, false otherwise.
 */
static inline bool
hidrd_item_basic_data_size_valid(hidrd_item_basic_data_size size)
{
    return hidrd_item_pfx_size_valid(size);
}

/** Basic item data size in bytes */
typedef hidrd_item_pfx_bytes    hidrd_item_basic_data_bytes;


/**
 * Check if a basic item prefix' data size in bytes is valid.
 *
 * @return Basic item data size in bytes to check.
 *
 * @return True if data size in bytes is valid, false otherwise.
 */
static inline bool
hidrd_item_basic_data_bytes_valid(hidrd_item_basic_data_bytes bytes)
{
    return hidrd_item_pfx_bytes_valid(bytes);
}

/**
 * Convert basic item prefix' data size code to bytes.
 *
 * @param size  Basic item data size code.
 *
 * @return Basic item data size in bytes.
 */
static inline hidrd_item_basic_data_bytes
hidrd_item_basic_data_size_to_bytes(hidrd_item_basic_data_size size)
{
    return hidrd_item_pfx_size_to_bytes(size);
}

/**
 * Convert basic item prefix' data size in bytes to code.
 *
 * @param bytes Basic item data size in bytes.
 *
 * @return Basic item data size code.
 */
static inline hidrd_item_basic_data_size
hidrd_item_basic_data_size_from_bytes(hidrd_item_basic_data_bytes bytes)
{
    return hidrd_item_pfx_size_from_bytes(bytes);
}

/* Declare decimal string conversion functions for data size in bytes */
HIDRD_DEC_CONV_DECLS(item_basic_data_bytes, bytes);


/**
 * Check if a basic item class identification is valid.
 *
 * @param item  Item to check the class identification of.
 *
 * @return True if the item class identification matches basic, false
 *         otherwise.
 */
static inline bool
hidrd_item_basic_valid_class(const hidrd_item *item)
{
    return item != NULL;
}


/**
 * Check if a basic item instance data is valid.
 *
 * @param item  Item to check the instance data of.
 *
 * @return True if the basic item instance data is valid, false otherwise.
 */
static inline bool
hidrd_item_basic_valid_inst(const hidrd_item *item)
{
    assert(hidrd_item_basic_valid_class(item));
    (void)item;
    return true;
}


/**
 * Check if an item is basic and its instance data is valid.
 *
 * @param item  Item to check the validity of.
 *
 * @return True if the item is valid, false otherwise.
 */
static inline bool
hidrd_item_basic_valid(const hidrd_item *item)
{
    return hidrd_item_basic_valid_class(item) &&
           hidrd_item_basic_valid_inst(item);
}


/**
 * Validate item as basic.
 *
 * @param item  Item to validate.
 *
 * @return Validated item.
 */
static inline hidrd_item *
hidrd_item_basic_validate(hidrd_item *item)
{
    assert(hidrd_item_basic_valid(item));
    return item;
}


/**
 * Retrieve basic item prefix.
 *
 * @param item  Basic item to retrieve prefix from.
 *
 * @return The item prefix.
 */
static inline hidrd_item_pfx
hidrd_item_basic_get_pfx(const hidrd_item *item)
{
    assert(hidrd_item_basic_valid(item));
    return item[0];
}


/**
 * Set basic item prefix.
 *
 * @param item  Basic item to set prefix to.
 * @param pfx   Basic item prefix to set.
 *
 * @return The item with the prefix set.
 */
static inline hidrd_item *
hidrd_item_basic_set_pfx(hidrd_item *item, hidrd_item_pfx pfx)
{
    assert(hidrd_item_basic_valid(item));
    item[0] = pfx;
    return item;
}


/** Basic item format */
typedef enum hidrd_item_basic_format {
    HIDRD_ITEM_BASIC_FORMAT_SHORT,  /**< Short format */
    HIDRD_ITEM_BASIC_FORMAT_LONG    /**< Long format */
} hidrd_item_basic_format;


/**
 * Check if a basic item format value is valid.
 *
 * @param format    Format to check the validity of.
 *
 * @return True if the basic item format value is valid, false otherwise.
 */
static inline bool
hidrd_item_basic_format_valid(hidrd_item_basic_format format)
{
    return format == HIDRD_ITEM_BASIC_FORMAT_SHORT ||
           format == HIDRD_ITEM_BASIC_FORMAT_LONG;
}


/**
 * Get a basic item format.
 *
 * @param item  Basic item to get format of.
 *
 * @return Basic item format value.
 */
static inline hidrd_item_basic_format
hidrd_item_basic_get_format(const hidrd_item *item)
{
    assert(hidrd_item_basic_valid(item));
    /* Check if bTag indicates long item */
    return (hidrd_item_pfx_get_tag(hidrd_item_basic_get_pfx(item)) ==
            HIDRD_ITEM_PFX_TAG_LONG)
            ? HIDRD_ITEM_BASIC_FORMAT_LONG
            : HIDRD_ITEM_BASIC_FORMAT_SHORT;
}


/**
 * Set format of a basic item.
 *
 * @param item      Basic item to set format to.
 * @param format    Basic item format value to set.
 *
 * @return The item with the new format set.
 *
 * @note As format is specified by the combination of bit fields within
 *       prefix, where long format is a specific combination, whereas the
 *       short format is everything else, the prefix is not modified if the
 *       format doesn't need an update.
 */
static inline hidrd_item *
hidrd_item_basic_set_format(hidrd_item                 *item,
                            hidrd_item_basic_format     format)
{
    assert(hidrd_item_basic_valid(item));
    assert(hidrd_item_basic_format_valid(format));

    if (format != hidrd_item_basic_get_format(item))
    {
        return hidrd_item_basic_set_pfx(
                    item,
                    (format == HIDRD_ITEM_BASIC_FORMAT_SHORT)
                        ? HIDRD_ITEM_PFX_SHORT
                        : HIDRD_ITEM_PFX_LONG);
    }
    else
        return item;
}


/**
 * Check if a basic item format is short.
 *
 * @param item  Basic item to check.
 *
 * @return True if the item format is short, false otherwise.
 */
static inline bool
hidrd_item_basic_is_short(const hidrd_item *item)
{
    assert(hidrd_item_basic_valid(item));
    return hidrd_item_basic_get_format(item) ==
           HIDRD_ITEM_BASIC_FORMAT_SHORT;
}


/**
 * Check if a basic item format is long.
 *
 * @param item  Basic item to check.
 *
 * @return True if the item format is long, false otherwise.
 */
static inline bool
hidrd_item_basic_is_long(const hidrd_item *item)
{
    assert(hidrd_item_basic_valid(item));

    return hidrd_item_basic_get_format(item) ==
           HIDRD_ITEM_BASIC_FORMAT_LONG;
}


/**
 * Initialize a basic item.
 *
 * @param item      Item to initialize.
 * @param type      Basic item type to set.
 * @param tag       Basic item tag to set.
 * @param size      Basic item data size code to set.
 *
 * @return The item initialized as basic.
 */
static inline hidrd_item *
hidrd_item_basic_init(hidrd_item                   *item,
                      hidrd_item_basic_type         type,
                      hidrd_item_basic_tag          tag,
                      hidrd_item_basic_data_size    size)
{
    assert(hidrd_item_basic_type_valid(type));
    assert(hidrd_item_basic_tag_valid(tag));
    assert(hidrd_item_basic_data_size_valid(size));

    return hidrd_item_basic_validate(
        hidrd_item_basic_set_pfx(
            item,
            hidrd_item_pfx_set_size(
                hidrd_item_pfx_set_tag(
                    hidrd_item_pfx_set_type(0, type),
                    tag),
                size)));
}


/**
 * Get type from a basic item's prefix.
 *
 * @param item  Item to get the type from.
 *
 * @return The type from the item's prefix.
 */
static inline hidrd_item_basic_type
hidrd_item_basic_get_type(const hidrd_item *item)
{
    assert(hidrd_item_basic_valid(item));
    return hidrd_item_pfx_get_type(hidrd_item_basic_get_pfx(item));
}

/**
 * Set type to a basic item's prefix.
 *
 * @param item  Item to set type to.
 * @param type  Basic item type to set.
 *
 * @return The item with prefix' type modified.
 */
static inline hidrd_item *
hidrd_item_basic_set_type(hidrd_item *item, hidrd_item_basic_type type)
{
    assert(hidrd_item_basic_valid(item));
    assert(hidrd_item_basic_type_valid(type));
    return hidrd_item_basic_set_pfx(
                item,
                hidrd_item_pfx_set_type(
                    hidrd_item_basic_get_pfx(item),
                    type));
}


/**
 * Get tag from a basic item's prefix.
 *
 * @param item  Item to get the tag from.
 *
 * @return The tag from the item's prefix.
 */
static inline hidrd_item_basic_tag
hidrd_item_basic_get_tag(const hidrd_item *item)
{
    assert(hidrd_item_basic_valid(item));
    return hidrd_item_pfx_get_tag(hidrd_item_basic_get_pfx(item));
}

/**
 * Set tag to a basic item's prefix.
 *
 * @param item  Item to set tag to.
 * @param tag   Basic item tag to set.
 *
 * @return The item with prefix' tag modified.
 */
static inline hidrd_item *
hidrd_item_basic_set_tag(hidrd_item *item, hidrd_item_basic_tag tag)
{
    assert(hidrd_item_basic_valid(item));
    assert(hidrd_item_basic_tag_valid(tag));
    return hidrd_item_basic_set_pfx(
                item,
                hidrd_item_pfx_set_tag(
                    hidrd_item_basic_get_pfx(item),
                    tag));
}


/**
 * Get data size code from a basic item's prefix.
 *
 * @param item  Item to get the data size code from.
 *
 * @return The data size code from the item's prefix.
 *
 * @note The data size code returned cannot be used to determine the actual
 *       item size directly, without taking the item format into account.
 */
static inline hidrd_item_basic_data_size
hidrd_item_basic_get_data_size(const hidrd_item *item)
{
    assert(hidrd_item_basic_valid(item));
    return hidrd_item_pfx_get_size(hidrd_item_basic_get_pfx(item));
}


/**
 * Get a basic item data size in bytes.
 *
 * @param item  Basic item to get data size from.
 *
 * @return Basic item data size in bytes.
 */
static inline size_t
hidrd_item_basic_get_data_bytes(const hidrd_item *item)
{
    assert(hidrd_item_basic_valid(item));
    return hidrd_item_basic_data_size_to_bytes(
            hidrd_item_basic_get_data_size(item));
}


/**
 * Set data size to a basic item's prefix.
 *
 * @param item  Item to set data size to.
 * @param size  Basic item data size to set.
 *
 * @return The item with prefix' data size modified.
 *
 * @note Doesn't modify anything except the data size bitfield of the
 *       prefix.
 */
static inline hidrd_item *
hidrd_item_basic_set_data_size(hidrd_item                  *item,
                               hidrd_item_basic_data_size   size)
{
    assert(hidrd_item_basic_valid(item));
    assert(hidrd_item_basic_data_size_valid(size));
    return hidrd_item_basic_set_pfx(
                item,
                hidrd_item_pfx_set_size(
                    hidrd_item_basic_get_pfx(item),
                    size));
}


/**
 * Retrieve data portion pointer of a basic item.
 *
 * @param item  Item to retrieve data pointer for.
 *
 * @return The item data portion pointer.
 *
 * @note The data pointer cannot be used directly without taking the item
 *       format into account.
 */
static inline void *
hidrd_item_basic_get_data(hidrd_item *item)
{
    assert(hidrd_item_basic_valid(item));
    return &item[1];
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_BASIC_H__ */

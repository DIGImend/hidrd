/** @file
 * @brief HID report descriptor - short item
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

#ifndef __HIDRD_ITEM_SHORT_H__
#define __HIDRD_ITEM_SHORT_H__

#include <assert.h>
#include "hidrd/item/basic.h"
#include "hidrd/bit.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Minimum size of a short item */
#define HIDRD_ITEM_SHORT_MIN_SIZE   1
/** Maximum size of a short item */
#define HIDRD_ITEM_SHORT_MAX_SIZE   (1 + 4)

/** Short item type */
typedef hidrd_item_basic_type hidrd_item_short_type;
#define HIDRD_ITEM_SHORT_TYPE_MAIN      HIDRD_ITEM_BASIC_TYPE_MAIN
#define HIDRD_ITEM_SHORT_TYPE_GLOBAL    HIDRD_ITEM_BASIC_TYPE_GLOBAL
#define HIDRD_ITEM_SHORT_TYPE_LOCAL     HIDRD_ITEM_BASIC_TYPE_LOCAL

/**
 * Check if a short item type is valid.
 *
 * @param type  Short item type to check.
 *
 * @return True if the type is valid, false otherwise.
 */
static inline bool
hidrd_item_short_type_valid(hidrd_item_short_type type)
{
    switch (type)
    {
        case HIDRD_ITEM_SHORT_TYPE_MAIN:
        case HIDRD_ITEM_SHORT_TYPE_GLOBAL:
        case HIDRD_ITEM_SHORT_TYPE_LOCAL:
            return true;
        default:
            return false;
    }
}

/** Short item tag */
typedef hidrd_item_basic_tag hidrd_item_short_tag;
#define HIDRD_ITEM_SHORT_TAG_MIN    HIDRD_ITEM_BASIC_TAG_MIN
#define HIDRD_ITEM_SHORT_TAG_MAX    HIDRD_ITEM_BASIC_TAG_MAX

/**
 * Check if a short item tag is valid.
 *
 * @param tag   Short item tag to check.
 *
 * @return True if the tag is valid, false otherwise.
 */
static inline bool
hidrd_item_short_tag_valid(hidrd_item_short_tag tag)
{
    return hidrd_item_basic_tag_valid(tag);
}


/** Short item data size code */
typedef hidrd_item_basic_data_size hidrd_item_short_data_size;
#define HIDRD_ITEM_SHORT_DATA_SIZE_0B   HIDRD_ITEM_BASIC_DATA_SIZE_0B
#define HIDRD_ITEM_SHORT_DATA_SIZE_1B   HIDRD_ITEM_BASIC_DATA_SIZE_1B
#define HIDRD_ITEM_SHORT_DATA_SIZE_2B   HIDRD_ITEM_BASIC_DATA_SIZE_2B
#define HIDRD_ITEM_SHORT_DATA_SIZE_4B   HIDRD_ITEM_BASIC_DATA_SIZE_4B

/**
 * Check if a short item data size code is valid.
 *
 * @param size  Short item data size code to check.
 *
 * @return True if the size code is valid, false otherwise.
 */
static inline bool
hidrd_item_short_data_size_valid(hidrd_item_short_data_size size)
{
    return hidrd_item_basic_data_size_valid(size);
}

/**
 * Convert short item data size code to bytes.
 *
 * @param size  Short item data size code.
 *
 * @return Short item data size to bytes.
 */
static inline size_t
hidrd_item_short_data_size_to_bytes(hidrd_item_short_data_size size)
{
    return hidrd_item_basic_data_size_to_bytes(size);
}


/**
 * Check if a short item class identification is valid.
 *
 * @param item  Item to check the class identification of.
 *
 * @return True if the item class identification matches short, false
 *         otherwise.
 */
static inline bool
hidrd_item_short_valid_class(const hidrd_item *item)
{
    return hidrd_item_basic_valid_class(item) &&
           hidrd_item_basic_is_short(item);
}


/**
 * Check if a short item instance data is valid.
 *
 * @param item  Item to check the instance data of.
 *
 * @return True if the short item instance data is valid, false otherwise.
 */
static inline bool
hidrd_item_short_valid_inst(const hidrd_item *item)
{
    assert(hidrd_item_short_valid_class(item));
    return hidrd_item_basic_valid_inst(item);
}


/**
 * Check if an item is short and its instance data is valid.
 *
 * @param item  Item to check the validity of.
 *
 * @return True if the item is valid, false otherwise.
 */
static inline bool
hidrd_item_short_valid(const hidrd_item *item)
{
    return hidrd_item_short_valid_class(item) &&
           hidrd_item_short_valid_inst(item);
}


/**
 * Validate item as short.
 *
 * @param item  Item to validate.
 *
 * @return Validated item.
 */
static inline hidrd_item *
hidrd_item_short_validate(hidrd_item *item)
{
    assert(hidrd_item_short_valid(item));
    return item;
}


/**
 * Get a short item type.
 *
 * @param item  Short item to get type from.
 *
 * @return Short item type.
 */
static inline hidrd_item_short_type
hidrd_item_short_get_type(const hidrd_item *item)
{
    assert(hidrd_item_short_valid(item));
    return hidrd_item_basic_get_type(item);
}


/**
 * Set a short item type.
 *
 * @param item  Short item to set type to.
 * @param type  Short item type to set.
 *
 * @return The item with the type set.
 */
static inline hidrd_item *
hidrd_item_short_set_type(hidrd_item *item, hidrd_item_short_type type)
{
    assert(hidrd_item_short_valid(item));
    assert(hidrd_item_short_type_valid(type));
    return hidrd_item_basic_set_type(item, type);
}


/**
 * Get a short item tag.
 *
 * @param item  Short item to get tag from.
 *
 * @return Short item tag.
 */
static inline hidrd_item_short_tag
hidrd_item_short_get_tag(const hidrd_item *item)
{
    assert(hidrd_item_short_valid(item));
    return hidrd_item_basic_get_tag(item);
}


/**
 * Set a short item tag.
 *
 * @param item  Short item to set tag to.
 * @param tag   Short item tag to set.
 *
 * @return The item with the tag set.
 */
static inline hidrd_item *
hidrd_item_short_set_tag(hidrd_item *item, hidrd_item_short_tag tag)
{
    assert(hidrd_item_short_valid(item));
    assert(hidrd_item_short_tag_valid(tag));
    return hidrd_item_basic_set_tag(item, tag);
}


/**
 * Get a short item data size code.
 *
 * @param item  Short item to get data size code from.
 *
 * @return Short item data size code.
 */
static inline hidrd_item_short_data_size
hidrd_item_short_get_data_size(const hidrd_item *item)
{
    assert(hidrd_item_short_valid(item));
    return hidrd_item_basic_get_data_size(item);
}


/**
 * Set a short item data size code.
 *
 * @param item  Short item to set data size code to.
 * @param size  Short item data size code to set.
 *
 * @return The item with the data size code set.
 */
static inline hidrd_item *
hidrd_item_short_set_data_size(hidrd_item                  *item,
                               hidrd_item_short_data_size   size)
{
    assert(hidrd_item_short_valid(item));
    assert(hidrd_item_short_data_size_valid(size));
    return hidrd_item_basic_set_data_size(item, size);
}


/**
 * Get data pointer of a short item.
 *
 * @param item  Short item to get data pointer of.
 *
 * @return Data pointer.
 */
static inline void *
hidrd_item_short_get_data(hidrd_item *item)
{
    assert(hidrd_item_short_valid(item));
    return hidrd_item_basic_get_data(item);
}


/**
 * Get short item size.
 *
 * @param item  Short item to get size of.
 *
 * @return The item size.
 */
static inline size_t
hidrd_item_short_get_size(const hidrd_item *item)
{
    assert(hidrd_item_short_valid(item));
    return 1 + hidrd_item_short_data_size_to_bytes(
                hidrd_item_short_get_data_size(item));
}


/**
 * Get short item data as an unsigned integer.
 *
 * @param item  Short item to get data from.
 *
 * @return Short item data as an unsigned integer.
 */
extern uint32_t hidrd_item_short_get_unsigned(const hidrd_item *item);

/**
 * Set short item data as an unsigned integer.
 *
 * @param item  Short item to set data to.
 * @param data  Short item data as an unsigned integer.
 *
 * @return The item with the data set.
 */
extern hidrd_item* hidrd_item_short_set_unsigned(hidrd_item *item,
                                                 uint32_t data);

/**
 * Get short item data as a signed integer.
 *
 * @param item  Short item to get data from.
 *
 * @return Short item data as a signed integer.
 */
extern int32_t hidrd_item_short_get_signed(const hidrd_item *item);

/**
 * Set short item data as a signed integer.
 *
 * @param item  Short item to set data to.
 * @param data  Short item data as a signed integer.
 *
 * @return The item with the data set.
 */
extern hidrd_item* hidrd_item_short_set_signed(hidrd_item *item,
                                               int32_t data);

/**
 * Get value of a short item data bit.
 *
 * @param item  Short item to get data from.
 * @param idx   Bit index to get value of.
 *
 * @return The data bit value.
 */
static inline bool
hidrd_item_short_get_bit(const hidrd_item *item, uint8_t idx)
{
    assert(hidrd_item_short_valid(item));
    assert(idx <= 31);
    return HIDRD_BIT_GET(hidrd_item_short_get_unsigned(item), idx) != 0;
}


/**
 * Set value of a short item data bit.
 *
 * @param item  Short item to set data to.
 * @param idx   Bit index to set value of.
 * @param val   Bit value; any non-zero value considered 1.
 *
 * @return The item with the data bit set.
 */
static inline hidrd_item *
hidrd_item_short_set_bit(hidrd_item *item, uint8_t idx, bool val)
{
    assert(hidrd_item_short_valid(item));
    assert(idx <= 31);
    return hidrd_item_short_set_unsigned(
            item,
            HIDRD_BIT_SET(hidrd_item_short_get_unsigned(item), idx, val));
}


/**
 * Initialize a short item.
 *
 * @param item  An item to initialize as short.
 * @param type  Short item type to set.
 * @param tag   Short item tag to set.
 *
 * @return The item initialized as short.
 */
static inline hidrd_item *
hidrd_item_short_init(hidrd_item                   *item,
                      hidrd_item_short_type         type,
                      hidrd_item_short_tag          tag)
{
    assert(hidrd_item_short_type_valid(type));
    assert(hidrd_item_short_tag_valid(tag));

    return hidrd_item_short_validate(
                hidrd_item_basic_init(item, type, tag, 0));
}


/**
 * Initialize a short item with data specified as a signed integer.
 *
 * @param item  An item to initialize as short.
 * @param type  Short item type to set.
 * @param tag   Short item tag to set.
 * @param data  Short item data as a signed integer.
 *
 * @return The item initialized as short.
 */
static inline hidrd_item *
hidrd_item_short_init_signed(hidrd_item            *item,
                             hidrd_item_short_type  type,
                             hidrd_item_short_tag   tag,
                             int32_t                data)
{
    assert(hidrd_item_short_type_valid(type));
    assert(hidrd_item_short_tag_valid(tag));

    return hidrd_item_short_set_signed(
                hidrd_item_short_init(item, type, tag), data);
}


/**
 * Initialize a short item with data specified as an unsigned integer.
 *
 * @param item  An item to initialize as short.
 * @param type  Short item type to set.
 * @param tag   Short item tag to set.
 * @param data  Short item data as an unsigned integer.
 *
 * @return The item initialized as short.
 */
static inline hidrd_item *
hidrd_item_short_init_unsigned(hidrd_item              *item,
                               hidrd_item_short_type    type,
                               hidrd_item_short_tag     tag,
                               uint32_t                 data)
{
    assert(hidrd_item_short_type_valid(type));
    assert(hidrd_item_short_tag_valid(tag));

    return hidrd_item_short_set_unsigned(
                hidrd_item_short_init(item, type, tag), data);
}


#define HIDRD_ITEM_SHORT_GEN_FUNCS(_name, _NAME) \
    static inline bool                                                  \
    hidrd_item_##_name##_valid_class(const hidrd_item *item)            \
    {                                                                   \
        return hidrd_item_short_valid(item) &&                          \
               (hidrd_item_short_get_type(item) ==                      \
                HIDRD_ITEM_SHORT_TYPE_##_NAME);                         \
    }                                                                   \
                                                                        \
    static inline bool                                                  \
    hidrd_item_##_name##_valid_inst(const hidrd_item *item)             \
    {                                                                   \
        assert(hidrd_item_##_name##_valid_class(item));                 \
        return hidrd_item_##_name##_tag_valid(                          \
                    hidrd_item_short_get_tag(item));                    \
    }                                                                   \
                                                                        \
    static inline bool                                                  \
    hidrd_item_##_name##_valid(const hidrd_item *item)                  \
    {                                                                   \
        return hidrd_item_##_name##_valid_class(item) &&                \
               hidrd_item_##_name##_valid_inst(item);                   \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_validate(hidrd_item *item)                     \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
        return item;                                                    \
    }                                                                   \
                                                                        \
    static inline hidrd_item_##_name##_tag                              \
    hidrd_item_##_name##_get_tag(const hidrd_item *item)                \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
        return hidrd_item_short_get_tag(item);                          \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_set_tag(hidrd_item                *item,       \
                                 hidrd_item_##_name##_tag   tag)        \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
        return hidrd_item_short_set_tag(item, tag);                     \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_init(hidrd_item               *item,           \
                              hidrd_item_##_name##_tag  tag)            \
    {                                                                   \
        assert(hidrd_item_##_name##_tag_valid(tag));                    \
                                                                        \
        return hidrd_item_##_name##_validate(                           \
            hidrd_item_short_init(item,                                 \
                                  HIDRD_ITEM_SHORT_TYPE_##_NAME,        \
                                  tag));                                \
    }                                                                   \
                                                                        \
    static inline int32_t                                               \
    hidrd_item_##_name##_get_signed(const hidrd_item *item)             \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
                                                                        \
        return hidrd_item_short_get_signed(item);                       \
    }                                                                   \
                                                                        \
    static inline uint32_t                                              \
    hidrd_item_##_name##_get_unsigned(const hidrd_item *item)           \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
                                                                        \
        return hidrd_item_short_get_unsigned(item);                     \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_set_signed(hidrd_item *item, int32_t data)     \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
                                                                        \
        return hidrd_item_short_set_signed(item, data);                 \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_set_unsigned(hidrd_item *item, uint32_t data)  \
    {                                                                   \
        assert(hidrd_item_##_name##_valid(item));                       \
                                                                        \
        return hidrd_item_short_set_unsigned(item, data);               \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_init_signed(hidrd_item                *item,   \
                                     hidrd_item_##_name##_tag   tag,    \
                                     int32_t                    data)   \
    {                                                                   \
        assert(hidrd_item_##_name##_tag_valid(tag));                    \
                                                                        \
        return hidrd_item_##_name##_validate(                           \
            hidrd_item_##_name##_set_signed(                            \
                hidrd_item_##_name##_init(item, tag), data));           \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_init_unsigned(hidrd_item               *item,  \
                                       hidrd_item_##_name##_tag  tag,   \
                                       uint32_t                  data)  \
    {                                                                   \
        assert(hidrd_item_##_name##_tag_valid(tag));                    \
                                                                        \
        return hidrd_item_##_name##_validate(                           \
            hidrd_item_##_name##_set_unsigned(                          \
                hidrd_item_##_name##_init(item, tag), data));           \
    }


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_SHORT_H__ */

/**
 * @brief USB HID input report descriptor converter - binary to XML.
 *
 * Copyright (C) 2009 Nikolai Kondrashov
 *
 * @author Nikolai Kondrashov <spbnick@gmail.com>
 */


#include <assert.h>
#include <stdbool.h>
#include <errno.h>
#include <error.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


#define BIT(v, n) ((v >> n) & 1)

#define BARR(_array) \
    for (uint32_t _a = _array, _f = 1; _f; _f = 0)

#define BARR_BIT    ((_a >> = 1) & 1)


typedef enum exit_status {
    EXIT_STATUS_OK  = 0,
    EXIT_STATUS_EIO,
    EXIT_STATUS_ESYNTAX,
} exit_status;

typedef enum item_type {
    ITEM_TYPE_MAIN      = 0,
    ITEM_TYPE_GLOBAL,
    ITEM_TYPE_LOCAL,
    ITEM_TYPE_RESERVED,
} item_type;


static bool
item_type_valid(item_type type)
{
    return type <= ITEM_TYPE_RESERVED;
}


typedef enum item_size {
    ITEM_SIZE_0B        = 0,
    ITEM_SIZE_1B,
    ITEM_SIZE_2B,
    ITEM_SIZE_4B
} item_size;


static bool
item_size_valid(item_size size)
{
    return size <= ITEM_SIZE_4B;
}


typedef enum main_item_tag {
    MAIN_ITEM_TAG_INPUT             = 0x8,
    MAIN_ITEM_TAG_OUTPUT            = 0x9,
    MAIN_ITEM_TAG_COLLECTION        = 0xA
    MAIN_ITEM_TAG_FEATURE           = 0xB,
    MAIN_ITEM_TAG_END_COLLECTION    = 0xC,
    MAIN_ITEM_TAG_RESERVED1         = 0xD,
    MAIN_ITEM_TAG_RESERVED2         = 0xE,
    MAIN_ITEM_TAG_RESERVED3         = 0xF
} main_item_tag;


static bool
main_item_tag_valid(main_item_tag tag)
{
    return tag >= MAIN_ITEM_TAG_INPUT &&
           tag <= MAIN_ITEM_TAG_RESERVED3;
}


static size_t
item_size_to_bytes(item_size size)
{
    assert(item_size_valid(size));

    return (size < ITEM_SIZE_4B) ? size : 4;
}


#define PFX_LONG_ITEM_SIZE  0x2
#define PFX_LONG_ITEM_TYPE  ITEM_TYPE_RESERVED
#define PFX_LONG_ITEM_TAG   0xF


static int
read_long_item_header(fd, uint8_t *psize, uint8_t ptag)
{
    ssize_t read_len;
    uint8_t size;
    uint8_t tag;

    read_len = read(fd, &size, sizeof(size));
    if (read_len <= 0)
        return read_len;

    read_len = read(fd, &tag, sizeof(tag));
    if (read_len <= 0)
        return read_len;

    if (psize != NULL)
        *psize = size;

    if (ptag != NULL)
        *ptag = tag;

    return 1;
}


static int
trns_long_item(int fd, uint8_t size, uint8_t tag)
{
    ssize_t read_len;
    uint8_t buf[255];

    (void)tag;

    read_len = read(fd, buf, size);
    if (read_len < 0)
        return read_len;
    else if (read_len < size)
        return 0;

    return 1;
}


static int
trns_main_item_input(int fd, uint8_t bytes)
{
    ssize_t     read_len;
    uint32_t    buf         = 0;

    bool        constant;
    bool        variable;
    bool        relative;
    bool        wrap;
    bool        non_linear;
    bool        no_preferred;
    bool        null_state;
    bool        buffered_bytes;

    read_len = read(fd, &buf, bytes);
    if (read_len < 0)
        return read_len;
    else if (read_len < bytes)
        return 0;

    BARR(buf)
    {
        constant        = BARR_BIT;
        variable        = BARR_BIT;
        relative        = BARR_BIT;
        wrap            = BARR_BIT;
        non_linear      = BARR_BIT;
        no_preferred;   = BARR_BIT;
        null_state      = BARR_BIT;
                          BARR_BIT;
        buffered_bytes  = BARR_BIT;
    }

    outp_main_item_input(constant, variable, relative, wrap,
                         non_linear, no_preferred, null_state,
                         buffered_bytes)

    return 1;
}


static int
trns_main_item_output(int fd, uint8_t bytes)
{
}


static int
trns_main_item_collection(int fd, uint8_t bytes)
{
}


static int
trns_main_item_end_collection(int fd, uint8_t bytes)
{
}


static int
trns_main_item_reserved(int fd, uint8_t bytes)
{
    ssize_t     read_len;
    uint32_t    buf;

    assert(bytes <= 4);

    read_len = read(fd, &buf, bytes);
    if (read_len < 0)
        return read_len;
    else if (read_len < bytes)
        return 0;

    return 1;
}


static int
trns_main_item_data(int fd, uint8_t bytes, main_item_tag tag)
{
    ssize_t read_len;

    switch (tag)
    {
        case MAIN_ITEM_TAG_INPUT:
            return trns_main_item_input(fd, bytes);
        case MAIN_ITEM_TAG_OUTPUT:
            return trns_main_item_output(fd, bytes);
        case MAIN_ITEM_TAG_FEATURE:
            return trns_main_item_feature(fd, bytes);
        case MAIN_ITEM_TAG_COLLECTION:
            return trns_main_item_collection(fd, bytes);
        case MAIN_ITEM_TAG_END_COLLECTION:
            return trns_main_item_end_collection(fd, bytes);
        case MAIN_ITEM_TAG_RESERVED1:
        case MAIN_ITEM_TAG_RESERVED2:
        case MAIN_ITEM_TAG_RESERVED3:
            return trns_main_item_reserved(fd, bytes);
        default:
            error(EXIT_STATUS_ESYNTAX, 0, "Invalid main item tag 0x%X", tag);
    }
}


static int
trns_reserved_item_data(int fd, uint8_t bytes, uint8_t tag)
{
    ssize_t     read_len;
    uint32_t    buf;

    (void)tag;

    assert(bytes <= 4);

    read_len = read(fd, &buf, bytes);
    if (read_len < 0)
        return read_len;
    else if (read_len < bytes)
        return 0;

    return 1;
}


static int
trns_short_item_data(int fd, uint8_t bytes, item_type type, uint8_t tag)
{
    ssize_t read_len;

    assert(item_type_valid(type));
    assert(bytes <= 4);

    switch (type)
    {
        case ITEM_TYPE_MAIN:
            return trns_main_item_data(fd, bytes, tag);
        case ITEM_TYPE_GLOBAL:
            return trns_global_item_data(fd, bytes, tag);
        case ITEM_TYPE_LOCAL:
            return trns_local_item_data(fd, bytes, tag);
        case ITEM_TYPE_RESERVED:
            return trns_reserved_item_data(fd, bytes, tag);
    }

    return 0;
}


static int
trns_item(int fd)
{
    ssize_t read_len;
    uint8_t pfx;
    uint8_t size;
    uint8_t type;
    uint8_t tag;


    read_len = read(fd, &pfx, sizeof(pfx));
    if (read_len <= 0)
        return read_len;

    size    = pfx & 0x3;
    type    = (pfx >> 2) & 0x3;
    tag     = (pfx >> 4) & 0xF;

    if (size == PFX_LONG_ITEM_SIZE &&
        type == PFX_LONG_ITEM_TYPE &&
        tag == PFX_LONG_ITEM_TAG)
    {
        read_len = read_long_item_header(fd, &size, &tag);
        if (read_len <= 0)
            return read_len;
        return trns_long_item_data(fd, size, tag);
    }

    return trns_short_item_data(fd, item_size_to_bytes(size), type, tag);
}


int
main(int argc, char **argv)
{
    ssize_t read_len;

    while ((read_len = trns_item(STDIN_FILENO)) > 0);

    if (read_len < 0)
        error(EXIT_STATUS_EIO, errno, "Failed reading report descriptor");

    return EXIT_STATUS_OK;
}

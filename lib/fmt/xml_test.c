/** @file
 * @brief HID report descriptor - XML format test
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

#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include "hidrd/fmt/xml.h"

typedef struct item_desc {
    uint8_t     buf[HIDRD_ITEM_MAX_SIZE];
    size_t      len;
} item_desc;

/** WP8060U report descriptor */
const item_desc item_list[] = {
    {.buf = {0x05, 0x0d}, .len = 2},                    // USAGE_PAGE (Digitizers)
    {.buf = {0x09, 0x02}, .len = 2},                    // USAGE (Pen)
    {.buf = {0xa1, 0x01}, .len = 2},                    // COLLECTION (Application)
    {.buf = {0x85, 0x07}, .len = 2},                    //   REPORT_ID (7)
    {.buf = {0x09, 0x20}, .len = 2},                    //   USAGE (Stylus)
    {.buf = {0xa1, 0x00}, .len = 2},                    //   COLLECTION (Physical)
    {.buf = {0x09, 0x42}, .len = 2},                    //     USAGE (Tip Switch)
    {.buf = {0x09, 0x44}, .len = 2},                    //     USAGE (Barrel Switch)
    {.buf = {0x09, 0x45}, .len = 2},                    //     USAGE (Eraser)
    {.buf = {0x15, 0x00}, .len = 2},                    //     LOGICAL_MINIMUM (0)
    {.buf = {0x25, 0x01}, .len = 2},                    //     LOGICAL_MAXIMUM (1)
    {.buf = {0x75, 0x01}, .len = 2},                    //     REPORT_SIZE (1)
    {.buf = {0x95, 0x03}, .len = 2},                    //     REPORT_COUNT (3)
    {.buf = {0x81, 0x02}, .len = 2},                    //     INPUT (Data,Var,Abs)
    {.buf = {0x95, 0x03}, .len = 2},                    //     REPORT_COUNT (3)
    {.buf = {0x81, 0x03}, .len = 2},                    //     INPUT (Cnst,Var,Abs)
    {.buf = {0x09, 0x32}, .len = 2},                    //     USAGE (In Range)
    {.buf = {0x95, 0x01}, .len = 2},                    //     REPORT_COUNT (1)
    {.buf = {0x81, 0x02}, .len = 2},                    //     INPUT (Data,Var,Abs)
    {.buf = {0x95, 0x01}, .len = 2},                    //     REPORT_COUNT (1)
    {.buf = {0x81, 0x03}, .len = 2},                    //     INPUT (Cnst,Var,Abs)
    {.buf = {0x05, 0x01}, .len = 2},                    //     USAGE_PAGE (Generic Desktop)
    {.buf = {0x09, 0x30}, .len = 2},                    //     USAGE (X)
    {.buf = {0x75, 0x10}, .len = 2},                    //     REPORT_SIZE (16)
    {.buf = {0x95, 0x01}, .len = 2},                    //     REPORT_COUNT (1)
    {.buf = {0xa4}, .len = 1},                          //     PUSH
    {.buf = {0x55, 0x0d}, .len = 2},                    //     UNIT_EXPONENT (-3)
    {.buf = {0x65, 0x33}, .len = 2},                    //     UNIT (Eng Lin:0x33)
    {.buf = {0x35, 0x00}, .len = 2},                    //     PHYSICAL_MINIMUM (0)
    {.buf = {0x46, 0x40, 0x1f}, .len = 3},              //     PHYSICAL_MAXIMUM (8000)
    {.buf = {0x26, 0x80, 0x3e}, .len = 3},              //     LOGICAL_MAXIMUM (16000)
    {.buf = {0x81, 0x02}, .len = 2},                    //     INPUT (Data,Var,Abs)
    {.buf = {0x09, 0x31}, .len = 2},                    //     USAGE (Y)
    {.buf = {0x46, 0x70, 0x17}, .len = 3},              //     PHYSICAL_MAXIMUM (6000)
    {.buf = {0x26, 0xe0, 0x2e}, .len = 3},              //     LOGICAL_MAXIMUM (12000)
    {.buf = {0x81, 0x02}, .len = 2},                    //     INPUT (Data,Var,Abs)
    {.buf = {0xb4}, .len = 1},                          //     POP
    {.buf = {0x05, 0x0d}, .len = 2},                    //     USAGE_PAGE (Digitizers)
    {.buf = {0x09, 0x30}, .len = 2},                    //     USAGE (Tip Pressure)
    {.buf = {0x26, 0xff, 0x03}, .len = 3},              //     LOGICAL_MAXIMUM (1023)
    {.buf = {0x81, 0x02}, .len = 2},                    //     INPUT (Data,Var,Abs)
    {.buf = {0x75, 0x10}, .len = 2},                    //     REPORT_SIZE (16)
    {.buf = {0xc0}, .len = 1},                          //   END_COLLECTION
    {.buf = {0xc0}, .len = 1},                          // END_COLLECTION
    {.buf = {0x05, 0x01}, .len = 2},                    // USAGE_PAGE (Generic Desktop)
    {.buf = {0x09, 0x02}, .len = 2},                    // USAGE (Mouse)
    {.buf = {0xa1, 0x01}, .len = 2},                    // COLLECTION (Application)
    {.buf = {0x85, 0x08}, .len = 2},                    //   REPORT_ID (8)
    {.buf = {0x09, 0x01}, .len = 2},                    //   USAGE (Pointer)
    {.buf = {0xa1, 0x00}, .len = 2},                    //   COLLECTION (Physical)
    {.buf = {0x05, 0x09}, .len = 2},                    //     USAGE_PAGE (Button)
    {.buf = {0x19, 0x01}, .len = 2},                    //     USAGE_MINIMUM (Undefined)
    {.buf = {0x29, 0x03}, .len = 2},                    //     USAGE_MAXIMUM (Undefined)
    {.buf = {0x15, 0x00}, .len = 2},                    //     LOGICAL_MINIMUM (0)
    {.buf = {0x25, 0x01}, .len = 2},                    //     LOGICAL_MAXIMUM (1)
    {.buf = {0x95, 0x03}, .len = 2},                    //     REPORT_COUNT (3)
    {.buf = {0x75, 0x01}, .len = 2},                    //     REPORT_SIZE (1)
    {.buf = {0x81, 0x02}, .len = 2},                    //     INPUT (Data,Var,Abs)
    {.buf = {0x95, 0x05}, .len = 2},                    //     REPORT_COUNT (5)
    {.buf = {0x81, 0x01}, .len = 2},                    //     INPUT (Cnst,Ary,Abs)
    {.buf = {0x05, 0x01}, .len = 2},                    //     USAGE_PAGE (Generic Desktop)
    {.buf = {0x09, 0x30}, .len = 2},                    //     USAGE (X)
    {.buf = {0x09, 0x31}, .len = 2},                    //     USAGE (Y)
    {.buf = {0x09, 0x38}, .len = 2},                    //     USAGE (Wheel)
    {.buf = {0x09, 0x00}, .len = 2},                    //     USAGE (Undefined)
    {.buf = {0x15, 0x81}, .len = 2},                    //     LOGICAL_MINIMUM (-127)
    {.buf = {0x25, 0x7f}, .len = 2},                    //     LOGICAL_MAXIMUM (127)
    {.buf = {0x75, 0x08}, .len = 2},                    //     REPORT_SIZE (8)
    {.buf = {0x95, 0x04}, .len = 2},                    //     REPORT_COUNT (4)
    {.buf = {0x81, 0x06}, .len = 2},                    //     INPUT (Data,Var,Rel)
    {.buf = {0xc0}, .len = 1},                          //   END_COLLECTION
    {.buf = {0xc0}, .len = 1},                          // END_COLLECTION
    {.buf = {0x05, 0x01}, .len = 2},                    // USAGE_PAGE (Generic Desktop)
    {.buf = {0x09, 0x02}, .len = 2},                    // USAGE (Mouse)
    {.buf = {0xa1, 0x01}, .len = 2},                    // COLLECTION (Application)
    {.buf = {0x85, 0x09}, .len = 2},                    //   REPORT_ID (9)
    {.buf = {0x09, 0x01}, .len = 2},                    //   USAGE (Pointer)
    {.buf = {0xa1, 0x00}, .len = 2},                    //   COLLECTION (Physical)
    {.buf = {0x05, 0x09}, .len = 2},                    //   USAGE_PAGE (Button)
    {.buf = {0x19, 0x01}, .len = 2},                    //   USAGE_MINIMUM (Button 1)
    {.buf = {0x29, 0x03}, .len = 2},                    //   USAGE_MAXIMUM (Button 3)
    {.buf = {0x15, 0x00}, .len = 2},                    //   LOGICAL_MINIMUM (0)
    {.buf = {0x25, 0x01}, .len = 2},                    //   LOGICAL_MAXIMUM (1)
    {.buf = {0x95, 0x03}, .len = 2},                    //   REPORT_COUNT (3)
    {.buf = {0x75, 0x01}, .len = 2},                    //     REPORT_SIZE (1)
    {.buf = {0x81, 0x02}, .len = 2},                    //     INPUT (Data,Var,Abs)
    {.buf = {0x95, 0x05}, .len = 2},                    //   REPORT_COUNT (5)
    {.buf = {0x81, 0x01}, .len = 2},                    //     INPUT (Cnst,Ary,Abs)
    {.buf = {0x05, 0x01}, .len = 2},                    //   USAGE_PAGE (Generic Desktop)
    {.buf = {0x09, 0x30}, .len = 2},                    //   USAGE (X)
    {.buf = {0x09, 0x31}, .len = 2},                    //   USAGE (Y)
    {.buf = {0x15, 0x00}, .len = 2},                    //   LOGICAL_MINIMUM (0)
    {.buf = {0x26, 0xff, 0x7f}, .len = 3},              //   LOGICAL_MAXIMUM (32767)
    {.buf = {0x35, 0x00}, .len = 2},                    //   PHYSICAL_MINIMUM (0)
    {.buf = {0x46, 0xff, 0x7f}, .len = 3},              //   PHYSICAL_MAXIMUM (32767)
    {.buf = {0x95, 0x02}, .len = 2},                    //   REPORT_COUNT (2)
    {.buf = {0x75, 0x10}, .len = 2},                    //   REPORT_SIZE (16)
    {.buf = {0x81, 0x02}, .len = 2},                    //     INPUT (Data,Var,Abs)
    {.buf = {0x05, 0x0d}, .len = 2},                    //     USAGE_PAGE (Digitizers)
    {.buf = {0x09, 0x30}, .len = 2},                    //     USAGE (Tip Pressure)
    {.buf = {0x26, 0xff, 0x03}, .len = 3},              //   LOGICAL_MAXIMUM (1023)
    {.buf = {0x95, 0x01}, .len = 2},                    //   REPORT_COUNT (1)
    {.buf = {0x75, 0x10}, .len = 2},                    //   REPORT_SIZE (16)
    {.buf = {0x81, 0x02}, .len = 2},                    //   INPUT (Data,Var,Abs)
    {.buf = {0xc0}, .len = 1},                          //   END_COLLECTION
    {.buf = {0xc0}, .len = 1},                          // END_COLLECTION
    {.len = 0}
};


#define ERR(_fmt, _args...) fprintf(stderr, _fmt "\n", ##_args)

#define ERR_CLNP(_fmt, _args...) \
    do {                            \
        ERR(_fmt, ##_args);         \
        goto cleanup;               \
    } while (0)

int
main(int argc, char **argv)
{
    bool                result          = 1;
    const item_desc    *orig_item;

    hidrd_snk          *snk             = NULL;
    char               *test_xml_buf    = NULL;
    size_t              test_xml_len    = 0;
    char               *err             = NULL;

    (void)argc;
    (void)argv;

    if (!hidrd_fmt_init(&hidrd_xml))
        ERR_CLNP("Failed to initialize XML format support");

    /*
     * Write report descriptor to an XML sink
     */
    snk = hidrd_snk_new(hidrd_xml.snk, &err,
                        (void **)&test_xml_buf, &test_xml_len,
                        true, HIDRD_XML_SCHEMA_PATH);
    if (snk == NULL)
        ERR_CLNP("Failed to create XML sink:\n%s\n", err);
    free(err);
    err = NULL;

    for (orig_item = item_list; orig_item->len != 0; orig_item++)
        if (!hidrd_snk_put(snk, orig_item->buf))
            ERR_CLNP("Failed to put item #%zu:\n%s\n",
                     (orig_item - item_list),
                     (err = hidrd_snk_errmsg(snk)));

    if (!hidrd_snk_close(snk))
        ERR_CLNP("Failed to close the test sink:\n%s\n",
                 (err = hidrd_snk_errmsg(snk)));
    snk = NULL;

    fprintf(stderr, "%.*s", (int)test_xml_len, test_xml_buf);

    result = 0;

cleanup:

    free(err); 
    free(test_xml_buf);
    hidrd_snk_delete(snk);
    hidrd_fmt_clnp(&hidrd_xml);

    return result;
}



/** @file
 * @brief HID report descriptor - XML stream test
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
#include "hidrd/strm.h"
#include "hidrd/strm/xml.h"

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


int
main(int argc, char **argv)
{
    const item_desc    *orig_item;
    void               *orig_rd_buf;
    size_t              orig_rd_len;
    void               *p;

    hidrd_strm         *strm            = NULL;
    char               *test_xml_buf    = NULL;
    size_t              test_xml_len    = 0;

#if 0
    const hidrd_item   *test_item;
#endif

    (void)argc;
    (void)argv;

    /*
     * Generate original report descriptor
     */
    for (orig_rd_len = 0, orig_item = item_list;
         orig_item->len != 0; orig_item++)
        orig_rd_len += orig_item->len;

    orig_rd_buf = malloc(orig_rd_len);

    for (p = orig_rd_buf, orig_item = item_list;
         orig_item->len != 0;
         p += orig_item->len, orig_item++)
        memcpy(p, orig_item->buf, orig_item->len);

    /*
     * Write report descriptor to an XML stream
     */
    strm = hidrd_strm_open(&hidrd_strm_xml,
                           &test_xml_buf, &test_xml_len, true);
    if (strm == NULL)
        error(1, errno, "Failed to create XML stream");

    for (orig_item = item_list; orig_item->len != 0; orig_item++)
        if (!hidrd_strm_write(strm, orig_item->buf))
            error(1, errno, "Failed to write item #%u",
                  (orig_item - item_list));

    if (hidrd_strm_error(strm))
        error(1, 0, "The test stream has unexpected error indicator");

    hidrd_strm_close(strm);

    fprintf(stderr, "%.*s", test_xml_len, test_xml_buf);

    free(test_xml_buf);

    return 0;
}



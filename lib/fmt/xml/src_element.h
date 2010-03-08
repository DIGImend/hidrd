/** @file
 * @brief HID report descriptor - XML source - element handling
 *
 * Copyright (C) 2010 Nikolai Kondrashov
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

#ifndef __SRC_ELEMENT_H__
#define __SRC_ELEMENT_H__

#include "hidrd/fmt/xml/src.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Element processing result code */
typedef enum element_rc {
    ELEMENT_RC_ERROR,   /**< An error has occured */
    ELEMENT_RC_END,     /**< End of stream */
    ELEMENT_RC_ITEM,    /**< An item has been read */
    ELEMENT_RC_NONE,    /**< No item has been read */
} element_rc;


/**
 * Handle an element.
 *
 * @param xml_src   XML source instance; element to be processed is
 *                  xml_src->cur.
 * @param penter    Location for the "enter" flag, false by default; set to
 *                  indicate that the current element should be entered.
 *
 * @return Element processing result code.
 */
extern element_rc element(hidrd_xml_src_inst *xml_src, bool *penter);


/**
 * Handle the exit from an element.
 *
 * @param xml_src   XML source instance; element the caller is about to exit
 *                  is xml_src->prnt.
 *
 * @return Element processing result code.
 */
extern element_rc element_exit(hidrd_xml_src_inst *xml_src);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __SRC_ELEMENT_H__ */

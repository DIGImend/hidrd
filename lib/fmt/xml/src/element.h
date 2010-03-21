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

#ifndef __XML_SRC_ELEMENT_H__
#define __XML_SRC_ELEMENT_H__

#include "hidrd/fmt/xml/src.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Element processing result code */
typedef enum xml_src_element_rc {
    XML_SRC_ELEMENT_RC_ERROR,   /**< An error has occured */
    XML_SRC_ELEMENT_RC_END,     /**< End of stream */
    XML_SRC_ELEMENT_RC_ITEM,    /**< An item has been read */
    XML_SRC_ELEMENT_RC_NONE,    /**< No item has been read */
} xml_src_element_rc;


/**
 * Prototype for an element processing function.
 *
 * @param item  Output item location.
 * @param e     Element to handle (src->cur - the encountered element).
 * 
 * @return Element processing result code.
 */
typedef xml_src_element_rc xml_src_element_fn(hidrd_item   *item,
                                              xmlNodePtr    e);

/**
 * Generate element handling function prototype.
 *
 * @param _name Element name.
 *
 * @return Element processing result code.
 */
#define ELEMENT(_name) \
    xml_src_element_rc                                      \
    xml_src_element_##_name(hidrd_item *item, xmlNodePtr e)

/**
 * Generate element exit handling function prototype.
 *
 * @param _name Element name.
 *
 * @return Element processing result code.
 */
#define ELEMENT_EXIT(_name) \
    xml_src_element_rc                                              \
    xml_src_element_##_name##_exit(hidrd_item *item, xmlNodePtr e)

/**
 * Generate element property variable declarations.
 *
 * @param _type Internal representation type name (without hidrd_ prefix).
 * @param _name Property name token.
 */
#define ELEMENT_PROP_DECL(_type, _name) \
    char           *_name##_str = NULL; \
    hidrd_##_type   _name

/**
 * Generate element property value retrieval.
 *
 * @param _type Internal representation type name (without hidrd_ prefix).
 * @param _name Property name token.
 * @param _repr Representation token (e.g. dec, or token_or_hex).
 */
#define ELEMENT_PROP_RETR(_type, _name, _repr) \
    do {                                                        \
        _name##_str = (char *)xmlGetProp(e, BAD_CAST #_name);   \
        if (_name##_str == NULL)                                \
            goto cleanup;                                       \
        if (!hidrd_##_type##_from_##_repr(&_name, _name##_str)) \
            goto cleanup;                                       \
    } while (0)

/**
 * Generate element property cleanup code (a call to xmlFree).
 *
 * @param _name Property name token.
 */
#define ELEMENT_PROP_CLNP(_name) \
    xmlFree(_name##_str)

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
extern xml_src_element_rc xml_src_element(hidrd_xml_src_inst   *xml_src,
                                          bool                 *penter);


/**
 * Handle the exit from an element.
 *
 * @param xml_src   XML source instance; element the caller is about to exit
 *                  is xml_src->prnt.
 *
 * @return Element processing result code.
 */
extern xml_src_element_rc xml_src_element_exit(
                                            hidrd_xml_src_inst  *xml_src);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __XML_SRC_ELEMENT_H__ */

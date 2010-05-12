/** @file
 * @brief HID report descriptor - XML format - internal declarations
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
 * @(#) $Id: element.h 400 2010-05-02 11:23:21Z spb_nick $
 */

#ifndef __XML_H__
#define __XML_H__

#include <libxml/globals.h>
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void xml_error(void *ctx, const char *fmt, ...);

#if HAVE_DECL_XMLSTRUCTUREDERRORCONTEXT
#define XML_ERR_FUNC_BACKUP_DECL \
    xmlGenericErrorFunc     xmlGEBackup  = xmlGenericError;             \
    void                   *xmlGECBackup = xmlGenericErrorContext;      \
    xmlStructuredErrorFunc  xmlSEBackup  = xmlStructuredError;          \
    void                   *xmlSECBackup = xmlStructuredErrorContext
#else /* HAVE_DECL_XMLSTRUCTUREDERRORCONTEXT */
/*
 * Older versions of libxml2 use and set generic error context for
 * structured errors.
 */
#define XML_ERR_FUNC_BACKUP_DECL \
    xmlGenericErrorFunc     xmlGEBackup  = xmlGenericError;             \
    void                   *xmlGECBackup = xmlGenericErrorContext;      \
    xmlStructuredErrorFunc  xmlSEBackup  = xmlStructuredError;          \
    void                   *xmlSECBackup = xmlGenericError
#endif /* ! HAVE_DECL_XMLSTRUCTUREDERRORCONTEXT */

#define XML_ERR_FUNC_SET(_ctx) \
    do {                                                                \
        /*                                                              \
         * NOTE: the order of calls is important for the older libxml2, \
         * which doesn't have separate structured error context.        \
         */                                                             \
        xmlSetStructuredErrorFunc(NULL, NULL);                          \
        xmlSetGenericErrorFunc(_ctx, xml_error);                        \
    } while (0)

#define XML_ERR_FUNC_RESTORE \
    do {                                                        \
        xmlSetStructuredErrorFunc(xmlSECBackup, xmlSEBackup);   \
        xmlSetGenericErrorFunc(xmlGECBackup, xmlGEBackup);      \
    } while (0)

#define XML_ERR(_fmt, _args...) \
    xmlGenericError(xmlGenericErrorContext, _fmt, ##_args)

#define XML_ERR_CLNP(_fmt, _args...) \
    do {                                \
        XML_ERR(_fmt, ##_args);         \
        goto cleanup;                   \
    } while (0)


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __XML_H__ */


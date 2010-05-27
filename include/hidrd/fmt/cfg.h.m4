dnl
dnl hidrd/fmt/cfg.h template.
dnl
dnl Copyright (C) 2010 Nikolai Kondrashov
dnl
dnl This file is part of hidrd.
dnl
dnl Hidrd is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.
dnl
dnl Hidrd is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with hidrd; if not, write to the Free Software
dnl Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
dnl
dnl @(#) $Id$
dnl
`/*
 * vim:nomodifiable
 *
 * ********** DO NOT EDIT *************
 * This file is generated from cfg.h.m4
 * ************************************
 */
/** @file
 * @brief HID report descriptor - formats - configuration
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
 */

#ifndef __HIDRD_FMT_CFG_H__
#define __HIDRD_FMT_CFG_H__

/** Defined if XML format is supported */
#'WITH_XML_DIRECTIVE()` HIDRD_FMT_WITH_XML

/** Defined if specification example format is supported */
#'WITH_SPEC_DIRECTIVE()` HIDRD_FMT_WITH_SPEC

/** Defined if source code format is supported */
#'WITH_CODE_DIRECTIVE()` HIDRD_FMT_WITH_CODE

#endif /* __HIDRD_FMT_CFG_H__ */'

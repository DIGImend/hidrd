dnl
dnl hidrd/cfg.h template.
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
 * @brief HID report descriptor - configuration
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

#ifndef __HIDRD_CFG_H__
#define __HIDRD_CFG_H__

/** Defined if options library is built */
#'WITH_OPT_DIRECTIVE()` HIDRD_WITH_OPT

/** Defined if tokens should be supported across all relevant libraries */
#'WITH_TOKENS_DIRECTIVE()` HIDRD_WITH_TOKENS

/** Defined if names should be supported across all relevant libraries */
#'WITH_NAMES_DIRECTIVE()` HIDRD_WITH_NAMES

#endif /* __HIDRD_CFG_H__ */'

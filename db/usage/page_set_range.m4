dnl
dnl Usage page set range table.
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
dnl
dnl PAGE_SET_RANGE - describe a page set range.
dnl Arguments:
dnl     * Set token (lowercase, underscores as spaces)
dnl     * Minimum hexadecimal page ID (four digits, uppercase)
dnl     * Maximum hexadecimal page ID (four digits, uppercase)
dnl
PAGE_SET_RANGE(`top_level',   `0001',   `001F')dnl
PAGE_SET_RANGE(`reserved',    `000E',   `000E')dnl
PAGE_SET_RANGE(`reserved',    `0011',   `0013')dnl
PAGE_SET_RANGE(`reserved',    `0015',   `003F')dnl
PAGE_SET_RANGE(`reserved',    `0041',   `007F')dnl
PAGE_SET_RANGE(`reserved',    `0083',   `0083')dnl
PAGE_SET_RANGE(`reserved',    `0086',   `008B')dnl
PAGE_SET_RANGE(`reserved',    `008F',   `008F')dnl
PAGE_SET_RANGE(`reserved',    `0092',   `FEFF')dnl
PAGE_SET_RANGE(`monitor',     `0080',   `0083')dnl
PAGE_SET_RANGE(`power',       `0084',   `0087')dnl
PAGE_SET_RANGE(`pos',         `008C',   `008F')dnl
PAGE_SET_RANGE(`vendor',      `FF00',   `FFFF')dnl

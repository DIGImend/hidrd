dnl
dnl Digitizer usage page ID set ranges.
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
dnl ID_SET_POINT - describe a usage ID set item.
dnl Arguments:
dnl     * Set token (non-capitalized, underscores for spaces)
dnl     * Hexadecimal usage ID (four digits, uppercase)
dnl
define(`ID_SET_POINT', `ID_SET_RANGE(`$1', `$2', `$2')')dnl
dnl
dnl ID_SET_RANGE - describe a usage ID set range.
dnl Arguments:
dnl     * Set token (non-capitalized, underscores for spaces)
dnl     * Minimum hexadecimal usage ID (four digits, uppercase)
dnl     * Maximum hexadecimal usage ID (four digits, uppercase)
dnl
ID_SET_RANGE(`reserved',    `0010', `001F')dnl
ID_SET_RANGE(`reserved',    `0025', `002F')dnl
ID_SET_RANGE(`reserved',    `004A', `0050')dnl
ID_SET_RANGE(`reserved',    `006D', `006F')dnl
ID_SET_RANGE(`reserved',    `0078', `007F')dnl
ID_SET_RANGE(`reserved',    `0086', `008F')dnl
ID_SET_RANGE(`reserved',    `0099', `009F')dnl
ID_SET_RANGE(`reserved',    `00A6', `FFFF')dnl

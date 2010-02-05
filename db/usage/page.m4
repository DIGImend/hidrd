dnl
dnl Known usage page table.
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
dnl PAGE_ID_NUM - calculate number of usage ID's in a page.
dnl Arguments:
dnl     * Page token (lowercase, underscores as spaces)
dnl
define(`PAGE_ID_NUM',
`pushdef(`$1_id_num', 0)dnl
pushdef(`ID', `define(`$1_id_num', incr($1_id_num))')dnl
sinclude(`db/usage/id_$1.m4')dnl
popdef(`ID')dnl
$1_id_num`'dnl
popdef(`$1_id_num')')dnl
dnl
dnl
dnl PAGE - describe a delegated page:
dnl Arguments:
dnl     * Hexadecimal page ID (four digits, uppercase)
dnl     * Page token (lowercase, underscores as spaces)
dnl     * Page description (non-capitalized)
dnl
PAGE(`0001',    `desktop',          `generic desktop controls')dnl
PAGE(`0002',    `simulation',       `simulation controls')dnl
PAGE(`0003',    `vr',               `virtual reality controls')dnl
PAGE(`0004',    `sport',            `sport controls')dnl
PAGE(`0005',    `game',             `game controls')dnl
PAGE(`0006',    `device',           `generic device controls')dnl
PAGE(`0007',    `keyboard',         `keyboard/keypad')dnl
PAGE(`0008',    `led',              `LEDs')dnl
PAGE(`0009',    `button',           `button')dnl
PAGE(`000A',    `ordinal',          `ordinal')dnl
PAGE(`000B',    `telephony',        `telephony')dnl
PAGE(`000C',    `consumer',         `consumer')dnl
PAGE(`000D',    `digitizer',        `digitizer')dnl
PAGE(`000F',    `pid',              `physical interface device')dnl
PAGE(`0010',    `unicode',          `Unicode')dnl
PAGE(`0014',    `alnum_display',    `alphanumeric display')dnl
PAGE(`0040',    `medical',          `medical')dnl
PAGE(`0080',    `monitor',          `USB monitor')dnl
PAGE(`0081',    `monitor_enum',     `monitor enumerated values')dnl
PAGE(`0082',    `monitor_vesa_vcp', `monitor VESA virtual control panel')dnl
PAGE(`0084',    `power_device',     `power device')dnl
PAGE(`0085',    `power_batsys',     `power battery system')dnl
PAGE(`008C',    `pos_bcs',          `POS devices - bar code scanner')dnl
PAGE(`008D',    `pos_scale',        `POS devices - scale')dnl
PAGE(`008E',    `pos_msr',          `POS devices - magnetic stripe reader')dnl
PAGE(`0090',    `camera',           `camera control')dnl
PAGE(`0091',    `arcade',           `arcade')dnl

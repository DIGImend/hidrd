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
dnl PAGE - describe a delegated page:
dnl Arguments:
dnl     * Hexadecimal page ID (four digits, uppercase)
dnl     * Page token (lowercase, underscores as spaces)
dnl     * Page description (non-capitalized)
dnl
PAGE(`0001',    `desktop',          `generic desktop controls')
PAGE(`0002',    `simulation',       `simulation controls')
PAGE(`0003',    `vr',               `virtual reality controls')
PAGE(`0004',    `sport',            `sport controls')
PAGE(`0005',    `game',             `game controls')
PAGE(`0006',    `device',           `generic device controls')
PAGE(`0007',    `keyboard',         `generic device controls')
PAGE(`0008',    `led',              `LEDs')
PAGE(`0009',    `button',           `button')
PAGE(`000A',    `ordinal',          `ordinal')
PAGE(`000B',    `telephony',        `telephony')
PAGE(`000C',    `consumer',         `consumer')
PAGE(`000D',    `digitizer',        `digitizer')
PAGE(`000F',    `pid',              `physical interface device')
PAGE(`0010',    `unicode',          `Unicode')
PAGE(`0014',    `alnum_display',    `alphanumeric display')
PAGE(`0040',    `medical',          `medical')
PAGE(`0080',    `monitor',          `USB monitor')
PAGE(`0081',    `monitor_enum',     `monitor enumerated values')
PAGE(`0082',    `monitor_vesa_vcp', `monitor VESA virtual control panel')
PAGE(`0084',    `power_device',     `power device')
PAGE(`0085',    `power_batsys',     `power battery system')
PAGE(`008C',    `pos_bcs',          `POS devices - bar code scanner')
PAGE(`008D',    `pos_scale',        `POS devices - scale')
PAGE(`008E',    `pos_msr',          `POS devices - magnetic stripe reader')
PAGE(`0090',    `camera',           `camera control')
PAGE(`0091',    `arcade',           `arcade')

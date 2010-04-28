dnl
dnl Usage page set table.
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
dnl PAGE_SET_RANGE_NUM - calculate number of set ranges.
dnl Arguments:
dnl     * Set token (non-capitalized, underscores for spaces).
dnl
define(`PAGE_SET_RANGE_NUM',
`pushdef(`range_num', 0)dnl
pushdef(`PAGE_SET_RANGE',
        `ifelse($'`1, $1, `define(`range_num', incr(range_num))')')dnl
include(`db/usage/page_set_range.m4')dnl
popdef(`PAGE_SET_RANGE')dnl
range_num`'dnl
popdef(`range_num')')dnl
dnl
dnl
dnl PAGE_SET_RANGE_CHECK - generate a set range check code.
dnl Arguments:
dnl     * Set token (non-capitalized, underscores for spaces).
dnl
define(`PAGE_SET_RANGE_CHECK',
`pushdef(`PAGE_SET_RANGE',
`ifelse('`$'`1, `$1',
        ifelse(eval(0x'`$'`2), eval(0x'`$'`3),dnl
    if (page == 0x'`$'`2)
        return true;
,dnl
    if (page >= 0x'`$'`2 && page <= 0x'`$'`3)
        return true;
))')dnl
include(`db/usage/page_set_range.m4')dnl
    return false;dnl
popdef(`PAGE_SET_RANGE')dnl
')dnl
dnl
dnl
dnl PAGE_SET - describe a page set.
dnl Arguments:
dnl     * Set token (non-capitalized, underscores for spaces)
dnl     * Set description (non-capitalized)
dnl
PAGE_SET(`reserved',  `reserved')dnl
PAGE_SET(`monitor',   `monitor page')dnl
PAGE_SET(`power',     `power page')dnl
PAGE_SET(`POS',       `POS page')dnl
PAGE_SET(`vendor',    `vendor-defined')dnl

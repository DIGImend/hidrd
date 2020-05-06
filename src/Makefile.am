#
# Copyright (C) 2010 Nikolai Kondrashov
#
# This file is part of hidrd.
#
# Hidrd is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# Hidrd is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with hidrd; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

bin_PROGRAMS =

if ENABLE_HIDRD_CONVERT

bin_PROGRAMS += hidrd-convert

hidrd_convert_SOURCES = hidrd-convert.c
hidrd_convert_LDADD = \
    ../lib/util/libhidrd_util.la    \
    ../lib/opt/libhidrd_opt.la      \
    ../lib/strm/libhidrd_strm.la    \
    ../lib/fmt/libhidrd_fmt.la

if ENABLE_FMT_XML
hidrd_convert_CFLAGS = @LIBXML2_CFLAGS@
endif

if ENABLE_OBSTACK
hidrd_convert_LDADD += ../lib/obstack/libhidrd_obstack.la
endif

endif	# ENABLE_HIDRD_CONVERT

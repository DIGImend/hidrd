hidrd_fmtdir = $(includedir)/hidrd/fmt#### Compiler and tool definitions shared by all build targets #####
#
# Copyright (C) 2016 Anthony Campbell
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


lib_LTLIBRARIES = libhidrd_adr.la

hidrd_adrdir = $(includedir)/hidrd/adr

libhidrd_adr_la_SOURCES = \
    adr.c


libhidrd_adr_la_LIBADD = \
    ../util/libhidrd_util.la    \
    ../opt/libhidrd_opt.la      \
    ../strm/libhidrd_strm.la    \
    ../fmt/libhidrd_fmt.la

if ENABLE_FMT_XML
libhidrd_adr_la_CFLAGS = @LIBXML2_CFLAGS@
endif


if ADD_OBSTACK
libhidrd_adr_la_LDFLAGS = -no-undefined
endif


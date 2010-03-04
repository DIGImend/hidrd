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

SUBDIRS = src snk

lib_LTLIBRARIES = libhidrd_strm.la

libhidrd_strm_la_SOURCES = 

libhidrd_strm_la_LIBADD = \
    ../item/libhidrd_item.la    \
    ../opt/libhidrd_opt.la      \
    snk/libhidrd_strm_snk.la    \
    src/libhidrd_strm_src.la

TESTS = 

bin_PROGRAMS =
check_PROGRAMS = $(TESTS)

if ENABLE_TESTS_INSTALL
bin_PROGRAMS += $(TESTS)
endif

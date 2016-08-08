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

lib_LTLIBRARIES = libhidrd_util.la

libhidrd_util_la_SOURCES = \
    bool.c                  \
    buf.c                   \
    char.c                  \
    dec.c                   \
    fd.c                    \
    fmt.c                   \
    hex.c                   \
    num.c                   \
    str.c                   \
    ttbl.c                  \
    unit.c

if ENABLE_MINGW_OSTACK
libhidrd_util_la_SOURCES += obstack.c
libhidrd_util_la_LDFLAGS = -no-undefined
endif

if ENABLE_TOKENS
libhidrd_util_la_SOURCES += tkn.c
endif

bin_PROGRAMS =
check_PROGRAMS = hidrd_num_test hidrd_ttbl_test

hidrd_num_test_SOURCES = num_test.c
hidrd_num_test_LDADD = $(lib_LTLIBRARIES)

hidrd_ttbl_test_SOURCES = ttbl_test.c
hidrd_ttbl_test_LDADD = $(lib_LTLIBRARIES)

TESTS = hidrd_num_test hidrd_ttbl_test

if ENABLE_TESTS_INSTALL
bin_PROGRAMS += $(check_PROGRAMS)
endif

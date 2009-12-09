# Copyright (C) 2009 Nikolai Kondrashov
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

lib_LTLIBRARIES = libhidrd_item.la

libhidrd_item_la_SOURCES = \
    any.c                   \
    basic.c                 \
    pfx.c                   \
    short.c

check_PROGRAMS = any_test
TESTS = any_test
# Uncomment to have the tests installed
# bin_PROGRAMS = $(TESTS)

any_test_SOURCES = any_test.c
any_test_LDADD = $(lib_LTLIBRARIES)

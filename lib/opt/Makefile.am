#
# Copyright (C) 2009-2010 Nikolai Kondrashov
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

lib_LTLIBRARIES = libhidrd_opt.la

libhidrd_opt_la_SOURCES = \
    inst.c                  \
    list.c                  \
    name_tkn.c              \
    spec.c                  \
    spec_list.c             \
    tkn.c                   \
    tkns.c                  \
    tkns_list.c             \
    type.c                  \
    value_tkn.c

libhidrd_opt_la_LIBADD = \
    ../util/libhidrd_util.la

TESTS = hidrd_opt_test

hidrd_opt_test_SOURCES = test.c
hidrd_opt_test_LDADD = $(lib_LTLIBRARIES)


bin_PROGRAMS =
check_PROGRAMS = $(TESTS)

if ENABLE_TESTS_INSTALL
bin_PROGRAMS += $(TESTS)
endif

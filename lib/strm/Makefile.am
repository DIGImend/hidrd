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

lib_LTLIBRARIES = libhidrd_strm.la

libhidrd_strm_la_SOURCES = \
    inst.c                  \
    mem.c                   \
    type.c

libhidrd_strm_la_LIBADD = ../item/libhidrd_item.la

check_PROGRAMS = mem_test
TESTS = mem_test

mem_test_SOURCES = mem_test.c
mem_test_LDADD = $(lib_LTLIBRARIES)

if WITH_LIBXML2
libhidrd_strm_la_SOURCES += xml.c xml_read.c xml_write.c
libhidrd_strm_la_CFLAGS = @LIBXML2_CFLAGS@
libhidrd_strm_la_LDFLAGS = @LIBXML2_LIBS@
noinst_HEADERS = xml.h

check_PROGRAMS += xml_test
TESTS += xml_test

xml_test_SOURCES = xml_test.c
xml_test_LDADD = $(lib_LTLIBRARIES)
endif

# Uncomment to have the tests installed
# bin_PROGRAMS = $(TESTS)

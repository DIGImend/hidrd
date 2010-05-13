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

SUBDIRS = natv read_test_data write_test_data

lib_LTLIBRARIES = libhidrd_fmt.la

noinst_HEADERS =

libhidrd_fmt_la_SOURCES = \
    inst.c                  \
    list.c                  \
    natv.c

libhidrd_fmt_la_LIBADD = \
    ../strm/libhidrd_strm.la    \
    ../util/libhidrd_util.la    \
    natv/libhidrd_natv.la

TESTS = hidrd_natv_test
TESTS_ENVIRONMENT = PATH="$$PATH:$(builddir):$(srcdir)" \
					HIDRD_READ_TEST_DATA="$(srcdir)/read_test_data" \
					HIDRD_WRITE_TEST_DATA="$(srcdir)/write_test_data" \
					HIDRD_XML_READ_TEST_SCHEMA="$(srcdir)/xml/hidrd.xsd"

bin_PROGRAMS =
bin_SCRIPTS =
check_PROGRAMS = hidrd_natv_test hidrd_read hidrd_write
check_SCRIPTS = hidrd_read_test hidrd_write_test
dist_noinst_SCRIPTS = $(check_SCRIPTS)

hidrd_natv_test_SOURCES = natv_test.c
hidrd_natv_test_LDADD = ../strm/libhidrd_strm.la $(lib_LTLIBRARIES)

hidrd_read_CFLAGS =
hidrd_read_SOURCES = read.c
hidrd_read_LDADD = \
    $(lib_LTLIBRARIES)          \
    ../strm/libhidrd_strm.la    \
    ../item/libhidrd_item.la    \
    ../util/libhidrd_util.la

hidrd_write_CFLAGS =
hidrd_write_SOURCES = write.c
hidrd_write_LDADD = \
    $(lib_LTLIBRARIES)          \
    ../strm/libhidrd_strm.la    \
    ../item/libhidrd_item.la    \
    ../util/libhidrd_util.la

if ENABLE_FMT_XML

SUBDIRS += xml

noinst_HEADERS += xml.h

libhidrd_fmt_la_SOURCES += xml.c
libhidrd_fmt_la_CFLAGS = @LIBXML2_CFLAGS@
libhidrd_fmt_la_LDFLAGS = @LIBXML2_LIBS@
libhidrd_fmt_la_LIBADD += xml/libhidrd_xml.la

check_SCRIPTS += hidrd_xml_read_test hidrd_xml_write_test
check_PROGRAMS += hidrd_xml_test
TESTS += hidrd_xml_test hidrd_xml_read_test hidrd_xml_write_test

hidrd_xml_test_CFLAGS = @LIBXML2_CFLAGS@
hidrd_xml_test_SOURCES = xml_test.c
hidrd_xml_test_LDADD = $(lib_LTLIBRARIES) ../strm/libhidrd_strm.la

hidrd_read_CFLAGS += @LIBXML2_CFLAGS@
hidrd_write_CFLAGS += @LIBXML2_CFLAGS@

endif	# ENABLE_FMT_XML

if ENABLE_FMT_SPEC

SUBDIRS += spec
check_SCRIPTS += hidrd_spec_read_test hidrd_spec_write_test
TESTS += hidrd_spec_read_test hidrd_spec_write_test
libhidrd_fmt_la_SOURCES += spec.c
libhidrd_fmt_la_LIBADD += spec/libhidrd_spec.la

endif	# ENABLE_FMT_SPEC


if ENABLE_TESTS_INSTALL
bin_PROGRAMS += $(check_PROGRAMS)
bin_SCRIPTS += $(check_SCRIPTS)
endif

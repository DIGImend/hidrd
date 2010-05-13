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

SUBDIRS = snk src

noinst_LTLIBRARIES = libhidrd_xml.la

libhidrd_xml_la_SOURCES = \
    snk.c                   \
    src.c

libhidrd_xml_la_LIBADD = \
    snk/libhidrd_xml_snk.la \
    src/libhidrd_xml_src.la

libhidrd_xml_la_CFLAGS = @LIBXML2_CFLAGS@
libhidrd_xml_la_LDFLAGS = @LIBXML2_LIBS@

schemadir = $(datadir)/xml/schema

dist_schema_DATA = hidrd.xsd


#
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

hidrd_usagedir = $(includedir)/hidrd/usage

%.h: %.h.m4 @top_srcdir@/m4/hidrd/*.m4 @top_srcdir@/db/usage/*.m4
	m4 -I "@top_srcdir@" $< > $@

dist_noinst_DATA = \
    all.h.m4            \
    id_desc_list.h.m4   \
    page.h.m4           \
    page_desc_list.h.m4

BUILT_SOURCES = \
    all.h               \
    id_desc_list.h      \
    page.h              \
    page_desc_list.h

CLEANFILES = $(BUILT_SOURCES)

hidrd_usage_HEADERS = \
    id.h                \
    id_desc.h           \
    page_desc.h         \
    type.h

nodist_hidrd_usage_HEADERS = \
    $(BUILT_SOURCES)


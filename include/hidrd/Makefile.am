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

SUBDIRS = util usage item

hidrddir = $(includedir)/hidrd

hidrd_HEADERS = \
    item.h

if ENABLE_OPT
WITH_OPT_DIRECTIVE = define
SUBDIRS += opt
hidrd_HEADERS += opt.h
else
WITH_OPT_DIRECTIVE = undef
endif

if ENABLE_TOKENS
WITH_TOKENS_DIRECTIVE = define
else
WITH_TOKENS_DIRECTIVE = undef
endif

if ENABLE_NAMES
WITH_NAMES_DIRECTIVE = define
else
WITH_NAMES_DIRECTIVE = undef
endif

if ENABLE_STRM
SUBDIRS += strm
hidrd_HEADERS += strm.h
endif

if ENABLE_FMT
SUBDIRS += fmt
hidrd_HEADERS += fmt.h
endif

cfg.h: cfg.h.m4
	m4 -DWITH_OPT_DIRECTIVE=$(WITH_OPT_DIRECTIVE) \
       -DWITH_TOKENS_DIRECTIVE=$(WITH_TOKENS_DIRECTIVE) \
       -DWITH_NAMES_DIRECTIVE=$(WITH_NAMES_DIRECTIVE) \
        $< > $@

dist_noinst_DATA = cfg.h.m4
BUILT_SOURCES = cfg.h
CLEANFILES = $(BUILT_SOURCES)
nodist_hidrd_HEADERS = $(BUILT_SOURCES)

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

check_DATA = \
    SET.bin         \
    SET.xml         \
    basic.bin       \
    basic.xml       \
    collection.bin  \
    collection.xml  \
    empty.bin       \
    empty.xml       \
    global.bin      \
    global.xml      \
    local.bin       \
    local.xml       \
    long.bin        \
    long.xml        \
    main.bin        \
    main.xml        \
    short.bin       \
    short.xml       \
    unit.bin        \
    unit.xml

if ENABLE_TESTS_INSTALL
write_test_datadir = $(pkgdatadir)/write_test_data
write_test_data_DATA = $(check_DATA)
else
dist_noinst_DATA = $(check_DATA)
endif

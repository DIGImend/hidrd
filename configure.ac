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
#
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([hidrd], [0.1])
AC_CONFIG_AUX_DIR([auxdir])
AM_INIT_AUTOMAKE([1.10.1 -Wall foreign])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])

# To have empty CFLAGS instead of undefined and '-g -O2' by default
CFLAGS=$CFLAGS
CFLAGS="-Wall -W -Os $CFLAGS"
ABS_SRCDIR=`cd ${srcdir} ; pwd`
CPPFLAGS="-DNDEBUG -I${ABS_SRCDIR}/include $CPPFLAGS"

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CONFIG_FILES([Makefile
                 include/Makefile
                 include/hidrd/Makefile
                 include/hidrd/item/Makefile
                 include/hidrd/item/pfx/Makefile
                 include/hidrd/strm/Makefile
                 
                 lib/Makefile
                 lib/item/Makefile
                 lib/strm/Makefile])
AC_OUTPUT

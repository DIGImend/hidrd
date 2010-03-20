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
#
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([hidrd], [0.2])
AC_CONFIG_AUX_DIR([auxdir])
AM_INIT_AUTOMAKE([1.9 -Wall foreign])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4/autoconf])

# To have empty CFLAGS instead of undefined and '-g -O2' by default
CFLAGS=$CFLAGS
CFLAGS="-Os -Wall -Wextra -Werror $CFLAGS"
ABS_SRCDIR=`cd ${srcdir} ; pwd`
ABS_BUILDDIR=`pwd`
CPPFLAGS="-I${ABS_BUILDDIR}/include -D_GNU_SOURCE -DNDEBUG $CPPFLAGS"
if test "$ABS_SRCDIR" != "$ABS_BUILDDIR"; then
    CPPFLAGS="-I${ABS_SRCDIR}/include $CPPFLAGS"
fi


#
# Checks for programs.
#
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LIBTOOL

#
# Checks for libraries.
#
AC_ARG_WITH(xml2-config,
            AC_HELP_STRING([--with-xml2-config=PATH],
                           [Specify xml2-config location @<:@default=$PATH@:>@]),
            [],
            [with_xml2_config=check])

XML2_CONFIG=
AS_IF([test "x$with_xml2_config" = "xcheck"],
      [AC_PATH_PROG(XML2_CONFIG, xml2-config)],
      [test "x$with_xml2_config" != "xno"],
      [XML2_CONFIG="$with_xml2_config"])

AM_CONDITIONAL([WITH_LIBXML2], [test -n "$XML2_CONFIG"])

LIBXML2_LIBS=
LIBXML2_CFLAGS=
if [test -n "$XML2_CONFIG"]; then
    $XML2_CONFIG --version >/dev/null ||
        AC_MSG_ERROR([cannot execute $XML2_CONFIG])

    LIBXML2_LIBS="`$XML2_CONFIG --libs`"
    LIBXML2_CFLAGS="`$XML2_CONFIG --cflags`"
fi
AC_SUBST(LIBXML2_LIBS)
AC_SUBST(LIBXML2_CFLAGS)

#
# Checks for features
#
AC_ARG_ENABLE(
    debug,
    AS_HELP_STRING([--enable-debug], [enable debugging features]),
    [], [enable_debug="no"])

AC_ARG_ENABLE(
    tests-install,
    AS_HELP_STRING([--enable-tests-install], [enable installation of tests]),
    [], [enable_tests_install="no"])

AC_ARG_ENABLE(
    opt,
    AS_HELP_STRING([--disable-opt],
                   [disable building options library (required by streams)]),
    [], [enable_opt="yes"])

AC_ARG_ENABLE(
    streams,
    AS_HELP_STRING([--disable-streams], [disable building stream library (required by formats)]),
    [], [enable_streams="yes"])

AC_ARG_ENABLE(
    formats,
    AS_HELP_STRING([--disable-formats], [disable building format library (required by hidrd-convert)]),
    [], [enable_formats="yes"])

AC_ARG_ENABLE(
    hidrd-convert,
    AS_HELP_STRING([--disable-hidrd-convert], [disable building hidrd-convert tool (requires formats)]),
    [], [enable_hidrd_convert="yes"])

AC_ARG_ENABLE(
    tokens,
    AS_HELP_STRING([--disable-tokens],
                   [disable tokens (required by XML format)]),
    [], [enable_tokens="yes"])

AC_ARG_ENABLE(
    names,
    AS_HELP_STRING([--disable-names],
                   [disable names (required by XML format)]),
    [], [enable_names="yes"])

AC_ARG_ENABLE(
    xml-format,
    AS_HELP_STRING(
        [--disable-xml-format],
        [disable building XML format support (requires tokens, names and libxml2)]),
    [], [enable_xml_format="yes"])

# Check for stream library dependencies
if test "$enable_streams" = "yes"; then
    if test "$enable_opt" != "yes"; then
        AC_MSG_WARN([option library is disabled, so disabling streams])
        enable_streams="no"
    fi
fi

# Check for format library dependencies
if test "$enable_formats" = "yes"; then
    if test "$enable_streams" != "yes"; then
        AC_MSG_WARN([stream library is disabled, so disabling formats])
        enable_formats="no"
    fi
fi

# Check for XML format dependencies
if test "$enable_xml_format" = "yes"; then
    if test "$enable_formats" != "yes"; then
        # Disable silently - quite obvious
        enable_xml_format="no"
    elif test "$enable_tokens" != "yes"; then
        AC_MSG_WARN([tokens are disabled, so disabling XML format])
        enable_xml_format="no"
    elif test "$enable_names" != "yes"; then
        AC_MSG_WARN([names are disabled, so disabling XML format])
        enable_xml_format="no"
    elif test -z "$XML2_CONFIG"; then
        AC_MSG_WARN([no xml2-config, so disabling XML format])
        enable_xml_format="no"
    fi
fi

# Check hidrd-convert tool dependencies
if test "$enable_hidrd_convert" = "yes"; then
    if test "$enable_formats" != "yes"; then
        AC_MSG_WARN([format library is disabled, so disabling hidrd-convert tool])
        enable_hidrd_convert="no"
    fi
fi

# Output features to automake
AM_CONDITIONAL([ENABLE_TESTS_INSTALL], [test "$enable_tests_install" = "yes"])
AM_CONDITIONAL([ENABLE_OPT], [test "$enable_opt" = "yes"])
AM_CONDITIONAL([ENABLE_STRM], [test "$enable_streams" = "yes"])
AM_CONDITIONAL([ENABLE_FMT], [test "$enable_formats" = "yes"])
AM_CONDITIONAL([ENABLE_HIDRD_CONVERT], [test "$enable_hidrd_convert" = "yes"])
AM_CONDITIONAL([ENABLE_TOKENS], [test "$enable_tokens" = "yes"])
AM_CONDITIONAL([ENABLE_NAMES], [test "$enable_names" = "yes"])
AM_CONDITIONAL([ENABLE_FMT_XML], [test "$enable_xml_format" = "yes"])

# Output features to preprocessor and compiler
if test "$enable_debug" == "yes"; then
    CPPFLAGS="$CPPFLAGS -UNDEBUG"
    CFLAGS="$CFLAGS -g -O0"
fi

if test "$enable_opt" == "yes"; then
    CPPFLAGS="$CPPFLAGS -DHIDRD_WITH_OPT"
fi

if test "$enable_tokens" == "yes"; then
    CPPFLAGS="$CPPFLAGS -DHIDRD_WITH_TOKENS"
fi

if test "$enable_names" == "yes"; then
    CPPFLAGS="$CPPFLAGS -DHIDRD_WITH_NAMES"
fi

if test "$enable_xml_format" == "yes"; then
    CPPFLAGS="$CPPFLAGS -DHIDRD_FMT_WITH_XML"
fi

#
# Checks for header files.
#

#
# Checks for typedefs, structures, and compiler characteristics.
#

#
# Checks for library functions.
#

#
# Output
#
AC_CONFIG_FILES([Makefile

                 m4/Makefile
                 m4/hidrd/Makefile

                 db/Makefile
                 db/usage/Makefile

                 include/Makefile
                 include/hidrd/Makefile
                 include/hidrd/util/Makefile
                 include/hidrd/item/Makefile
                 include/hidrd/item/pfx/Makefile
                 include/hidrd/opt/Makefile
                 include/hidrd/strm/Makefile
                 include/hidrd/strm/src/Makefile
                 include/hidrd/strm/snk/Makefile
                 include/hidrd/fmt/Makefile
                 include/hidrd/fmt/natv/Makefile
                 include/hidrd/fmt/xml/Makefile
                 include/hidrd/usage/Makefile
                 
                 lib/Makefile
                 lib/util/Makefile
                 lib/item/Makefile
                 lib/opt/Makefile
                 lib/strm/Makefile
                 lib/strm/src/Makefile
                 lib/strm/snk/Makefile
                 lib/fmt/Makefile
                 lib/fmt/natv/Makefile
                 lib/fmt/xml/Makefile
                 lib/fmt/xml/snk/Makefile
                 lib/fmt/xml/src/Makefile
                 lib/usage/Makefile
                 lib/unit/Makefile
                 
                 src/Makefile])
AC_OUTPUT

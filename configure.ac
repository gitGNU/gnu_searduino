dnl Process this file with autoconf to produce a configure script.

dnl Copyright (C) 2012 Henrik Sandklef
dnl
dnl This file is part of Searduino
dnl
dnl This program is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program.  If not, see <http://www.gnu.org/licenses/>.

AC_PREREQ(2.63)
AC_INIT([Searduino], [0.45], [hesa@sandklef.com])
AC_COPYRIGHT([Copyright (c) 2012 Henrik Sandklef <hesa@sandklef.com>.])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE([1.10 -Wall -Werror -Wno-override])
AM_SILENT_RULES([yes])


AC_PROG_CC
AC_LANG_C
AC_PROG_LIBTOOL
AM_PROG_CC_C_O
# Check for program
AM_MISSING_PROG(PYTHON, python, $missing_dir)

# Checks for header files.
AC_HEADER_STDC



AC_ARG_ENABLE([pedantic],
  [AS_HELP_STRING([--enable-pedantic],
	  [turn on more GCC warnings (mainly for developers)])],
  [case $enableval in
     yes|no) ;;
     *)      AC_MSG_ERROR([bad value $enableval for enable-pedantic option]) ;;
   esac
   pedantic_warnings=$enableval],
  [pedantic_warnings=no]
)


if test "$pedantic_warnings" = yes; then
   PEDANTIC_FLAGS='-W -Wall -pedantic -pedantic-errors  -Werror'
fi

AC_ARG_ENABLE([python],
  [AS_HELP_STRING([--enable-python],
	  [Enable python extension to Searduino])],
  [case $enableval in
     yes|no) ;;
     *)      AC_MSG_ERROR([bad value $enableval for enable-pedantic option]) ;;
   esac
   python_enabled=$enableval],
  [python_enabled=yes]
)


AC_ARG_ENABLE([unittest],
  [AS_HELP_STRING([--enable-unittest],
	  [Enable unit test code (UT framework: check)])],
  [case $enableval in
     yes|no) ;;
     *)      AC_MSG_ERROR([bad value $enableval for enable-pedantic option]) ;;
   esac
   ut_enabled=$enableval],
  [ut_enabled=no]
)


if test "$python_enabled" = "yes"; then
   AX_PYTHON_DEVEL([])
#   AX_PYTHON_DEVEL([">= '2.7'"])
#     AX_PYTHON_VERSION_ENSURE( ["2.7"] )
#   AC_SUBST(PYTHON_LDFLAGS)
#    AC_CHECK_HEADER(Python.h)
fi

if test "$ut_enabled" = "yes"; then
    PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])
fi
AC_SUBST(PYTHON_CPPFLAGS)

AC_MSG_NOTICE([summary of build options:
  version:          ${VERSION} shared
  Host type:        ${host}
  Install prefix:   ${prefix}
  Compiler:         ${CC}
  Warning flags:    ${WARN_CFLAGS}
  Library types:    Shared=${enable_shared}, Static=${enable_static}
  Python:           $python_enabled
  Python flags:     $PYTHON_CPPFLAGS  $PYTHON_LDFLAGS 
  Unit test:        $ut_enabled
  Unit test flags:  C: '$CHECK_CFLAGS   LD: '$CHECK_LIBS'
])

./bin/get-arduino-src.sh



prepare_examples()
{
    cat example/digpins/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${prefix},g" > example/digpins/Makefile.digpins
    cat example/python-digcounter/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${prefix},g" > example/python-digcounter/Makefile.digcounter

}

prepare_searduino_mk()
{
    cat mk/searduino.mk.tmpl  | sed "s,__INSTALL_DIR__,${prefix},g" > mk/searduino.mk
    cat mk/arduino-sources/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${prefix},g" > arduino-sources/Makefile
}

prepare_examples
prepare_searduino_mk

cat simulators/pardon/searduino-pardon.sh.tmpl | sed "s,__INSTALL_DIR__,${prefix},g" > simulators/pardon/searduino-pardon.sh

AC_CONFIG_FILES([Makefile faked-arduino/Makefile faked-arduino/arduino/Makefile faked-arduino/arduino/test/Makefile extensions/Makefile extensions/python/Makefile extensions/arduino-lib/Makefile simulators/Makefile simulators/stream/Makefile simulators/pardon/Makefile faked-arduino/include/Makefile faked-arduino/include/communication/Makefile faked-arduino/include/arduino/boards/Makefile faked-arduino/include/arduino/avr/Makefile faked-arduino/include/arduino/Makefile faked-arduino/include/utils/Makefile example/Makefile example/digpins/Makefile mk/Makefile example/python-digcounter/Makefile  mk/arduino-sources/Makefile mk/board-makefiles/Makefile  ])

AC_OUTPUT

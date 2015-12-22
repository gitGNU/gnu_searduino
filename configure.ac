dnl Process this file with autoconf to produce a configure script.

dnl Copyright (C) 2012, 2013, 2014 Henrik Sandklef
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

#AC_PREREQ(2.63)
AC_INIT([Searduino], [0.9.94], [hesa@sandklef.com])
AC_COPYRIGHT([Copyright (c) 2012-2015 Henrik Sandklef <hesa@sandklef.com>, Viktor Green.])
AC_CONFIG_AUX_DIR([build-aux])
#AM_INIT_AUTOMAKE
AM_INIT_AUTOMAKE([subdir-objects])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS(config.h)
AC_CHECK_HEADERS(fcntl.h)
AC_CHECK_HEADERS(pthread.h)

AC_CHECK_FUNCS([usleep])
AC_CHECK_FUNCS([nanosleep])
AC_CHECK_FUNCS([clock_nanosleep])

#AC_MSG_CHECKING(for usleep)
#AH_TEMPLATE(HAVE_USLEEP)
#AC_EGREP_HEADER(usleep, unistd.h, is_usleep=yes, is_usleep=no)
#if test $is_usleep = yes; then
#  AC_DEFINE(HAVE_USLEEP)
#  AC_MSG_RESULT(yes)
#else
#  AC_MSG_RESULT(no)
#fi


AC_SUBST(CPPFLAGS)

#AM_INIT_AUTOMAKE($PACKAGE, $VERSION)
AM_SILENT_RULES([yes])
AC_PROG_CXX
AC_PROG_CC
# PREPARING FOR USING GNULIB (for pthread.h)
gl_EARLY
gl_INIT
AC_LANG_C
AC_LIBTOOL_DLOPEN
AC_LIBLTDL_CONVENIENCE
AC_PROG_LIBTOOL
AM_PROG_CC_C_O


# Checks for header files.
AC_HEADER_STDC

AC_CHECK_HEADER([ltdl.h],
    [AC_CHECK_LIB([ltdl], [lt_dladvise_init],
        [LIBLTDL=-lltdl], [LIBLTDL=])],
    [LIBLTDL=])

# libtool impl of dlopen
LT_INIT([dlopen])
#LT_CONFIG_LTDL_DIR([libltdl])
AC_CONFIG_SUBDIRS(libltdl)		 

#LTDL_INIT([subproject])

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
   PEDANTIC_FLAGS='-W -Wall -Wformat'
#-pedantic -pedantic-errors
   AC_SUBST([PEDANTIC_FLAGS])
fi

AC_ARG_ENABLE([python-extension],
  [AS_HELP_STRING([--enable-python-extension],
	  [Enable python extension to Searduino])],
  [case $enableval in
     yes|no) ;;
     *)      AC_MSG_ERROR([bad value $enableval for enable-python-extension option]) ;;
   esac
   python_ext_enabled=$enableval],
  [python_ext_enabled=no]
)


AC_ARG_ENABLE([java-extension],
  [AS_HELP_STRING([--enable-java-extension],
	  [Enable Java extension to Searduino])],
  [case $enableval in
     yes|no) ;;
     *)      AC_MSG_ERROR([bad value $enableval for enable-java-extension option]) ;;
   esac
   java_ext_enabled=$enableval],
  [java_ext_enabled=yes]
)


AC_ARG_ENABLE([pearduino],
  [AS_HELP_STRING([--enable-pearduino],
	  [Enable the Python/Gtk Simulator])],
  [case $enableval in
     yes|no) ;;
     *)      AC_MSG_ERROR([bad value $enableval for enable-pearduino option]) ;;
   esac
   pearduino_enabled=$enableval],
  [pearduino_enabled=no]
)

AC_ARG_ENABLE([jearduino],
  [AS_HELP_STRING([--enable-jearduino],
	  [Enable the Java Simulator])],
  [case $enableval in
     yes|no) ;;
     *)      AC_MSG_ERROR([bad value $enableval for enable-jearduino option]) ;;
   esac
   jearduino_enabled=$enableval],
  [jearduino_enabled=yes]
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

AC_ARG_ENABLE([shared-test],
  [AS_HELP_STRING([--enable-shared-test],
	  [Disable tests using sharead version of Searduino libs)])],
  [case $enableval in
     yes|no) ;;
     *)      AC_MSG_ERROR([bad value $enableval for enable-pedantic option]) ;;
   esac
   st_enabled=$enableval],
  [st_enabled=yes]
)

AC_ARG_ENABLE([debian-sources],
  [AS_HELP_STRING([--enable-debian-sources],
	  [Use Arduino source code from Debian packages)])],
  [case $enableval in
     yes|no) ;;
     *)      AC_MSG_ERROR([bad value $enableval for debian-sources option]) ;;
   esac
   debian_sources=$enableval],
  [debian_sources=no]
)


AC_ARG_ENABLE([doc],
  [AS_HELP_STRING([--enable-doc],
	  [Build documentation])],
  [case $enableval in
     yes|no) ;;
     *)      AC_MSG_ERROR([bad value $enableval for doc option]) ;;
   esac
   seard_doc=$enableval],
  [seard_doc=no]
)


AC_ARG_ENABLE([avrtools-copy],
  [AS_HELP_STRING([--enable-avrtools-copy],
	  [Copy avr tools from Arduino])],
  [case $enableval in
     yes|no) ;;
     *)      AC_MSG_ERROR([bad value $enableval for avrtools-copy option]) ;;
   esac
   avrtools_copy=$enableval],
  [avrtools_copy=no]
)




AC_ARG_ENABLE([fedora-sources],
  [AS_HELP_STRING([--enable-fedora-sources],
	  [Use Arduino source code from Fedora packages])],
  [case $enableval in
     yes|no) ;;
     *)      AC_MSG_ERROR([bad value $enableval for fedora-sources option]) ;;
   esac
   fedora_sources=$enableval],
  [fedora_sources=no]
)
if test "$fedora_sources" = "yes"; then
   debian_sources="yes"
fi


if test "$python_ext_enabled" = "yes"; then
# Check for program
# Keep this echo, it's needed on cygwin
echo
  ##################################AM_MISSING_PROG(PYTHON, python, $missing_dir)
#   AX_PYTHON_DEVEL([])
#    AX_PYTHON_DEVEL([">= '2.7'"])
#AM_PATH_PYTHON([2.7],, [:])
#AM_PATH_PYTHON()
    ##################################AC_PYTHON_DEVEL([">= '2.7'"])
#     AX_PYTHON_VERSION_ENSURE( ["2.7"] )
#   AC_SUBST(PYTHON_LDFLAGS)
#    AC_CHECK_HEADER(Python.h)
   AC_SUBST(PYTHON_CPPFLAGS)
fi

echo "UT: $ut_enabled"

if test "$ut_enabled" = "yes"; then
   echo "CHEC"
#   PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])
else
	echo "NO CHECK"
fi

#exit 0

export CYGWIN=""
if test "$(uname -s | grep -i -c cygwin)" != "0" ;
then   
  CYGWIN="true"
fi

#if test "x$jearduino_enabled" = "xyes" ; then
#  if test "x$java_ext_enabled" != "xyes" ; then
#     echo "Jearduino enabled, enabling Java extension"
#     java_ext_enabled="yes"
#  fi
#fi

if test "x$java_ext_enabled" = "xyes" ; then
  AC_PATH_PROG(JAVA,java)
AX_PROG_JAVA
AX_PROG_JAVAC
DARWIN=$(uname -s | grep -i Darw | wc -l)
if test "x$JAVA_HOME" != "x" && test "x$DARWIN" != "x"
then
  for dir in `find $JAVA_HOME/include -follow -type d`
  do
    CPPFLAGS="$CPPFLAGS -I$dir"
  done
else
    AX_JNI_INCLUDE_DIR2
    for JNI_INCLUDE_DIR in $JNI_INCLUDE_DIRS
    do
	CPPFLAGS="$CPPFLAGS -I$JNI_INCLUDE_DIR -I$JNI_INCLUDE_DIR/linux"
    done
    CXXFLAGS="$CXXFLAGS $CPPFLAGS"
fi
AC_CHECK_HEADERS(jni.h)

fi



# GNULIB 
gl_PTHREAD_CHECK


#
AM_CONDITIONAL(PYTHON_EXT_SUPPORT, test "x$python_ext_enabled" = "xyes")
AM_CONDITIONAL(PEARDUINO_SUPPORT,  test "x$pearduino_enabled" = "xyes")
AM_CONDITIONAL(JAVA_EXT_SUPPORT,   test "x$java_ext_enabled" = "xyes")
AM_CONDITIONAL(JEARDUINO_SUPPORT,  test "x$jearduino_enabled" = "xyes")
AM_CONDITIONAL(COPY_AVR,           test "x$avrtools_copy" = "xyes")


AM_CONDITIONAL(BUILD_DOC,          test x$seard_doc = xyes)
AM_CONDITIONAL(DEBIAN_SOURCES,     test x$debian_sources = xyes)
#AM_CONDITIONAL(DEBIANSOURCES,     test "x$debian_sources" = "xyes")
AM_CONDITIONAL(DEBIANSOURCES,      test x$debian_sources = xyes)

AM_CONDITIONAL(UNITTEST,       test "x$ut_enabled"     = "xyes")
AM_CONDITIONAL(SHAREDTEST,     test "x$st_enabled"     = "xyes")
AM_CONDITIONAL(CYGWIN_USED,    test "x$CYGWIN"         = "xtrue")

# GNULIB
AM_CONDITIONAL(GL_GENERATE_PTHREAD_H, test "x$ac_cv_header_pthread_h"  = "xno")
AM_CONDITIONAL(GL_GENERATE_SCHED_H,   test "x$ac_cv_header_pthread_h"  = "xno")
AM_CONDITIONAL(GL_GENERATE_STDDEF_H,  test "x$ac_cv_header_pthread_h"  = "xno")

if test "x$ac_cv_header_pthread_h"  = "xno"; then
   echo " ***  Will generate pthread.h from gnulib  "
   GL_GENERATE_PTHREAD_H=true
   AC_SUBST([GL_GENERATE_PTHREAD_H])
   AC_SUBST([GL_GENERATE_SCHED_H])
   AC_SUBST([GL_GENERATE_STDDEF_H])
fi

echo "CHECK JAVA: $java_ext_enabled"
if test "x$java_ext_enabled" = "xyes" ; then
    if test "x$ac_cv_header_jni_h"  = "xno"; then
	echo "Java extension enabled, but cant find jni.h"
	echo "Try setting JAVA_HOME, "
	echo "  or CFLAGS, CXXFLAGS"

	exit 1
    fi
else
    if test  "x$jearduino_enabled" = "xyes" ; then
	echo "Jearduino build is enabled but not Java extension"
	echo " Either disable Jearduino or enable Java extension"
	
	exit
    fi
fi


if test "x$python_ext_enabled" = "xno" ; then
    if test  "x$pearduino_enabled" = "xyes" ; then
	echo " Pearduino build is enabled but not Python extension"
	echo " Either disable Pearduino or enable Python extension"
	
	exit
    fi
fi

#
# Set up misc stuff:
#     shared lib extensions, 
#
case $host in
 *linux*) SHLIB_EXT='.so'    ;;
 *mac*)   SHLIB_EXT='.dylib' ;;
 *win*)   SHLIB_EXT='.dll'   ;;
esac
AC_SUBST([SHLIB_EXT])

# GNULIB
AC_SUBST(GL_GENERATE_PTHREAD_H)

exit_on_failure()
{
  if test "$1" != "0"; 
  then
    echo "$2 failed (return value: $1)"
    exit
  else	
    echo "$2 OK"
  fi
}

print_avr_settings()
{
  echo "AVR stuff:"
  echo "------------------"
  echo "avr-gcc:            $AVR_GCC"
  echo "avr-g++:            $AVR_GCXX"
  echo "avr-objcopy:        $AVR_OBJCP"
  echo "avr-ar:             $AVR_AR"
  echo "avrdude:            $AVR_DUDE"

}

check_avr() 
{
  if test "$1" = "" ;  then 
      echo ""
      echo "***** ERROR *****"
      echo "   Can't find: $2"
      echo "   Without it, Searduino will not work. Bailing out....."
      echo " "
      echo "One solution is to use the avr tools as found in the Arduino sources."
      echo "Searduino will assist you doing that, simple configure again with the following flag:"
      echo ""
      echo "    --enable-avrtools-copy"
      echo ""
      exit 1
  fi   
}

setup_avr_copy()
{
    AVR_GCC=${SEARD_PREFIX}/searduino/lib/avr/bin/avr-gcc
    AVR_GCXX=${SEARD_PREFIX}/searduino/lib/avr/bin/avr-g++
    AVR_OBJCP=${SEARD_PREFIX}/searduino/lib/avr/bin/avr-objcopy
    AVR_AR=${SEARD_PREFIX}/searduino/lib/avr/bin/avr-ar
    AVR_DUDE=${SEARD_PREFIX}/searduino/lib/avrdude
}

check_avr_stuff()
{
  AC_PATH_PROG(AVR_GCC,avr-gcc)
  AC_PATH_PROG(AVR_GCXX,avr-g++)
  AC_PATH_PROG(AVR_OBJCP,avr-objcopy)
  AC_PATH_PROG(AVR_AR,avr-ar)
  AC_PATH_PROG(AVR_DUDE,avrdude)

  check_avr "$AVR_GCC" "avr-gcc"
  check_avr "$AVR_GCXX" "avr-g++"
  check_avr "$AVR_OBJCP" "avr-objcopy"
  check_avr "$AVR_AR" "avr-ar"
  check_avr "$AVR_DUDE" "avrdude"

}


set_lversion()
{
    VERSION_SPLIT=`echo  ${VERSION} | sed 's,\., ,g'` 
    VERSION_LONG_MAJOR=`echo ${VERSION_SPLIT} | awk '{print $1}' `
    VERSION_LONG_MINOR=`echo ${VERSION_SPLIT} | awk '{print $2}' `
    VERSION_LONG_PREPARE=`echo ${VERSION_SPLIT} | awk '{print $3}' `

#    echo "$VERSION_LONG_MAJOR - $VERSION_LONG_MINOR - $VERSION_LONG_PREPARE"

    VERSION_LONG=0

    if test "x$VERSION_LONG_MAJOR" != "x" ;
    then
	VERSION_LONG=`echo "$VERSION_LONG_MAJOR * 10000" | bc`
    fi
    if test "x$VERSION_LONG_MINOR" != "x" ;
    then
	if test $VERSION_LONG_MINOR -gt 99 ; 
	then
	    echo "You can't have minor version greater than 99 (you've set it to $VERSION_LONG_MINOR)"
	    exit
	fi
	VERSION_LONG=`echo "$VERSION_LONG + $VERSION_LONG_MINOR * 100 " | bc`
    fi
    if test "x$VERSION_LONG_PREPARE" != "x" ;
    then
	VERSION_LONG=`echo "$VERSION_LONG + $VERSION_LONG_PREPARE " | bc`
    fi

 #   echo "VERSION_LONG is now:     $VERSION_LONG  / $VERSION"


}


setup_debianized()
{
    mkdir -p debian-mk/libraries/	
    mkdir -p debian-mk/arduino-sources/	

    cp -r mk/arduino-sources           debian-mk/
    cp -r mk/libraries                 debian-mk/

    cp mk/debian-mk/arduino-sources/arduino-sources.mk   debian-mk/arduino-sources/
    cp mk/debian-mk/libraries/libraries.mk               debian-mk/libraries/

    cat mk/debian-mk/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > \
                 debian-mk/Makefile
    exit_on_failure $? "Prepared top level Makefile (debian/fedora)"
    
    cat mk/debian-mk/libraries/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > \
                 debian-mk/libraries/Makefile
    exit_on_failure $? "Prepared libraries Makefile (debian/fedora)"
    
    cat mk/debian-mk/arduino-sources/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > \
                 debian-mk/arduino-sources/Makefile
    exit_on_failure $? "Prepared arduino-sources Makefile (debian/fedora)"

}

prepare_examples()
{

    cat example/serial/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/serial/Makefile.serial
    exit_on_failure $? "Prepared  serial"

    cat example/digital-rw/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/digital-rw/Makefile.digitalrw
    exit_on_failure $? "Prepared  digital-rw"

    cat example/digpins/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/digpins/Makefile.digpins
    exit_on_failure $? "Prepared  digpins"

    cat example/hid/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/hid/Makefile.hid
    exit_on_failure $? "Prepared  hid"

    cat example/log/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/log/Makefile.log
    exit_on_failure $? "Prepared  log"

    cat example/python-digcounter/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/python-digcounter/Makefile.digcounter
    exit_on_failure $? "Prepared  python-digcounter"

    cat example/python-digcounter/simple-hw.sh.tmpl | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/python-digcounter/simple-hw.sh
    exit_on_failure $? "Prepared  python-digcounter"

    cat example/verification/distance/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/verification/distance/Makefile.distance
    exit_on_failure $? "Prepared  verification/distance"

    cat example/verification/ok-version/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/verification/ok-version/Makefile.ok-version
    exit_on_failure $? "Prepared  verification/ok-version"

    cat example/verification/nok-version/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/verification/nok-version/Makefile.nok-version
    exit_on_failure $? "Prepared  verification/nok-version"

    cat example/many-boards/Makefile.blink-fast.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/many-boards/Makefile.blink-fast
    exit_on_failure $? "Prepared  example/many-boards/Makefile.blink-fast"

    cat example/many-boards/Makefile.blink-four.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/many-boards/Makefile.blink-four
    exit_on_failure $? "Prepared  example/many-boards/Makefile.blink-four"

    cat example/many-boards/Makefile.blink-rand.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/many-boards/Makefile.blink-rand
    exit_on_failure $? "Prepared  example/many-boards/Makefile.blink-rand"

    cat example/lcd-shield/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/lcd-shield/Makefile.lcd-shield
    exit_on_failure $? "Prepared  example/lcd-shield/Makefile.lcd-shield"

    cat example/toggle-pins/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/toggle-pins/Makefile.toggle-pins
    exit_on_failure $? "Prepared  example/toggle-pins/Makefile.toggle-pins"

    cat example/relay/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > example/relay/Makefile.relay
    exit_on_failure $? "Prepared  example/relay/Makefile.relay"


}


prepare_test_mk()
{
  if test "x$debian_sources"  != "xyes"  ;
  then
     export DEBIAN_SOURCE_SUBST="false"
  else
     export DEBIAN_SOURCE_SUBST="true"
  fi

    cat test/arduino-lib/Makefile.tmpl  | sed "s,__DEBIANSOURCES__,$DEBIAN_SOURCE_SUBST,g" > test/arduino-lib/Makefile
    exit_on_failure $? "Prepared  test/arduino-lib"

    cat test/hw/Makefile.tmpl  | sed "s,__DEBIANSOURCES__,$DEBIAN_SOURCE_SUBST,g" > test/hw/Makefile
    exit_on_failure $? "Prepared  test/hw"

    cat test/arduino-code-dynamic/Makefile.tmpl  | sed "s,__DEBIANSOURCES__,$DEBIAN_SOURCE_SUBST,g" > test/arduino-code-dynamic/Makefile
    exit_on_failure $? "Prepared  test/arduino-code-dynamic"

    cat test/arduino-code-static/Makefile.tmpl  | sed "s,__DEBIANSOURCES__,$DEBIAN_SOURCE_SUBST,g" > test/arduino-code-static/Makefile
    exit_on_failure $? "Prepared  test/arduino-code-static"

    cat test/stub/Makefile.tmpl  | sed "s,__DEBIANSOURCES__,$DEBIAN_SOURCE_SUBST,g" > test/stub/Makefile
    exit_on_failure $? "Prepared  test/stub"

    cat test/searduino_loop/Makefile.tmpl  | sed "s,__DEBIANSOURCES__,$DEBIAN_SOURCE_SUBST,g" > test/searduino_loop/Makefile
    exit_on_failure $? "Prepared  test/searduino_loop"

    cat test/shared/Makefile.tmpl  | sed "s,__DEBIANSOURCES__,$DEBIAN_SOURCE_SUBST,g" > test/shared/Makefile
    exit_on_failure $? "Prepared  test/shared"

    cat test/shared-main/Makefile.tmpl  | sed "s,__DEBIANSOURCES__,$DEBIAN_SOURCE_SUBST,g" > test/shared-main/Makefile
    exit_on_failure $? "Prepared  test/shared-main"

    cat test/static/Makefile.tmpl  | sed "s,__DEBIANSOURCES__,$DEBIAN_SOURCE_SUBST,g" > test/static/Makefile
    exit_on_failure $? "Prepared  test/static"

}




replace_vars()
{
    INFILE=$1
    OUTFILE=$2

   cat ${INFILE}                           | \
        sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g"      | \
        sed "s,__CYGWIN__,${CYGWIN},g"                 | \
        sed "s,__DEBIAN_SOURCES__,$debian_sources,g"   | \
        sed "s,__ARDUINO_PATH__,${ARDUINO_PATH},g"     | \
        sed "s,__ARDUINO_SOURCES_FROM__,${ARDUINO_SOURCES_FROM},g"      | \
        sed "s,__SEARDUINO_VERSION_MAJOR__,${VERSION_LONG_MAJOR},g"     | \
        sed "s,__SEARDUINO_VERSION_STRING__,${VERSION},g"               | \
        sed "s,__SEARDUINO_VERSION_MINOR__,${VERSION_LONG_MINOR},g"     | \
        sed "s,__SEARDUINO_VERSION_PREPARE__,${VERSION_LONG_PREPARE},g" | \
        sed "s,__AVRDUDE_PREFIX__,${AVRDUDE_PREFIX},g"    | \
        sed "s,__SEARDUINO_VERSION__,${VERSION_LONG},g"   | \
        sed -e "s,__AVR_PREFIX__,${AVR_PREFIX},g" > ${OUTFILE}
}
#        sed "s,__AVR_PREFIX__,${AVR_PREFIX},g"            | \

prepare_searduino_mk()
{
#  CYGWIN_NT-6.1
#  CYGWIN_NT-6.1-WOW64
#  CYGWIN_NT-5.1

	
    export VERSION_LONG=""
    set_lversion

echo "LOCAL_AVR_PREFIX:      '$LOCAL_AVR_PREFIX'"
echo "LOCAL_AVRDUDE_PREFIX:  '$LOCAL_AVRDUDE_PREFIX'"
echo "AVR_PREFIX:            '$AVR_PREFIX'"
echo "AVRDUDE_PREFIX:        '$AVRDUDE_PREFIX'"



    replace_vars mk/searduino.mk.tmpl mk/searduino.mk
    exit_on_failure $? "Prepared searduino.mk "

    replace_vars mk/searduino-arduino.mk.tmpl mk/searduino-arduino.mk
    exit_on_failure $? "Prepared searduino-arduino.mk "


    replace_vars mk/library-functions.mk.tmpl mk/library-functions.mk
    exit_on_failure $? "Prepared library-functions.mk "

    cat mk/arduino-sources/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > arduino-sources/Makefile
    exit_on_failure $? "Prepared arduino-sources Makefile"

    mkdir -p arduino-sources/libraries/	 
    cat mk/libraries/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > arduino-sources/libraries/Makefile
    exit_on_failure $? "Prepared libraries Makefile"
}

prepare_scripts()
{
    replace_vars scripts/settings.tmpl  scripts/settings
    exit_on_failure $? "Prepared settings script"

    replace_vars scripts/functions.tmpl scripts/functions
    exit_on_failure $? "Prepared functions script"
}


if test "x${prefix}" = "xNONE" ;
then 
    SEARD_PREFIX=${ac_default_prefix}
else	
    SEARD_PREFIX=${prefix}
fi

echo "prefix: ${prefix}   SEARD_PREFIX=${SEARD_PREFIX}"
export SEARD_PREFIX

#
#  DEBIAN or not
# 
if test "x$debian_sources"  != "xyes"  ;
then
    GET_SRC_ARGS=""
    if test "x$avrtools_copy" = "xyes" ;
    then
        GET_SRC_ARGS=" --avrtools-copy"
    fi
    echo "./bin/get-arduino-src.sh $GET_SRC_ARGS"
    ./bin/get-arduino-src.sh $GET_SRC_ARGS
    exit_on_failure $? ./bin/get-arduino-src.sh
    export ARDUINO_PATH=${SEARD_PREFIX}/
    export ARDUINO_SOURCES_FROM=Arduino
else
  echo "Not downloading Arduino sources from internet"
  setup_debianized
  export ARDUINO_PATH=/usr/share/arduino/hardware/arduino/	
  export ARDUINO_SOURCES_FROM=Debian
fi


#
#
#
echo "CHECKING AVR: $avrtools_copy"
if test "x$avrtools_copy" != "xyes" ;
then
    check_avr_stuff

    export AVR_PREFIX=""
    export AVRDUDE_PREFIX=""

    AVR_COPY_MSG0=""
    AVR_COPY_MSG1="Locally installed avr-gcc and avrdude used"
    AVR_COPY_MSG2=""
    AVR_COPY_MSG3=""
    export LOCAL_AVR_PREFIX=${AVR_PREFIX}
    export LOCAL_AVRDUDE_PREFIX=${AVRDUDE_PREFIX}

else

    echo "USING ARD SOURCES"
    
echo "Locally find avr-gcc "
    export AVR_PREFIX=${SEARD_PREFIX}/searduino/lib/$(cd avr-tools-copy ; find . -name "avr-gcc"  -type f  | grep bin | head -1 | xargs dirname)/
echo "Locally find avrdude "
echo "$(cd avr-tools-copy/ ; find . -name avrdude | xargs dirname)/"
    export AVRDUDE_PREFIX=${SEARD_PREFIX}/searduino/lib/$(cd avr-tools-copy/ ; find . -name "avrdude"  -type f | head -1 | xargs dirname)/

echo "Locally find avr-gcc VCS"
    export LOCAL_AVR_PREFIX=$(pwd)/$(find . -name "avr-gcc"  -type f  | grep bin | head -1 | xargs dirname)/
echo "Locally find avrdude VCS"
    export LOCAL_AVRDUDE_PREFIX=$(pwd)/$(find . -name "avrdude" -type f | grep -v doc | head -1 | xargs dirname)/

    setup_avr_copy
    AVR_COPY_MSG0="During installation, you need to add ${SEARD_PREFIX}/searduino/lib/avr/bin/ and ${SEARD_PREFIX}/searduino/lib/ to your PATH"
    AVR_COPY_MSG1="In bash you do this by adding the following line (typically in ~/.bash_profile): "
    AVR_COPY_MSG2=" "
    AVR_COPY_MSG3="  PATH=$(pwd)/$(find . -name "avrdude" | head -1 | xargs dirname):$(pwd)/$(find . -name "avr-gcc" | grep bin | head -1 | xargs dirname):\$PATH"
fi




cat  mk/searduino-vcs.mk.tmpl | \
    sed "s,__AVR_PREFIX__,${LOCAL_AVR_PREFIX},g" | \
    sed "s,__AVRDUDE_PREFIX__,${LOCAL_AVRDUDE_PREFIX},g" \
  > mk/searduino-vcs.mk 
exit_on_failure $? "Prepared searduino-vcs.mk "
print_avr_settings


cat doc/Makefile.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > doc/Makefile
exit_on_failure $? "Prepared doc Makefile"


cat simulators/pardon/searduino-pardon.sh.tmpl | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > simulators/pardon/searduino-pardon.sh
exit_on_failure $? "Prepared python simulator wrapper script"

cat simulators/jearduino/searduino-jearduino.sh.tmpl | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > simulators/jearduino/searduino-jearduino.sh
exit_on_failure $? "Prepared Java simulator wrapper script"

cat simulators/stream/searduino-stream.sh.tmpl | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > simulators/stream/searduino-stream.sh
exit_on_failure $? "Prepared Streamed simulator wrapper script"

cat scripts/verify-install.sh.tmpl  | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > scripts/verify-install.sh
exit_on_failure $? "Prepared installation verification script"
chmod a+x scripts/verify-install.sh

cat bin/searduino-arduino-ex2c.tmpl | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > bin/searduino-arduino-ex2c
exit_on_failure $? "Prepared Arduino examples to C translator"

cat bin/searduino-builder.tmpl | sed "s,__INSTALL_DIR__,${SEARD_PREFIX},g" > bin/searduino-builder
exit_on_failure $? "Prepared Searduino buider"

prepare_examples
prepare_searduino_mk
prepare_test_mk
prepare_scripts



AC_CONFIG_FILES([Makefile faked-arduino/Makefile faked-arduino/arduino/Makefile faked-arduino/arduino/test/Makefile    faked-arduino/wire/test/Makefile faked-arduino/wire/Makefile extensions/Makefile extensions/python/Makefile extensions/java/Makefile extensions/java/test/Makefile extensions/arduino-lib/Makefile simulators/Makefile simulators/stream/Makefile simulators/pardon/Makefile  simulators/jearduino/Makefile faked-arduino/include/Makefile  faked-arduino/include/arduino/boards/Makefile faked-arduino/include/avr/Makefile faked-arduino/include/avr/util/Makefile faked-arduino/include/arduino/Makefile faked-arduino/include/seasim/Makefile  faked-arduino/include/utils/Makefile example/Makefile example/digpins/Makefile  example/many-boards/Makefile example/hid/Makefile example/log/Makefile example/digital-rw/Makefile example/serial/Makefile mk/Makefile example/python-digcounter/Makefile  mk/arduino-sources/Makefile mk/libraries/Makefile mk/external-libraries/Makefile mk/board-makefiles/Makefile test/Makefile  test/mk/Makefile arduino-extras/include/Makefile arduino-extras/Makefile faked-arduino/EEPROM/test/Makefile faked-arduino/EEPROM/Makefile faked-arduino/Ethernet/test/Makefile faked-arduino/Ethernet/Makefile faked-arduino/Firmata/test/Makefile faked-arduino/Firmata/Makefile faked-arduino/LiquidCrystal/test/Makefile faked-arduino/LiquidCrystal/Makefile faked-arduino/SD/test/Makefile faked-arduino/SD/Makefile faked-arduino/Servo/test/Makefile faked-arduino/Servo/Makefile faked-arduino/SoftwareSerial/test/Makefile faked-arduino/SoftwareSerial/Makefile faked-arduino/SPI/test/Makefile faked-arduino/SPI/Makefile faked-arduino/Stepper/test/Makefile faked-arduino/Stepper/Makefile example/verification/Makefile example/verification/distance/Makefile example/lcd-shield/Makefile example/toggle-pins/Makefile example/relay/Makefile example/verification/ok-version/Makefile  example/verification/nok-version/Makefile tools/Makefile scripts/Makefile ])

LIBXTST=""
AC_CHECK_LIB(Xtst, XTestFakeMotionEvent, LIBXTST="-lXtst",[AC_CHECK_LIB(Xext,XTestFakeMotionEvent , LIBXTST="-lXext")])

USE_XTEST=false
if test "x$LIBXTST" != "x" ; 
then
   USE_XTEST=true
fi
AM_CONDITIONAL(USE_XTEST,  test "x$LIBXTST"  != "x")


AC_OUTPUT
	
AC_SUBST(VERSION)
AC_SUBST(PACKAGE)
AC_SUBST(INCLTDL)
AC_SUBST(LIBLTDL)	
AC_SUBST(USE_XTEST)
AC_SUBST(LIBXTST)	
AC_SUBST(PYTHON_EXT_SUPPORT)
AC_SUBST(PEARDUINO_SUPPORT)
AC_SUBST(JAVA_EXT_SUPPORT)
AC_SUBST(JEARDUINO_SUPPORT)
AC_SUBST(DEBIAN_SOURCES)
AC_SUBST(BUILD_DOC)
AC_SUBST(DEBIANSOURCES)



AC_MSG_NOTICE([summary of build options:
  package:            ${PACKAGE} 
  version:            ${VERSION} 
  Host type:          ${host}
  Target:             ${target}
  Install prefix:     ${prefix}
  C Compiler:         ${CC}
  CXX Compiler:       ${CXX}
  Warning flags:      ${WARN_CFLAGS}
  Library types:      Shared=${enable_shared}, Static=${enable_static}
  Shared lib test:    $st_enabled
  Pedantic flags:     $PEDANTIC_FLAGS
  Pthreads:           $ac_cv_header_pthread_h  / $GL_GENERATE_PTHREAD_H

  AVR stuff:
  ------------------
    avr-gcc:          $AVR_GCC
    avr-g++:          $AVR_GCXX
    avr-objcopy:      $AVR_OBJCP
    avr-ar:           $AVR_AR
    avrdude:          $AVR_DUDE

  Java extension:
  ------------------
    Enabled:          $java_ext_enabled
    Jni.h found:      $ac_cv_header_jni_h

  Python extension:
  ------------------
    Enabled:          $python_ext_enabled
    Python flags:     $PYTHON_CPPFLAGS  $PYTHON_LDFLAGS 

  Simulators:
  ------------------
    Jearduino:        $jearduino_enabled
    Pearduino:        $pearduino_enabled

  Unit test:
  ------------------
    Enabled:          $ut_enabled
    cflags:           $CHECK_CFLAGS
    ldflags:          $CHECK_LIBS

  HID backends:     
  ------------------
    X11:              $USE_XTEST ($LIBXTST)

  Use Debian/Fedora Arduino: $debian_sources

  $AVR_COPY_MSG0
  $AVR_COPY_MSG1
  $AVR_COPY_MSG2
  $AVR_COPY_MSG3
  

])



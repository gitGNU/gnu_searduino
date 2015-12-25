#!/bin/sh

mv configure.ac configure.ac.orig 
cat configure.ac.orig | \
  sed -e 's,AM_MISSING_PROG,#AM_MISSING_PROG,g' \
      -e 's,AC_PYTHON_DEVEL,#AC_PYTHON_DEVEL,g' > configure.ac 

export JAVA_HOME=/cygdrive/c/Java/jdk1.7.0_79
export PATH=$PATH:/cygdrive/c/Java/jdk1.7.0_79/bin


CFLAGS="-I${JAVA_HOME}/include -D__int64=int64_t"
CPPFLAGS="$CFLAGS"


make -f Makefile.git && \
  ./configure CFLAGS="$CFLAGS" CPPFLAGS="$CFLAGS" --disable-unittest --prefix=/opt/searduino && \
  make && make install


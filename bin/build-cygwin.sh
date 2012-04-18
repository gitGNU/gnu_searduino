#!/bin/sh

mv configure.ac configure.ac.orig 
cat configure.ac.orig | \
  sed -e 's,AM_MISSING_PROG,#AM_MISSING_PROG,g' \
      -e 's,AC_PYTHON_DEVEL,#AC_PYTHON_DEVEL,g' > configure.ac 

make -f Makfile.git && \
  ./configure --disable-python --disable-unittest && \
  make && make install
#!/bin/sh

mv configure.ac configure.ac.orig 
cat configure.ac.orig | \
  sed 's,AM_MISSING_PROG,#AC_PYTHON_DEVEL,g' > configure.ac 

make -f Makfile.git && \
  ./configure --disable-python --disable-unittest && \
  make && make install
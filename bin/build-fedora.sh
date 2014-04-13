#!/bin/bash

MACH=$(uname -m)

if [ "$MACH" = "i686" ]
then
    ARCH=i386
else
    ARCH=amd64
fi

DEFAULT_JAVA_PATH=/usr/lib/jvm/java-1.7.0/include/


if [ "$1" = "fedora" ]
then
    FEDORA_ARGS="--enable-fedora-sources"
fi


export CFLAGS="-I${DEFAULT_JAVA_PATH} -I${DEFAULT_JAVA_PATH}/linux/"
export CXXFLAGS="-I${DEFAULT_JAVA_PATH} -I${DEFAULT_JAVA_PATH}/linux/"

#--enable-unittest
make -f Makefile.git && \
  ./configure  --prefix=/opt/searduino --disable-python-extension  --disable-pearduino $FEDORA_ARGS  && \
  make clean && make && \
  sudo make install && \
  echo "Wow, it all passed :)"

#&&  \
#  make check &&         \




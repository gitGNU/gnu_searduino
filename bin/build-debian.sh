#!/bin/sh

MACH=$(uname -m)

if [ "$MACH" = "i686" ]
then
    ARCH=i386
else
    ARCH=amd64
fi

if [ "$1" = "debian" ]
then
    DEBIAN_ARGS="--enable-debian-sources"
fi

DEFAULT_JAVA_PATH=/usr/lib/jvm/java-6-openjdk-$ARCH/include/

export CFLAGS="-I${DEFAULT_JAVA_PATH} -I${DEFAULT_JAVA_PATH}/linux/"
export CXXFLAGS="-I${DEFAULT_JAVA_PATH} -I${DEFAULT_JAVA_PATH}/linux/"

#--enable-unittest
make -f Makefile.git && \
  ./configure  --prefix=/opt/searduino --disable-python-extension  --disable-pearduino $DEBIAN_ARGS && \
  make clean && make && \
  sudo make install && \
  echo "Wow, it all passed :)"

#&&  \
#  make check &&         \




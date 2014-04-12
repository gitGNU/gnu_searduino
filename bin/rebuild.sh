#!/bin/sh

MACH=$(uname -m)

if [ "$MACH" = "i686" ]
then
    ARCH=i386
else
    ARCH=amd64
fi

DEFAULT_JAVA_PATH=/usr/lib/jvm/java-7-openjdk-$ARCH/include/
export CFLAGS="-I${DEFAULT_JAVA_PATH} -I${DEFAULT_JAVA_PATH}/linux/"
export CXXFLAGS="-I${DEFAULT_JAVA_PATH} -I${DEFAULT_JAVA_PATH}/linux/"


make -f Makefile.git && \
  ./configure --enable-unittest --prefix=/opt/searduino --disable-python-extension  --disable-pearduino && \
  make clean && make && \
  sudo make install &&  \
  make check &&         \
  echo "Wow, it all passed :)"




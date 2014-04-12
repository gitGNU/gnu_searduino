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
    DEFAULT_JAVA_PATH=/usr/lib/jvm/java-6-openjdk/include/
else
    DEBIAN_ARGS=""
    DEFAULT_JAVA_PATH=/usr/lib/jvm/java-7-openjdk-$ARCH/include/
fi

export CFLAGS="-I${DEFAULT_JAVA_PATH} -I${DEFAULT_JAVA_PATH}/linux/"
export CXXFLAGS="-I${DEFAULT_JAVA_PATH} -I${DEFAULT_JAVA_PATH}/linux/"


make -f Makefile.git && \
  ./configure --enable-unittest --prefix=/opt/searduino --disable-python-extension  --disable-pearduino $DEBIAN_ARGS && \
  make clean && make && \
  sudo make install 
  echo "Wow, it all passed :)"

#&&  \
#  make check &&         \




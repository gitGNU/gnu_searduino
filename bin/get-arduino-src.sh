#!/bin/sh

if [ -d arduino-sources ]
then
    echo "Already setup... "
    exit 0 
fi


MY_OS=$(uname -s)

if [ "$MY_OS" = "Linux" ]
then
    if [ "$(uname -m | grep -c _64)" != "0" ]
	then
	echo "No support for 64 bit"
	exit 1
    else
	ARD_BASE=http://arduino.googlecode.com/files/
	ARD_FILE=arduino-1.0-linux.tgz
	ARD_URL=$ARD_BASE/$ARD_FILE
    fi
else
    echo "Currently no support for non GNU/Linux platforms"
    echo "Contact the searduino team"
    exit 1
fi

get_sources()
{
    mkdir -p download-tmp
    rm -f $ARD_FILE
    wget $ARD_URL
    mv   $ARD_FILE download-tmp
}

unpack_sources()
{
    cd download-tmp
    tar zxvf $ARD_FILE
    cd ..
}

setup_sources()
{
    mkdir arduino-sources
    mkdir arduino-sources/core
    mkdir arduino-sources/variants

    cp -r download-tmp/arduino-1.0/hardware/arduino/cores/arduino/* arduino-sources/core
    cp -r download-tmp/arduino-1.0/hardware/arduino/variants/* arduino-sources/variants/

    cp misc/Makefile-arduino-sources  arduino-sources/Makefile
}

get_sources
unpack_sources
setup_sources


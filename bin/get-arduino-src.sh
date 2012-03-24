#!/bin/sh

MY_OS=$(uname -s )
OS_EXTRA_DIR="arduino-1.0"

if [ "$MY_OS" = "Linux" ]
then
    if [ "$(uname -m | grep -c _64)" != "0" ]
	then
	ARD_BASE=http://arduino.googlecode.com/files/
	ARD_FILE=arduino-1.0-linux64.tgz
	ARD_URL=$ARD_BASE/$ARD_FILE
    else
	ARD_BASE=http://arduino.googlecode.com/files/
	ARD_FILE=arduino-1.0-linux.tgz
	ARD_URL=$ARD_BASE/$ARD_FILE
    fi
elif [ "${MY_OS:0:5}" = "CYGWI" ]
then
	ARD_BASE=http://arduino.googlecode.com/files/
	ARD_FILE=arduino-1.0-windows.zip
	ARD_URL=$ARD_BASE/$ARD_FILE
elif [ "${MY_OS:0:6}" = "Darwin" ]
then
	ARD_BASE=http://arduino.googlecode.com/files/
	ARD_FILE=arduino-1.0-macosx.zip
	ARD_URL=$ARD_BASE/$ARD_FILE
	OS_EXTRA_DIR="Arduino.app/Contents/Resources/Java"
else
    echo "Currently no support for non GNU/Linux platforms"
    echo "Contact the searduino team"
    exit 1
fi

exit_on_failure()
{
    RET=$1
    shift
    COMM="$*"
    if [ "$RET" != "0" ]
	then
	echo "***************************"
	echo "****  ERROR in $0:  $COMM"
	echo "***************************"
	exit $RET
    fi
}

exec_comm()
{
    echo "$*"
    $*
    exit_on_failure "$?" "$*"

#    echo "Finished: $*"
#    sleep 2
}




get_sources()
{
    mkdir -p download-tmp
    exec_comm rm -f $ARD_FILE
    wget $ARD_URL
    exec_comm mv   $ARD_FILE download-tmp
}

unpack_sources()
{
    exec_comm cd download-tmp
    if [ "$MY_OS" = "Linux" ]
    then
	exec_comm tar zxvf $ARD_FILE
    elif [ "${MY_OS:0:5}" = "CYGWI" ]
    then
	exec_comm unzip $ARD_FILE
    elif [ "${MY_OS:0:6}" = "Darwin" ]
    then
	exec_comm unzip $ARD_FILE
    else
	echo "Currently no support for non GNU/Linux platforms"
	echo "Contact the searduino team"
	exit 1
    fi
    exec_comm cd ..
}

setup_sources()
{
    mkdir -p arduino-sources
    mkdir -p arduino-sources/core
    mkdir -p arduino-sources/variants
    mkdir -p ard-ex

    exec_comm cp -r download-tmp/${OS_EXTRA_DIR}/hardware/arduino/cores/arduino/* arduino-sources/core
    exec_comm cp -r download-tmp/${OS_EXTRA_DIR}/hardware/arduino/variants/* arduino-sources/variants/
    exec_comm cp -r download-tmp/${OS_EXTRA_DIR}/examples/* ard-ex/
}


create_mk()
{
    exec_comm cp mk/arduino-sources/Makefile.*                arduino-sources/
##    exec_comm cp mk/arduino-sources/Makefile                  arduino-sources/
    exec_comm cp mk/arduino-sources/arduino-sources.mk        arduino-sources/
}

if [ -f arduino-sources/core/WMath.cpp ]
then
    echo "Arduino code already downloaded, skipping download and unpack"
else
    get_sources
    unpack_sources
    setup_sources
fi

create_mk


exit 0
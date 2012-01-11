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
	ARD_BASE=http://arduino.googlecode.com/files/
	ARD_FILE=arduino-1.0-linux64.tgz
	ARD_URL=$ARD_BASE/$ARD_FILE
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
    exec_comm mkdir -p download-tmp
    exec_comm rm -f $ARD_FILE
    wget $ARD_URL
    exec_comm mv   $ARD_FILE download-tmp
}

unpack_sources()
{
    exec_comm cd download-tmp
    exec_comm tar zxvf $ARD_FILE
    exec_comm cd ..
}

setup_sources()
{
    exec_comm mkdir arduino-sources
    exec_comm mkdir arduino-sources/core
    exec_comm mkdir arduino-sources/variants

    exec_comm cp -r download-tmp/arduino-1.0/hardware/arduino/cores/arduino/* arduino-sources/core
    exec_comm cp -r download-tmp/arduino-1.0/hardware/arduino/variants/* arduino-sources/variants/

    exec_comm cp misc/Makefile-arduino-sources  arduino-sources/Makefile
}

get_sources
unpack_sources
setup_sources


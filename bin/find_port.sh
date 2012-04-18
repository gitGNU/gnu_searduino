#!/bin/bash

# arguments: arduino-type [OS-String]

parse_arguments() {
    TYPE=$1
    MY_OS=$2
    OS=""
    
    if [ "$TYPE" = "" ]
    then
	echo "Missing Argument: arduino-type"
	exit 1
    fi
    
    if [ "$MY_OS" = "" ]
    then
	MY_OS=`uname -s`
    fi

#Verify valid OS
    if [ "${MY_OS:0:6}" = "Darwin" ]
    then
	OS="osx"
    elif [ "$MY_OS" = "Linux" ]
    then
	OS="linux"
    else
	echo "No support for: $MY_OS"
	exit 1
    fi

#Verify valid board
    if [ "$TYPE" = "uno" ]
    then
	: # OK
    elif [ "$TYPE" = "due" ]
    then
	: # OK
    elif [ "$TYPE" = "mega" ]
    then
	: # OK
    elif [ "$TYPE" = "mega2560" ]
    then
	: # OK
    else
	echo "No support for: $TYPE"
	exit 1
    fi
}

osx_mega2560() {
    PORT=tty.usbmodem
}
osx_due() {
    PORT=tty.usbserial
}
osx_mega() {
    PORT=tty.usbserial
}
osx_uno() {
    PORT=tty.usbmodem
}

linux_mega2560() {
    PORT=ttyACM
}
linux_due() {
    PORT=ttyUSB
}
linux_mega() {
    PORT=ttyUSB
}
linux_uno() {
    PORT=ttyACM
}


parse_arguments $*

${OS}_${TYPE}

OUTPUT=`find /dev -name $PORT* 2>/dev/null | head -1`

echo $OUTPUT
#!/bin/sh

export SEARDUINO_VERSION=$(cat mk/VERSION)

export ARDUINO=
export BOARD=
export CPU=

MY_OS=$(uname -s)

if [ "$MY_OS" = "Linux" ]
then
    if [ "$(uname -m | grep -c _64)" != "0" ]
	then
	echo "No support for 64 bit"
	exit 1
    else
	BIN_DIST_FILE=searduino-bin-${SEARDUINO_VERSION}-x86.tar.gz
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

find_dist_file()
{
    export DIST_FILE=$(ls -1t searduino-*.tar | head -1)
    if [ ! -f $DIST_FILE ]
    then
	echo "DIST_FILE ($DIST_FILE) missing"
	exit 1
    fi
}

build_local()
{
    exec_comm ./configure
    exec_comm make clean
    exec_comm make lib
    exec_comm make stub
    exec_comm make check-sw
    exec_comm make check-hw
    

    exec_comm make dist

    find_dist_file
}

build_dist()
{
    find_dist_file

    exec_comm rm -fr tmp-searduino
    exec_comm mkdir -p tmp-searduino
    exec_comm cp  $DIST_FILE tmp-searduino/
    cd tmp-searduino/
    
    exec_comm tar xvf $DIST_FILE
    
    exec_comm rm -fr /opt/searduino
    exec_comm ./configure --prefix=/opt/

    exec_comm make clean
    exec_comm make lib
    exec_comm make stub
    exec_comm make check-hw
    exec_comm make check-sw
    exec_comm make install
}

build_bin_dist()
{
    CURR_DIR=$(pwd)
    cd /opt

    exec_comm tar zcvf /tmp/${BIN_DIST_FILE} searduino

    cd /tmp
    exec_comm cp -r /opt/searduino/example .
    cd example/digpins/
    pwd
    exec_comm make clean
    exec_comm make all
    export LD_LIBRARY_PATH=/opt/searduino/libs
    ./blinker
}


build_local
build_dist
build_bin_dist


echo "Done :)"
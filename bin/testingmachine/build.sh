#!/bin/sh

SCRIPT_DIR=$(dirname $0)
if [ -f $SCRIPT_DIR/functions ]
then
    . $SCRIPT_DIR/functions 
else
    echo "Failed sourcing functions file: '$SCRIPT_DIR/functions' "
    exit 1
fi

setup_debian_ubuntu()
{
    if [ "$ARCH" = "Arm" ]
	CONF_ARGS="--disable-python-extension --enable-debian-sources --disable-java-extension --disable-jearduino"
    else
	DEFAULT_JAVA_PATH=/usr/lib/jvm/java-7-openjdk-amd64/include/
	
	export CFLAGS="-I${DEFAULT_JAVA_PATH} -I${DEFAULT_JAVA_PATH}/linux/"
	export CXXFLAGS="-I${DEFAULT_JAVA_PATH} -I${DEFAULT_JAVA_PATH}/linux/"
	CONF_ARGS="--disable-python-extension --enable-debian-sources"
    fi
}

setup_per_dist() 
{
    set_dist
    if [ "$DIST" = "Ubuntu" ]
    then
	setup_debian_ubuntu
    elif [ "$DIST" = "Debian" ]
    then
	setup_debian_ubuntu
    else
	echo "No setup possible for: $DIST"
	return 1
    fi
}



setup_per_dist
cd $SCRIPT_DIR/../../
#
#
#
make -f Makefile.git 
exit_on_error "$?" "Creating configure scripts"

./configure $CONF_ARGS
exit_on_error "$?" "Configuring"

make
exit_on_error "$?" "make"

make check
exit_on_error "$?" "make check"


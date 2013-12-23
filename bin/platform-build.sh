#!/bin/sh

OS=$(uname -o)

exit_on_error()
{
    if [ "$1" != "0" ]
    then
	echo "ERROR: $2"
	exit $1
    fi
}

set_dist()
{
    if [ "$OS" = "GNU/Linux" ] 
    then
	PROC_VERSION=$(cat /proc/version)
	case "$PROC_VERSION" in 
	   *buntu* )
		DIST="Ubuntu"
		;;
	    *ebian*)
		DIST="Debian"
		;;
	    *)
		echo "Unsupport dist: $PROC_VERSION"
		exit
		;;
	esac
    else
	echo "Unsupport OS: $OS"
	exit
    fi
}


set_debian_ubuntu()
{
    DEFAULT_JAVA_PATH=/usr/lib/jvm/java-7-openjdk-amd64/include/
    export CFLAGS="-I${DEFAULT_JAVA_PATH} -I${DEFAULT_JAVA_PATH}/linux/"
    export CXXFLAGS="-I${DEFAULT_JAVA_PATH} -I${DEFAULT_JAVA_PATH}/linux/"


    CONF_ARGS="--disable-python-extension --enable-debian-sources"
}

setup_per_dist() 
{
    if [ "$DIST" = "Ubuntu" ]
    then
	set_debian_ubuntu
    elif [ "$DIST" = "Debian" ]
    then
	set_debian_ubuntu
    fi
}



set_dist
echo "OS:   $OS"
echo "DIST: $DIST"
setup_per_dist


make -f Makefile.git 
exit_on_error "$?" "Creating configure scripts"

./configure $CONF_ARGS
exit_on_error "$?" "Configuring"

make
exit_on_error "$?" "make"

make check
exit_on_error "$?" "make check"

#!/bin/bash


OS=$(uname -o)


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
    sudo apt-get update
    sudo apt-get update --fix-missing
    sudo apt-get install -y git openjdk-7-jdk python2.7-dev autoconf-archive check avr-libc avrdude binutils-avr gcc-avr gcc g++ arduino bc
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

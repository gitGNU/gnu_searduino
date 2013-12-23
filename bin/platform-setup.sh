#!/bin/bash


OS=$(uname -o)
MACHINE=$(uname -m)

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
	case "$MACHINE" in 
	    *x86* )
		ARCH="x86"
		;;
	    *arm*)
		ARCH="Arm"
		;;
            *)
		echo "Unsupport machine: $MACHINE"
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
    sudo apt-get install -y git  autoconf-archive check avr-libc avrdude binutils-avr gcc-avr gcc g++ arduino bc
    if [ "$MACHINE" = "x86" ]
	then
	sudo apt-get install -y git openjdk-7-jdk python2.7-dev 
    fi
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

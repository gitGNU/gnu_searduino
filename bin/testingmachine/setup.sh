#!/bin/bash



setup_debian_ubuntu()
{
    sudo apt-get update
    sudo apt-get update --fix-missing
    sudo apt-get install -y git  autoconf-archive check avr-libc avrdude binutils-avr gcc-avr gcc g++ arduino bc
    if [ "$MACHINE" = "x86" ]
	then
	sudo apt-get install -y git openjdk-7-jdk python2.7-dev 
    fi
}

setup_raspbian()
{
    sudo apt-get update
    sudo apt-get update --fix-missing
    sudo apt-get install -y git  autoconf-archive check avr-libc avrdude binutils-avr gcc-avr gcc g++ arduino bc
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
    elif [ "$DIST" = "Raspbian" ]
    then
	setup_raspbian
    else
	echo "No setup possible for: $DIST"
	return 1
    fi
}


setup_per_dist

#!/bin/sh

DOC_PKGS=" pandoc " 

DEVEL_PKGS="avrdude avr-gcc avr-g++  openjdk-6-jdk  arduino libtool autoconf automake gcc g++  python2.7-dev  autoconf-archive  python-dev  lib32z1-dev  check  gcc-avr binutils-avr avrdude avr-libc libtool"

my_install() 
{
    apt-get install -y  $*
}


my_install $DOC_PKGS

my_install $DEVEL_PKGS


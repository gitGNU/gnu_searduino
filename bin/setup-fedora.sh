#!/bin/sh

DOC_PKGS=" pandoc " 

DEVEL_PKGS=" java-1.7.0-openjdk-devel  avr-binutils avr-gcc avr-gcc-c++ avr-libc avrdude automake autoconf autoconf-arhive libtool gcc-c++ libXtst-devel arduino"

my_install() 
{
    yum install -y  $*
}


my_install $DOC_PKGS

my_install $DEVEL_PKGS


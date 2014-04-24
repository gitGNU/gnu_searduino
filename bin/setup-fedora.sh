#!/bin/sh

DOC_PKGS=" pandoc " 

DEVEL_PKGS=" java-1.7.0-openjdk-devel  avr-binutils avr-gcc avr-gcc-g++ avr-libc avrdude automake autoconf libtool gcc-c++ libXtst-devel"

my_install() 
{
    yum install -y  $*
}


my_install $DOC_PKGS

my_install $DEVEL_PKGS


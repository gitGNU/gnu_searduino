#!/bin/sh

DOC_PKGS=" pandoc " 

DEVEL_PKGS="avrdude gcc gcc-avr  openjdk-7-jdk  arduino libtool autoconf automake gcc g++  python2.7-dev  autoconf-archive  python-dev    check binutils-avr avrdude avr-libc libtool"

my_install() 
{
    yum install -y  $*
}


my_install $DOC_PKGS

my_install $DEVEL_PKGS


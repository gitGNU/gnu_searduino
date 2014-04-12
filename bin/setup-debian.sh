#!/bin/sh

DOC_PKGS=" pandoc " 
# python2.7-dev python-dev
DEVEL_PKGS="avrdude gcc gcc-avr  openjdk-6-jdk  arduino libtool autoconf automake gcc g++    autoconf-archive      check binutils-avr avrdude avr-libc libtool"

my_install() 
{
    apt-get install -y  $*
}


my_install $DOC_PKGS

my_install $DEVEL_PKGS


#!/bin/sh

DOC_PKGS=" pandoc " 
# python2.7-dev python-dev
DEVEL_PKGS="avrdude gcc gcc-avr  openjdk-7-jdk  arduino libtool autoconf automake gcc g++    autoconf-archive      check binutils-avr avrdude avr-libc libtool libxtst-dev libxcb-xtest0 libxext-dev"

my_install() 
{
    apt-get install -y  $*
}


my_install $DOC_PKGS

my_install $DEVEL_PKGS


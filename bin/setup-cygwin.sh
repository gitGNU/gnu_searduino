#!/bin/sh

PKGS=" install make automake autoconf autoconf-archive libtool gcc-core gcc-g++ check pkg-config unzip "

my_install() 
{
    apt-cyg install  $*
}


my_install $PKGS


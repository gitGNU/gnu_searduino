#!/bin/sh

PKGS=" install make automake autoconf autoconf-archive libtool gcc-core gcc-g++ check pkg-config unzip "



for i in $PKGS
do
    apt-cyg install  $i
done


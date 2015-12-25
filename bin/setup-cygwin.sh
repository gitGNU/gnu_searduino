#!/bin/sh

PKGS="  make automake autoconf autoconf-archive libtool gcc-core gcc-g++ check pkg-config unzip "



for i in $PKGS
do
    echo apt-cyg install  $i
done


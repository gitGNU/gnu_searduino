#!/bin/sh

DOC_PKGS=" pandoc texinfo  texlive-fonts-recommended texi2html  texlive-extra-utils texlive-font-utils doxygen " 
# python2.7-dev python-dev
DEVEL_PKGS="avrdude gcc gcc-avr  openjdk-6-jdk  arduino libtool autoconf automake gcc g++    autoconf-archive      check binutils-avr avrdude avr-libc libtool pkg-config  libxtst-dev  python-dev zlib1g-dev "



my_install() 
{
    apt-get install -y  $*
}


my_install $DOC_PKGS

my_install $DEVEL_PKGS


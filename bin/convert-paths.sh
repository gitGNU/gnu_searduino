#!/bin/bash

rm -f $1.new

cat $1 |\
 sed -e 's,=/,=C:\\,g' -e 's,/,\\,g' > $1.new
if [ "$?" != "0" ]
then
    echo "Failed creating new makefile for $1"
    exit 1
fi

echo "mv $1.new $1"

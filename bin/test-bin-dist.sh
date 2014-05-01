#!/bin/sh

INSTALL_DIR=/opt/
DIST_FILE=$(pwd)/$1

if [ ! -f $DIST_FILE ]
then
    echo "$DIST_FILE does not exist"
    exho ....
    exit 1
fi



cleanup() 
{
    cd $INSTALL_DIR/../
    if [ "$?" != "0" ]
    then
	echo "Uh oh...."
	exit 1
    fi

    #Looks a bit stupid, but just to be safe (see further down)
    rm -fr searduino
    cd -
}


unpack() 
{
    tar zxvf $DIST_FILE
}

check_file()
{
    if [ ! -f $1 ]
    then
	echo "Could not find file: $1"
	FILES_MISSING="$FILES_MISSING $1"
    fi
}

check_files()
{
    FILES_MISSING=""
    check_file $INSTALL_DIR/searduino/share/doc/searduino/searduino-jearduino.pdf
    check_file $INSTALL_DIR/searduino/bin/searduino-jearduino.sh 
    check_file $INSTALL_DIR/opt/searduino/lib/libsearduinostub.so
}

do_all()
{
    #cleanup
    #unpack
    check_file
}


cd $INSTALL_DIR/

do_all

echo "Files missing: $FILES_MISSING"

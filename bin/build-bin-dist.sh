#!/bin/bash

PACKAGE=searduino
TMP_INST=/opt/$PACKAGE

#DEFAULT_JAVA_PATH=/usr/lib/jvm/java-7-openjdk-amd64/include/

FUNC_FILE=$(dirname $0)/functions
if [ ! -f $FUNC_FILE ] || [ "$FUNC_FILE" = "" ]
then
    echo "Can't find the file: '$FUNC_FILE'"
    echo "... bailing out"
    exit 1
fi

. $FUNC_FILE



prepare()
{
    if [ -d ${TMP_INST}/ ]
	then
	sudo rm -fr ${TMP_INST}/*
    fi
    make -f Makefile.git 
    exit_on_failure $? "make -f Makefile.git"

#    if [ "$CFLAGS" = "" ]
#    then
#	export CFLAGS="-I${DEFAULT_JAVA_PATH} -I${DEFAULT_JAVA_PATH}/linux/"
#    fi

#    if [ "$CXXFLAGS" = "" ]
#    then
#	export CXXFLAGS="-I${DEFAULT_JAVA_PATH} -I${DEFAULT_JAVA_PATH}/linux/"
#    fi
    
    
    if [ "x$MY_OS" != "xDarwin" ]
    then
	./configure --prefix=${TMP_INST}   --enable-doc --disable-pearduino --disable-python-extension --enable-avrtools-copy 
        #--enable-unittest
	exit_on_failure $? "configure"
    else
	./configure --prefix=${TMP_INST}  --enable-doc  --disable-pearduino --disable-python-extension --enable-avrtools-copy 
	exit_on_failure $? "configure"
    fi
}

build()
{
    make clean
    exit_on_failure $? "make clean"

    make 
    exit_on_failure $? "make "

    make doc
    exit_on_failure $? "make "

    sudo make install
    exit_on_failure $? "make install"
}


check()
{
    make check
    exit_on_failure $? "make check"

    SAVED_DIR=$(pwd)

    cd ${TMP_INST}/share/searduino/example/digpins/ && make -f Makefile.digpins clean prog  && make -f Makefile.digpins clean shlib
    exit_on_failure $? "make digpins in install dir"
    
    cd ${TMP_INST}/share/searduino/example/python-digcounter && make -f Makefile.digcounter clean prog && make -f Makefile.digcounter clean shlib
    exit_on_failure $? "make digcounter in installed dir"

    cd ${SAVED_DIR}
}


packit()
{
    START_DIR=$(pwd)
    TAR_FILE=${START_DIR}/$PACKAGE-bin-$SEARD_VERSION-${MY_OS}-${CPU}.tar
    cd $TMP_INST
    cd ..
    rm -f   ${TAR_FILE}*
    tar cvf ${TAR_FILE} $PACKAGE
    gzip    ${TAR_FILE}
}

log "Building and checking"

init_logging

log_and_exec prepare
log_and_exec build
#log_and_exec check
log_and_exec packit

close_logging



exit 0


#!/bin/bash

PACKAGE=searduino
TMP_INST=/opt/$PACKAGE

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
	rm -fr ${TMP_INST}/*
    fi
    make -f Makefile.git 
    exit_on_failure $? "make -f Makefile.git"

    export CFLAGS=/usr/lib/jvm/java-6-sun-1.6.0.26/include/
    export CXXFLAGS=/usr/lib/jvm/java-6-sun-1.6.0.26/include/

    ./configure --prefix=${TMP_INST}  --enable-unittest 
    exit_on_failure $? "configure"
}

build()
{
    make clean
    exit_on_failure $? "make clean"

    make 
    exit_on_failure $? "make "

    make install
    exit_on_failure $? "make install"
}


check()
{
    make check
    exit_on_failure $? "make check"

    SAVED_DIR=$(pwd)

    cd ${TMP_INST}/share/searduino/example/digpins/ && make -f Makefile.digpins clean all
    exit_on_failure $? "make digpins in install dir"
    
    cd ${TMP_INST}/share/searduino/example/python-digcounter && make -f Makefile.digcounter clean all
    exit_on_failure $? "make digcounter in installed dir"

    cd ${SAVED_DIR}
}


packit()
{
    START_DIR=$(pwd)
    cd $TMP_INST
    cd ..
    rm -f   ${START_DIR}/$PACKAGE-bin-$SEARD_VERSION-${CPU}.tar*
    tar cvf ${START_DIR}/$PACKAGE-bin-$SEARD_VERSION-${CPU}.tar $PACKAGE
    gzip    ${START_DIR}/$PACKAGE-bin-$SEARD_VERSION-${CPU}.tar
}

log "Building and checking"

init_logging

log_and_exec prepare
log_and_exec build
log_and_exec check
log_and_exec packit

close_logging



exit 0


#!/bin/bash

LOG_FILE=test-dist.log

FUNC_FILE=$(dirname $0)/functions
if [ ! -f $FUNC_FILE ] || [ "$FUNC_FILE" = "" ]
then
    echo "Can't find the file: 'function'"
    echo "... bailing out"
    exit 1
fi

source $FUNC_FILE

DIST_FILE=$1
if [ "$DIST_FILE" = "" ]
then
    DIST_FILE=$(ls -1t seard*.tar.gz | head -1)
fi

if [ "$DIST_FILE" = "" ]
then
    echo "No dist file to test ... bailing out"
    exit 1
fi

echo "Working with: $DIST_FILE"

TMP_INST=/tmp/TMP_INSTALL3

prepare()
{
    CUR_DIR=$(pwd)

    rm -fr /tmp/TMP-SEARD
    mkdir  /tmp/TMP-SEARD
    cd     /tmp/TMP-SEARD

    
    tar zxvf ${CUR_DIR}/${DIST_FILE}
    exit_on_failure $? "Unpacking DIST_FILE: ${CUR_DIR}/${DIST_FILE}"

    cd *
    exit_on_failure $? "Changing directory"
    
    ./configure --prefix=/tmp/TMP-SEARD-INSTALL --enable-unittest 
    exit_on_failure $? "configure"
}

build()
{
    make
    exit_on_failure $? "make"
}

check_sw()
{
    make check
    exit_on_failure $? "make check"
}

install_sw()
{
    make install
    exit_on_failure $? "make install"
}

test_code()
{
    cd /tmp/TMP-SEARD-INSTALL/share/searduino/example/digpins/ && make -f Makefile.digpins clean all
    exit_on_failure $? "make digpins in install dir (testing dist) (in $(pwd))"
    
    cd /tmp/TMP-SEARD-INSTALL/share/searduino/example/python-digcounter/ && make -f Makefile.digcounter clean all
    exit_on_failure $? "make digcounter in installed dir (testing dist)  (in $(pwd))"
}


init_logging
log "Testing distribution"

log_and_exec prepare
log_and_exec build
log_and_exec check_sw
log_and_exec install_sw
log_and_exec test_code
close_logging

exit 0


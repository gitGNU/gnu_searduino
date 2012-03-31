#!/bin/bash

TMP_INST=/tmp/TMP_INSTALL3

LOG_FILE=build-and-test.log


FUNC_FILE=$(dirname $0)/functions
if [ ! -f $FUNC_FILE ] || [ "$FUNC_FILE" = "" ]
then
    echo "Can't find the file: 'function'"
    echo "... bailing out"
    exit 1
fi

. $FUNC_FILE


prepare()
{
    rm -fr ${TMP_INSTALL}
    make -f Makefile.git 
    exit_on_failure $? "make -f Makefile.git"

    ./configure --prefix=${TMP_INST}  --enable-unittest
    exit_on_failure $? "configure"
}

doc()
{
    cd doc

    make clean
    exit_on_failure $? "make clean in doc"

    make all
    exit_on_failure $? "make in doc"
    
    cd ..
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


cov_prepare()
{
    make clean

    rm -fr ${TMP_INSTALL}
    make -f Makefile.git 
    exit_on_failure $? "make -f Makefile.git"

    ./configure --disable-shared-test  --disable-shared --enable-unittest  --prefix=${TMP_INST} 
    exit_on_failure $? "configure"
}

cov()
{
    export COV_FLAGS=" -fprofile-arcs -ftest-coverage -g "
    make clean
    exit_on_failure $? "make clean"

    export CFLAGS="$COV_FLAGS" 
    export CXXFLAGS="$COV_FLAGS" 
    export CFLAGS="$COV_FLAGS -ldl" 
#    make CFLAGS="$COV_FLAGS" CXXFLAGS="$COV_FLAGS" CFLAGS="$COV_FLAGS -ldl"  coverage
    make LDFLAGS=" -fprofile-arcs -ftest-coverage -g"   CFLAGS=" -fprofile-arcs -ftest-coverage -g"   V=1   LDFLAGS=" -fprofile-arcs -ftest-coverage -g"   CXXFLAGS=" -fprofile-arcs -ftest-coverage -g"   coverage
    exit_on_failure $? "make coverage"
    export CFLAGS="" 
    export CXXFLAGS="" 
    export CFLAGS="" 
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

dist()
{
    pwd

    make dist
    exit_on_failure $? "make dist"
}


log "Building and checking"

init_logging

log_and_exec prepare
log_and_exec build
log_and_exec doc
log_and_exec check
log_and_exec dist
log_and_exec cov_prepare
log_and_exec cov

close_logging

DIST_FILE=$(ls -1t seard*.tar.gz | head -1)
echo "To test the dist:"
echo "#  bin/test-dist.sh $DIST_FILE"
exit 0

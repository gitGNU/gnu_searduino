#!/bin/bash

TMP_INST=/tmp/TMP_INSTALL3

LOG_FILE=build-and-test.log

log()
{
    echo "$*"
}

logn()
{
    printf "%40s:" "$(echo $* | awk '{ print $1}' )"
}

exit_on_failure()
{
    STOP_SEC=$(date '+%s')
    if [ $1 -ne 0 ]
    then
	echo "ERROR:  $2"
	exit $1
    else
	printf " OK ($(( $STOP_SEC - $LOCAL_START_SEC )) seconds)\n"
    fi
}

log_and_exec()
{
    LOCAL_START_SEC=$(date '+%s')
    logn "$*"
    $*   2&>1 >> $LOG_FILE
    exit_on_failure $? ""
}


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
    rm -fr ${TMP_INSTALL}
    make -f Makefile.git 
    exit_on_failure $? "make -f Makefile.git"

    ./configure --prefix=${TMP_INST}  --enable-unittest
    exit_on_failure $? "configure"
}

cov()
{
    make clean
    exit_on_failure $? "make clean"

    make coverage
    exit_on_failure $? "make coverage"

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

rm -f $LOG_FILE

START_SEC=$(date '+%s')

log_and_exec prepare
log_and_exec build
log_and_exec doc
log_and_exec check
log_and_exec dist
log_and_exec cov_prepare
log_and_exec cov

STOP_SEC=$(date '+%s')

log "It all took: $(( $STOP_SEC - $START_SEC )) seconds."


DIST_FILE=$(ls -1t seard*.tar.gz | head -1)
echo "To test the dist:"
echo "#  bin/test-dist.sh $DIST_FILE"
exit 0

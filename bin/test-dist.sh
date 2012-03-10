#!/bin/sh

LOG_FILE=test-dist.log

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


log "Testing distribution"

rm -f $LOG_FILE

START_SEC=$(date '+%s')

log_and_exec prepare
log_and_exec build
log_and_exec check_sw
log_and_exec install_sw
log_and_exec test_code
STOP_SEC=$(date '+%s')

log "It all took: $(( $STOP_SEC - $START_SEC )) seconds."


exit 0


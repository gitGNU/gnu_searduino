#!/bin/bash

TMP_INST=/tmp/TMP_INSTALL3

LOG_FILE=test-installed.log

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



#log " * Compile static arduino code for local execution"
test_static()
{
    cd test/examples/arduino-code-static/
    exit_on_failure $? "change dir"
    make clean
    make
    exit_on_failure $? "make"
    cd $START_DIR
}

test_static2()
{
#    log " * Execute static arduino code localy"
    cd test/examples/arduino-code-static/
    make clean
    make check
    exit_on_failure $? "make check"
    cd $START_DIR
}

test_dynamic()
{
#log " * Compile dynamic arduino code for local execution"
    cd test/examples/arduino-code-dynamic/
    exit_on_failure $? "change dir"
    make clean
    make
    exit_on_failure $? "make"
    cd $START_DIR
}

test_streamed()
{

#log " * Execute dynamic code with streamed simulator"
    cd test/examples/test-c/
    exit_on_failure $? "change dir"
    
    ./launch-sim.sh
    exit_on_failure $? ""
    cd $START_DIR
}

log "Testing using examples"
START_DIR=$(pwd)

rm -f $LOG_FILE

START_SEC=$(date '+%s')


log_and_exec test_static
log_and_exec test_static2
log_and_exec test_dynamic
log_and_exec test_streamed

STOP_SEC=$(date '+%s')

log "It all took: $(( $STOP_SEC - $START_SEC )) seconds."


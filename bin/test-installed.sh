#!/bin/bash

TMP_INST=/tmp/TMP_INSTALL3

LOG_FILE=test-installed.log

FUNC_FILE=$(dirname $0)/functions

if [ ! -f $FUNC_FILE ]
then
    echo "Can't find the file: 'function'"
    echo "... bailing out"
    exit 1
fi

source $FUNC_FILE


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

init_logging
log "Testing using examples"
START_DIR=$(pwd)

log_and_exec test_static
log_and_exec test_static2
log_and_exec test_dynamic
log_and_exec test_streamed

close_logging

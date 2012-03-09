#!/bin/bash

exit_on_failure()
{
    if [ $1 -ne 0 ]
    then
	echo "ERROR:  $2"
	exit $1
    else
	echo "$2:  OK"
    fi
}


echo "Testing using examples"
START_DIR=$(pwd)

echo " * Compile static arduino code for local execution"
cd test/examples/arduino-code-static/
exit_on_failure $? "change dir"
make clean
make
exit_on_failure $? "make"
cd $START_DIR

echo " * Execute static arduino code localy"
cd test/examples/arduino-code-static/
make clean
make check
exit_on_failure $? "make check"
cd $START_DIR

echo " * Compile dynamic arduino code for local execution"
cd test/examples/arduino-code-dynamic/
exit_on_failure $? "change dir"
make clean
make
exit_on_failure $? "make"
cd $START_DIR

echo " * Execute dynamic code with streamed simulator"
cd test/examples/test-c/
exit_on_failure $? "change dir"

./launch-sim.sh
exit_on_failure $? ""
cd $START_DIR


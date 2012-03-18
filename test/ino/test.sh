#!/bin/sh

TMP_INST=/tmp/TMP_INSTALL3/

SEARDUINO_PATH=$TMP_INST
INO_EX=/tmp/ino-example
EX_PATH=/home/hesa/nongnu/searduino/tmp/searduino-examples/arduino-1.0/build/shared/examples
mkdir -p $INO_EX
cd       $INO_EX



exit_on_failure()
{
    if [ $1 -ne 0 ]
    then
	echo "ERROR:  $2"
	exit $1
    fi
}


test_ex()
{
    TYPE=$1
    EXA=$2

    $SEARDUINO_PATH/bin/arduino-ex2c    \
       --searduino-path $SEARDUINO_PATH \
       --$TYPE                          \
       --yes                            \
       $EX_PATH/$EXA
    exit_on_failure $? "Failed creating C code for $EXA"

    cd $(basename $EXA)

    make clean 
    exit_on_failure $? "Make clean in $(pwd)"
    
    make 
    exit_on_failure $? "Make in $(pwd)"
  
    if [ "$TYPE" = "uno" ] && [ "$UPLOAD" = "true" ] 
    then
	make upload 
	exit_on_failure $? "Make in $(pwd)"
    fi
  
    cd ..
}

if [ "$1" = "--upload" ]
then
    export UPLOAD="true"
fi

test_ex shlib 1.Basics/Blink/
test_ex prog  1.Basics/Blink/
test_ex uno   1.Basics/Blink/


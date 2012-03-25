#!/bin/sh

TMP_INST=/opt/searduino
SEARDUINO_PATH=$TMP_INST

INO_EX=/tmp/ino-example
EX_PATH=$TMP_INST/share/examples/arduino

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

    echo "Test: type:$TYPE $EXA"
    

    $SEARDUINO_PATH/bin/arduino-ex2c    \
       --searduino-path $SEARDUINO_PATH \
       --$TYPE                          \
       --yes                            \
       $EX_PATH/$EXA
    exit_on_failure $? "Failed creating C code for $EXA with type $TYPE  (    $SEARDUINO_PATH/bin/arduino-ex2c --searduino-path $SEARDUINO_PATH --$TYPE --yes  $EX_PATH/$EXA
)"

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

test_types()
{
    DIR=$1
    TYPES="shlib prog uno mega due"
    for t in  $TYPES
    do
	test_ex $t $DIR
    done
    
}

if [ "$1" = "--upload" ]
then
    export UPLOAD="true"
fi

#test_types ./1.Basics/AnalogReadSerial
test_types ./1.Basics/BareMinimum
test_types ./1.Basics/Blink
#test_types ./1.Basics/DigitalReadSerial
test_types ./1.Basics/Fade
#test_types ./2.Digital/BlinkWithoutDelay
test_types ./2.Digital/Button
#test_types ./2.Digital/Debounce
#test_types ./2.Digital/StateChangeDetection
#test_types ./2.Digital/toneKeyboard
#test_types ./2.Digital/toneMelody
#test_types ./2.Digital/toneMultiple
#test_types ./2.Digital/tonePitchFollower
#test_types ./3.Analog/AnalogInOutSerial
#test_types ./3.Analog/AnalogInput
#test_types ./3.Analog/AnalogWriteMega
#test_types ./3.Analog/Calibration
#test_types ./3.Analog/Fading
#test_types ./3.Analog/Smoothing
exit 0
test_types ./4.Communication/ASCIITable
test_types ./4.Communication/Dimmer
test_types ./4.Communication/Graph
test_types ./4.Communication/MIDI
test_types ./4.Communication/MultiSerialMega
test_types ./4.Communication/PhysicalPixel
test_types ./4.Communication/SerialCallResponse
test_types ./4.Communication/SerialCallResponseASCII
test_types ./4.Communication/SerialEvent
test_types ./4.Communication/VirtualColorMixer
test_types ./5.Control/Arrays
test_types ./5.Control/ForLoopIteration
test_types ./5.Control/IfStatementConditional
test_types ./5.Control/switchCase
test_types ./5.Control/switchCase2
test_types ./5.Control/WhileStatementConditional
test_types ./6.Sensors/ADXL3xx
test_types ./6.Sensors/Knock
test_types ./6.Sensors/Memsic2125
test_types ./6.Sensors/Ping
test_types ./7.Display/barGraph
test_types ./7.Display/RowColumnScanning
test_types ./8.Strings/CharacterAnalysis
test_types ./8.Strings/StringAdditionOperator
test_types ./8.Strings/StringAppendOperator
test_types ./8.Strings/StringCaseChanges
test_types ./8.Strings/StringCharacters
test_types ./8.Strings/StringComparisonOperators
test_types ./8.Strings/StringConstructors
test_types ./8.Strings/StringIndexOf
test_types ./8.Strings/StringLength
test_types ./8.Strings/StringLengthTrim
test_types ./8.Strings/StringReplace
test_types ./8.Strings/StringStartsWithEndsWith
test_types ./8.Strings/StringSubstring
test_types ./8.Strings/StringToInt
test_types ./8.Strings/StringToIntRGB

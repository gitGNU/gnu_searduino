#!/bin/sh

SEARD_TOP=../../
SEARD_INST=/tmp/seard-test-eternal

BOARDS="stub uno mega due leonardo"
PROGS="blink-fast blink-four"

exit_on_error() 
{
    if [ "$1" != "0" ] 
    then
	echo "ERROR: $2"
	exit $1
    fi
}

build_and_install()
{
    make -f Makefile.git  && \
	./configure --prefix=${SEARD_INST} --enable-unittest --enable-debian-sources \
	--enable-jearduino --enable-java-extension --enable-python-extension && \
	make clean && \
	make && \
	make install
    exit_on_error $? "Build and install Searduino at $SEARD_INST"
}


log_and_make()
{
    echo "ARDUINO=$ARDUINO $*"
    $* >/dev/null
    exit_on_error $? "$*"
}

make_a_lot()
{
    BOARD=$1
    PROG=$2

    if [ "$BOARD" = "stub" ]
	then
	RULES="clean all shlib prog"
    else
	RULES="clean all"
    fi
    
    export ARDUINO=$BOARD
    log_and_make  make -f Makefile.$PROG $RULES
}

#cd $SEARD_TOP
#build_and_install

cd $SEARD_INST/share/searduino/example/many-boards
exit_on_error $? "cd $SEARD_INST/share/searduino/example/many-boards"

for p in $PROGS
do
    for b in $BOARDS
    do
	make_a_lot $b $p
    done
done








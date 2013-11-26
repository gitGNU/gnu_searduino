#!/bin/sh

SEARD_TOP=../../
SEARD_INST=/tmp/seard-test-eternal
LIMIT=0

BOARDS="stub uno mega due leonardo"
PROGS="blink-fast blink-four"

LOG_DIR=${SEARD_INST}/tmp/logs/
DATE=$(date +%Y-%m-%d)
LOG_FILE=${LOG_DIR}/searduino-test-eternity-${DATE}
if [ ! -d ${LOG_DIR} ]
then
    mkdir -p ${LOG_DIR}
fi


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
    $* >> ${LOG_FILE}
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

rename_log_file()
{
    DATE=$(date +%Y-%m-%d)
    LOG_FILE=${LOG_DIR}/searduino-test-eternity-${DATE}
}

loop_ctr()
{
    # Inc counter
    CTR=$(( $CTR + 1 ))
    echo "Build: $CTR"
    sleep 3

    # If a limit is set
    if [ $LIMIT -ne 0 ]
    then
	# if we've reachd the limit, break
	if [ $CTR -ge $LIMIT ]
	    then
	    return 1
	fi
    fi
    return 0
}

#cd $SEARD_TOP
#build_and_install

cd $SEARD_INST/share/searduino/example/many-boards
exit_on_error $? "cd $SEARD_INST/share/searduino/example/many-boards"

CTR=0
while (true)
do
    for p in $PROGS
    do
	for b in $BOARDS
	do
	    make_a_lot $b $p
	done
    done
    rename_log_file

    loop_ctr
    if [ $? -ne 0 ]
    then
	break
    fi

done

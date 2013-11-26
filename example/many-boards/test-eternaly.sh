####################################################################
#
#       Searduino
#
#  Copyright (C) 2013 Henrik Sandklef      
#                                                                   
# This program is free software; you can redistribute it and/or     
# modify it under the terms of the GNU General Public License       
# as published by the Free Software Foundation; either version 3    
# of the License, or any later version.                             
#                                                                   
#                                                                   
# This program is distributed in the hope that it will be useful,   
# but WITHOUT ANY WARRANTY; without even the implied warranty of    
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     
# GNU General Public License for more details.                      
#                                                                   
# You should have received a copy of the GNU General Public License 
# along with this program; if not, write to the Free Software       
# Foundation, Inc., 51 Franklin Street, Boston,            
# MA  02110-1301, USA.                                              
#
####################################################################
#!/bin/sh

SEARD_TOP=../../
SEARD_INST=/tmp/seard-test-eternal
LIMIT=0

BOARDS="stub uno mega due leonardo"
BOARDS="stub "
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
    cd $SEARD_TOP
    exit_on_error $? "cd $SEARD_TOP"

    make -f Makefile.git  && \
	./configure --prefix=${SEARD_INST} --enable-unittest --enable-debian-sources \
	--enable-jearduino --enable-java-extension --enable-python-extension && \
	make clean && \
	make && \
	make install
    exit_on_error $? "Build and install Searduino at $SEARD_INST"

    return 0
}


log_and_make()
{
    echo "ARDUINO=$ARDUINO $*"
    $* >> ${LOG_FILE}
    exit_on_error $? "$*"
    return 0
}

make_a_lot()
{
    BOARD=$1
    PROG=$2

    if [ "$BANNER_MODE" = "true" ]
    then
	banner "$BOARD"
	banner "$PROG"
    fi

    if [ "$BOARD" = "stub" ]
	then
	RULES="clean "
    else
	RULES="clean all"
	if [ "$UPLOAD_MODE" = "true" ]
	    then
	    RULES="$RULES upload"
	fi
    fi
    

    if [ "$BOARD" = "stub" ]
	then

	#
	if [ "$SIMULATOR_MODE" = "stream" ]
	then
	    RULES="$RULES shlib"

	    export ARDUINO=$BOARD
	    log_and_make  make -f Makefile.$PROG $RULES

	    ${SEARD_INST}/bin/searduino-stream-sim --arduino-code ./$PROG.so 
	elif [ "$SIMULATOR_MODE" = "jearduino" ]
	then
	    RULES="$RULES shlib"

	    export ARDUINO=$BOARD
	    log_and_make  make -f Makefile.$PROG $RULES

	    ${SEARD_INST}/bin/searduino-jearduino.sh --arduino-code ./$PROG.so --board $ARDUINO
	else
	    RULES="$RULES prog"

	    export ARDUINO=$BOARD
	    log_and_make  make -f Makefile.$PROG $RULES

	    ./$PROG
	    exit_on_error $? "Executing ./$PROG"
	fi

    fi

    exit_on_error $? "make -f Makefile.$PROG $RULES"
    return 0
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


###################################################
#
# Main
#
###################################################
while [ "$1" != "" ]
do
    case "$1" in 
	"--full")
	    build_and_install
	    exit_on_error $? "build_and_install"
	    ;;
	"--banner")
	    BANNER_MODE=true
	    ;;
	"--upload")
	    UPLOAD_MODE=true
	    ;;
	"--simulator")
	    SIMULATOR_MODE=$2
	    shift
	    ;;
    esac
    shift
done
	

# Go to installation dir
cd $SEARD_INST/share/searduino/example/many-boards
exit_on_error $? "cd $SEARD_INST/share/searduino/example/many-boards"

#
# Main loop
#
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

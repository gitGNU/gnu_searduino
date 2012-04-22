#!/bin/sh

LOG_FILE=build-win.log
TMP_INST=/opt/searduino-win

FUNC_FILE=$(dirname $0)/functions
if [ ! -f $FUNC_FILE ] || [ "$FUNC_FILE" = "" ]
then
    echo "Can't find the file: 'function'"
    echo "... bailing out"
    exit 1
fi
. $FUNC_FILE

init_logging


CONF_FLAGS="--host=i686-w64-mingw32"
CONF_FLAGS="$CONF_FLAGS  --disable-python"
CONF_FLAGS="$CONF_FLAGS  --prefix=/opt/searduino-win"
CONF_FLAGS="$CONF_FLAGS  --disable-unittest"

export SEARD_OS=CYGWIN
log_and_exec   make -f Makefile.git

LOCAL_START_SEC=$(date '+%s')
logn "$*"
export CFLAGS="-I/opt/searduino-win/dlfcn/include/ " 
#export CFLAGS="-I/opt/searduino-win/dlfcn/include/ -I/opt/searduino-win/pthread/include/" 
#export CFLAGS="-I/home/hesa/cyg-dev/include " 
#export LDFLAGS="-I/home/hesa/cyg-dev/lib " 
export LDFLAGS="-L/opt/searduino-win/dlfcn/lib -ldl"
# -L/opt/searduino-win/pthread/lib -lpthread"
./configure $CONF_FLAGS   >> $REAL_LOG_FILE  2>> $REAL_LOG_FILE 
exit_on_failure $? ""

#rm -fr /opt/searduino/*
#log_and_exec   make
#log_and_exec   make install







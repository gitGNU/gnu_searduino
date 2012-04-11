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


CONF_FLAGS="--host i686-w64-mingw32"
CONF_FLAGS="$CONF_FLAGS  --disable-python"
CONF_FLAGS="$CONF_FLAGS  --prefix=/opt/searduino-win"
CONF_FLAGS="$CONF_FLAGS  --disable-unittest"
PRE_FLAGS="CFLAGS=\"-I/opt/searduino-win/dlfcn/include/\""
PRE_FLAGS="$PRE_FLAGS  LDFLAGS=\"-I/opt/searduino-win/dlfcn/lib -ldl\""

export SEARD_OS=CYGWIN
#log_and_exec   make -f Makefile.git
#log_and_exec   $PRE_FLAGS ./configure $CONF_FLAGS
echo   $PRE_FLAGS ./configure $CONF_FLAGS






#!/bin/bash


LOG_FILE=mega-test.log
FUNC_FILE=$(dirname $0)/functions
if [ ! -f $FUNC_FILE ] || [ "$FUNC_FILE" = "" ]
then
    echo "Can't find the file: 'function'"
    echo "... bailing out"
    exit 1
fi

source $FUNC_FILE


init_logging

log_and_exec "bin/build-and-test.sh"

DIST_FILE=$(ls -1t seard*.tar.gz | head -1)

log_and_exec "bin/test-dist.sh $DIST_FILE"

log_and_exec "bin/test-installed.sh"

close_logging

exit 0




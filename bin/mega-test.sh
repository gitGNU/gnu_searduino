#!/bin/sh

LOG_FILE=mega-test.log

log()
{
    echo "$*"
}

logn()
{
    printf "%40s:" "$(echo $* | awk '{ print $1}' )"
}

exit_on_failure()
{
    STOP_SEC=$(date '+%s')
    if [ $1 -ne 0 ]
    then
	echo "ERROR:  $2"
	exit $1
    else
	printf " OK ($(( $STOP_SEC - $LOCAL_START_SEC )) seconds)\n"
    fi
}

log_and_exec()
{
    LOCAL_START_SEC=$(date '+%s')
    logn "$*"
    $*  >> $LOG_FILE 2&>1
    exit_on_failure $? ""
}

rm -f $LOG_FILE

START_SEC=$(date '+%s')

log_and_exec "bin/build-and-test.sh"

DIST_FILE=$(ls -1t seard*.tar.gz | head -1)

log_and_exec "bin/test-dist.sh $DIST_FILE"

log_and_exec "bin/test-installed.sh"

STOP_SEC=$(date '+%s')

log "It all took: $(( $STOP_SEC - $START_SEC )) seconds."





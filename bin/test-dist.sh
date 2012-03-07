#!/bin/sh


DIST_FILE=$1
if [ "$DIST_FILE" = "" ]
then
    DIST_FILE=$(ls -1t seard*.tar.gz | head -1)
fi

if [ "$DIST_FILE" = "" ]
then
    echo "No dist file to test ... bailing out"
    exit 1
fi

echo "Working with: $DIST_FILE"

TMP_INST=/tmp/TMP_INSTALL3

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


test_dist()
{
    CUR_DIR=$(pwd)

    rm -fr /tmp/TMP-SEARD
    mkdir  /tmp/TMP-SEARD
    cd     /tmp/TMP-SEARD

    
    tar zxvf ${CUR_DIR}/${DIST_FILE}
    exit_on_failure $? "Unpacking DIST_FILE: ${CUR_DIR}/${DIST_FILE}"

    cd *
    exit_on_failure $? "Changing directory"
    
    ./configure --prefix=/tmp/TMP-SEARD-INSTALL --enable-unittest 
    exit_on_failure $? "configure"

    make
    exit_on_failure $? "make"

    make check
    exit_on_failure $? "make check"

    make install
    exit_on_failure $? "make install"

    cd /tmp/TMP-SEARD-INSTALL/share/searduino/example/digpins/ && make -f Makefile.digpins clean all
    exit_on_failure $? "make digpins in install dir (testing dist) (in $(pwd))"
    
    cd /tmp/TMP-SEARD-INSTALL/share/searduino/example/python-digcounter/ && make -f Makefile.digcounter clean all
    exit_on_failure $? "make digcounter in installed dir (testing dist)  (in $(pwd))"
}

test_dist 
exit 0

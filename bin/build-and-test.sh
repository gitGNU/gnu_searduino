#!/bin/bash

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

prepare()
{
    rm -fr ${TMP_INSTALL}
    make -f Makefile.git 
    exit_on_failure $? "make -f Makefile.git"

    ./configure --prefix=${TMP_INST}  --enable-unittest
    exit_on_failure $? "configure"
}

doc()
{
    cd doc

    make clean
    exit_on_failure $? "make clean in doc"

    make all
    exit_on_failure $? "make in doc"
    
    cd ..
}

build()
{
    make clean
    exit_on_failure $? "make clean"

    make 
    exit_on_failure $? "make "

    make install
    exit_on_failure $? "make install"
}


cov_prepare()
{
    rm -fr ${TMP_INSTALL}
    make -f Makefile.git 
    exit_on_failure $? "make -f Makefile.git"

    ./configure --prefix=${TMP_INST}  --enable-unittest
    exit_on_failure $? "configure"
}

cov()
{
    make clean
    exit_on_failure $? "make clean"

    make coverage
    exit_on_failure $? "make coverage"

}

check()
{
    make check
    exit_on_failure $? "make check"

    SAVED_DIR=$(pwd)

    cd ${TMP_INST}/share/searduino/example/digpins/ && make -f Makefile.digpins clean all
    exit_on_failure $? "make digpins in install dir"
    
    cd ${TMP_INST}/share/searduino/example/python-digcounter && make -f Makefile.digcounter clean all
    exit_on_failure $? "make digcounter in installed dir"

    cd ${SAVED_DIR}
}

dist()
{
    pwd

    make dist
    exit_on_failure $? "make dist"
}



test_dist()
{
    DIST_FILE=$(ls -1t seard*.tar.gz | head -1)
    echo "Working with: $DIST_FILE"
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

prepare
build
doc
check
dist
test_dist
cov_prepare
cov

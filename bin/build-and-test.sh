#!/bin/bash

TMP_INST=/tmp/TMP_INSTALL3

#cd searduino
rm -fr /tmp/TMP_INSTALL3/ && \
make -f Makefile.git      && \
./configure --prefix=${TMP_INST}  --enable-unittest && \
make clean && make && \
cd mk/ && make clean && make && make install && cd .. && \
cd arduino-sources/ && make clean && make && make install && cd .. && \
cd faked-arduino/ && make clean && make && make install && cd .. && \
cd extensions/ && make clean && make && make install && cd .. && \
cd example/ && make clean && make && make install && cd .. && \
echo "Test 1 in vcs dir " && \
cd test/ && cd hw && make clean && make && make check && cd ../.. && \
echo "Test 2 in vcs dir " && \
cd test/ && cd shared && make clean && make && make check && cd ../.. && \
echo "Test 3 in vcs dir " && \
cd test/ && cd shared-main && make clean && make && make check && cd ../.. && \
echo "Test 4 in vcs dir " && \
cd test/ && cd stub && make clean && make && make check && cd ../..  && \
echo "TEST 1 in dest dir" && \
pushd ${TMP_INST}/share/searduino/example/digpins/ && make -f Makefile.digpins clean all && popd && \
echo "TEST 2 in dest dir" && \
pushd ${TMP_INST}/share/searduino/example/python-digcounter && make -f Makefile.digcounter clean all && popd \
echo "Done"
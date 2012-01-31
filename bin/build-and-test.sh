#!/bin/bash

TMP_INST=/tmp/TMP_INSTALL3

#cd searduino
rm -fr /tmp/TMP_INSTALL3/ && \
make -f Makefile.git      && \
./configure --prefix=${TMP_INST}  --enable-unittest && \
make clean && make && make check && make install && \
pushd ${TMP_INST}/share/searduino/example/digpins/ && make -f Makefile.digpins clean all && popd && \
echo "TEST 2 in dest dir" && \
pushd ${TMP_INST}/share/searduino/example/python-digcounter && make -f Makefile.digcounter clean all && popd \
echo "Done"

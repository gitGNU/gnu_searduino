#!/bin/sh

TMP_INST=/tmp/TMP_INSTALL3

#cd searduino
rm -fr /tmp/TMP_INSTALL3/ && \
make -f Makefile.git      && \
./configure --prefix=${TMP_INST} && \
make && \
cd example/ && make && make install && cd .. && \
 cd mk/ && make && make install && cd .. && \
cd arduino-sources/ && make && make install && cd .. && \
cd extensions/ && make && make install && cd .. && \
cd test/ && cd hw && make && make check && cd ../.. && \
cd test/ && cd shared && make && make check && cd ../.. && \
cd test/ && cd shared-main && make && make check && cd ../.. && \
cd test/ && cd stub && make && make check && cd ../..  && \
pushd ${TMP_INST}/share/searduino/example/digpins/ && make -f Makefile.digpins clean all && popd
#!/bin/sh


SEARDUINO_PATH=/tmp/TMP_INSTALL3/
ARD_CODE=../

export LD_LIBRARY_PATH=${SEARDUINO_PATH}/lib
export DYLD_LIBRARY_PATH=${SEARDUINO_PATH}/lib

${SEARDUINO_PATH}/bin/searduino-stream-sim --arduino-code ../arduino-code-dynamic/libarduino-test-code.so


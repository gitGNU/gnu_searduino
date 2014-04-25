#!/bin/sh


VMM=/opt/bin/tm-vmm
#CLIENT=Ubuntu-12-04-32
CLIENT=Ubuntu-13-04-x86
SNAPSHOT_NAME=SEARD_BASE
DIST=ubuntu


FUNC=$(dirname $0)/vmm-test-functions
if [ -f $FUNC ]
then
    . $FUNC
else
    echo "Failed finding functions file ....."
    exit 1
fi

vmm_test  $*

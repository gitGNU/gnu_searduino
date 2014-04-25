#!/bin/sh


VMM=/opt/bin/tm-vmm
CLIENT=Fedora19
SNAPSHOT_NAME=SEARD_BASE
DIST="fedora"


FUNC=$(dirname $0)/vmm-test-functions
if [ -f $FUNC ]
then
    . $FUNC
else
    echo "Failed finding functions file ....."
    exit 1
fi

vmm_test  $*

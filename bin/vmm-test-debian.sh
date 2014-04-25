#!/bin/sh

VMM=/opt/bin/tm-vmm
CLIENT=Debian-6-0-6
SNAPSHOT_NAME=SEARD_BASE
DIST="debian"


FUNC=$(dirname $0)/vmm-test-functions
if [ -f $FUNC ]
then
    . $FUNC
else
    echo "Failed finding functions file ....."
    exit 1
fi

vmm_test  $*



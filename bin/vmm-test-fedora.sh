#!/bin/sh


VMM=/opt/bin/tm-vmm
CLIENT=Fedora19
SNAPSHOT_NAME=SEARD_BASE




exit_on_err()
{
    if [ "$1" != "0" ]
    then
	echo "$2 failed: $1"
	exit 1
    fi
}

snapshot()
{
    $VMM --take-snapshot $CLIENT $SNAPSHOT_NAME
    exit_on_err $? " take snapshot client"
}


prepare()
{
    $VMM --start-client $CLIENT 
    exit_on_err $? " start client"

    $VMM --wait-for-client $CLIENT 
    exit_on_err $? " wait for client"

    $VMM --client-exec-as-root  $CLIENT "yum install -y git"
    exit_on_err $? "install git"
    
    $VMM --client-exec $CLIENT "rm -fr searduino ; git clone http://git.savannah.gnu.org/r/searduino.git"
    exit_on_err $? " git clone"

    $VMM --client-exec-as-root  $CLIENT "cd /home/vmm/searduino && bin/setup-fedora.sh"
    exit_on_err $? " setup"

}

build()
{
    $VMM --client-exec  $CLIENT "cd searduino && bin/build-ubuntu.sh $FED_ARGS"
    exit_on_err $? " build"
}

stop()
{
    $VMM --stop-client $CLIENT 
    exit_on_err $? " restore client"

}

restore()
{
    $VMM --restore-snapshot $CLIENT $SNAPSHOT_NAME
    exit_on_err $? " restore client"

    $VMM --delete-snapshot $CLIENT $SNAPSHOT_NAME
    exit_on_err $? " restore client"
}


do_all() 
{
    snapshot
    prepare 
    build
    stop
    restore
}

TASKS="all"
FED_ARGS=""

while [ "$1" != "" ]
do
    case "$1" in
	 "--client" )
	    CLIENT=$2
	    shift
	    ;;
	"--fedora" )
	    FED_ARGS="fedora"
	    ;;
	 * )
	    TASKS=$1
	    ;;
    esac

    shift
done

case "$TASKS" in
    "all" )
	do_all
	;;
    "snapshot")
	snapshot
	;;
    "prepare")
	prepare
	;;
    "build")
	build
	;;
    "stop")
	stop
	;;
    "restore")
	restore
	;;
esac




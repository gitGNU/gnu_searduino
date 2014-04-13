#!/bin/sh


VMM=/opt/bin/tm-vmm
CLIENT=Debian-6-0-6
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

    $VMM --client-exec-as-root  $CLIENT "apt-get install -y git"
    exit_on_err $? "install git"
    
    $VMM --client-exec $CLIENT "rm -fr searduino ; git clone http://git.savannah.gnu.org/r/searduino.git"
    exit_on_err $? " git clone"

    $VMM --client-exec-as-root  $CLIENT "cd /home/vmm/searduino && bin/setup-debian.sh"
    exit_on_err $? " setup"

}

build()
{
    $VMM --client-exec  $CLIENT "cd searduino && bin/rebuild.sh $DEB_ARGS"
#    $VMM --client-exec  $CLIENT "cd searduino && make -f Makefile.git  && ./configure --prefix=/opt/ --enable-unittest --enable-debian-sources --enable-jearduino --enable-java-extension --enable-python-extension && make && make check"
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
DEB_ARGS=""

while [ "$1" != "" ]
do
    case "$1" in
	 "--client" )
	    CLIENT=$2
	    shift
	    ;;
	"--debian" )
	    DEB_ARGS="debian"
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




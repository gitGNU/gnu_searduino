#!/bin/sh

INSTALL_TOP=/opt
INSTALL_DIR=${INSTALL_TOP}/searduino
VMM=/opt/bin/tm-vmm
MY_ARCH=$(uname -m)

exit_on_err()
{
    if [ "$1" != "0" ]
    then
	echo "$2 failed: $1"
	exit 1
    fi
}



cleanup() 
{
    cd $INSTALL_TOP
    if [ "$?" != "0" ]
    then
	echo "Uh oh...."
	exit 1
    fi

    #Looks a bit stupid, but just to be safe (see further down)
    rm -fr searduino
    cd -
}


unpack() 
{
    cd $INSTALL_TOP

    tar zxvf $DIST
}

check_file()
{
    printf "  * %-30s " $(basename $1)
    if [ ! -f $1 ]
    then
	echo " FAIL"
	FILES_MISSING="$FILES_MISSING $1"
    else
	echo " OK"
    fi
}

check_files()
{
    echo "Checking files"
    FILES_MISSING=""
    check_file $INSTALL_DIR/share/doc/searduino/searduino-jearduino.pdf
    check_file $INSTALL_DIR/share/doc/searduino/searduino-jearduino.html
    check_file $INSTALL_DIR/bin/searduino-jearduino.sh 
    check_file $INSTALL_DIR/lib/libsearduinostub.so


    check_file $INSTALL_DIR/share/searduino/arduino-libs/atmega32u4/libsearduino.a
    check_file $INSTALL_DIR/share/searduino/arduino-libs/atmega32u4/liblibraries.a

    check_file $INSTALL_DIR/share/examples/arduino/01.Basics/Blink/Blink.ino
    check_file $INSTALL_DIR/include/searduino/arduino-extras/searduino.h
    check_file $INSTALL_DIR/include/searduino/seasim/seasim.h
}

verify_install()
{
    bash $INSTALL_DIR/share/searduino/scripts/verify-install.sh
}

do_all()
{
    if [ ! -f $DIST ]
    then
	echo "$DIST does not exist"
	echo ....
	exit 1
    fi

    ARCH_TEST=$(echo $DIST | grep $MY_ARCH | wc -l)
    if [ "$ARCH_TEST" = "0" ]
    then
	echo "Arch seem to differ"
	echo "  ARCH: $MY_ARCH"
	echo "  DIST: $DIST"
	exit 1
    fi

    cleanup
    unpack
    cd $INSTALL_DIR/
    check_files
    verify_install

    if [ "$FILES_MISSING" != "" ]
    then
	echo "Missing files: $FILES_MISSING"
    fi
    
}

transfer_and_exec()
{
    if [ "$CLIENT" = "" ]
    then
	echo "Missing client spscification"
	return 1
    fi
    if [ "$DIST" = "" ]
    then
	echo "Missing dist spscification"
	return 1
    fi

    SNAPSHOT_NAME=SEARD_BIN_TEST

    $VMM --take-snapshot $CLIENT $SNAPSHOT_NAME
    exit_on_err $? " take snapshot client"

    $VMM --start-client-headless $CLIENT 
    exit_on_err $? " start client"

    $VMM --wait-for-client $CLIENT 
    exit_on_err $? " wait for client"

    $VMM --wait-for-ssh $CLIENT 
    exit_on_err $? " wait for client's ssh server to be up"

    $VMM --client-exec $CLIENT "cd /tmp; rm -fr searduino-tmp ; mkdir searduino-tmp "
    exit_on_err $? " create tmp dir"

    $VMM   --client-copy-file $DIST  "$CLIENT:/tmp/searduino-tmp/"
    exit_on_err $? " copy file"

    $VMM   --client-copy-file bin/test-bin-dist.sh  "$CLIENT:/tmp/searduino-tmp/"
    exit_on_err $? " copy file"

   $VMM --client-exec-as-root  $CLIENT "cd /opt ; rm -fr searduino ; tar xvf /tmp/searduino-tmp/$DIST"
   exit_on_err $? " setup"
  
    $VMM --client-exec-as-root  $CLIENT "bash /tmp/searduino-tmp/test-bin-dist.sh --dist /tmp/searduino-tmp/$DIST --execute "
    exit_on_err $? " setup"

    $VMM --stop-client $CLIENT 
    exit_on_err $? " stop client"

    $VMM --restore-snapshot $CLIENT $SNAPSHOT_NAME
    exit_on_err $? " restore client"

    $VMM --delete-snapshot $CLIENT $SNAPSHOT_NAME
    exit_on_err $? " restore client"
    
}



while [ "$1" != "" ]
do
    case "$1" in
	"--execute")
	    do_all
	    exit 0
	    ;;
	"--client")
	    CLIENT=$2
	    shift
	    ;;
	"--dist")
	    DIST=$2
	    shift
	    ;;
	*)
	    DIST=$1
    esac
    shift
done

# on host
transfer_and_exec

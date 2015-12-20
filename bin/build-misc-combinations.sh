#!/bin/sh

MACH=$(uname -m)

if [ "$MACH" = "i686" ]
then
    ARCH=i386
else
    ARCH=amd64
fi

MY_OS=$(uname -s     | tr [A-Z] [a-z] )
CPU=$(uname -m       | tr [A-Z] [a-z] )
KERNEL=$(uname -r -v | tr [A-Z] [a-z] )

echo "MY_OS:  $MY_OS"
echo "MACH:   $MACH"
echo "CPU:    $CPU"

case "$MY_OS" in
    "*linux*" )
        case "$KERNEL" in
            *buntu*)
                DIST="ubuntu"
                ;;
            *ebian*)
                DIST="debian"
                ;;
            *edora*)
                DIST="fedora"
                ;;
            *)
                echo "Can't determine OS/Dist"
                exit 1
                ;;
        esac
        ;;
    "*arwin*")
        DIST=darwin
        ;;
    *)
        echo "Can't determine OS/Dist"
        exit 1
        ;;
esac

#exit

#for arg in " " "--avrtools-copy" "--cflags"

for arg in " " "--arduino-sources" "--bin-dist"  "--only-check" "--avrtools-copy" "--cflags"
do
    echo "---> =========================== $0 '$arg' ==================="
    $(dirname $0)/build-$DIST.sh $arg
    if [ $? -ne  0 ]
    then
        echo "Failure: build-ubuntu.sh $arg"
        exit 1
    fi
    echo "<--- =========================== $0 '$arg' ==================="
done


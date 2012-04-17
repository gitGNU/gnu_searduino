#!/bin/bash

DIST_FILE=$1

FUNC_FILE=$(dirname $0)/functions
if [ ! -f $FUNC_FILE ] || [ "$FUNC_FILE" = "" ]
then
    echo "Can't find the file: 'function'"
    echo "... bailing out"
    exit 1
fi

. $FUNC_FILE



if [ ! -f $DIST_FILE ] || [ "$DIST_FILE" = "" ]
then
    echo "Dist file '$DIST_FILE' not found..."
    exit 1
fi

copy_file()
{
    FILE=$1
    DEST_BASE=dl.sv.nongnu.org:/releases/searduino


    if [ "$(echo $FILE | grep bin)" != "" ]
	then	
	SRC_DIST=false
	OS_DIR=""
	if [ "$MY_OS" = "Linux" ]
	then
	    OS_DIR="gnu-linux/"
	elif [ "${MY_OS:0:5}" = "CYGWI" ]
	then
	    OS_DIR="cygwin/"
	elif [ "${MY_OS:0:6}" = "Darwin" ]
	then
	    OS_DIR="osx/"
	else
	    echo "Currently no support for non GNU/Linux platforms"
	    echo "Contact the searduino team"
	    exit 1
	fi
	DEST=$DEST_BASE/bin/$OS_DIR/
    elif [ "$(echo $FILE | grep doc)" != "" ]
	then
	SRC_DIST=false
	DEST=$DEST_BASE/doc
    else
	SRC_DIST=true

	echo "Signing $DIST_FILE: gpg -b $DIST_FILE"
	gpg -b $DIST_FILE
	
	echo "Verifying: gpg --verify $DIST_FILE"
	gpg --verify $DIST_FILE.sig
	
	echo "Changing permissions"
	chmod 644 ${DIST_FILE} 
	chmod 644 ${DIST_FILE}.sig

	DEST=$DEST_BASE/src
    fi

#    echo "Copying $FILE to $DEST"
#    echo "Ok?  [y/*]"
#    read TMP_ANSWER
#    if [ "$TMP_ANSWER" != "y" ]
#    then
#	echo "Did NOT do:"
#	echo "   scp  $FILE $DEST"
#    else
	echo "#  scp  $FILE $DEST"
#    fi
}


SRC_DIST=unset
copy_file ${DIST_FILE} 
if [ "$SRC_DIST" = "true" ] ;
then
    copy_file ${DIST_FILE}.sig
fi
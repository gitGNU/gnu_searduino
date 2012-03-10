#!/bin/sh

DIST_FILE=$1

if [ ! -f $DIST_FILE ] || [ "$DIST_FILE" = "" ]
then
    echo "Dist file '$DIST_FILE' not found..."
    exit 1
fi



echo "Signing $DIST_FILE: gpg -b $DIST_FILE"
gpg -b $DIST_FILE

echo "Verifying: gpg --verify $DIST_FILE"
gpg --verify $DIST_FILE.sig

echo "Changing permissions"
chmod 644 ${DIST_FILE} 
chmod 644 ${DIST_FILE}.sig

copy_file()
{
    FILE=$1
    DEST_BASE=dl.sv.nongnu.org:/releases/searduino

    if [ "$(echo $FILE | grep bin)" != "" ]
	then
	DEST=$DEST_BASE/bin
    elif [ "$(echo $FILE | grep doc)" != "" ]
	then
	DEST=$DEST_BASE/doc
    else
	DEST=$DEST_BASE/src
    fi

    echo "Copying $FILE to $DEST"
    echo "Ok?  [y/*]"
    read TMP_ANSWER
    if [ "$TMP_ANSWER" != "y" ]
    then
	echo "Did NOT do:"
	echo "   scp  $FILE $DEST"
    else
	echo "#  scp  $FILE $DEST"
    fi
}


echo "Copying files"
for i in ${DIST_FILE}  ${DIST_FILE}.sig  
do
    copy_file $i
done

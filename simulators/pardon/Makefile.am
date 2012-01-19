AUTOMAKE_OPTIONS = gnu
bin_SCRIPTS = searduino-pardon.sh pardon.py
EXTRA_DIST = searduino-pardon.sh.in

CLEAN_FILES=searduino-pardon.sh



searduino-pardon.sh:
	cat searduino-pardon.sh.in | sed 's,__DEST_DIR__,$(prefix),g' >> $@
	chmod a+x searduino-pardon.sh
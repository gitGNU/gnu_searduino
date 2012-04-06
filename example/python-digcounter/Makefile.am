pkgdataexampledir = $(pkgdatadir)/example/python-digcounter/

EXTRA_DIST= simple-hw.sh.tmpl

dist_pkgdataexample_DATA = \
  ard_code.c \
  Makefile.digcounter \
  Makefile.tmpl \
  simple-hw.py  \
  simple-hw.sh


check2:
	make -f Makefile.digcounter clean
	make -f Makefile.digcounter prog
	make -f Makefile.digcounter clean
	make -f Makefile.digcounter shlib

pkgdataexampledir = $(pkgdatadir)/example/hid/
dist_pkgdataexample_DATA = \
  Makefile.hid \
  Makefile.tmpl




check2:
	make -f Makefile.hid clean
	make -f Makefile.hid prog
	make -f Makefile.hid clean
	make -f Makefile.hid shlib

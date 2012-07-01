pkgdataexampledir = $(pkgdatadir)/example/digpins/
dist_pkgdataexample_DATA = \
  Makefile.hid \
  Makefile.tmpl




check2:
	make -f Makefile.digpins clean
	make -f Makefile.digpins prog
	make -f Makefile.digpins clean
	make -f Makefile.digpins shlib

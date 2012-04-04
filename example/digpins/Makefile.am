pkgdataexampledir = $(pkgdatadir)/example/digpins/
dist_pkgdataexample_DATA = \
  blink.c \
  blink.h \
  main.c  \
  Makefile.digpins \
  Makefile.tmpl



check:
	make -f Makefile.digpins clean
	make -f Makefile.digpins prog
	make -f Makefile.digpins clean
	make -f Makefile.digpins shlib

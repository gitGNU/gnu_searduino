pkgdataexampledir = $(pkgdatadir)/example/digital-rw/
dist_pkgdataexample_DATA = \
  main.c                   \
  Makefile.digitalrw



check2:
	make -f Makefile.digitalrw clean
	make -f Makefile.digitalrw prog
	make -f Makefile.digitalrw clean
	make -f Makefile.digitalrw shlib

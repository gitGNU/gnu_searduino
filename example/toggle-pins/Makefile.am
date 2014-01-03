pkgdataexampledir = $(pkgdatadir)/example/lcd-shield/
dist_pkgdataexample_DATA = \
  main.c                    \
  Makefile.toggle-pins       \
  Makefile.tmpl



check2:
	make -f Makefile.lcd-shield clean
	make -f Makefile.lcd-shield prog
	make -f Makefile.lcd-shield clean
	make -f Makefile.lcd-shield shlib

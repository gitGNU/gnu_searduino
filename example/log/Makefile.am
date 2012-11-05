pkgdataexampledir = $(pkgdatadir)/example/log/
dist_pkgdataexample_DATA = \
  Makefile.log \
  Makefile.tmpl \
  main.c 


check2:
	make -f Makefile.log clean
	make -f Makefile.log prog
	make -f Makefile.log clean
	make -f Makefile.log shlib

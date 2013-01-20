pkgdataexampledir = $(pkgdatadir)/example/serial/
dist_pkgdataexample_DATA = \
 main.c \
 Makefile.serial \
 Makefile.tmpl \
 serial.cpp



check2:
	make -f Makefile.serial clean
	make -f Makefile.serial prog
	make -f Makefile.serial clean
	make -f Makefile.serial shlib

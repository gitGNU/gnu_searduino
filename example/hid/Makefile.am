pkgdataexampledir = $(pkgdatadir)/example/hid/
dist_pkgdataexample_DATA = \
  Makefile.hid \
  Makefile.tmpl \
  kbd.cpp \
  kbd.h \
  main.c \
  mouse.cpp \
  mouse.h


check2:
	make -f Makefile.hid clean
	make -f Makefile.hid prog
	make -f Makefile.hid clean
	make -f Makefile.hid shlib

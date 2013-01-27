docdir = $(datadir)/searduino

library_includedir=$(includedir)/searduino/seasim
library_include_HEADERS =  \
	seasim.h 

doc: 
	doxygen

seasim.pdf: doc
	cd latex && make pdf && cp refman.pdf ../seasim.pdf

install: 

doc-install:doc seasim.pdf
	mkdir -p $(DESTDIR)/$(docdir)
	cp seasim.pdf $(DESTDIR)$(docdir)/
	cp -r html $(DESTDIR)$(docdir)/

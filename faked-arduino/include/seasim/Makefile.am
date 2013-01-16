docdir = $(datadir)/searduino

library_includedir=$(includedir)/searduino/seasim
library_include_HEADERS =  \
	seasim.h 

seasim.pdf: doc
	cd latex && make pdf && cp refman.pdf ../seasim.pdf

doc: seasim.pdf
	doxygen

install: doc
	mkdir -p $(DESTDIR)/$(docdir)
	cp seasim.pdf $(DESTDIR)$(docdir)/
	cp -r html $(DESTDIR)$(docdir)/

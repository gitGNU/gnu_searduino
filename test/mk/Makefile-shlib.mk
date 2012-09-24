dummy:
	@echo make love instead of all

all:

check: 
	make -f ../mk/Makefile.stub     clean check-shlib

install:
	echo nothing to do in install

distdir:
	echo nothing to do in dist

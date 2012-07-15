dummy:
	@echo make love instead of all

all:

check: 
	make -f ../mk/Makefile.mega     clean check-lib lib-install
	make -f ../mk/Makefile.mega2560 clean check-lib lib-install
	make -f ../mk/Makefile.uno      clean check-lib lib-install
	make -f ../mk/Makefile.leonardo clean check-lib lib-install
	make -f ../mk/Makefile.stub     clean check-lib lib-install


test2:
	make -f ../mk/Makefile.mega2560 clean check-lib
	make -f ../mk/Makefile.uno      clean check-lib
	make -f ../mk/Makefile.leonardo clean check-lib
	make -f ../mk/Makefile.stub     clean check-lib

distdir:
	echo nothing to do in dist

install:

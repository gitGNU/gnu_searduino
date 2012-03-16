DATE=$(shell date '+%Y%m%d-%H%M%S')
DATE_SHORT=$(shell date '+%d %b %Y')
MONTH=$(shell date '+%b %Y')
VERSION=$(shell ../bin/get-version)
#| sed -e 's,\[,,g' -e  's,\],,g' -e 's/,//g')
all: doc
VIEWER=evince
TEXI=architecture.texi manual.texi
TEXI_INC=abbrevs.texi  background.texi  supported.texi download.texi
PDF := $(TEXI:.texi=.pdf)
HTML := $(TEXI:.texi=.html)
TXT := $(TEXI:.texi=.txt)
DOC= $(PDF) $(HTML) $(TXT)
DOC_DIST=searduino-docs-$(VERSION).tar.gz
DAILY_DOC_DIST=searduino-docs-$(DATE).tar.gz
SRC=$(TEXI) Makefile ../mk/VERSION $(TEXI_INC)


UPDATED_MONTH=UPDATED-MONTH=

version.texi:
	echo "@set UPDATED $(DATE_SHORT)" > version.texi
	echo "@set UPDATED_MONTH $(MONTH) " >> version.texi
	echo "@set EDITION $(VERSION)" >> version.texi
	echo "@set VERSION $(VERSION)" >> version.texi

daily-version:
	echo "@set UPDATED $(DATE_SHORT)" > version.texi
	echo "@set UPDATED_MONTH $(MONTH) " >> version.texi
	echo "@set EDITION $(DATE)" >> version.texi
	echo "@set VERSION $(DATE)" >> version.texi


REMOVE=*.aux *.cp *.fn *.ky *.log *.pdf *.pg *.toc *.tp *.vr *~  *.cps $(DOC) version.texi

%.pdf:%.texi
	texi2pdf $< 

%.html:%.texi
	texi2html $<

%.txt:%.texi
	makeinfo -o $@ --no-headers --no-split --no-validate $<

clean:
	rm -fr $(REMOVE) 

pdf:  $(SRC) 
html: $(HTML)
txt:  $(TXT)
doc:  $(DOC)

$(PDF): $(SRC) Makefile version.texi

li:
	echo "PDF $(PDF)"

dist: $(DOC) version.texi
	tar cvfz $(DOC_DIST) $(SRC) 
	mkdir -p dists
	mv $(DOC_DIST) dists/

daily-doc: 
	make clean
	make daily-version
	make $(DOC)
	tar cvfz $(DAILY_DOC_DIST) $(DOC)
	mkdir -p dists
	mv $(DAILY_DOC_DIST) dists/

view: $(PDF)
	$(VIEWER) $(PDF) 

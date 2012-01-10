DATE=$(shell date '+%Y%m%d-%H%M%S')
VERSION=$(shell cat ../mk/VERSION)
all: doc
VIEWER=evince
TEXI=architecture.texi manual.texi
TEXI_INC=abbrevs.texi  background.texi  supported.texi download.texi
PDF := $(TEXI:.texi=.pdf)
HTML := $(TEXI:.texi=.html)
TXT := $(TEXI:.texi=.txt)
DOC= $(PDF) $(HTML) $(TXT)
DOC_DIST=searduino-docs-$(VERSION).tar.gz
SRC=$(TEXI) Makefile ../mk/VERSION $(TEXI_INC)


REMOVE=*.aux *.cp *.fn *.ky *.log *.pdf *.pg *.toc *.tp *.vr *~  $(DOC)

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

$(PDF): $(SRC) Makefile

li:
	echo "PDF $(PDF)"

dist: $(DOC)
	tar cvfz $(DOC_DIST) $(SRC) 
	mkdir -p dists
	mv $(DOC_DIST) dists/

view: $(PDF)
	$(VIEWER) $(PDF) 

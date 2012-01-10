DATE=$(shell date '+%Y%m%d-%H%M%S')
all: doc
VIEWER=evince
TEXI=architecture.texi manual.texi
PDF := $(TEXI:.texi=.pdf)
HTML := $(TEXI:.texi=.html)
TXT := $(TEXI:.texi=.txt)
DOC= $(PDF) $(HTML) $(TXT)
DOC_DIST=searduino-docs-$(DATE).tar.gz
SRC=$(TEXI) Makefile


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

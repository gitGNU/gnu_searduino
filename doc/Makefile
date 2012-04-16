DATE=$(shell date '+%Y%m%d-%H%M%S')
DATE_SHORT=$(shell date '+%d %b %Y')
MONTH=$(shell date '+%b %Y')
VERSION=$(shell sh ../bin/functions  --version)
SRC2TEXI=../bin/c2texi
M2TEXI=../bin/makefile2texi
#| sed -e 's,\[,,g' -e  's,\],,g' -e 's/,//g')
all: doc
VIEWER=evince
TEXI=architecture.texi manual.texi
TEXI_INC=abbrevs.texi  background.texi  supported.texi download.texi examples.texi
PDF := $(TEXI:.texi=.pdf)
HTML := $(TEXI:.texi=.html)
TXT := $(TEXI:.texi=.txt)
DOC= $(PDF) $(HTML) $(TXT)
DOC_DIST=searduino-docs-$(VERSION).tar.gz
DAILY_DOC_DIST=searduino-docs-$(DATE).tar.gz
SRC=$(TEXI) Makefile ../mk/VERSION $(TEXI_INC)
C_FILES=example_01.c
M_FILES=example_m_01.m
C_EXAMPLES := $(C_FILES:.c=.texi)
M_EXAMPLES := $(M_FILES:.m=.texi)

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



%.texi:%.c
	$(SRC2TEXI) $< 

%.texi:%.m
	$(M2TEXI) $< 

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

$(PDF): $(SRC) Makefile version.texi $(TEXI_INC) $(TEXI) $(C_EXAMPLES) $(M_EXAMPLES)

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


check1:
	-mkdir -p tmp-doc-test
	cp example_01.c tmp-doc-test/seardex.c
	cat example_m_01.m | sed 's,ARDUINO=[a-z]*,ARDUINO=stub,g' > tmp-doc-test/Makefile
	cd tmp-doc-test/ && make clean shlib 
	cd tmp-doc-test/ && make clean prog
	cat example_m_01.m | sed 's,ARDUINO=[a-z]*,ARDUINO=uno,g' > tmp-doc-test/Makefile
	cd tmp-doc-test/ && make clean prog

check: check1

SUBDIRS = faked-arduino extensions simulators mk arduino-sources example test


TOPDIR=./
COVERAGE_OUT ?= $(TOPDIR)/reports/coverage
PROFILE_OUT ?= $(TOPDIR)/reports/profile
GCOV_FLAG = " -fprofile-arcs -ftest-coverage -g"
GPROF_FLAG = "-pg -g"


init-cov:
	make clean
	lcov --directory . --zerocounters

build-cov:
	cd arduino-sources && make
	cd faked-arduino && make CFLAGS=$(GCOV_FLAG)   CXXFLAGS=$(GCOV_FLAG)  
	cd example && make CFLAGS=$(GCOV_FLAG)   CXXFLAGS=$(GCOV_FLAG)  
	cd extensions && make CFLAGS=$(GCOV_FLAG)   CXXFLAGS=$(GCOV_FLAG)  
	cd simulators && make CFLAGS=$(GCOV_FLAG)   CXXFLAGS=$(GCOV_FLAG)  
	make check
	mkdir -p $(COVERAGE_OUT)
	lcov --directory ./ --output-file $(COVERAGE_OUT)/$(PACKAGE).info \
		--capture

gen-coverage:
	genhtml --output-directory $(COVERAGE_OUT) \
		$(COVERAGE_OUT)/$(PACKAGE).info \
		--highlight --frames --legend \
		--title "$(PACKAGE_NAME)"

coverage: init-cov build-cov gen-coverage 


old-check:
	cd test/ && cd hw && make clean && make && make check
	cd test/ && cd shared && make clean && make && make check 
	cd test/ && cd shared-main && make clean && make && make check
	cd test/ && cd stub && make clean && make && make check

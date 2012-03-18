SUBDIRS = arduino-sources arduino-extras faked-arduino extensions simulators mk example test 

ARD_SRC = arduino-sources/core/wiring_analog.c arduino-sources/core/main.cpp arduino-sources/core/WString.cpp arduino-sources/core/HID.cpp arduino-sources/core/new.cpp arduino-sources/core/wiring_shift.c arduino-sources/core/IPAddress.cpp arduino-sources/core/Stream.cpp arduino-sources/core/wiring_pulse.c arduino-sources/core/wiring_digital.c arduino-sources/core/CDC.cpp arduino-sources/core/WMath.cpp arduino-sources/core/HardwareSerial.cpp arduino-sources/core/wiring.c arduino-sources/core/Tone.cpp arduino-sources/core/USBCore.cpp arduino-sources/core/WInterrupts.c arduino-sources/core/Print.cpp arduino-sources/core/WCharacter.h arduino-sources/core/Printable.h arduino-sources/core/HardwareSerial.h arduino-sources/core/Server.h arduino-sources/core/Print.h arduino-sources/core/Udp.h arduino-sources/core/USBDesc.h arduino-sources/core/USBCore.h arduino-sources/core/new.h arduino-sources/core/USBAPI.h arduino-sources/core/wiring_private.h arduino-sources/core/Platform.h arduino-sources/core/Stream.h arduino-sources/core/WString.h arduino-sources/core/Arduino.h arduino-sources/core/binary.h arduino-sources/core/Client.h arduino-sources/core/IPAddress.h arduino-sources/variants/micro/pins_arduino.h arduino-sources/variants/mega/pins_arduino.h arduino-sources/variants/eightanaloginputs/pins_arduino.h arduino-sources/variants/leonardo/pins_arduino.h arduino-sources/variants/standard/pins_arduino.h  

SCRIPT_SRC = bin/build-and-test.sh bin/get-arduino-src.sh 


bin_SCRIPTS = bin/arduino-ex2c bin/functions

pkgdataexampledir = $(pkgdatadir)/tmpl

dist_pkgdataexample_DATA = \
  tmpl/main_c.tmpl     \
  tmpl/post_c.tmpl     \
  tmpl/pre_c.tmpl      \
  tmpl/Makefile.tmpl


EXTRA_DIST =  ${ARD_SRC} ${SCRIPT_SRC}


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

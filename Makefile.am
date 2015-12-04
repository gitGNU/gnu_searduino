if DEBIAN_SOURCES
   SUBDIRS =         debian-mk arduino-extras faked-arduino extensions simulators mk example test tools scripts 
   DIST_SUBDIRS = $(SUBDIRS)
else
   SUBDIRS =   arduino-sources arduino-extras faked-arduino extensions simulators mk example test tools scripts
   DIST_SUBDIRS = $(SUBDIRS)
endif
# lib

SCRIPT_SRC = bin/build-and-test.sh bin/get-arduino-src.sh bin/searduino-arduino-ex2c.tmpl bin/searduino-builder.tmpl  scripts/verify-install.sh bin/searduino_find_port.sh scripts/settings.tmpl scripts/functions.tmpl 


ARD_SRC= \
    arduino-sources/core/WCharacter.h \
    arduino-sources/core/Printable.h \
    arduino-sources/core/HardwareSerial.h \
    arduino-sources/core/wiring_analog.c \
    arduino-sources/core/Server.h \
    arduino-sources/core/wiring_shift.c \
    arduino-sources/core/Print.h \
    arduino-sources/core/wiring_pulse.c \
    arduino-sources/core/Udp.h \
    arduino-sources/core/wiring_digital.c \
    arduino-sources/core/USBDesc.h \
    arduino-sources/core/USBCore.h \
    arduino-sources/core/new.h \
    arduino-sources/core/wiring.c \
    arduino-sources/core/USBAPI.h \
    arduino-sources/core/wiring_private.h \
    arduino-sources/core/Platform.h \
    arduino-sources/core/Stream.h \
    arduino-sources/core/WString.h \
    arduino-sources/core/Arduino.h \
    arduino-sources/core/binary.h \
    arduino-sources/core/WInterrupts.c \
    arduino-sources/core/Client.h \
    arduino-sources/core/IPAddress.h \
    arduino-sources/variants/mega/pins_arduino.h \
    arduino-sources/variants/eightanaloginputs/pins_arduino.h \
    arduino-sources/variants/leonardo/pins_arduino.h \
    arduino-sources/variants/standard/pins_arduino.h \
arduino-sources/libraries/Ethernet/EthernetUdp.h arduino-sources/libraries/Ethernet/EthernetClient.h arduino-sources/libraries/Ethernet/Ethernet.h arduino-sources/libraries/Ethernet/EthernetServer.h arduino-sources/libraries/Ethernet/Dns.h arduino-sources/libraries/Ethernet/utility/w5100.h arduino-sources/libraries/Ethernet/utility/socket.h arduino-sources/libraries/Ethernet/util.h arduino-sources/libraries/Ethernet/Dhcp.h arduino-sources/libraries/Firmata/Firmata.h arduino-sources/libraries/Firmata/Boards.h arduino-sources/libraries/Wire/Wire.h arduino-sources/libraries/Wire/utility/twi.h arduino-sources/libraries/SPI/SPI.h arduino-sources/libraries/LiquidCrystal/LiquidCrystal.h arduino-sources/libraries/SoftwareSerial/SoftwareSerial.h arduino-sources/libraries/SD/utility/SdFat.h arduino-sources/libraries/SD/utility/Sd2Card.h arduino-sources/libraries/SD/utility/SdFatmainpage.h arduino-sources/libraries/SD/utility/Sd2PinMap.h arduino-sources/libraries/SD/utility/FatStructs.h arduino-sources/libraries/SD/utility/SdFatUtil.h arduino-sources/libraries/SD/utility/SdInfo.h arduino-sources/libraries/SD/SD.h arduino-sources/libraries/Stepper/Stepper.h arduino-sources/libraries/EEPROM/EEPROM.h arduino-sources/libraries/Servo/Servo.h 

#    arduino-sources/variants/micro/pins_arduino.h 


if DEBIANSOURCES
ARD_EXAMPLES = \
  ./ard-ex/01.Basics/AnalogReadSerial/AnalogReadSerial.ino \
  ./ard-ex/01.Basics/BareMinimum/BareMinimum.ino \
  ./ard-ex/01.Basics/Blink/Blink.ino \
  ./ard-ex/01.Basics/DigitalReadSerial/DigitalReadSerial.ino \
  ./ard-ex/01.Basics/Fade/Fade.ino \
  ./ard-ex/01.Basics/ReadAnalogVoltage/ReadAnalogVoltage.ino \
  ./ard-ex/02.Digital/BlinkWithoutDelay/BlinkWithoutDelay.ino \
  ./ard-ex/02.Digital/Button/Button.ino \
  ./ard-ex/02.Digital/Debounce/Debounce.ino \
  ./ard-ex/02.Digital/DigitalIputPullup/DigitalIputPullup.ino \
  ./ard-ex/02.Digital/StateChangeDetection/StateChangeDetection.ino \
  ./ard-ex/02.Digital/toneKeyboard/toneKeyboard.ino \
  ./ard-ex/02.Digital/toneMelody/toneMelody.ino \
  ./ard-ex/02.Digital/toneMultiple/toneMultiple.ino \
  ./ard-ex/02.Digital/tonePitchFollower/tonePitchFollower.ino \
  ./ard-ex/03.Analog/AnalogInOutSerial/AnalogInOutSerial.ino \
  ./ard-ex/03.Analog/AnalogInput/AnalogInput.ino \
  ./ard-ex/03.Analog/AnalogWriteMega/AnalogWriteMega.ino \
  ./ard-ex/03.Analog/Calibration/Calibration.ino \
  ./ard-ex/03.Analog/Fading/Fading.ino \
  ./ard-ex/03.Analog/Smoothing/Smoothing.ino \
  ./ard-ex/04.Communication/ASCIITable/ASCIITable.ino \
  ./ard-ex/04.Communication/Dimmer/Dimmer.ino \
  ./ard-ex/04.Communication/Graph/Graph.ino \
  ./ard-ex/04.Communication/MIDI/Midi.ino \
  ./ard-ex/04.Communication/MultiSerialMega/MultiSerialMega.ino \
  ./ard-ex/04.Communication/PhysicalPixel/PhysicalPixel.ino \
  ./ard-ex/04.Communication/ReadASCIIString/ReadASCIIString.ino \
  ./ard-ex/04.Communication/SerialCallResponseASCII/SerialCallResponseASCII.ino \
  ./ard-ex/04.Communication/SerialCallResponse/SerialCallResponse.ino \
  ./ard-ex/04.Communication/SerialEvent/SerialEvent.ino \
  ./ard-ex/04.Communication/VirtualColorMixer/VirtualColorMixer.ino \
  ./ard-ex/05.Control/Arrays/Arrays.ino \
  ./ard-ex/05.Control/ForLoopIteration/ForLoopIteration.ino \
  ./ard-ex/05.Control/IfStatementConditional/IfStatementConditional.ino \
  ./ard-ex/05.Control/switchCase2/switchCase2.ino \
  ./ard-ex/05.Control/switchCase/switchCase.ino \
  ./ard-ex/05.Control/WhileStatementConditional/WhileStatementConditional.ino \
  ./ard-ex/06.Sensors/ADXL3xx/ADXL3xx.ino \
  ./ard-ex/06.Sensors/Knock/Knock.ino \
  ./ard-ex/06.Sensors/Memsic2125/Memsic2125.ino \
  ./ard-ex/06.Sensors/Ping/Ping.ino \
  ./ard-ex/07.Display/barGraph/barGraph.ino \
  ./ard-ex/07.Display/RowColumnScanning/RowColumnScanning.ino \
  ./ard-ex/08.Strings/CharacterAnalysis/CharacterAnalysis.ino \
  ./ard-ex/08.Strings/StringAdditionOperator/StringAdditionOperator.ino \
  ./ard-ex/08.Strings/StringAppendOperator/StringAppendOperator.ino \
  ./ard-ex/08.Strings/StringCaseChanges/StringCaseChanges.ino \
  ./ard-ex/08.Strings/StringCharacters/StringCharacters.ino \
  ./ard-ex/08.Strings/StringComparisonOperators/StringComparisonOperators.ino \
  ./ard-ex/08.Strings/StringConstructors/StringConstructors.ino \
  ./ard-ex/08.Strings/StringIndexOf/StringIndexOf.ino \
  ./ard-ex/08.Strings/StringLength/StringLength.ino \
  ./ard-ex/08.Strings/StringLengthTrim/StringLengthTrim.ino \
  ./ard-ex/08.Strings/StringReplace/StringReplace.ino \
  ./ard-ex/08.Strings/StringStartsWithEndsWith/StringStartsWithEndsWith.ino \
  ./ard-ex/08.Strings/StringSubstring/StringSubstring.ino \
  ./ard-ex/08.Strings/StringToIntRGB/StringToIntRGB.ino \
  ./ard-ex/08.Strings/StringToInt/StringToInt.ino \
  ./ard-ex/09.USB(Leonardo)/KeyboardAndMouseControl/KeyboardAndMouseControl.ino \
  ./ard-ex/09.USB(Leonardo)/Keyboard/KeyboardLogout/KeyboardLogout.ino \
  ./ard-ex/09.USB(Leonardo)/Keyboard/KeyboardMessage/KeyboardMessage.ino \
  ./ard-ex/09.USB(Leonardo)/Keyboard/KeyboardReprogram/KeyboardReprogram.ino \
  ./ard-ex/09.USB(Leonardo)/Keyboard/KeyboardSerial/KeyboardSerial.ino \
  ./ard-ex/09.USB(Leonardo)/Mouse/ButtonMouseControl/ButtonMouseControl.ino \
  ./ard-ex/09.USB(Leonardo)/Mouse/JoystickMouseControl/JoystickMouseControl.ino \
  ./ard-ex/ArduinoISP/ArduinoISP.ino 
else
ARD_EXAMPLES = 
endif


bin_SCRIPTS = bin/searduino-arduino-ex2c bin/searduino-builder scripts/functions  bin/searduino_find_port.sh scripts/man-support
# bin/verify-install.sh
#ACLOCAL_AMFLAGS = -I.m4

pkgdataexampledir = $(pkgdatadir)/tmpl

dist_pkgdataexample_DATA = \
  tmpl/main_c.tmpl     \
  tmpl/main_tot_c.tmpl \
  tmpl/post_c.tmpl     \
  tmpl/pre_c.tmpl      \
  tmpl/Makefile.tmpl

if BUILD_DOC
MANUALS= \
 doc/searduino-arch.html \
 doc/searduino-jearduino.html \
 doc/searduino-manual.html \
 doc/searduino-arch.pdf \
 doc/searduino-jearduino.pdf \
 doc/searduino-manual.pdf \
 doc/searduino-arch.txt \
 doc/searduino-jearduino.txt \
 doc/searduino-manual.txt \
 doc/jearduino.png \
 doc/jearduino-log.png 
else
MANUALS=
endif

EXTRA_DIST =  ${SCRIPT_SRC} ${ARD_EXAMPLES} scripts/verify-install.sh.tmpl doc/Makefile.tmpl Makefile.git debian-mk/Makefile scripts/functions.tmpl scripts/settings.tmpl $(MANUALS) bin/build-functions bin/functions bin/build-ubuntu.sh bin/build-fedora.sh  bin/build-darwin.sh bin/build-debian.sh bin/build-cygwin.sh

#m4/gnulib-cache.m4
#  ${ARD_SRC}

.PHONY: doc
doc:
	cd doc && make all
	cd faked-arduino/include/seasim && doxygen

#AM_CXXFLAGS=   \
#           -I m4

#AM_CFLAGS=   \
#           -I m4



TOPDIR=./
COVERAGE_OUT ?= $(TOPDIR)/reports/coverage
PROFILE_OUT ?= $(TOPDIR)/reports/profile
GCOV_FLAG = " -fprofile-arcs -ftest-coverage -g"
GPROF_FLAG = "-pg -g"

if COPY_AVR
install-avr:
	@echo Copying avr tools from Arduino sources
	@mkdir -p $(prefix)/searduino/lib/
	@cp -r avr-tools-copy/* $(prefix)/searduino/lib/
else
install-avr:
	@echo Using existing avr tools, not copying
endif

if DEBIANSOURCES
check-local:
	echo "No local check when using Debian's Arduino sources"
else
check-local:
	scripts/verify-install.sh --vcs 
endif

init-cov:
	make clean
	lcov --directory . --zerocounters

build-cov:
	cd arduino-sources && make
	cd faked-arduino   && make CFLAGS=$(GCOV_FLAG)   CXXFLAGS=$(GCOV_FLAG)  
	cd example         && make CFLAGS=$(GCOV_FLAG)   CXXFLAGS=$(GCOV_FLAG)  
	cd extensions      && make CFLAGS=$(GCOV_FLAG)   CXXFLAGS=$(GCOV_FLAG)  
	cd simulators      && make CFLAGS=$(GCOV_FLAG)   CXXFLAGS=$(GCOV_FLAG)  
	make CFLAGS=$(GCOV_FLAG)   CXXFLAGS=$(GCOV_FLAG)  check
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


searduino-builder.1: bin/searduino-builder

man1_MANS = searduino-builder.1
	bash bin/searduino-builder --nroff searduino-builder.1

install-data-local: $(MANUALS)
	echo "$(PACKAGE)" >  version.txt
	echo "$(VERSION)" >> version.txt
	cp version.txt $(pkgdatadir)/
	mkdir -p $(docdir)/
	cp version.txt $(MANUALS)  $(docdir)/
	make install-avr

clean:
	for dir in $(SUBDIRS); do cd $$dir ; make clean ; cd - ; done

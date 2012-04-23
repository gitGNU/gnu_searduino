SUBDIRS =  libltdl arduino-sources arduino-extras faked-arduino extensions simulators mk example test 
# lib

SCRIPT_SRC = bin/build-and-test.sh bin/get-arduino-src.sh bin/arduino-ex2c.tmpl bin/functions bin/verify-install.sh bin/find_port.sh 


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
    arduino-sources/variants/micro/pins_arduino.h \
    arduino-sources/variants/mega/pins_arduino.h \
    arduino-sources/variants/eightanaloginputs/pins_arduino.h \
    arduino-sources/variants/leonardo/pins_arduino.h \
    arduino-sources/variants/standard/pins_arduino.h \
arduino-sources/libraries/Ethernet/EthernetUdp.h arduino-sources/libraries/Ethernet/EthernetClient.h arduino-sources/libraries/Ethernet/Ethernet.h arduino-sources/libraries/Ethernet/EthernetServer.h arduino-sources/libraries/Ethernet/Dns.h arduino-sources/libraries/Ethernet/utility/w5100.h arduino-sources/libraries/Ethernet/utility/socket.h arduino-sources/libraries/Ethernet/util.h arduino-sources/libraries/Ethernet/Dhcp.h arduino-sources/libraries/Firmata/Firmata.h arduino-sources/libraries/Firmata/Boards.h arduino-sources/libraries/Wire/Wire.h arduino-sources/libraries/Wire/utility/twi.h arduino-sources/libraries/SPI/SPI.h arduino-sources/libraries/LiquidCrystal/LiquidCrystal.h arduino-sources/libraries/SoftwareSerial/SoftwareSerial.h arduino-sources/libraries/SD/utility/SdFat.h arduino-sources/libraries/SD/utility/Sd2Card.h arduino-sources/libraries/SD/utility/SdFatmainpage.h arduino-sources/libraries/SD/utility/Sd2PinMap.h arduino-sources/libraries/SD/utility/FatStructs.h arduino-sources/libraries/SD/utility/SdFatUtil.h arduino-sources/libraries/SD/utility/SdInfo.h arduino-sources/libraries/SD/SD.h arduino-sources/libraries/Stepper/Stepper.h arduino-sources/libraries/EEPROM/EEPROM.h arduino-sources/libraries/Servo/Servo.h 



ARD_EXAMPLES = \
    ard-ex/ArduinoISP/ArduinoISP.ino \
    ard-ex/5.Control/switchCase/switchCase.ino \
    ard-ex/5.Control/WhileStatementConditional/WhileStatementConditional.ino \
    ard-ex/5.Control/IfStatementConditional/IfStatementConditional.ino \
    ard-ex/5.Control/switchCase2/switchCase2.ino \
    ard-ex/5.Control/ForLoopIteration/ForLoopIteration.ino \
    ard-ex/5.Control/Arrays/Arrays.ino \
    ard-ex/7.Display/RowColumnScanning/RowColumnScanning.ino \
    ard-ex/7.Display/barGraph/barGraph.ino \
    ard-ex/3.Analog/Calibration/Calibration.ino \
    ard-ex/3.Analog/Fading/Fading.ino \
    ard-ex/3.Analog/AnalogInput/AnalogInput.ino \
    ard-ex/3.Analog/Smoothing/Smoothing.ino \
    ard-ex/3.Analog/AnalogInOutSerial/AnalogInOutSerial.ino \
    ard-ex/3.Analog/AnalogWriteMega/AnalogWriteMega.ino \
    ard-ex/2.Digital/Debounce/Debounce.ino \
    ard-ex/2.Digital/BlinkWithoutDelay/BlinkWithoutDelay.ino \
    ard-ex/2.Digital/Button/Button.ino \
    ard-ex/2.Digital/StateChangeDetection/StateChangeDetection.ino \
    ard-ex/2.Digital/toneMelody/toneMelody.ino \
    ard-ex/2.Digital/toneKeyboard/toneKeyboard.ino \
    ard-ex/2.Digital/toneMultiple/toneMultiple.ino \
    ard-ex/2.Digital/tonePitchFollower/tonePitchFollower.ino \
    ard-ex/6.Sensors/Ping/Ping.ino \
    ard-ex/6.Sensors/Memsic2125/Memsic2125.ino \
    ard-ex/6.Sensors/Knock/Knock.ino \
    ard-ex/6.Sensors/ADXL3xx/ADXL3xx.ino \
    ard-ex/4.Communication/Graph/Graph.ino \
    ard-ex/4.Communication/PhysicalPixel/PhysicalPixel.ino \
    ard-ex/4.Communication/SerialEvent/SerialEvent.ino \
    ard-ex/4.Communication/VirtualColorMixer/VirtualColorMixer.ino \
    ard-ex/4.Communication/Dimmer/Dimmer.ino \
    ard-ex/4.Communication/SerialCallResponse/SerialCallResponse.ino \
    ard-ex/4.Communication/ASCIITable/ASCIITable.ino \
    ard-ex/4.Communication/SerialCallResponseASCII/SerialCallResponseASCII.ino \
    ard-ex/4.Communication/MultiSerialMega/MultiSerialMega.ino \
    ard-ex/4.Communication/MIDI/Midi.ino \
    ard-ex/8.Strings/StringConstructors/StringConstructors.ino \
    ard-ex/8.Strings/StringSubstring/StringSubstring.ino \
    ard-ex/8.Strings/StringReplace/StringReplace.ino \
    ard-ex/8.Strings/StringIndexOf/StringIndexOf.ino \
    ard-ex/8.Strings/StringStartsWithEndsWith/StringStartsWithEndsWith.ino \
    ard-ex/8.Strings/StringLengthTrim/StringLengthTrim.ino \
    ard-ex/8.Strings/StringAdditionOperator/StringAdditionOperator.ino \
    ard-ex/8.Strings/StringLength/StringLength.ino \
    ard-ex/8.Strings/StringAppendOperator/StringAppendOperator.ino \
    ard-ex/8.Strings/StringCaseChanges/StringCaseChanges.ino \
    ard-ex/8.Strings/StringComparisonOperators/StringComparisonOperators.ino \
    ard-ex/8.Strings/StringCharacters/StringCharacters.ino \
    ard-ex/8.Strings/StringToIntRGB/StringToIntRGB.ino \
    ard-ex/8.Strings/CharacterAnalysis/CharacterAnalysis.ino \
    ard-ex/8.Strings/StringToInt/StringToInt.ino \
    ard-ex/1.Basics/BareMinimum/BareMinimum.ino \
    ard-ex/1.Basics/DigitalReadSerial/DigitalReadSerial.ino \
    ard-ex/1.Basics/AnalogReadSerial/AnalogReadSerial.ino \
    ard-ex/1.Basics/Fade/Fade.ino \
    ard-ex/1.Basics/Blink/Blink.ino 


bin_SCRIPTS = bin/arduino-ex2c bin/functions bin/verify-install.sh bin/find_port.sh

#ACLOCAL_AMFLAGS = -I.m4

pkgdataexampledir = $(pkgdatadir)/tmpl

dist_pkgdataexample_DATA = \
  tmpl/main_c.tmpl     \
  tmpl/main_tot_c.tmpl \
  tmpl/post_c.tmpl     \
  tmpl/pre_c.tmpl      \
  tmpl/Makefile.tmpl



EXTRA_DIST =  ${ARD_SRC} ${SCRIPT_SRC} ${ARD_EXAMPLES} bin/verify-install.sh.tmpl 
#m4/gnulib-cache.m4



#AM_CXXFLAGS=   \
#           -I m4

#AM_CFLAGS=   \
#           -I m4



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

install-data-local:
	echo "$(PACKAGE)" >  version.txt
	echo "$(VERSION)" >> version.txt
	cp version.txt $(pkgdatadir)/

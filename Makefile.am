SUBDIRS =   arduino-sources arduino-extras faked-arduino extensions simulators mk example test tools
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
    arduino-sources/variants/mega/pins_arduino.h \
    arduino-sources/variants/eightanaloginputs/pins_arduino.h \
    arduino-sources/variants/leonardo/pins_arduino.h \
    arduino-sources/variants/standard/pins_arduino.h \
arduino-sources/libraries/Ethernet/EthernetUdp.h arduino-sources/libraries/Ethernet/EthernetClient.h arduino-sources/libraries/Ethernet/Ethernet.h arduino-sources/libraries/Ethernet/EthernetServer.h arduino-sources/libraries/Ethernet/Dns.h arduino-sources/libraries/Ethernet/utility/w5100.h arduino-sources/libraries/Ethernet/utility/socket.h arduino-sources/libraries/Ethernet/util.h arduino-sources/libraries/Ethernet/Dhcp.h arduino-sources/libraries/Firmata/Firmata.h arduino-sources/libraries/Firmata/Boards.h arduino-sources/libraries/Wire/Wire.h arduino-sources/libraries/Wire/utility/twi.h arduino-sources/libraries/SPI/SPI.h arduino-sources/libraries/LiquidCrystal/LiquidCrystal.h arduino-sources/libraries/SoftwareSerial/SoftwareSerial.h arduino-sources/libraries/SD/utility/SdFat.h arduino-sources/libraries/SD/utility/Sd2Card.h arduino-sources/libraries/SD/utility/SdFatmainpage.h arduino-sources/libraries/SD/utility/Sd2PinMap.h arduino-sources/libraries/SD/utility/FatStructs.h arduino-sources/libraries/SD/utility/SdFatUtil.h arduino-sources/libraries/SD/utility/SdInfo.h arduino-sources/libraries/SD/SD.h arduino-sources/libraries/Stepper/Stepper.h arduino-sources/libraries/EEPROM/EEPROM.h arduino-sources/libraries/Servo/Servo.h 

#    arduino-sources/variants/micro/pins_arduino.h 



ARD_EXAMPLES = \
  "./01.Basics/AnalogReadSerial/AnalogReadSerial.ino" \
  "./01.Basics/BareMinimum/BareMinimum.ino" \
  "./01.Basics/Blink/Blink.ino" \
  "./01.Basics/DigitalReadSerial/DigitalReadSerial.ino" \
  "./01.Basics/Fade/Fade.ino" \
  "./01.Basics/ReadAnalogVoltage/ReadAnalogVoltage.ino" \
  "./02.Digital/BlinkWithoutDelay/BlinkWithoutDelay.ino" \
  "./02.Digital/Button/Button.ino" \
  "./02.Digital/Debounce/Debounce.ino" \
  "./02.Digital/DigitalIputPullup/DigitalIputPullup.ino" \
  "./02.Digital/StateChangeDetection/StateChangeDetection.ino" \
  "./02.Digital/toneKeyboard/toneKeyboard.ino" \
  "./02.Digital/toneMelody/toneMelody.ino" \
  "./02.Digital/toneMultiple/toneMultiple.ino" \
  "./02.Digital/tonePitchFollower/tonePitchFollower.ino" \
  "./03.Analog/AnalogInOutSerial/AnalogInOutSerial.ino" \
  "./03.Analog/AnalogInput/AnalogInput.ino" \
  "./03.Analog/AnalogWriteMega/AnalogWriteMega.ino" \
  "./03.Analog/Calibration/Calibration.ino" \
  "./03.Analog/Fading/Fading.ino" \
  "./03.Analog/Smoothing/Smoothing.ino" \
  "./04.Communication/ASCIITable/ASCIITable.ino" \
  "./04.Communication/Dimmer/Dimmer.ino" \
  "./04.Communication/Graph/Graph.ino" \
  "./04.Communication/MIDI/Midi.ino" \
  "./04.Communication/MultiSerialMega/MultiSerialMega.ino" \
  "./04.Communication/PhysicalPixel/PhysicalPixel.ino" \
  "./04.Communication/ReadASCIIString/ReadASCIIString.ino" \
  "./04.Communication/SerialCallResponseASCII/SerialCallResponseASCII.ino" \
  "./04.Communication/SerialCallResponse/SerialCallResponse.ino" \
  "./04.Communication/SerialEvent/SerialEvent.ino" \
  "./04.Communication/VirtualColorMixer/VirtualColorMixer.ino" \
  "./05.Control/Arrays/Arrays.ino" \
  "./05.Control/ForLoopIteration/ForLoopIteration.ino" \
  "./05.Control/IfStatementConditional/IfStatementConditional.ino" \
  "./05.Control/switchCase2/switchCase2.ino" \
  "./05.Control/switchCase/switchCase.ino" \
  "./05.Control/WhileStatementConditional/WhileStatementConditional.ino" \
  "./06.Sensors/ADXL3xx/ADXL3xx.ino" \
  "./06.Sensors/Knock/Knock.ino" \
  "./06.Sensors/Memsic2125/Memsic2125.ino" \
  "./06.Sensors/Ping/Ping.ino" \
  "./07.Display/barGraph/barGraph.ino" \
  "./07.Display/RowColumnScanning/RowColumnScanning.ino" \
  "./08.Strings/CharacterAnalysis/CharacterAnalysis.ino" \
  "./08.Strings/StringAdditionOperator/StringAdditionOperator.ino" \
  "./08.Strings/StringAppendOperator/StringAppendOperator.ino" \
  "./08.Strings/StringCaseChanges/StringCaseChanges.ino" \
  "./08.Strings/StringCharacters/StringCharacters.ino" \
  "./08.Strings/StringComparisonOperators/StringComparisonOperators.ino" \
  "./08.Strings/StringConstructors/StringConstructors.ino" \
  "./08.Strings/StringIndexOf/StringIndexOf.ino" \
  "./08.Strings/StringLength/StringLength.ino" \
  "./08.Strings/StringLengthTrim/StringLengthTrim.ino" \
  "./08.Strings/StringReplace/StringReplace.ino" \
  "./08.Strings/StringStartsWithEndsWith/StringStartsWithEndsWith.ino" \
  "./08.Strings/StringSubstring/StringSubstring.ino" \
  "./08.Strings/StringToIntRGB/StringToIntRGB.ino" \
  "./08.Strings/StringToInt/StringToInt.ino" \
  "./09.USB(Leonardo)/KeyboardAndMouseControl/KeyboardAndMouseControl.ino" \
  "./09.USB(Leonardo)/Keyboard/KeyboardLogout/KeyboardLogout.ino" \
  "./09.USB(Leonardo)/Keyboard/KeyboardMessage/KeyboardMessage.ino" \
  "./09.USB(Leonardo)/Keyboard/KeyboardReprogram/KeyboardReprogram.ino" \
  "./09.USB(Leonardo)/Keyboard/KeyboardSerial/KeyboardSerial.ino" \
  "./09.USB(Leonardo)/Mouse/ButtonMouseControl/ButtonMouseControl.ino" \
  "./09.USB(Leonardo)/Mouse/JoystickMouseControl/JoystickMouseControl.ino" \
  "./ArduinoISP/ArduinoISP.ino" 



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

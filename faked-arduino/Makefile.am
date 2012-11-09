#
#       Searduino
#
#  Copyright (C) 2011, 2012 Henrik Sandklef      
#                                                                   
# This program is free software; you can redistribute it and/or     
# modify it under the terms of the GNU General Public License       
# as published by the Free Software Foundation; either version 3    
# of the License, or any later version.                             
#                                                                   
#                                                                   
# This program is distributed in the hope that it will be useful,   
# but WITHOUT ANY WARRANTY; without even the implied warranty of    
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     
# GNU General Public License for more details.                      
#                                                                   
# You should have received a copy of the GNU General Public License 
# along with this program; if not, write to the Free Software       
# Foundation, Inc., 51 Franklin Street, Boston,            
# MA  02110-1301, USA.                                              
#
#

AUTOMAKE_OPTIONS = gnu
SUBDIRS=include arduino wire EEPROM Ethernet Firmata LiquidCrystal SD Servo SoftwareSerial SPI Stepper 


LIB_SEARDUINO_H_FILES=\
       ./include/arduino/ext_io.h \
       ./include/arduino/boards/pins_due.h \
       ./include/arduino/error.h \
       ./include/arduino/boards.h \
       ./include/avr/interrupt.h \
       ./include/avr/io.h \
       ./include/avr/eeprom.h \
       ./include/avr/pgmspace.h \
       ./include/avr/util/delay.h \
       ./include/arduino/wiring_private.h \
       ./include/arduino/twi_mock.h  \
       ./include/arduino/pins_arduino.h \
       ./include/arduino/setup.h \
       ./include/seasim/seasim.h \
       ./include/utils/types.h \
       ./include/utils/error.h \
       ./include/utils/print.h \
       ./include/arduino/time_stuff.h \
       ./include/arduino/searduino_pin.h \
       ./include/arduino/searduino_log.h \
       ./include/arduino/searduino_log_impl.h \
       ./include/arduino/searduino_internal_log.h \
       ./include/arduino/setup.h \
       ./include/arduino/i2c_loader.h \
       ./include/arduino/hid-x11.h \
       ./include/arduino/hid-generic.h \
       ./include/seasim/seasim.h 

LIB_LIBRARIES_SOURCES_FILES = \
      wire/src/wire.cpp \
      wire/src/twi_mock.c \
      EEPROM/src/eeprom.cpp  \
      Ethernet/src/ethernet.cpp  \
      Firmata/src/firmata.cpp  \
      LiquidCrystal/src/liquidcrystal.cpp  \
      SD/src/sd.cpp  \
      Servo/src/servo.cpp  \
      SoftwareSerial/src/softwareserial.cpp  \
      SPI/src/spi.cpp  \
      Stepper/src/stepper.cpp  

#\
#       ./include/arduino/searduino.h

LIB_SEARDUINO_SOURCES_FILES= \
       ./arduino/src/ext_io.c \
       ./arduino/src/time_stuff.c \
       ./arduino/src/setup.c \
       ./arduino/src/searduino_pin.c \
       ./arduino/src/searduino_log.c \
       ./arduino/src/searduino_log_impl.c \
       ./arduino/src/searduino_internal_log.c \
       ./arduino/src/WString.cpp \
       ./arduino/src/WMath.cpp \
       ./arduino/src/wiring_digital.c \
       ./arduino/src/wiring_pulse.c \
       ./arduino/src/wiring_analog.c  \
       ./arduino/src/Print.cpp  \
       ./arduino/src/utils.c \
       ./seasim/src/seasim.c \
       ./utils/src/print-funs.cpp \
       ./arduino/src/HardwareSerial.cpp \
       ./arduino/src/HID.cpp \
       ./arduino/src/USBCore.cpp \
       ./arduino/src/i2c_loader.c \
       ./arduino/src/CDC.cpp \
       ./arduino/src/boards.c \
       ./arduino/src/hid-backends/x11.c     \
       ./arduino/src/hid-backends/generic.c \
        $(LIB_SEARDUINO_H_FILES)  \
        $(LIB_LIBRARIES_SOURCES_FILES)

libsearduinostub_la_SOURCES = $(LIB_SEARDUINO_SOURCES_FILES)
#libsearduino-stub_SOURCES=$(LIB_SEARDUINO_SOURCES_FILES)
#EXTRA_LTLIBRARIES = libsearduino-stub.la
lib_LTLIBRARIES = libsearduinostub.la


if USE_XTEST
XTEST_C_FLAGS = -DUSE_X11
else
XTEST_C_FLAGS =
endif



AM_CFLAGS= -I../arduino-sources/core           \
           -I../arduino-sources/libraries/Wire \
           -I../arduino-sources/libraries/Wire/utility \
           -I../faked-arduino/include/arduino  \
           -I../faked-arduino/include/         \
           -I../faked-arduino/include/avr      \
           -I../arduino-extras/include/        \
           $(PEDANTIC_FLAGS) -DPACKAGE="\"$(PACKAGE)\"" \
           -DVERSION="\"$(VERSION)\"" $(XTEST_C_FLAGS)  \
           -DSEARDUINO_STUB



AM_CXXFLAGS= -I../arduino-sources/core          \
           -I../arduino-sources/libraries/Wire  \
           -I../arduino-sources/libraries/Wire/utility \
           -I../arduino-sources/libraries/Servo \
           -I../faked-arduino/include/arduino   \
           -I../faked-arduino/include/avr       \
           -I../faked-arduino/include/          \
           -I../arduino-extras/include/         \
           $(PEDANTIC_FLAGS) $(XTEST_C_FLAGS) -DSEARDUINO_STUB

tag:
	find . -name "*.c" -o -name "*.h" -o -name "*.cpp" | xargs etags

if USE_XTEST
XTESTFLAGS = $(LIBXTST)
else
XTESTFLAGS = 
endif

AM_LDFLAGS= -ldl  $(LIBXTST)

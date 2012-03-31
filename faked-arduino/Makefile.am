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

SUBDIRS=include arduino communication wire EEPROM Ethernet Firmata LiquidCrystal SD Servo SoftwareSerial SPI Stepper 


LIB_SEARDUINO_H_FILES=\
       ./include/communication/error.h \
       ./include/communication/comm.h \
       ./include/communication/digio.h \
       ./include/communication/ext_io.h \
       ./include/arduino/boards/pins_due.h \
       ./include/arduino/error.h \
       ./include/avr/interrupt.h \
       ./include/avr/io.h \
       ./include/avr/pgmspace.h \
       ./include/avr/delay.h \
       ./include/arduino/wiring_private.h \
       ./include/arduino/pins_arduino.h \
       ./include/arduino/setup.h \
       ./include/seasim/seasim.h \
       ./include/utils/types.h \
       ./include/utils/error.h \
       ./include/utils/print.h \
       ./include/arduino/time_stuff.h \
       ./include/arduino/setup.h 

LIB_LIBRARIES_SOURCES_FILES = \
      wire/src/wire.cpp \
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
       ./communication/src/ext_io.c \
       ./communication/src/comm.c \
       ./communication/src/digio.c \
       ./arduino/src/time_stuff.c \
       ./arduino/src/setup.c \
       ./arduino/src/WString.cpp \
       ./arduino/src/wiring_digital.c \
       ./arduino/src/wiring_analog.c  \
       ./arduino/src/utils.c \
       ./seasim/src/seasim.c \
       ./utils/src/print-funs.c \
       ./arduino/src/Print.cpp \
        $(LIB_SEARDUINO_H_FILES) \
        $(LIB_LIBRARIES_SOURCES_FILES)

libsearduinostub_la_SOURCES = $(LIB_SEARDUINO_SOURCES_FILES)
#libsearduino-stub_SOURCES=$(LIB_SEARDUINO_SOURCES_FILES)
#EXTRA_LTLIBRARIES = libsearduino-stub.la
lib_LTLIBRARIES = libsearduinostub.la




AM_CFLAGS= -I../arduino-sources/core          \
           -I../faked-arduino/include/arduino \
           -I../faked-arduino/include/        \
           -I../arduino-extras/include/ 

AM_CXXFLAGS= -I../arduino-sources/core          \
           -I../arduino-sources/libraries/Wire  \
           -I../faked-arduino/include/arduino \
           -I../faked-arduino/include/        \
           -I../arduino-extras/include/ 


AM_LDFLAGS= -ldl 

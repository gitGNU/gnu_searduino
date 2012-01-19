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

LIB_SEARDUINO_H_FILES=\
       ./include/communication/error.h \
       ./include/communication/comm.h \
       ./include/communication/digio.h \
       ./include/communication/ext_io.h \
       ./include/arduino/boards/pins_due.h \
       ./include/arduino/error.h \
       ./include/arduino/avr/interrupt.h \
       ./include/arduino/avr/io.h \
       ./include/arduino/avr/pgmspace.h \
       ./include/arduino/avr/delay.h \
       ./include/arduino/wiring_private.h \
       ./include/arduino/pins_arduino.h \
       ./include/arduino/setup.h \
       ./include/utils/types.h \
       ./include/utils/error.h \
       ./include/utils/print.h

LIB_SEARDUINO_SOURCES_FILES= \
       ./communication/src/ext_io.c \
       ./communication/src/comm.c \
       ./communication/src/digio.c \
       ./arduino/src/time_stuff.c \
       ./arduino/src/setup.c \
       ./arduino/src/wiring_digital.c \
       ./arduino/src/utils.c \
       ./utils/src/print.c \
        $(LIB_SEARDUINO_H_FILES)

libsearduinostub_la_SOURCES = $(LIB_SEARDUINO_SOURCES_FILES)
#libsearduino-stub_SOURCES=$(LIB_SEARDUINO_SOURCES_FILES)
#EXTRA_LTLIBRARIES = libsearduino-stub.la
lib_LTLIBRARIES = libsearduinostub.la


AM_CFLAGS= -I../arduino-sources/core  -I../faked-arduino/include/arduino -I../faked-arduino/include/
AM_LDFLAGS=






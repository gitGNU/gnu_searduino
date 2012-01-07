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

MODULE_C_FLAGS   = -fPIC -Wl,-G -Wl,-dy \
                   -I$(SEARDUINO_PATH)/faked-arduino/arduino/include \
                   -I$(SEARDUINO_PATH)/faked-arduino/communication/include

MODULE_CXX_FLAGS = fPIC -Wl,-G -Wl,-dy \
                   -I$(SEARDUINO_PATH)/faked-arduino/arduino/include \
                   -I$(SEARDUINO_PATH)/faked-arduino/communication/include

SRC_C= ./communication/src/comm.c      \
       ./communication/src/ext_io.c \
       ./communication/src/digio.c \
       ./communication/src/read_command.c \
       ./utils/src/print.c             \
       ./arduino/src/wiring_digital.c  \
       ./arduino/src/time_stuff.c

LIB=$(SEARDUINO_PATH)/faked-arduino/libsearduino-stub.a
SHLIB=$(SEARDUINO_PATH)/faked-arduino/libsearduino-stub.so

ARDUINO=stub
BOARD=stub

SEARDUINO_PATH=..
SEARDUINO_MK=../mk/searduino.mk
SEARDUINO_LIB_MK=../mk/searduino_lib.mk
SRC_HEADERS=./communication/include/comm.h  \
            ./communication/include/ext_io.h  \
            ./communication/include/digio.h  \
            ./communication/include/read_command.h  \
            ./utils/include/types.h        \
            ./utils/include/error.h        \
            ./utils/include/print.h        \
            ./arduino/include/error.h      \
            ./arduino/include/wiring_private.h  \
            ./arduino/include/pins_arduino.h    \
            ./arduino/include/avr/delay.h       \
            ./arduino/include/avr/interrupt.h   \
            ./arduino/include/avr/pgmspace.h    \
            ./arduino/include/avr/io.h    

lib: $(LIB)
shlib: $(SHLIB)

include $(SEARDUINO_MK)
include $(SEARDUINO_LIB_MK)


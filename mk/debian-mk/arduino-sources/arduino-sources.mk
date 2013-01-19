#
#       Searduino
#                                                                   
# Basically a couple of Makefile wrapping the Ardunio
# C and C++ files
#                                                                   
#  Copyright (C) 2013 Henrik Sandklef      
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
SEARDUINO_PATH=..
DEBIAN_BUILD=true
DEBIANSOURCES=true

ARDUINO_SOURCE_PATH=/usr/share/arduino/hardware/arduino/cores/arduino/
ARDUINO_PATH=/usr/share/arduino/hardware/arduino/

SRC_C=$(ARDUINO_SOURCE_PATH)/WInterrupts.c  $(ARDUINO_SOURCE_PATH)/wiring_analog.c  $(ARDUINO_SOURCE_PATH)/wiring.c  $(ARDUINO_SOURCE_PATH)/wiring_digital.c  $(ARDUINO_SOURCE_PATH)/wiring_pulse.c  $(ARDUINO_SOURCE_PATH)/wiring_shift.c

SRC_CXX=$(ARDUINO_SOURCE_PATH)/CDC.cpp $(ARDUINO_SOURCE_PATH)/HID.cpp  $(ARDUINO_SOURCE_PATH)/Print.cpp   $(ARDUINO_SOURCE_PATH)/Tone.cpp     $(ARDUINO_SOURCE_PATH)/WMath.cpp $(ARDUINO_SOURCE_PATH)/HardwareSerial.cpp  $(ARDUINO_SOURCE_PATH)/IPAddress.cpp  $(ARDUINO_SOURCE_PATH)/new.cpp   $(ARDUINO_SOURCE_PATH)/Stream.cpp  $(ARDUINO_SOURCE_PATH)/USBCore.cpp  $(ARDUINO_SOURCE_PATH)/WString.cpp

LIB_PATH=$(SEARDUINO_PATH)/arduino-sources/libs/$(BOARD)/
LIB=$(LIB_PATH)/libsearduino.a


SEARDUINO_MK=../mk/searduino-vcs.mk
#SEARDUINO_FUNC=../mk/searduino-functions.mk

lib: $(LIB)
$(LIB): $(OBJ_C)  $(OBJ_CXX) 

include $(SEARDUINO_MK)
include $(SEARDUINO_FUNC)



objs: $(OBJ_C) $(OBJ_CXX)
	-ls -al $(OBJ_C)
	-ls -al $(OBJ_CXX)

due: ARDUINO=due
due: 
	make lib

uno: ARDUINO=uno
uno: 
	make lib

mega: ARDUINO=mega
mega: 
	make lib

mega2560: ARDUINO=mega2560
mega2560:
	make lib

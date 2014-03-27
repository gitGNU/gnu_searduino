#
#       Searduino
#                                                                   
# Basically a couple of Makefile wrapping the Ardunio
# C and C++ files
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
SEARDUINO_PATH=../
ARDUINO_PATH=./


SRC_C=core/WInterrupts.c  core/wiring_analog.c  core/wiring.c  core/wiring_digital.c  core/wiring_pulse.c  core/wiring_shift.c
SRC_CXX=core/CDC.cpp core/HID.cpp  core/Print.cpp   core/Tone.cpp     core/WMath.cpp core/HardwareSerial.cpp  core/IPAddress.cpp  core/new.cpp   core/Stream.cpp  core/USBCore.cpp  core/WString.cpp

LIB_PATH=$(SEARDUINO_PATH)/arduino-sources/lib/$(BOARD)/
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



#
#       Searduino
#
#  Copyright (C) 2011, 2012, 2013 Henrik Sandklef      
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

ifndef ARDUINO
$(error Variables not set correctly ARDUINO='${ARDUINO}')
endif		

ARDUINO_VERSION=101
SEARDUINO_MK_PATH=$(SEARDUINO_PATH)/
SEARDUINO_INC_PATH=$(SEARDUINO_PATH)/


ifeq (${DEBIANSOURCES},true)
#ARDUINO_SOURCE_PATH=/usr/share/arduino/hardware/arduino/cores/arduino/
  ARDUINO_PATH=/usr/share/arduino/hardware/arduino/
  ARDUINO_LIBS_SOURCE_PATH=/usr/share/arduino/libraries
  #Debian build only
  ARDUINO_INC_PATH=$(ARDUINO_PATH)
  ARDUINO_LIB_PATH=$(ARDUINO_PATH)
  ARDUINO_LIB_INC_PATH=$(ARDUINO_LIBS_SOURCE_PATH)/../

  ifeq (${ARDUINO},stub)
    SEARDUINO_LIB_PATH=  -L$(SEARDUINO_PATH)/faked-arduino/.libs
  else
    SEARDUINO_LIB_PATH=  -L$(ARDUINO_LIB_PATH)/arduino-sources/libs/$(BOARD) \
                         -L$(ARDUINO_LIB_PATH)/arduino-sources/libraries/libs/$(BOARD)

  endif
else
  ARDUINO_INC_PATH=$(ARDUINO_PATH)/arduino-sources/
#  ARDUINO_MK_PATH=$(ARDUINO_MK_PATH)/
  ARDUINO_LIB_INC_PATH=$(SEARDUINO_PATH)/arduino-sources/

  ifeq (${ARDUINO},stub)
    SEARDUINO_LIB_PATH=  -L$(SEARDUINO_PATH)/faked-arduino/.libs 
  else
    SEARDUINO_LIB_PATH=  -L$(SEARDUINO_PATH)/arduino-sources/libs/$(BOARD) \
                         -L$(SEARDUINO_PATH)/arduino-sources/libraries/libs/$(BOARD) 
  endif


endif

VCS_IFLAGS= -I$(SEARDUINO_INC_PATH)/arduino-extras/include \
            -I$(SEARDUINO_INC_PATH)/faked-arduino/include/arduino

ifeq (${ARDUINO},stub)
include $(SEARDUINO_MK_PATH)/mk/searduino-stub.mk
else
include $(SEARDUINO_MK_PATH)/mk/searduino-arduino.mk
endif

include $(SEARDUINO_MK_PATH)/mk/searduino-functions.mk

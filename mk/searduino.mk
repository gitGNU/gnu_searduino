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

ifndef ARDUINO
$(error Variables not set correctly ARDUINO='${ARDUINO}')
endif		

UNAME := $(shell uname -s)


ARDUINO_VERSION=100
SEARDUINO_MK_PATH=/opt/searduino/share/searduino/
SEARDUINO_INC_PATH=/opt/searduino/include/searduino/

ifeq (${ARDUINO},stub)
include $(SEARDUINO_MK_PATH)/mk/searduino-stub.mk
else
include $(SEARDUINO_MK_PATH)/mk/searduino-arduino.mk
endif

SEARDUINO_LIB_PATH=-L/opt/searduino/libs/searduino/arduino-libs/$(BOARD) -L/opt/searduino/lib

include $(SEARDUINO_MK_PATH)/mk/searduino-functions.mk

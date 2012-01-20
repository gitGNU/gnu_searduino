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

SEARDUINO_MK_PATH=/tmp/TMP_INSTALL2/share/searduino/
SEARDUINO_INC_PATH=/tmp/TMP_INSTALL2/include/searduino/

ifeq (${ARDUINO},stub)
include $(SEARDUINO_MK_PATH)/mk/searduino-stub.mk
else
include $(SEARDUINO_MK_PATH)/mk/searduino-arduino.mk
endif

SEARDUINO_LIB_PATH=/tmp/TMP_INSTALL2/searduino/arduino-libs/$(BOARD)

include $(SEARDUINO_MK_PATH)/mk/searduino-functions.mk

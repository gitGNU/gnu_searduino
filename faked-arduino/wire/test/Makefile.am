#
#       Searduino
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
if UNITTEST

TESTS = testbegin
check_PROGRAMS = testbegin

if DEBIANSOURCES
SEARDUINO_INC_PATH=/usr/share/arduino/hardware/arduino/cores/arduino/
SEARDUINO_LIB_INC_PATH=/usr/share/arduino/libraries
else
SEARDUINO_INC_PATH=../../../arduino-sources/core
SEARDUINO_LIB_INC_PATH=../../../arduino-sources/libraries
endif

testbegin_SOURCES = test_begin.cpp
testbegin_CXXFLAGS = @CHECK_CFLAGS@  -DSEARDUINO_STUB -I../../include/utils -I../../include -I$(SEARDUINO_LIB_INC_PATH)/Wire/ -I$(SEARDUINO_INC_PATH)
testbegin_LDADD = ../../.libs/libsearduinostub.a @CHECK_LIBS@ -ldl $(LIBXTST) -lX11

endif
#
#       Searduino
#
#  Copyright (C) 2013,2014 Henrik Sandklef      
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


if DEBIANSOURCES
SEARDUINO_INC_PATH=-I/usr/share/arduino/hardware/arduino/cores/arduino/ -I/usr/share/arduino/libraries/LiquidCrystal/
SEARDUINO_LIB_INC_PATH=/usr/share/arduino/libraries
else
SEARDUINO_INC_PATH=-I../../../arduino-sources/core -I../../../arduino-sources/libraries/LiquidCrystal
SEARDUINO_LIB_INC_PATH=../../../arduino-sources/libraries 
endif


ARDUINO_CODE=../../../extensions/arduino-lib/.libs/libarduino-code.so
ARDUINO_CODE_ARG=-DARDUINO_CODE=\"$(ARDUINO_CODE)\"

ARDUINO_LCD_CODE=./liblcd.so
ARDUINO_LCD_CODE_ARG=-DARDUINO_LCD_CODE=\"$(ARDUINO_LCD_CODE)\"

MYCFLAGS=-I../../include/arduino -I../../include/arduino/ -I../../../arduino-extras/include $(SEARDUINO_INC_PATH)/ -I../../include -DSEARDUINO_STUB -I../../include/seasim/ $(ARDUINO_CODE_ARG) $(ARDUINO_LCD_CODE_ARG)
AM_CFLAGS=$(MYCFLAGS)
AM_CXXFLAGS=$(MYCFLAGS)

AM_LDFLAGS=-lpthread 


TESTS =  testliquidcrystal testbegin testlcdcallback testclear
check_PROGRAMS = testliquidcrystal testbegin testlcdcallback testclear

all: $(ARDUINO_CODE)

testbegin_SOURCES = test_begin.cpp
testbegin_CXXFLAGS = @CHECK_CFLAGS@ $(MYCFLAGS)
testbegin_CFLAGS = @CHECK_CFLAGS@ $(MYCFLAGS)
testbegin_LDADD = ../../libsearduinostub.la @CHECK_LIBS@ -lpthread

testliquidcrystal_SOURCES = test_liquidcrystal.cpp
testliquidcrystal_CXXFLAGS = @CHECK_CFLAGS@ $(MYCFLAGS)
testliquidcrystal_CFLAGS = @CHECK_CFLAGS@ $(MYCFLAGS)
testliquidcrystal_LDADD = ../../libsearduinostub.la @CHECK_LIBS@ -lpthread

testlcdcallback_SOURCES = test_lcdcallback.cpp
testlcdcallback_CXXFLAGS = @CHECK_CFLAGS@ $(MYCFLAGS)
testlcdcallback_CFLAGS = @CHECK_CFLAGS@ $(MYCFLAGS)
testlcdcallback_LDADD = ../../libsearduinostub.la @CHECK_LIBS@ -lpthread

testclear_SOURCES = test_clear.cpp
testclear_CXXFLAGS = @CHECK_CFLAGS@ $(MYCFLAGS)
testclear_CFLAGS = @CHECK_CFLAGS@ $(MYCFLAGS)
testclear_LDADD = ../../libsearduinostub.la @CHECK_LIBS@ -lpthread

endif
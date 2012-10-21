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

if UNITTEST

lib_LTLIBRARIES = libi2c.la
libi2c_la_SOURCES = i2c_setup.c
AM_CFLAGS= -I../../include/arduino -I../../include/arduino/ -I../../../arduino-sources/core -I../../include

TESTS =  testtime testsetup  testi2c testcomm testdigio testwiring testboards testuno
check_PROGRAMS = testtime testsetup testlimit testi2c  testcomm testdigio testwiring testboards testuno

testtime_SOURCES = test_time.c 
testtime_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../../arduino-sources/core 
testtime_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

testsetup_SOURCES = test_setup.c 
testsetup_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../include -I../../../arduino-sources/core 
testsetup_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

testlimit_SOURCES = test_limit.c 
testlimit_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../../arduino-sources/core -I../../include
testlimit_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

testi2c_SOURCES = test_i2cload.c 
testi2c_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../../arduino-sources/core -I../../include
testi2c_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

testcomm_SOURCES = test_comm.c 
testcomm_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../include/utils -I../../include
testcomm_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

testdigio_SOURCES = test_digio.c 
testdigio_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../include/utils -I../../include
testdigio_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

testboards_SOURCES = test_boards.c 
testboards_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../include/utils -I../../include  -I../../../arduino-sources/core   -I../../../arduino-extras/include
testboards_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

testwiring_SOURCES = test_wiring_digital.c 
testwiring_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../include -I../../../arduino-sources/core 
testwiring_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

testuno_SOURCES = test_uno.c 
testuno_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../include/utils -I../../include  -I../../../arduino-sources/core   -I../../../arduino-extras/include
testuno_LDADD = ../../libsearduinostub.la @CHECK_LIBS@


endif

if UNITTEST

lib_LTLIBRARIES = libi2c.la
libi2c_la_SOURCES = i2c_setup.c
AM_CFLAGS= -I../../include/arduino -I../../include/arduino/ -I../../../arduino-sources/core -I../../include

TESTS =  testtime testwiring testsetup  testi2c testcomm testdigio testboards
check_PROGRAMS = testtime testwiring testsetup testlimit testi2c  testcomm testdigio testboards

testtime_SOURCES = test_time.c 
testtime_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../../arduino-sources/core 
testtime_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

testwiring_SOURCES = test_wiring_digital.c 
testwiring_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../include -I../../../arduino-sources/core 
testwiring_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

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

endif
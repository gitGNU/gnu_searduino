
if UNITTEST

TESTS = testtime testwiring testsetup
check_PROGRAMS = testtime testwiring testsetup testlimit

testtime_SOURCES = test_time.c 
testtime_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/
testtime_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

testwiring_SOURCES = test_wiring_digital.c 
testwiring_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../include
testwiring_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

testsetup_SOURCES = test_setup.c 
testsetup_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../include
testsetup_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

testlimit_SOURCES = test_limit.c 
testlimit_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../../arduino-sources/core -I../../include
testlimit_LDADD = ../../libsearduinostub.la @CHECK_LIBS@


endif
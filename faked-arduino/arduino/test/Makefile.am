TESTS = testtime testwiring testsetup
check_PROGRAMS = testtime testwiring testsetup

testtime_SOURCES = test_time.c 
testtime_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/
testtime_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

testwiring_SOURCES = test_wiring_digital.c 
testwiring_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../include
testwiring_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

testsetup_SOURCES = test_setup.c 
testsetup_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../include
testsetup_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

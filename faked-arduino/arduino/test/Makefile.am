TESTS = testtime testwiring
check_PROGRAMS = testtime testwiring
testtime_SOURCES = test_time.c 
testtime_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/
testtime_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

testwiring_SOURCES = test_wiring_digital.c 
testwiring_CFLAGS = @CHECK_CFLAGS@ -I../../include/arduino/ -I../../include
testwiring_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

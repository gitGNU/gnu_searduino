if UNITTEST

TESTS = testcomm testdigio
check_PROGRAMS = testcomm testdigio

testcomm_SOURCES = test_comm.c 
testcomm_CFLAGS = @CHECK_CFLAGS@ -I../../include/communication/ -I../../include/utils -I../../include
testcomm_LDADD = ../../libsearduinostub.la @CHECK_LIBS@



testdigio_SOURCES = test_digio.c 
testdigio_CFLAGS = @CHECK_CFLAGS@ -I../../include/communication/ -I../../include/utils -I../../include
testdigio_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

endif
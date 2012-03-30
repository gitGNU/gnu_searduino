if UNITTEST

TESTS = testbegin
check_PROGRAMS = testbegin

testbegin_SOURCES = test_begin.cpp
testbegin_CXXFLAGS = @CHECK_CFLAGS@  -I../../include/utils -I../../include -I../../../arduino-sources/libraries/Wire/ -I../../../arduino-sources/core
testbegin_LDADD = ../../libsearduinostub.la @CHECK_LIBS@

endif
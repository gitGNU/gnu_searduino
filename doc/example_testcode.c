SEARDUINO_PATH=/opt/searduino/
SRC_C=distance.c test_distance.c
SRC_CXX=
ARDUINO=stub
PROG=distance
SHLIB=distance.so
include $(SEARDUINO_PATH)/share/searduino/mk/searduino.mk

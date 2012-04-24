SEARDUINO_PATH=/opt/searduino/
SRC_C=distance.c test_distance.c
SRC_CXX=
ARDUINO=stub
PROG=distance
SHLIB=distance.so
USER_C_FLAGS=-I/opt/searduino/include/searduino/seasim -I/opt/searduino/include/searduino/ -I/opt/searduino/include/searduino/arduino

include $(SEARDUINO_PATH)/share/searduino/mk/searduino.mk

ARDUINO=uno
USER_OBJ_PATH=./objs/$(BOARD)/
include libraries.mk

all:
	make uno

ARDUINO=uno
USER_OBJ_PATH=./objs/$(BOARD)/
include arduino-sources.mk

all:
	make uno

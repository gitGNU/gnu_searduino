#
#       Searduino
#
#  Copyright (C) 2011, 2012 Henrik Sandklef      
#                                                                   
# This program is free software; you can redistribute it and/or     
# modify it under the terms of the GNU General Public License       
# as published by the Free Software Foundation; either version 3    
# of the License, or any later version.                             
#                                                                   
#                                                                   
# This program is distributed in the hope that it will be useful,   
# but WITHOUT ANY WARRANTY; without even the implied warranty of    
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     
# GNU General Public License for more details.                      
#                                                                   
# You should have received a copy of the GNU General Public License 
# along with this program; if not, write to the Free Software       
# Foundation, Inc., 51 Franklin Street, Boston,            
# MA  02110-1301, USA.                                              
#
#


stubbed: ARDUINO=stub
stubbed: 
	make $(PROG)


ifeq (${ARDUINO},due)
BOARD=atmega328
CPU=atmega328p
VARIANT=standard
ARDUINO_CPU=ATmega328P
USB_DEV=/dev/ttyUSB0
endif
ifeq ($(ARDUINO),uno)
BOARD=atmega328
CPU=atmega328p
VARIANT=standard
ARDUINO_CPU=ATmega328p
USB_DEV=/dev/ttyACM0
endif
ifeq ($(ARDUINO),mega)
BOARD=atmega1280
CPU=atmega1280
VARIANT=mega
ARDUINO_CPU=ATmega1280
USB_DEV=/dev/ttyUSB0
endif


ifeq (${ARDUINO},stub)
OBJ_C = $(SRC_C:.c=.o) $(MAIN_SRC:.c=.o)
OBJ_CXX = $(SRC_CXX:.cpp=.o) 
else
OBJ_C = $(SRC_C:.c=.o) 
OBJ_CXX = $(SRC_CXX:.cpp=.o) 
endif

ifeq ($(ARDUINO),stub)
	BOARD=stub
endif

uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')

ifndef BOARD
$(error Variables not set correctly BOARD='$(BOARD)' (ARDUINO='${ARDUINO}'))
else
	include $(SEARDUINO_PATH)/mk/board-makefiles/$(BOARD).mk
#	include $(SEARDUINO_PATH)/mk/device-specific.mk
endif		

ifeq ($(ARDUINO),stub)
CC=gcc
CXX=g++
OBJ_CP=
AVRDUDE=
AR=ar
JAVAC=gcj
else
CC=avr-gcc
CXX=avr-g++
OBJ_CP=avr-objcopy
AR=avr-ar
AVRDUDE=avrdude
F_CPU=$(board_build.f_cpu)
#$(error HERE EINAR?  ARDUINO=$(ARDUNIO) BOARD=$(BOARD) CPU=$(CPU)  F_CPU=$(F_CPU))
endif

ifndef PROG
ARDUINO_VERSION=100
endif



ifeq ($(ARDUINO),stub)
ifeq ($(BUILD_FROM_VCS),true)
INC_FLAGS= -I$(SEARDUINO_PATH)/include/arduino/core \
           -I$(SEARDUINO_PATH)/include/arduino/variants \
           -I$(SEARDUINO_PATH)/faked-arduino/arduino/include \
           -I$(SEARDUINO_PATH)/faked-arduino/include \
           -I$(SEARDUINO_PATH)/faked-arduino/include/arduino \
           -I$(SEARDUINO_PATH)/faked-arduino/utils/include \
           -I$(SEARDUINO_PATH)/faked-arduino/commnication/include \
           -I$(SEARDUINO_PATH)/arduino-sources/core

SEARDUINO_LIB_PATH= $(SEARDUINO_PATH)/libs
else
INC_FLAGS=  -I$(SEARDUINO_PATH)/include/arduino/core \
           -I$(SEARDUINO_PATH)/include/arduino/variants \
           -I$(SEARDUINO_PATH)/include/faked-arduino/arduino \
           -I$(SEARDUINO_PATH)/include/faked-arduino/
SEARDUINO_LIB_PATH= $(SEARDUINO_PATH)/libs
endif

CFLAGS=   -g $(USER_C_FLAGS) -Wall \
           $(LIB_FLAGS) \
           $(MODULE_C_FLAGS) \
           $(INC_FLAGS)

CXXFLAGS=-g $(USER_CXX_FLAGS) \
            $(MODULE_CXX_FLAGS) \
           $(INC_FLAGS)


LDFLAGS = -L$(SEARDUINO_LIB_PATH) -lsearduino-stub $(USER_LD_FLAGS) -lpthread

else
ifeq ($(BUILD_FROM_VCS),true)
INC_FLAGS=  -I$(SEARDUINO_PATH)/arduino-sources/core  \
            -I$(SEARDUINO_PATH)/arduino-sources/variants/$(VARIANT) 
else
INC_FLAGS=  -I$(SEARDUINO_PATH)/include/arduino/core \
            -I$(SEARDUINO_PATH)/include/arduino/variants/$(VARIANT) 
endif

LIBSEARDUINO_C_CPP_FLAGS= -g -Os -w -fno-exceptions \
                          -ffunction-sections -fdata-sections \
                          -mmcu=$(CPU) -DF_CPU=$(F_CPU) \
                          -DARDUINO=$(ARDUINO_VERSION) \
                           $(INC_FLAGS)

#-I$(SEARDUINO_PATH)/src
#-Wall -Wa,-ahlms=$(PROG).lst -fno-exceptions -w = -fno-exceptions

LIBSEARDUINO_CFLAGS=
LIBSEARDUINO_CXXFLAGS=

CFLAGS= $(LIBSEARDUINO_C_CPP_FLAGS) $(LIBSEARDUINO_CFLAGS) $(USER_C_FLAGS)
CXXFLAGS=$(LIBSEARDUINO_C_CPP_FLAGS) $(LIBSEARDUINO_CXXFLAGS) $(USER_CXX_FLAGS)


ifeq ($(BUILD_FROM_VCS),true)
SEARDUINO_LIB_PATH=$(SEARDUINO_PATH)/arduino-sources/libs/$(BOARD)
else
SEARDUINO_LIB_PATH=$(SEARDUINO_PATH)/libs/$(BOARD) 
endif
LDFLAGS=-L$(SEARDUINO_LIB_PATH) -lsearduino 

endif


$(OBJ_C): $(SRC_HEADERS) $(SRC_C) 
$(OBJ_CXX): $(SRC_HEADERS) $(SRC_CXX)  

INTERNAL_FLAGS= -DMY_ARDUINO=$(ARDUINO) -DMY_BOARD=$(BOARD)

%.o: %.c
#	echo "  BOARD=$(BOARD)   from ARDUINO=$(ARDUINO)  CPU=${CPU} => $(CFLAGS))"
#	$(error HERE EINAR2xs?   BOARD=$(BOARD)   from ARDUINO=$(ARDUINO)  CPU=$(CPU) => $(CFLAGS))
	$(CC) -c $(CFLAGS) -I. $(INTERNAL_FLAGS) $<  -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -I. $(INTERNAL_FLAGS) $< -o $@ 


$(MAIN_SRC).elf: $(MAIN_SRC).o  $(OBJ_C) $(OBJ_CXX)
	$(CC) -Os -Wl,--gc-sections -mmcu=$(CPU)  -o $(MAIN_SRC).elf $(MAIN_SRC).o $(LIB) -lm $(LDFLAGS) $(OBJ_C) $(OBJ_CXX)

$(MAIN_SRC).o: $(MAIN_SRC) 
	$(CC) -c $(CFLAGS)  $(MAIN_SRC) -o  $(MAIN_SRC).o

hex: $(MAIN_SRC).hex
$(MAIN_SRC).hex:   $(MAIN_SRC).o $(LIB) $(MAIN_SRC).elf
	$(OBJ_CP)   -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma  .eeprom=0 $(MAIN_SRC).elf $(MAIN_SRC).eep 
	$(OBJ_CP)  -O ihex -R .eeprom $(MAIN_SRC).elf $(MAIN_SRC).hex  


ifeq ($(ARDUINO),stub)
$(PROG): $(LIB) $(OBJ_C) $(OBJ_CXX)
	$(CC) $(LIB) $(OBJ_C) $(OBJ_CXX) -o $(PROG) $(LDFLAGS) 
else
$(PROG): $(MAIN_SRC).hex 
	@echo "--- Program '$(PROG).hex' ready for upload ---"
endif
upload: $(MAIN_SRC).hex
	echo "$(ARDUINO)   $(BOARD)"
	$(AVRDUDE) -q -q -p$(CPU) -carduino -P$(USB_DEV) -b$(board_upload.speed) -D -Uflash:w:${MAIN_SRC}.hex:i

clean:
	rm -f *.o *.rom *.elf *.map *~ *.lst $(OBJ_C) $(OBJ_CXX) *.eep *.hex *.a $(LIB) $(SHLIB) *.so libs/*/* $(PROG) *.pyc

light-clean:
	rm -f *.o *.rom *.elf *.map *~ *.lst $(OBJ_C) $(OBJ_CXX) *.eep *.hex 


all: $(PROG) $(LIB) $(OBJ_C) $(OBJ_CXX)

# LocalWords:  ARDUINO

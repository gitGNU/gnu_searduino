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
ifeq ($(ARDUINO),mega2560)
BOARD=atmega2560
CPU=atmega2560
VARIANT=mega
ARDUINO_CPU=ATmega2560
USB_DEV=/dev/ttyACM0
endif

include $(SEARDUINO_MK_PATH)/mk/board-makefiles/$(BOARD).mk

SEARDUINO_ARDUINO=dummyvalue

OBJ_C = $(SRC_C:.c=.o) 
OBJ_CXX = $(SRC_CXX:.cpp=.o) 
OBJ_MAIN = $(MAIN_SRC:.c=.o) 


CC=avr-gcc
CXX=avr-g++
OBJ_CP=avr-objcopy
AR=avr-ar
AVRDUDE=avrdude
F_CPU=$(board_build.f_cpu)

INC_FLAGS=  -I$(SEARDUINO_INC_PATH)/arduino-sources/core \
            -I$(SEARDUINO_INC_PATH)/arduino-extras/      \
            -I$(SEARDUINO_INC_PATH)/arduino-extras/include    \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/variants/$(VARIANT) \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Ethernet/utility \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Ethernet/ \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/SPI        \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Firmata     \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Wire/utility \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/SD/           \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/SD/utility     \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/SD/EEPROM       \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/LiquidCrystal    \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Servo             \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/SoftwareSerial     \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Stepper


LIBSEARDUINO_C_CPP_FLAGS= -g -Os -w -fno-exceptions \
                          -ffunction-sections -fdata-sections \
                          -mmcu=$(CPU) -DF_CPU=$(F_CPU) \
                          -DARDUINO=$(ARDUINO_VERSION) \
                           $(INC_FLAGS)

SEARDUINO_LIB=-lsearduino
LIBRARIES_LIB=-llibraries


#$(OBJ_O): $(OBJ_C)
#	

#$(PROG).elf:   $(OBJ_C) $(OBJ_CXX)
#	echo "HEX HEX"
#	$(CC) -Os -Wl,--gc-sections -mmcu=$(CPU)  -o $(PROG).elf $(LIB) -lm $(LDFLAGS) $(OBJ_C) $(OBJ_CXX) 

#helo:
#	echo "$(OBJ_MAIN)"

$(PROG).elf: $(OBJ_MAIN) $(OBJ_C) $(OBJ_CXX)
	$(CC) -Os -Wl,--gc-sections -mmcu=$(CPU)  -o $(PROG).elf $(OBJ_MAIN) $(OBJ_C) $(OBJ_CXX) $(LIB) -lm $(LDFLAGS) 

#$(PROG).o: $(PROG) 
#	$(CC) -c $(CFLAGS)  $(MAIN_OBJS) -o  $(MAIN_SRC).o

#$(MAIN_SRC).hex:   $(MAIN_SRC).o $(LIB) $(MAIN_SRC).elf
$(PROG).hex:   $(OBJ_MAIN) $(LIB) $(PROG).elf
	echo HEX
	$(OBJ_CP)   -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma  .eeprom=0 $(PROG).elf $(PROG).eep 
	$(OBJ_CP)  -O ihex -R .eeprom $(PROG).elf $(PROG).hex  

#$(PROG): $(MAIN_SRC).hex 
$(PROG): $(PROG).hex 
	@echo "--- Program '$(PROG).hex' ready for upload ---"

prog: $(PROG).hex

#upload: $(PROG).hex
upload: $(PROG).hex
	echo "Will upload to: $(ARDUINO)   $(BOARD)"
	$(AVRDUDE) -q -q -p$(CPU) -carduino -P$(USB_DEV) -b$(board_upload.speed) -D -Uflash:w:${PROG}.hex:i


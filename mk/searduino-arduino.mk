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

include $(SEARDUINO_MK_PATH)/mk/board-makefiles/$(BOARD).mk




OBJ_C = $(SRC_C:.c=.o) 
OBJ_CXX = $(SRC_CXX:.cpp=.o) 


CC=avr-gcc
CXX=avr-g++
OBJ_CP=avr-objcopy
AR=avr-ar
AVRDUDE=avrdude
F_CPU=$(board_build.f_cpu)

INC_FLAGS=  -I$(SEARDUINO_INC_PATH)/arduino-sources/core \
            -I$(SEARDUINO_INC_PATH)/arduino-extras/    \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/variants/$(VARIANT) 

LIBSEARDUINO_C_CPP_FLAGS= -g -Os -w -fno-exceptions \
                          -ffunction-sections -fdata-sections \
                          -mmcu=$(CPU) -DF_CPU=$(F_CPU) \
                          -DARDUINO=$(ARDUINO_VERSION) \
                           $(INC_FLAGS)

SEARDUINO_LIB=searduino


#$(OBJ_O): $(OBJ_C)
#	

#$(PROG).elf:   $(OBJ_C) $(OBJ_CXX)
#	echo "HEX HEX"
#	$(CC) -Os -Wl,--gc-sections -mmcu=$(CPU)  -o $(PROG).elf $(LIB) -lm $(LDFLAGS) $(OBJ_C) $(OBJ_CXX) 

$(MAIN_SRC).elf: $(MAIN_SRC).o  $(OBJ_C) $(OBJ_CXX)
	$(CC) -Os -Wl,--gc-sections -mmcu=$(CPU)  -o $(MAIN_SRC).elf $(MAIN_SRC).o $(LIB) -lm $(LDFLAGS) $(OBJ_C) $(OBJ_CXX) 

$(MAIN_SRC).o: $(MAIN_SRC) 
	$(CC) -c $(CFLAGS)  $(MAIN_SRC) -o  $(MAIN_SRC).o

#hex: $(PROG).hex
#$(PROG).hex:  $(LIB) $(PROG).elf
$(MAIN_SRC).hex:   $(MAIN_SRC).o $(LIB) $(MAIN_SRC).elf
	$(OBJ_CP)   -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma  .eeprom=0 $(MAIN_SRC).elf $(MAIN_SRC).eep 
	$(OBJ_CP)  -O ihex -R .eeprom $(MAIN_SRC).elf $(MAIN_SRC).hex  

#$(PROG): $(PROG).hex 
$(PROG): $(MAIN_SRC).hex 
	@echo "--- Program '$(PROG).hex' ready for upload ---"


#upload: $(PROG).hex
upload: $(MAIN_SRC).hex
	echo "Will upload to: $(ARDUINO)   $(BOARD)"
	$(AVRDUDE) -q -q -p$(CPU) -carduino -P$(USB_DEV) -b$(board_upload.speed) -D -Uflash:w:${MAIN_SRC}.hex:i


ifeq (${ARDUINO},due)
BOARD=atmega328
CPU=atmega328p
VARIANT=standard
ARDUINO_CPU=ATmega328P
endif
ifeq ($(ARDUINO),uno)
BOARD=atmega328
CPU=atmega328p
VARIANT=standard
ARDUINO_CPU=ATmega328p
endif
ifeq ($(ARDUINO),mega)
BOARD=atmega1280
CPU=atmega1280
VARIANT=mega
ARDUINO_CPU=ATmega1280
endif
ifeq ($(ARDUINO),mega2560)
BOARD=atmega2560
CPU=atmega2560
VARIANT=mega
ARDUINO_CPU=ATmega2560
endif

USB_DEV="no-device-set"
include $(SEARDUINO_MK_PATH)/mk/board-makefiles/$(BOARD).mk



OBJ_PATH = ./
ifdef USER_OBJ_PATH
OBJ_PATH = $(USER_OBJ_PATH)
endif

OBJ_C = $(addprefix $(OBJ_PATH), $(SRC_C:.c=.o)) 
OBJ_CXX = $(addprefix $(OBJ_PATH), $(SRC_CXX:.cpp=.o))
OBJ_MAIN = $(addprefix $(OBJ_PATH), $(MAIN_SRC:.c=.o)) 


CC=avr-gcc
CXX=avr-g++
OBJ_CP=avr-objcopy
AR=avr-ar
AVRDUDE=avrdude
F_CPU=$(board_build.f_cpu)


INC_FLAGS=  -I$(SEARDUINO_INC_PATH)/arduino-sources/core 		   \
            -I$(SEARDUINO_INC_PATH)/arduino-extras/ 			    \
            -I$(SEARDUINO_INC_PATH)/arduino-extras/include    		     \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/variants/$(VARIANT)	      \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Ethernet/utility \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Ethernet/ 	\
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/SPI       	 \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Firmata   	  \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Wire/utility	   \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/SD/       	    \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/SD/utility	     \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/SD/EEPROM 	      \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/LiquidCrystal	       \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Servo        	        \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/SoftwareSerial	         \
            -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Stepper


LIBSEARDUINO_C_CPP_FLAGS= -g -Os -w -fno-exceptions \
                          -ffunction-sections -fdata-sections \
                          -mmcu=$(CPU) -DF_CPU=$(F_CPU) \
                          -DARDUINO=$(ARDUINO_VERSION) \
                           $(INC_FLAGS) -DSEARDUINO_ARDUINO

SEARDUINO_LIB=-lsearduino
LIBRARIES_LIB=-llibraries


$(PROG).elf: $(OBJ_MAIN) $(OBJ_C) $(OBJ_CXX)
	$(CC) -Os -Wl,--gc-sections -mmcu=$(CPU)  -o $(PROG).elf $(OBJ_MAIN) $(OBJ_C) $(OBJ_CXX) $(LIB) -lm $(LDFLAGS) 

$(PROG).hex: $(LIB) $(PROG).elf
	$(OBJ_CP)  -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma  .eeprom=0 $(PROG).elf $(PROG).eep 
	$(OBJ_CP)  -O ihex -R .eeprom $(PROG).elf $(PROG).hex  

$(PROG): $(PROG).hex 
	@echo "--- Program '$(PROG).hex' ready for upload ---"

prog: $(PROG).hex

upload: $(PROG).hex
	echo "Will upload to: $(ARDUINO)   $(BOARD)"
	$(AVRDUDE) -q -q -p$(CPU) -c$(board_upload.protocol) -P$(USB_DEV) \
                   -b$(board_upload.speed) -D -Uflash:w:${PROG}.hex:i





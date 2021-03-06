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
ifeq ($(ARDUINO),leonardo)
BOARD=atmega32u4
CPU=atmega32u4
VARIANT=leonardo
ARDUINO_CPU=atmega32u4
BOARD_SPECIFIC_CFLAGS=-MMD
endif

include $(SEARDUINO_MK_PATH)/mk/board-makefiles/$(BOARD).mk



OBJ_PATH = ./
ifdef USER_OBJ_PATH
OBJ_PATH = $(USER_OBJ_PATH)
endif

OBJ_C = $(addprefix $(OBJ_PATH), $(SRC_C:.c=.o)) 
OBJ_CXX = $(addprefix $(OBJ_PATH), $(SRC_CXX:.cpp=.o))
OBJ_MAIN = $(addprefix $(OBJ_PATH), $(MAIN_SRC:.c=.o)) 


ifndef SEARDUINO_VCS
CC=avr-gcc
CXX=avr-g++
OBJ_CP=avr-objcopy
AR=avr-ar
AVRDUDE=avrdude
endif

einar:
	echo "SEARDUINO_VCS $(SEARDUINO_VCS)"

F_CPU=$(board_build.f_cpu)


ifeq ($(CYGWIN_USED),true)
INC_FLAGS=  \
            -I$(shell cygpath -w ${SEARDUINO_INC_PATH})/arduino-extras/ 	    \
            -I$(shell cygpath -w ${SEARDUINO_INC_PATH})/arduino-extras/include   \
            -I$(shell cygpath -w ${ARDUINO_INC_PATH})/variants/$(VARIANT)      \
            -I$(shell cygpath -w ${ARDUINO_INC_PATH})/cores/arduino/               \
            -I$(shell cygpath -w ${ARDUINO_INC_PATH})/core/                         \
            -I$(shell cygpath -w ${ARDUINO_LIB_INC_PATH})/libraries/Ethernet/utility    \
            -I$(shell cygpath -w ${ARDUINO_LIB_INC_PATH})/libraries/Ethernet/        \
            -I$(shell cygpath -w ${ARDUINO_LIB_INC_PATH})/libraries/SPI       	 \
            -I$(shell cygpath -w ${ARDUINO_LIB_INC_PATH})/libraries/Firmata   	  \
            -I$(shell cygpath -w ${ARDUINO_LIB_INC_PATH})/libraries/Wire/utility   \
            -I$(shell cygpath -w ${ARDUINO_LIB_INC_PATH})/libraries/Wire/	    \
            -I$(shell cygpath -w ${ARDUINO_LIB_INC_PATH})/libraries/SD/       	     \
            -I$(shell cygpath -w ${ARDUINO_LIB_INC_PATH})/libraries/SD/utility	      \
            -I$(shell cygpath -w ${ARDUINO_LIB_INC_PATH})/libraries/EEPROM     	       \
            -I$(shell cygpath -w ${ARDUINO_LIB_INC_PATH})/libraries/SD/EEPROM 	        \
            -I$(shell cygpath -w ${ARDUINO_LIB_INC_PATH})/libraries/LiquidCrystal        \
            -I$(shell cygpath -w ${ARDUINO_LIB_INC_PATH})/libraries/Servo                 \
            -I$(shell cygpath -w ${ARDUINO_LIB_INC_PATH})/libraries/SoftwareSerial         \
            -I$(shell cygpath -w ${ARDUINO_LIB_INC_PATH})/libraries/Stepper
else
INC_FLAGS=  \
            -I$(SEARDUINO_INC_PATH)/arduino-extras/ 	    \
            -I$(SEARDUINO_INC_PATH)/arduino-extras/include   \
            -I$(ARDUINO_INC_PATH)/variants/$(VARIANT)	      \
            -I$(ARDUINO_INC_PATH)/cores/arduino/               \
            -I$(ARDUINO_INC_PATH)/core/                         \
            -I$(ARDUINO_LIB_INC_PATH)/libraries/Ethernet/utility    \
            -I$(ARDUINO_LIB_INC_PATH)/libraries/Ethernet/        \
            -I$(ARDUINO_LIB_INC_PATH)/libraries/SPI       	 \
            -I$(ARDUINO_LIB_INC_PATH)/libraries/Firmata   	  \
            -I$(ARDUINO_LIB_INC_PATH)/libraries/Wire/utility   \
            -I$(ARDUINO_LIB_INC_PATH)/libraries/Wire/	    \
            -I$(ARDUINO_LIB_INC_PATH)/libraries/SD/       	     \
            -I$(ARDUINO_LIB_INC_PATH)/libraries/SD/utility	      \
            -I$(ARDUINO_LIB_INC_PATH)/libraries/EEPROM     	       \
            -I$(ARDUINO_LIB_INC_PATH)/libraries/SD/EEPROM 	        \
            -I$(ARDUINO_LIB_INC_PATH)/libraries/LiquidCrystal        \
            -I$(ARDUINO_LIB_INC_PATH)/libraries/Servo                 \
            -I$(ARDUINO_LIB_INC_PATH)/libraries/SoftwareSerial         \
            -I$(ARDUINO_LIB_INC_PATH)/libraries/Stepper
endif

LIBSEARDUINO_C_CPP_FLAGS= -g -Os -w -fno-exceptions \
                          -ffunction-sections -fdata-sections \
                          -mmcu=$(CPU) -DF_CPU=$(F_CPU) \
                          -DARDUINO=$(ARDUINO_VERSION)  \
			  $(BOARD_SPECIFIC_CFLAGS)      \
                           $(INC_FLAGS) -DSEARDUINO_ARDUINO \
                           -D__AVR_LIBC_DEPRECATED_ENABLE__=1 \
                           -DUSB_VID=$(build_vid) -DUSB_PID=$(build_pid)

SEARDUINO_LIB=-lsearduino
LIBRARIES_LIB=-llibraries


_CFLAGS=   -g $(USER_C_FLAGS) \
            $(MODULE_C_FLAGS) \
            $(INC_FLAGS) $(USER_ARDUINO_C_FLAGS)

_CXXFLAGS=-g -fPIC $(USER_CXX_FLAGS) \
             $(MODULE_CXX_FLAGS) \
             $(INC_FLAGS) $(USER_ARDUINO_CXX_FLAGS) 

ifdef CYGWIN_USED
SEARDUINO_LD_PATH=$(shell cygpath -w ${SEARDUINO_PATH})
else
SEARDUINO_LD_PATH=$(SEARDUINO_PATH)
endif

_LDFLAGS = $(USER_LD_FLAGS)  $(USER_ARDUINO_LD_FLAGS)  -Wl,-rpath,$(SEARDUINO_LD_PATH)/lib 


all: $(PROG)

$(PROG).elf: $(OBJ_MAIN) $(OBJ_C) $(OBJ_CXX)
	$(CXX) -Os -Wl,--gc-sections -mmcu=$(CPU)  -o $(PROG).elf $(OBJ_MAIN) $(OBJ_C) $(OBJ_CXX) \
                $(LIB)  -lm $(LDFLAGS) $(USER_ARDUINO_LDFLAGS) 

$(PROG).hex: $(LIB) $(PROG).elf
	$(OBJ_CP)  -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma  .eeprom=0 $(PROG).elf $(PROG).eep 
	$(OBJ_CP)  -O ihex -R .eeprom $(PROG).elf $(PROG).hex  

$(PROG): $(PROG).hex 
	@echo "--- Program '$(PROG).hex' ready for upload ---"

prog: $(PROG).hex

check-objects: $(PROG).hex
	@echo "--> Scanning for objects known to cause errors on the Arduino boards -- "
	@echo -n "   ** Looking for references to printf: " && export REFS="$(nm *.o $(PROG).hex 2>/dev/null | grep -c printf)" && if [ "$(REFS)" != "0" ] ; then echo " fail  ($REFS)"; return 1 ; else echo "ok" ; fi
	@echo -n "   ** Looking for references to searduino_log: " && export REFS="$(nm *.o $(PROG).hex 2>/dev/null | grep -c searduino_log)" && if [ "$(REFS)" != "0" ] ; then echo " fail  ($REFS)"; return 1 ; else echo "ok" ; fi
	@echo "<-- done scanning --"

upload: $(PROG).hex 
	@if [ "$(USB_DEV)" = "" ] || [ "`echo $(USB_DEV) | grep -i unknown`" != "" ] ; then echo "Could not find a USB port"; exit 1 ; fi 
	@echo "Will upload to: $(ARDUINO)   $(BOARD)  (device: (" $(USB_DEV) ")"
	$(AVRDUDE) -q -q -p$(CPU) -c$(board_upload.protocol) -P$(USB_DEV) \
                   -b$(board_upload.speed) -D -Uflash:w:${PROG}.hex:i

safe-upload: $(PROG).hex check-objects
	@echo "Will upload to: $(ARDUINO)   $(BOARD)  (device: (" $(USB_DEV) ")"
	$(AVRDUDE) -q -q -p$(CPU) -c$(board_upload.protocol) -P$(USB_DEV) \
                   -b$(board_upload.speed) -D -Uflash:w:${PROG}.hex:i


	@echo "Will upload to: $(ARDUINO)   $(BOARD)  (device: (" $(USB_DEV) ")"
	$(AVRDUDE) -q -q -p$(CPU) -c$(board_upload.protocol) -P$(USB_DEV) \
                   -b$(board_upload.speed) -D -Uflash:w:${PROG}.hex:i



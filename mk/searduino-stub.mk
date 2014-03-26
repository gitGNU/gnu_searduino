BOARD=stub

E_C = $(SRC_C:.c=.E) $(MAIN_SRC:.c=.o)
E_CXX = $(SRC_CXX:.cpp=.E) 

# These are now set with a optional OBJ_PATH prefix
#OBJ_C = $(SRC_C:.c=.o) 
#OBJ_CXX = $(SRC_CXX:.cpp=.o) 
#OBJ_MAIN = $(MAIN_SRC:.c=.o) 

OBJ_PATH = 
ifdef USER_OBJ_PATH
OBJ_PATH = $(USER_OBJ_PATH)
endif

OBJ_C = $(addprefix $(OBJ_PATH), $(SRC_C:.c=.o)) 
OBJ_CXX = $(addprefix $(OBJ_PATH), $(SRC_CXX:.cpp=.o))
OBJ_MAIN = $(addprefix $(OBJ_PATH), $(MAIN_SRC:.c=.o)) 

CC=gcc
CXX=g++
OBJ_CP=
AVRDUDE=
AR=ar
JAVAC=gcj

VARIANT=standard

INC_FLAGS= -I$(SEARDUINO_INC_PATH)/arduino-extras/             \
           -I$(SEARDUINO_INC_PATH)/                             \
           -I$(SEARDUINO_INC_PATH)/arduino                       \
           -I$(SEARDUINO_INC_PATH)/faked-arduino/include         \
           -I$(SEARDUINO_INC_PATH)/faked-arduino/include/avr         \
           -I$(SEARDUINO_INC_PATH)/faked-arduino/include/arduino  \
           -I$(ARDUINO_INC_PATH)/variants/$(VARIANT)	      \
           -I$(ARDUINO_INC_PATH)/core/                        \
           -I$(ARDUINO_INC_PATH)/cores/arduino/               \
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
           -I$(ARDUINO_LIB_INC_PATH)/libraries/Servo                \
           -I$(ARDUINO_LIB_INC_PATH)/libraries/SoftwareSerial       \
           -I$(ARDUINO_LIB_INC_PATH)/libraries/Stepper              \
           -I$(SEARDUINO_INC_PATH)/seasim  \
           $(VCS_IFLAGS) 
#           -I$(SEARDUINO_INC_PATH)/boards  \
#\
#           -I$(SEARDUINO_INC_PATH)/faked-arduino/include/arduino \
#           -I$(SEARDUINO_INC_PATH)/faked-arduino/include \

SEARDUINO_LIB=-lsearduinostub
LIBRARIES_LIB=



_CFLAGS=   -g $(USER_C_FLAGS) -Wall -fPIC \
            $(LIB_FLAGS) \
            $(MODULE_C_FLAGS) \
            $(INC_FLAGS) $(USER_STUB_C_FLAGS)  -DSEARDUINO_STUB

_CXXFLAGS=-g -fPIC $(USER_CXX_FLAGS) \
            $(LIB_FLAGS) \
             $(MODULE_CXX_FLAGS) \
             $(INC_FLAGS) $(USER_STUB_CXX_FLAGS) -DSEARDUINO_STUB

_LDFLAGS = $(USER_LD_FLAGS)  $(USER_STUB_LD_FLAGS) -lpthread -Wl,-rpath,$(SEARDUINO_PATH)/lib 

all: $(SHLIB)

$(PROG): $(LIB) $(OBJ_C) $(OBJ_CXX) $(OBJ_MAIN)
	$(CXX) $(LIB) $(OBJ_MAIN) $(OBJ_C) $(OBJ_CXX) -o $(PROG) $(LDFLAGS)


plugin: ARDUINO=stub
plugin: $(SHLIB)

prog: ARDUINO=stub
prog: $(PROG)


run:
	./$(PROG)



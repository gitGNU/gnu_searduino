BOARD=stub

E_C = $(SRC_C:.c=.E) $(MAIN_SRC:.c=.o)
E_CXX = $(SRC_CXX:.cpp=.E) 

# These are now set with a optional OBJ_PATH prefix
#OBJ_C = $(SRC_C:.c=.o) 
#OBJ_CXX = $(SRC_CXX:.cpp=.o) 
#OBJ_MAIN = $(MAIN_SRC:.c=.o) 

OBJ_PATH = ./
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

INC_FLAGS= -I$(SEARDUINO_INC_PATH)/arduino-sources/core \
           -I$(SEARDUINO_INC_PATH)/arduino/             \
           -I$(SEARDUINO_INC_PATH)/arduino-extras/      \
           -I$(SEARDUINO_INC_PATH)/                      \
           -I$(SEARDUINO_INC_PATH)/faked-arduino/include \
           -I$(SEARDUINO_INC_PATH)/arduino-sources/variants/standard  \
	   -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Ethernet/utility \
           -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Ethernet/ \
           -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/SPI        \
           -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Firmata     \
           -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Wire/utility \
           -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Wire          \
           -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/SD/            \
           -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/SD/utility      \
           -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/SD/EEPROM        \
           -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/LiquidCrystal     \
           -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Servo              \
           -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/SoftwareSerial      \
           -I$(SEARDUINO_INC_PATH)/arduino-sources/libraries/Stepper
#           -I$(SEARDUINO_INC_PATH)/boards  \
#\
#           -I$(SEARDUINO_INC_PATH)/faked-arduino/include/arduino \
#           -I$(SEARDUINO_INC_PATH)/faked-arduino/include \

SEARDUINO_LIB=-lsearduinostub
LIBRARIES_LIB=



_CFLAGS=   -g $(USER_C_FLAGS) -Wall -fPIC \
            $(LIB_FLAGS) \
            $(MODULE_C_FLAGS) \
            $(INC_FLAGS) -DSEARDUINO_STUB

_CXXFLAGS=-g -fPIC $(USER_CXX_FLAGS) \
             $(MODULE_CXX_FLAGS) \
             $(INC_FLAGS) -DSEARDUINO_STUB

_LDFLAGS = $(USER_LD_FLAGS) -lpthread -Wl,-rpath,$(SEARDUINO_PATH)/lib 

$(PROG): $(LIB) $(OBJ_C) $(OBJ_CXX) $(OBJ_MAIN)
	$(CC) $(LIB) $(OBJ_MAIN) $(OBJ_C) $(OBJ_CXX) -o $(PROG) $(LDFLAGS)


plugin: ARDUINO=stub
plugin: $(SHLIB)

prog: ARDUINO=stub
prog: $(PROG)


run:
	./$(PROG)


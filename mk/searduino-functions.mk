#
#       Searduino
#
#  Copyright (C) 2011, 2012, 2014 Henrik Sandklef      
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

ifndef ARDUINO
$(error Variables not set correctly ARDUINO='${ARDUINO}')
endif		


uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')

ifndef BOARD
$(error Variables not set correctly BOARD='$(BOARD)' (ARDUINO='${ARDUINO}'))
endif		

LIB_INSTALL=.
ifdef USER_LIB_INSTALL_PATH
LIB_INSTALL=$(USER_LIB_INSTALL_PATH)
endif		


LIBSEARDUINO_CFLAGS=
LIBSEARDUINO_CXXFLAGS=

#
#  C and C++ options
#  
override CFLAGS +=  $(LIBSEARDUINO_C_CPP_FLAGS) $(LIBSEARDUINO_CFLAGS) $(USER_C_FLAGS)  $(_CFLAGS) -DARDUINO=$(ARDUINO_VERSION)
override CXXFLAGS += $(LIBSEARDUINO_C_CPP_FLAGS) $(LIBSEARDUINO_CXXFLAGS) $(USER_CXX_FLAGS) $(_CXXFLAGS) -DARDUINO=$(ARDUINO_VERSION)

#########################################
#
#   LD options
#
ifeq ($(uname_S),Linux)
   # GNU/Linux
   override LDFLAGS += $(_LDFLAGS) $(SEARDUINO_LIB_PATH) $(LIBRARIES_LIB) \
                   -Wl,-whole-archive $(SEARDUINO_LIB) -Wl,-no-whole-archive \
                    $(USER_LD_FLAGS)  $(_LDFLAGS) $(LIBRARIES_LIB) $(SEARDUINO_LIB) 
else 
  ifeq ($(uname_S),Darwin)
  # Mac / Darwin
 override LDFLAGS += $(_LDFLAGS) $(SEARDUINO_LIB_PATH) $(LIBRARIES_LIB) \
                    $(SEARDUINO_LIB)  \
                    $(USER_LD_FLAGS) $(_LDFLAGS) $(LIBRARIES_LIB) $(SEARDUINO_LIB) 
  else
  # Win....
  override LDFLAGS += $(_LDFLAGS) $(SEARDUINO_LIB_PATH) $(LIBRARIES_LIB) \
                   -Wl,-whole-archive $(SEARDUINO_LIB) -Wl,-no-whole-archive \
                    $(USER_LD_FLAGS) $(_LDFLAGS) $(LIBRARIES_LIB) $(SEARDUINO_LIB) 
  endif
endif
#
#   LD options
#
#########################################


$(OBJ_C): $(SRC_HEADERS) $(SRC_C) 
$(OBJ_CXX): $(SRC_HEADERS) $(SRC_CXX)

INTERNAL_FLAGS= -DMY_ARDUINO=$(ARDUINO) -DMY_BOARD=$(BOARD)

$(OBJ_PATH)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -I. $(INTERNAL_FLAGS) $<  -o $@

$(OBJ_PATH)%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) -I. $(INTERNAL_FLAGS) $< -o $@ 

%.E: %.cpp
	$(CXX) -E $(CXXFLAGS) -I. $(INTERNAL_FLAGS) $< -o $@ 

%.E: %.c
	$(CC) -E $(CXXFLAGS) -I. $(INTERNAL_FLAGS) $< -o $@ 

clean:
	rm -f *.o *.rom *.elf *.map *~ *.lst $(OBJ_C) $(OBJ_CXX) $(OBJ_MAIN) *.eep *.hex *.a $(LIB) $(SHLIB) *.so libs/*/* $(PROG) *.pyc *.d

light-clean:
	rm -f *.o *.rom *.elf *.map *~ *.lst $(OBJ_C) $(OBJ_CXX) $(OBJ_MAIN) *.eep *.hex $(PROG) *.pyc

efile: $(E_C) $(E_CXX)

all: $(PROG) $(LIB) $(OBJ_C) $(OBJ_CXX)

shlib: $(SHLIB)

$(LIB): $(OBJ_C)  $(OBJ_CXX) 
	@echo "Creating directory: $(LIB_PATH)/"
	mkdir -p $(LIB_PATH)/
	$(AR) rcs $(LIB)  $(OBJ_C)  $(OBJ_CXX) 
	@echo "Created lib: $(LIB)   for $(BOARD) $(ARDUINO)"

$(SHLIB): LIB_FLAGS:=-Dmain=searduino_main
$(SHLIB): $(OBJ_MAIN) $(OBJ_C)  $(OBJ_CXX) 
	@echo "Creating directory: $(LIB_PATH)/"
	mkdir -p $(LIB_PATH)/
	$(CXX)  -shared  $(OBJ_MAIN) $(OBJ_C)  $(OBJ_CXX)   -o $(SHLIB) $(LDFLAGS)
	@echo "Created lib: $(SHLIB)"


lib: $(LIB) $(OBJ_C) $(OBJ_CXX) 

lib-install: $(LIB) $(LIB_H)
	-mkdir -p $(LIB_INSTALL)/lib/$(BOARD)/
	-mkdir -p $(LIB_INSTALL)/include
	-cp $(LIB) $(LIB_INSTALL)/lib/$(BOARD)/
	-cp $(LIB_H)  $(LIB_INSTALL)/include/


libs: lib shlib


uno:
        SEARDUINO_OVERRIDE_ARDUINO=uno ARDUINO=stub make clean all upload

due:
        SEARDUINO_OVERRIDE_ARDUINO=due ARDUINO=stub make clean all upload

mega:
        SEARDUINO_OVERRIDE_ARDUINO=mega ARDUINO=stub make clean all upload

mega2560:
        SEARDUINO_OVERRIDE_ARDUINO=mega2560 ARDUINO=stub make clean all upload

sim:
        SEARDUINO_OVERRIDE_ARDUINO=stub ARDUINO=stub make clean shlib

sim-start:
	make sim
	$(ARDUINO_PATH)/bin/searduino-jearduino.sh --arduino-code $(SHLIB)

simpson:
	make sim-start



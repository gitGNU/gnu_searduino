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

ifndef ARDUINO
$(error Variables not set correctly ARDUINO='${ARDUINO}')
endif		


#uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')

ifndef BOARD
$(error Variables not set correctly BOARD='$(BOARD)' (ARDUINO='${ARDUINO}'))
endif		

LIB_INSTALL=.
ifdef USER_LIB_INSTALL_PATH
LIB_INSTALL=$(USER_LIB_INSTALL_PATH)
endif		


LIBSEARDUINO_CFLAGS=
LIBSEARDUINO_CXXFLAGS=

override CFLAGS +=  $(LIBSEARDUINO_C_CPP_FLAGS) $(LIBSEARDUINO_CFLAGS) $(USER_C_FLAGS)  $(_CFLAGS)
override CXXFLAGS += $(LIBSEARDUINO_C_CPP_FLAGS) $(LIBSEARDUINO_CXXFLAGS) $(USER_CXX_FLAGS) $(_CXXFLAGS)

override LDFLAGS += $(_LDFLAGS) $(SEARDUINO_LIB_PATH) -l$(SEARDUINO_LIB)


$(OBJ_C): $(SRC_HEADERS) $(SRC_C) 
$(OBJ_CXX): $(SRC_HEADERS) $(SRC_CXX)  

INTERNAL_FLAGS= -DMY_ARDUINO=$(ARDUINO) -DMY_BOARD=$(BOARD)

%.o: %.c
	$(CC) -c $(CFLAGS) -I. $(INTERNAL_FLAGS) $<  -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -I. $(INTERNAL_FLAGS) $< -o $@ 

%.E: %.cpp
	$(CXX) -E $(CXXFLAGS) -I. $(INTERNAL_FLAGS) $< -o $@ 

%.E: %.c
	$(CC) -E $(CXXFLAGS) -I. $(INTERNAL_FLAGS) $< -o $@ 

clean:
	rm -f *.o *.rom *.elf *.map *~ *.lst $(OBJ_C) $(OBJ_CXX) *.eep *.hex *.a $(LIB) $(SHLIB) *.so libs/*/* $(PROG) *.pyc

light-clean:
	rm -f *.o *.rom *.elf *.map *~ *.lst $(OBJ_C) $(OBJ_CXX) *.eep *.hex $(PROG) *.pyc

efile: $(E_C) $(E_CXX)

all: $(PROG) $(LIB) $(OBJ_C) $(OBJ_CXX)

OBJ_C = $(SRC_C:.c=.o)
OBJ_CXX = $(SRC_CXX:.cpp=.o)
OBJ_JAVA= $(SRC_JAVA:.java=.o)

#$(SHLIB): clean $(OBJ_C)  $(OBJ_CXX) 
#	echo "msmsm"

shlib: $(SHLIB)

$(LIB): $(OBJ_C)  $(OBJ_CXX) 
	@echo "Creating directory: $(LIB_PATH)/"
	mkdir -p $(LIB_PATH)/
	$(AR) rcs $(LIB)  $(OBJ_C)  $(OBJ_CXX) 
	@echo "Created lib: $(LIB)   for $(BOARD) $(ARDUINO)"

$(SHLIB): LIB_FLAGS:=-Dmain=searduino_main
$(SHLIB): $(OBJ_C)  $(OBJ_CXX) 
	@echo "Creating directory: $(LIB_PATH)/"
	mkdir -p $(LIB_PATH)/
	$(CC)  -shared  $(OBJ_C)  $(OBJ_CXX)   -o $(SHLIB) $(LDFLAGS)
	@echo "Created lib: $(SHLIB)"


lib: $(LIB) $(OBJ_C) $(OBJ_CXX) 

lib-install: $(LIB) $(LIB_H)
	-mkdir -p $(LIB_INSTALL)/lib/$(BOARD)/
	-mkdir -p $(LIB_INSTALL)/include
	-cp $(LIB) $(LIB_INSTALL)/lib/$(BOARD)/
	-cp $(LIB_H)  $(LIB_INSTALL)/include/


libs: lib shlib


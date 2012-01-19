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

ifeq (${ARDUINO},stub)
include $(SEARDUINO_PATH)/mk/searduino-stub.mk
else
include $(SEARDUINO_PATH)/mk/searduino-arduino.mk
endif


#uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')

ifndef BOARD
$(error Variables not set correctly BOARD='$(BOARD)' (ARDUINO='${ARDUINO}'))
endif		


LIBSEARDUINO_CFLAGS=
LIBSEARDUINO_CXXFLAGS=

CFLAGS=  $(LIBSEARDUINO_C_CPP_FLAGS) $(LIBSEARDUINO_CFLAGS) $(USER_C_FLAGS)  $(_CFLAGS)
CXXFLAGS=$(LIBSEARDUINO_C_CPP_FLAGS) $(LIBSEARDUINO_CXXFLAGS) $(USER_CXX_FLAGS) $(_CXXFLAGS)

SEARDUINO_LIB_PATH=$(SEARDUINO_PATH)/arduino-libs/$(BOARD) 
LDFLAGS=$(_LDFLAGS) -L$(SEARDUINO_LIB_PATH) -lsearduino 



$(OBJ_C): $(SRC_HEADERS) $(SRC_C) 
$(OBJ_CXX): $(SRC_HEADERS) $(SRC_CXX)  

INTERNAL_FLAGS= -DMY_ARDUINO=$(ARDUINO) -DMY_BOARD=$(BOARD)

%.o: %.c
	echo "This rule?"
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
	rm -f *.o *.rom *.elf *.map *~ *.lst $(OBJ_C) $(OBJ_CXX) *.eep *.hex 

efile: $(E_C) $(E_CXX)

all: $(PROG) $(LIB) $(OBJ_C) $(OBJ_CXX)


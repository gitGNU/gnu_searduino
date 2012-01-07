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
	@echo "Created lib: $(LIB)   for $(BOARD) $(ARDUINO) ***************"

$(SHLIB): LIB_FLAGS:=-Dmain=searduino_main
$(SHLIB): $(OBJ_C)  $(OBJ_CXX) 
	@echo "Creating directory: $(LIB_PATH)/"
	mkdir -p $(LIB_PATH)/
	$(CC) -shared  $(OBJ_C)  $(OBJ_CXX)  $(SHLIB_LIBS)  -o $(SHLIB) 
	@echo "Created lib: $(SHLIB)"


lib: $(LIB) $(OBJ_C)  $(OBJ_CXX) 



libs: lib shlib

li: 
	@echo "LIB      $(LIB)"
	@echo "BOARD    $(BOARD)"
	@echo "ARDUINO  $(ARDUINO)"
	@echo "C        $(OBJ_C)"
	@echo "C        $(SRC_C)"
	@echo "CXX      $(OBJ_CXX)"
	@echo "CXX      $(SRC_CXX)"
	@echo "SHF      $(LIB_FLAGS)"


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



BUILD_FROM_VCS=true
ARDUINO=stub
SRC_C=wrapper_py.c
SRC_CXX=
SHLIB=pardon.so
USER_C_FLAGS=-I/usr/include/python2.7/ -lpython2.7 -fPIC
USER_CXX_FLAGS=-I/usr/include/python2.7/ -lpython2.7 -fPIC
SHLIB_LIBS=   -lsearduino-stub -L../faked-arduino  -L../example/python-digcounter/ -ldigcounter
# -L../test/shared -ltest
#-L../example/python-digcounter/ -ldigcounter

#lib:
#	gcc -shared wrapper_py.c -o $(SHLIB) 


SEARDUINO_PATH=..
SEARDUINO_MK=../mk/searduino.mk
SEARDUINO_LIB_MK=../mk/searduino_lib.mk
SRC_HEADERS=

shlib: $(SHLIB)
lib: $(LIB)



include $(SEARDUINO_MK)
include $(SEARDUINO_LIB_MK)


check:
	export LD_LIBRARY_PATH=../faked-arduino:../test/shared/ && ./pardon.py

install:
	@cp $(SHLIB) $(INSTALL_DIR)/searduino/libs/

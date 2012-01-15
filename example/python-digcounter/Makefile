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


ARDUINO_VERSION=100
ARDUINO=stub

SHLIB=libdigcounter.so
SHLIB_LIBS= -L/opt/searduino/libs -lsearduino-stub -lpthread 
SRC_C=ard_code.c
SRC_CXX=

USER_C_FLAGS=-fPIC -Wl,-G -Wl,-dy 
USER_LD_FLAGS=-lpthread -fPIC -Wl,-G -Wl,-dy $(SHLIB_LIBS)


SEARDUINO_PATH=/opt/searduino




all: $(SHLIB)

include $(SEARDUINO_PATH)/mk/searduino.mk
include $(SEARDUINO_PATH)/mk/searduino_lib.mk


check: 
	export LD_LIBRARY_PATH=$(SEARDUINO_PATH)/libs && \
	export PYTHONPATH=$(SEARDUINO_PATH)/libs && \
	./simple-hw.py
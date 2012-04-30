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

#
# Set the variable below if you want to run together with simple-hw.py
SHLIB=arduino-code.so

#
# Set the variable below if you want to run your program stand alone
#PROG=ard_code

SHLIB_LIBS= 
SRC_C=arduino-code.c
SRC_CXX=

USER_C_FLAGS=-fPIC 
USER_LD_FLAGS=$(SHLIB_LIBS)


SEARDUINO_PATH=../../../../

all: $(SHLIB)

include $(SEARDUINO_PATH)/mk/searduino-vcs.mk

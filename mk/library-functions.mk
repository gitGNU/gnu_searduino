#
#       Searduino
#                                                                   
# Basically a couple of Makefile wrapping the Ardunio
# C and C++ files
#                                                                   
#  Copyright (C) 2014 Henrik Sandklef      
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
SEARDUINO_PATH=/opt/searduino/
ARDUINO_PATH==/opt/searduino/

export SRC_C
export SRC_CXX
export H_FILES
export LIB
export USER_CXX_FLAGS
export USER_C_FLAGS
export USER_LD_FLAGS
export PACKAGE
export SEARDUINO_PATH
export SEARDUINO_MK=$(SEARDUINO_PATH)/share/searduino/mk/searduino.mk

MK_PATH= $(SEARDUINO_PATH)/share/searduino/mk/external-libraries/

ifeq (${BOARDS_TO_BUILD},)
BOARDS_TO_BUILD=due uno leonardo mega mega2560 stub
endif


all: $(BOARDS_TO_BUILD)

stub: ARDUINO=stub
stub: 
	make -f $(MK_PATH)/Makefile.stub extlib

due: ARDUINO=due
due: 
	make -f $(MK_PATH)/Makefile.due extlib

uno: ARDUINO=uno
uno: 
	make -f $(MK_PATH)/Makefile.uno extlib

mega: ARDUINO=mega
mega: 
	make -f $(MK_PATH)/Makefile.mega extlib

mega2560: ARDUINO=mega2560
mega2560: 
	make -f $(MK_PATH)/Makefile.mega2560 extlib

leonardo: ARDUINO=leonardo
leonardo: 
	make -f $(MK_PATH)/Makefile.leonardo extlib

install: uno
install: 
	make -f $(MK_PATH)/Makefile.uno extinstall

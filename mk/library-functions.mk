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
SEARDUINO_PATH=/opt/searduino
ARDUINO_PATH=/opt/searduino

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

install:
	make -f $(MK_PATH)/Makefile.uno extinstall


clean:
	make -f $(MK_PATH)/Makefile.uno extclean


all: mydue myuno myleonardo mymega mymega2560

mydue: ARDUINO=due
mydue: 
	make -f $(MK_PATH)/Makefile.due extlib

myuno: ARDUINO=uno
myuno: 
	make -f $(MK_PATH)/Makefile.uno extlib

mymega: ARDUINO=mega
mymega: 
	make -f $(MK_PATH)/Makefile.mega extlib

mymega2560: ARDUINO=mega2560
mymega2560: 
	make -f $(MK_PATH)/Makefile.mega2560 extlib

myleonardo: ARDUINO=leonardo
myleonardo: 
	make -f $(MK_PATH)/Makefile.leonardo extlib



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
include ../mk/Makefile-prog.mk

export ARDUINO=stub
export SRC_C=test.c
export LIBTEST_PATH=../shared/
export LIBTEST=-ltest 
export SEARDUINO_PATH=../..

export USER_C_FLAGS= -g -I../../faked-arduino/include/arduino -I../../faked-arduino/include/../../arduino-extras/include/
export USER_LD_FLAGS= -ldl -L$(LIBTEST_PATH) $(LIBTEST) 

include $(SEARDUINO_PATH)/mk/searduino-vcs.mk

# dummy target for internal searduino devel
distclean:
	@echo

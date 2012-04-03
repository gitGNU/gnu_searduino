
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


ARDUINO=stub

PROG=test
SRC_C=test.c

LIBTEST_PATH=../shared/
LIBTEST=-ltest 

SEARDUINO_PATH=../..

USER_C_FLAGS= -g -I../../faked-arduino/include/arduino -I../../faked-arduino/include/../../arduino-extras/include/
SER_LD_FLAGS= -ldl -L$(LIBTEST_PATH) $(LIBTEST) 

$(PROG): 

include $(SEARDUINO_PATH)/mk/searduino-vcs.mk

check: $(PROG)
	cd ../shared && make clean shlib
	./$(PROG)

install:
	echo nothing to do in install

distdir:
	echo nothing to do in dist

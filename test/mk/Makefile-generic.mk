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

export PROG=test
export SEARDUINO_PATH=../../
export LIB_PATH=.


first:
	echo nothing to do for all

check-stub: 
	make -f ../mk/Makefile-generic.mk clean
	make -f ../mk/Makefile-generic.mk prog
	make -f ../mk/Makefile-generic.mk clean
	make -f ../mk/Makefile-generic.mk shlib

check-simulator: 
	../../simulators/stream/searduino-stream-sim --arduino-code ./$(SHLIB)

check-board: 
	make -f ../mk/Makefile-generic.mk clean
	make -f ../mk/Makefile-generic.mk prog

check-upload: 

check-shlib: 
	make -f ../mk/Makefile-generic.mk clean
	make -f ../mk/Makefile-generic.mk shlib

check-lib: 
	make -f ../mk/Makefile-generic.mk clean
	make -f ../mk/Makefile-generic.mk lib

check-prog:
	make -f ../mk/Makefile-generic.mk clean
	make -f ../mk/Makefile-generic.mk prog
	LD_LIBRARY_PATH=../../faked-arduino/.libs/:../shared DYLD_LIBRARY_PATH=../../faked-arduino/.libs/:../shared  ./$(PROG)

include $(SEARDUINO_PATH)/mk/searduino-vcs.mk

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
SRC_C=simulator.c
SRC_CXX=
MAIN_SRC=
PROG=cim_sim
#SHLIB=pardon.so
USER_C_FLAGS=
USER_LD_FLAGS=  -L../test/shared -L../faked-arduino -ltest -lsearduino-stub
#lib:
#	gcc -shared wrapper_py.c -o $(SHLIB) 


SEARDUINO_PATH=..
SEARDUINO_MK=../mk/searduino.mk
SEARDUINO_LIB_MK=../mk/searduino_lib.mk
SRC_HEADERS=

$(PROG):


include $(SEARDUINO_MK)
include $(SEARDUINO_LIB_MK)

#
#       Searduino
#                                                                   
# Basically a couple of Makefile wrapping the Ardunio
# C and C++ files
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

all: uno mega due

uno:
	make -f Makefile.uno

due:
	make -f Makefile.due

mega:
	make -f Makefile.mega

clean:
	make -f Makefile.uno clean

install: due uno mega
	 @echo "installing to /opt/searduino"
	 mkdir -p  /opt/searduino/arduino-libs 
	 @cp -r libs/*  /opt/searduino/arduino-libs/
	 @mkdir -p /opt/searduino/include/arduino
	 @mkdir -p /opt/searduino/include/arduino/core
	 @cp -r core/*.h     /opt/searduino/include/arduino/core
	 @cp -r variants /opt/searduino/include/arduino/


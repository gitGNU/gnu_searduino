#
#       Searduino
#                                                                   
# Basically a couple of Makefile wrapping the Ardunio
# C and C++ files
#                                                                   
#  Copyright (C) 2012 Henrik Sandklef      
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

INSTALLATION_DIR=/tmp/conf-test

all: uno mega due mega2560 leonardo

uno:
#	make -f Makefile.uno light-clean
	make -f Makefile.uno lib

due:
#	make -f Makefile.due light-clean
	make -f Makefile.due lib

mega:
#	make -f Makefile.mega light-clean
	make -f Makefile.mega lib

mega2560:
#	make -f Makefile.mega2560 light-clean
	make -f Makefile.mega2560 lib

leonardo:
	make -f Makefile.leonardo lib

clean:
	make -f Makefile.uno clean

check:
	@echo "Nothing to do in libraries"

install: due uno mega mega2560
	 @echo "installing to $(INSTALLATION_DIR)"
	 mkdir -p  $(INSTALLATION_DIR)/libs/searduino/arduino-libs 
	 @cp -r ../../arduino-sources/libs/*     $(INSTALLATION_DIR)/libs/searduino/arduino-libs/

distdir:
	echo dummy impl

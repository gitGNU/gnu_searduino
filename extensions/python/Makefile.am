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

AUTOMAKE_OPTIONS = gnu

if PYTHON_EXT_SUPPORT

lib_LTLIBRARIES = libpearduino.la
libpearduino_la_SOURCES = pearduino.c

AM_CFLAGS=@PYTHON_CPPFLAGS@ -I../../arduino-sources/core  -I../../faked-arduino/include/arduino -I../../faked-arduino/include/  -I../../arduino-extras/include/ 
AM_LDFLAGS=@PYTHON_LDFLAGS@   -L../../faked-arduino/.libs  -L../../faked-arduino/.libs   -lsearduinostub   
#-L../arduino-lib/
#-larduino-code 

install-exec-hook:
	@-rm $(DESTDIR)$(libdir)/pearduino$(SHLIB_EXT)
	ln -s $(DESTDIR)$(libdir)/libpearduino$(SHLIB_EXT) \
              $(DESTDIR)$(libdir)/pearduino$(SHLIB_EXT)

endif

#
#       Searduino
#
#  Copyright (C) 2013 Henrik Sandklef      
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

if JAVA_EXT_SUPPORT

BUILT_SOURCES = com_sandklef_searduino_Searduino.h



SEARD_JNI_SRC = c/searduino-jni.cpp c/searduino-jni.h

lib_LTLIBRARIES = libsearduinojni.la 
libsearduinojni_la_SOURCES = $(SEARD_JNI_SRC)

#libsearduinojni.la: $(SEARDUINO_JAR)
#$(lib_LTLIBRARIES): $(SEARDUINO_JAR)


if DEBIANSOURCES
SEARDUINO_INC_PATH=/usr/share/arduino/hardware/arduino/cores/arduino/
SEARDUINO_LIB_INC_PATH=/usr/share/arduino/libraries
else
SEARDUINO_INC_PATH=../../arduino-sources/core
SEARDUINO_LIB_INC_PATH=../../arduino-sources/libraries
endif

EXTRA_DIST= $(SEARD_JNI_SRC) $(SEARDUINO_JAVA_SOURCES)

AM_CXXFLAGS= -I$(SEARDUINO_INC_PATH)/   -I../../faked-arduino/include/arduino -I../../faked-arduino/include/  -I../../arduino-extras/include/ 
AM_LDFLAGS= -L../../faked-arduino/.libs   -lsearduinostub

LIB_PATHS=./:../../faked-arduino/.libs/

JAVACFLAGS=-cp $(LIB_PATHS)  

com_sandklef_searduino_Searduino.h: $(SEARDUINO_JAR)

SEARDUINO_JAR=Searduino.jar
SEARDUINO_PATH=com/sandklef/searduino/
SEARDUINO_JAVA_SOURCES=$(SEARDUINO_PATH)/Searduino.java $(SEARDUINO_PATH)/SearduinoObserver.java
$(SEARDUINO_JAR): $(SEARDUINO_JAVA_SOURCES) 
	javac $(JAVACFLAGS) $(SEARDUINO_JAVA_SOURCES)
	javah com.sandklef.searduino.Searduino
	jar cf $(SEARDUINO_JAR) $(SEARDUINO_PATH)/*.class

EXTRA_DIST = $(SEARD_JNI_SRC) $(SEARDUINO_JAVA_SOURCES)

install-exec-hook: $(SEARDUINO_JAR) $(libsearduinojni.la)
	-rm $(DESTDIR)$(libdir)/jearduino$(SHLIB_EXT)
	ln -s $(DESTDIR)$(libdir)/libjearduino$(SHLIB_EXT) \
              $(DESTDIR)$(libdir)/jearduino$(SHLIB_EXT)
	cp $(SEARDUINO_JAR)  $(DESTDIR)$(libdir)/


endif

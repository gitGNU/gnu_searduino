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
SIMULATOR=searduino-stream-sim
bin_PROGRAMS= $(SIMULATOR)
searduino_stream_sim_SOURCES=simulator.c

#if GL_GENERATE_PTHREAD_H
#  GNULIB_PTHREAD_I=-I../../lib
#  GNULIB_PTHREAD_A=lib/libgnu.a
#else
#  GNULIB_PTHREAD_I=
#  GNULIB_PTHREAD_A= -lpthread 
#endif


if DEBIANSOURCES
SEARDUINO_INC_PATH=/usr/share/arduino/hardware/arduino/cores/arduino/
SEARDUINO_LIB_INC_PATH=/usr/share/arduino/libraries
else
SEARDUINO_INC_PATH=../../arduino-sources/core
SEARDUINO_LIB_INC_PATH=../../arduino-sources/libraries
endif

bin_SCRIPTS = searduino-stream.sh 

EXTRA_DIST = searduino-stream.sh.tmpl $(bin_SCRIPTS) $(JAVA_SOURCES)


AM_CFLAGS= -I$(SEARDUINO_INC_PATH)/   -I../../faked-arduino/include/arduino -I../../faked-arduino/include/ -I../../arduino-extras/include/ $(GNULIB_PTHREAD_I) --std=c99

if USE_XTEST
XTESTFLAGS = $(LIBXTST)
else
XTESTFLAGS = 
endif



AM_LDFLAGS= -L../../faked-arduino/.libs  -lsearduinostub  -lpthread $(LIBXTST)
#$(GNULIB_PTHREAD_I) 






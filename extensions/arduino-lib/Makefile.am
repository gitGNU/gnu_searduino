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

LIB_ARDUINOCODE_H_FILES=
LIB_ARDUINOCODE_C_FILES=arduino_code.c $(LIB_ARDUINOCODE_H_FILES)

libarduino_code_la_SOURCES = $(LIB_ARDUINOCODE_C_FILES)
lib_LTLIBRARIES = libarduino-code.la


AM_CFLAGS= -I../../arduino-sources/core  -I../../faked-arduino/include/arduino -I../../faked-arduino/include/ -I../../faked-arduino/ -I../../arduino-extras/include -Dmain=searduino_main
AM_LDFLAGS=







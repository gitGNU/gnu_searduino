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
####################################################################

#
# Instructions on how to use this Makefile can be found at the end 
# of this file
#

#
# Path to your Searduino installation
#
SEARDUINO_PATH=/tmp/TMP_INSTALL3/

#
# Source code
#
SRC_C=main.c 
SRC_CXX=serial.cpp

#
# Build type should be any of the following
#
# ARDUINO=due
# ARDUINO=uno
# ARDUINO=mega
# ARDUINO=stub
#
# By default, we're building for local execution (not Arduino boards)
#   you can change this value at wish
#
ARDUINO=stub

#PROG=fastdigio
SHLIB=fastdigio.so

#include $(SEARDUINO_PATH)/share/searduino//mk/searduino.mk
include $(SEARDUINO_PATH)/share/searduino//mk/searduino.mk


########## Build instructions ################
#
#
#
# Build shared library (for use in simulators):
#
#    Set the ARDUNIO variable in this Makefile to stub and then execute
#
#        make clean shlib
#
#
# Build stand alone binary
#
#     Set the ARDUNIO variable in this Makefile to stub and then execute
#
#        make clean prog
#
#
# Build binary for uno
#
#     Set the ARDUNIO variable in this Makefile to uno and then execute
#
#        make clean prog
#
#
#
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
SEARDUINO_PATH=../..

SRC_C= ./Wire/utility/twi.c
SRC_CXX=./Ethernet/Ethernet.cpp ./Ethernet/EthernetServer.cpp ./Ethernet/Dhcp.cpp ./Ethernet/utility/w5100.cpp ./Ethernet/utility/socket.cpp ./Ethernet/EthernetUdp.cpp ./Ethernet/Dns.cpp ./Ethernet/EthernetClient.cpp  ./Wire/Wire.cpp ./SPI/SPI.cpp ./LiquidCrystal/LiquidCrystal.cpp ./SoftwareSerial/SoftwareSerial.cpp ./SD/SD.cpp ./SD/utility/SdVolume.cpp ./SD/utility/SdFile.cpp ./SD/utility/Sd2Card.cpp ./SD/File.cpp ./Stepper/Stepper.cpp ./EEPROM/EEPROM.cpp ./Servo/Servo.cpp 

#./Firmata/Firmata.cpp

LIB_PATH=$(SEARDUINO_PATH)/arduino-sources/libraries/libs/$(BOARD)/
LIB=$(LIB_PATH)/liblibraries.a



SEARDUINO_MK=$(SEARDUINO_PATH)/mk/searduino-vcs.mk

lib: $(LIB)
$(LIB): $(OBJ_C)  $(OBJ_CXX) 

include $(SEARDUINO_MK)
include $(SEARDUINO_FUNC)



objs: $(OBJ_C) $(OBJ_CXX)
	-ls -al $(OBJ_C)
	-ls -al $(OBJ_CXX)

due: ARDUINO=due
due: 
	make lib

uno: ARDUINO=uno
uno: 
	make lib

mega: ARDUINO=mega
mega: 
	make lib


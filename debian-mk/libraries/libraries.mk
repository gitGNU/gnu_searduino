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
DEBIAN_BUILD=true

ARDUINO_SOURCE_PATH=/usr/share/arduino/hardware/arduino/cores/arduino/
ARDUINO_PATH=/usr/share/arduino/hardware/arduino/
ARDUINO_LIBS_SOURCE_PATH=/usr/share/arduino/libraries



SRC_C= $(ARDUINO_LIBS_SOURCE_PATH)/Wire/utility/twi.c
SRC_CXX= \
	$(ARDUINO_LIBS_SOURCE_PATH)/Ethernet/Ethernet.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/Ethernet/EthernetServer.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/Ethernet/Dhcp.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/Ethernet/utility/w5100.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/Ethernet/utility/socket.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/Ethernet/EthernetUdp.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/Ethernet/Dns.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/Ethernet/EthernetClient.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/Wire/Wire.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/SPI/SPI.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/LiquidCrystal/LiquidCrystal.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/SoftwareSerial/SoftwareSerial.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/SD/SD.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/SD/utility/SdVolume.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/SD/utility/SdFile.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/SD/utility/Sd2Card.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/SD/File.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/Stepper/Stepper.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/EEPROM/EEPROM.cpp \
	$(ARDUINO_LIBS_SOURCE_PATH)/Servo/Servo.cpp 

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

mega2560: ARDUINO=mega2560
mega2560:
	make lib

leonardo: ARDUINO=leonardo
leonardo:
	make lib


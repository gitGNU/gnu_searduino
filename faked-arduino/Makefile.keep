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

MODULE_C_FLAGS   = -fPIC -Wl,-G -Wl,-dy \
                   -I$(SEARDUINO_PATH)/faked-arduino/arduino/include \
                   -I$(SEARDUINO_PATH)/faked-arduino/communication/include

MODULE_CXX_FLAGS = fPIC -Wl,-G -Wl,-dy \
                   -I$(SEARDUINO_PATH)/faked-arduino/arduino/include \
                   -I$(SEARDUINO_PATH)/faked-arduino/communication/include

SRC_C= ./communication/src/comm.c      \
       ./communication/src/ext_io.c \
       ./communication/src/digio.c \
       ./communication/src/read_command.c \
       ./utils/src/print.c             \
       ./arduino/src/wiring_digital.c  \
       ./arduino/src/setup.c  \
       ./arduino/src/time_stuff.c

LIB=$(SEARDUINO_PATH)/faked-arduino/libsearduino-stub.a
SHLIB=$(SEARDUINO_PATH)/faked-arduino/libsearduino-stub.so

ARDUINO=stub
BOARD=stub

SEARDUINO_PATH=..
SEARDUINO_MK=../mk/searduino.mk
SEARDUINO_LIB_MK=../mk/searduino_lib.mk
SRC_HEADERS=

lib: $(LIB)
shlib: $(SHLIB)

include $(SEARDUINO_MK)
include $(SEARDUINO_LIB_MK)

install: 
#$(LIB) $(SHLIB)
	@echo "installing to $(INSTALL_DIR)"
	@cp $(LIB) $(SHLIB) $(INSTALL_DIR)/searduino/libs/
	@mkdir -p $(INSTALL_DIR)/searduino/include/faked-arduino/communication/
	@mkdir -p $(INSTALL_DIR)/searduino/include/faked-arduino/arduino/
	@mkdir -p $(INSTALL_DIR)/searduino/include/faked-arduino/utils/
	@cp -r include/* $(INSTALL_DIR)/searduino/include/faked-arduino/

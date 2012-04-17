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

ifeq ($(UNAME), Linux)
	USB_DEV=/dev/ttyUSB0
endif
ifeq ($(UNAME), Darwin)
	USB_DEV=/dev/change-me-atmega1280.mk
endif



board_name="Arduino Mega (ATboard_280)"
board_upload.protocol="arduino"
board_upload.maximum_size=126976
board_upload.speed=57600
board_bootloader.low_fuses="0xFF"
board_bootloader.high_fuses="0xDA"
board_bootloader.extended_fuses="0xF5"
board_bootloader.path="atmega"
board_bootloader.file="ATboard_OOT_168_atboard_280.hex"
board_bootloader.unlock_bits="0x3F"
board_bootloader.lock_bits="0x0F"
board_build.mcu="atboard_280"
board_build.f_cpu=16000000L
board_build.core=arduino
board_build.variant=mega


mega.name=Arduino Mega (ATmega1280)


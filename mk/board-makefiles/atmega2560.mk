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

ifeq ("$(USB_DEV)", "")
  ifeq ($(UNAME), Linux)
	USB_DEV=/dev/ttyACM0
  endif
  ifeq ($(UNAME), Darwin)
	USB_DEV=unknown-port-$(ARDUINO)
  endif
  ifeq ($(UNAME), CYGWIN_NT_5.1)
	USB_DEV="\\.\COM1"
  endif
endif


board_name="Arduino Mega 2560"
board_upload.protocol="stk500v2"
board_upload.maximum_size=258048
board_upload.speed=115200
board_bootloader.low_fuses="0xFF"
board_bootloader.high_fuses="0xD8"
board_bootloader.extended_fuses="0xFD"
board_bootloader.path="stk500v2"
board_bootloader.file="stk500_v2_mega_2560.hex"
board_bootloader.unlock_bits="0x3F"
board_bootloader.lock_bits="0x0F"
board_build.mcu="atmega2560"
board_build.f_cpu=16000000L
board_build.core=arduino
board_build.variant=mega


mega2560.name=Arduino Mega 2560 or Mega ADK





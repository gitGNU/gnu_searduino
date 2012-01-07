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


board_name="Arduino Uno"
board_upload.protocol="arduino"
board_upload.maximum_size="32256"
board_upload.speed="115200"
board_bootloader.low_fuses="0xff"
board_bootloader.high_fuses="0xde"
board_bootloader.extended_fuses="0x05"
board_bootloader.path="optiboot"
board_bootloader.file="optiboot_atmega328.hex"
board_bootloader.unlock_bits="0x3F"
board_bootloader.lock_bits="0x0F"
board_build.mcu="atmega328p"
board_build.f_cpu="16000000L"
board_build.core="arduino"
board_build.variant="standard"

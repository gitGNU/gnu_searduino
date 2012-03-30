#
#       Searduino
#                                                                   
# Basically a couple of Makefile wrapping the Ardunio
# C and C++ files
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


USB_DEV=NO-DEVICE-SPECIFIED

#
#  Linux
#
ifeq ($(uname_S),Linux)

ifeq ($(ARDUINO),due)
endif
ifeq ($(ARDUINO),uno)
endif
ifeq ($(ARDUINO),mega)
endif
ifeq ($(ARDUINO),mega2560)
endif

endif


#
#  Windows with cygwin
#
ifeq ($(uname_S),Cygwin)

ifeq ($(ARDUINO),due)
	USB_DEV=UNKNOWN-FOR-CYGWIN-DUE
endif
ifeq ($(ARDUINO),uno)
	USB_DEV=UNKNOWN-FOR-CYGWIN-UNO
endif
ifeq ($(ARDUINO),mega)
	USB_DEV=UNKNOWN-FOR-CYGWIN-MEGA
endif
ifeq ($(ARDUINO),mega2560)
	USB_DEV=UNKNOWN-FOR-CYGWIN-MEGA2560
endif

endif


#
#  Mac 
#
ifeq ($(uname_S),Darwin)

ifeq ($(ARDUINO),due)
	USB_DEV=UNKNOWN-FOR-MAC-DUE
#$(error FreeBSD not yet supported, edit the usb-device.mk)
endif
ifeq ($(ARDUINO),uno)
	USB_DEV=/dev/tty.usbmodemfa141
endif
ifeq ($(ARDUINO),mega)
	USB_DEV=UNKNOWN-FOR-MAC-MEGA
endif
ifeq ($(ARDUINO),mega2560)
	USB_DEV=UNKNOWN-FOR-MAC-MEGA2560
endif

endif



#
# FreeBSD
#
ifeq ($(uname_S),GNU/kFreeBSD)
$(error FreeBSD not yet supported, edit the usb-device.mk)
endif

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

SUBDIRS = arduino-sources board-makefiles libraries external-libraries

pkgdataexampledir = $(pkgdatadir)/mk
dist_pkgdataexample_DATA = \
  device-specific.mk \
  searduino-arduino.mk \
  searduino.mk \
  searduino-stub.mk \
  searduino-functions.mk \
  library-functions.mk \
  VERSION

DEBIAN_FILES= \
    debian-mk/Makefile.tmpl \
    debian-mk/arduino-sources \
    debian-mk/arduino-sources/Makefile.tmpl \
    debian-mk/arduino-sources/arduino-sources.mk \
    debian-mk/libraries \
    debian-mk/libraries/Makefile.tmpl \
    debian-mk/libraries/libraries.mk 

EXTRA_DIST = ./Makefile ./VERSION ./device-specific.mk ./searduino-vcs.mk ./board-makefiles/lilypad.mk ./board-makefiles/Makefile ./board-makefiles/nano328.mk ./board-makefiles/atmega168.mk ./board-makefiles/lilypad328.mk ./board-makefiles/fio.mk ./board-makefiles/pro328.mk ./board-makefiles/mini.mk ./board-makefiles/bt.mk ./board-makefiles/mega.mk ./board-makefiles/nano.mk ./board-makefiles/uno.mk ./board-makefiles/ethernet.mk ./board-makefiles/diecimila.mk ./board-makefiles/atmega1280.mk ./board-makefiles/pro5v328.mk ./board-makefiles/bt328.mk ./board-makefiles/atmega328.mk ./board-makefiles/atmega8.mk ./board-makefiles/mini328.mk ./board-makefiles/stub.mk ./board-makefiles/pro.mk ./board-makefiles/pro5v.mk ./board-makefiles/mega2560.mk ./searduino-stub.mk ./searduino-functions.mk    ./arduino-sources/Makefile ./arduino-sources/Makefile.tmpl ./arduino-sources/Makefile.due ./arduino-sources/arduino-sources.mk  ./arduino-sources/Makefile.mk ./arduino-sources/Makefile.mega ./arduino-sources/Makefile.mega2560 ./arduino-sources/Makefile.leonardo ./arduino-sources/Makefile.uno ./searduino.mk.tmpl  ./searduino-arduino.mk.tmpl ./searduino.mk ./searduino_lib.mk ./searduino-arduino.mk   ./board-makefiles/atmega2560.mk $(DEBIAN_FILES)

#./arduino-sources/libraries/Makefile.tmpl ./arduino-sources/libraries/Makefile.due ./arduino-sources/libraries/arduino-sources.mk  ./arduino-sources/libraries/Makefile.mk ./arduino-sources/libraries/Makefile.mega ./arduino-sources/libraries/Makefile.uno ./arduino-sources/libraries/Makefile


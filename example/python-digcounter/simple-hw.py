#!/usr/bin/python

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

from pardon import *
from threading import Thread
import time
import sys

#from gi.repository import Gtk
#from gi.repository import Gdk
#from gi.repository import GObject


#
# Input pin on Ardunio that the ard-code reads
ardInputPin=1

#
# Output pin on Ardunio where Ack is set
ardAckPin=5


receivedAck=0

def newDigOutCallback(pin, val):
    print "====================================> Py Callback:  new dig out: " + str(pin) + " = " + str(val)
    

def tickOneTime():
    tmp=0
    tmp2=0
    while True:
        limit = 10
        
        tmp = tmp + 1

        py_ext_set_input(ardInputPin,(tmp%2))

#        print "setting dig in: " + str(tmp) + " to: " +  str((tmp+tmp2)%2)
        py_ext_set_input(tmp,(tmp+tmp2)%2)
        time.sleep(0.1)

        if (tmp==8):
            tmp=0
            tmp2=tmp2+1
      
def main():

    print "Starting????"

    global receivedAck
    receivedAck=0 

    print "Register callback"
    my_set_callback(newDigOutCallback)
    time.sleep(1)


    print "Start thread"
    tt = Thread(target=tickOneTime, args=())
    tt.start()

    tmp = 0 
    while True:
        time.sleep (1)
        if (tmp==0):
            searduino_resume();
            tmp=1
        elif (tmp==10):
            searduino_pause();
            tmp=0
        else:
            tmp = tmp + 1
        



if __name__ == "__main__":
    main()

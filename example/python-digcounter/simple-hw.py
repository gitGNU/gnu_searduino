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

from pearduino import *
from threading import Thread
import time
import sys

#
# Digital pins (as seen by the Arduino)
# 
arduinoDigOutPinB = 3
arduinoDigInPin   = 2

sim_pause=0

arduinoDigOutPinBValue = 0 

expectedArduinoDigOutPinBValue = 0 

checkCounter = 0 

def newDigModeCallback(pin, mode):
    print "py:dmode" + str(pin) + ":" + str(mode) + "   callbacked Arduino dig mode   "

def newDigOutCallback(pin, val, pin_type):
    global arduinoDigOutPinBValue
    global arduinoDigOutPinB
    print "pyc:" + str(pin) + ":" + str(val) 
    if (pin==arduinoDigOutPinB):
        arduinoDigOutPinBValue = val
    
    
def setValues(value):
    global expectedArduinoDigOutPinBValue
    expectedArduinoDigOutPinBValue = value%2

    print "setValues(" + str(value) + ")  => set pin " + str(arduinoDigInPin) + " => " + str(expectedArduinoDigOutPinBValue)
    seasim_set_input(arduinoDigInPin,expectedArduinoDigOutPinBValue,1)
    time.sleep(0.4)



def pause():
    print "Pausing...."
    global sim_pause
    sim_pause=1;
    seasim_pause();
#    setValues(1)
      
def resume():
    print "Resuming...."
    global sim_pause
    seasim_resume();
#    setValues(1)
    sim_pause=0;

def check_values():
    global checkCounter 
    global expectedArduinoDigOutPinBValue
    global arduinoDigOutPinBValue
    global sim_pause

    if (sim_pause==0):
        checkCounter = checkCounter + 1
        checkEq1 = (expectedArduinoDigOutPinBValue==arduinoDigOutPinBValue)
        if (checkEq1==False):
            print "CHECK 1 Failed:     " + str(expectedArduinoDigOutPinBValue) + "==" + \
                str(arduinoDigOutPinBValue) + " => " + \
                str(checkEq1)
            sys.exit(1)

        print "CHECK 1 OK:     " + str(expectedArduinoDigOutPinBValue) + "==" + \
                str(arduinoDigOutPinBValue) + " => " + \
                str(checkEq1)

            
def main():
        
    print "Starting????"
    
    
    seasim_set_arduino_code("./libarduino-code.so")
    seasim_initialise();
    seasim_disable_streamed_output()

    print "Register callback for digital "

    seasim_set_callback(newDigOutCallback)
    seasim_set_dig_mode_callback(newDigModeCallback)

    seasim_start();

    tmp = 2 
    setValues(tmp)
    time.sleep(2)

    while True:

        setValues(tmp)
        check_values()

        setValues(tmp+1)
        time.sleep(0.1)
        check_values()
        
        remainder = tmp%10
        if (remainder==0):
            resume();
            time.sleep(1)
        elif (remainder==9):
            pause();
            time.sleep(3)
        tmp = tmp + 1

        # start from 0 at 1023, since we're using tmp+1 above
        if (tmp>=1023):
            tmp=0;
        

if __name__ == "__main__":
    main()

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
arduinoDigOutPinA = 1
arduinoDigOutPinB = 3
arduinoDigInPin   = 2

sim_pause=0

arduinoDigOutPinAValue = 0 
arduinoDigOutPinBValue = 0 

expectedArduinoDigOutPinAValue = 0 
expectedArduinoDigOutPinBValue = 0 

arduinoAnaOutPin              = 3
arduinoAnaInPin               = 4 
arduinoAnaOutPinValue         = 0 
expectedArduinoAnaOutPinValue = 0 


checkCounter = 0 

def newDigModeCallback(pin, mode):
    print "py:dmode" + str(pin) + ":" + str(mode) + "   callbacked Arduino dig mode   "

def newAnaOutCallback(pin, val):
    global arduinoAnaOutPin
    global arduinoAnaOutPinValue
    global expectedArduinoAnaOutPinValue

#    print "py:apin" + str(pin) + ":" + str(val) + "   callbacked Arduino ana pin   "

    if (pin==arduinoAnaOutPin):
        arduinoAnaOutPinValue = val
    else:
        print "py:apin" + str(pin) + ":" + str(val) + "   callbacked Arduino ana pin   "

def newDigOutCallback(pin, val):
    global arduinoDigOutPinBValue
    global arduinoDigOutPinA
    global arduinoDigOutPinB
#    print "pyc:" + str(pin) + ":" + str(val) + "   callbacked Arduino dig out   "
    if (pin==arduinoDigOutPinA):
        arduinoDigOutPinAValue = val
    elif (pin==arduinoDigOutPinB):
        arduinoDigOutPinBValue = val
    
    
def setValues(value):
    global expectedArduinoDigOutPinBValue
    global expectedArduinoAnaOutPinValue
    expectedArduinoDigOutPinBValue = value%2
    expectedArduinoAnaOutPinValue  = value
#    print "Write Analog value(" + str(arduinoAnaInPin) + ", " + str(expectedArduinoAnaOutPinValue) + ")"
    seasim_set_dig_input(arduinoDigInPin,expectedArduinoDigOutPinBValue)
    seasim_set_ana_input(arduinoAnaInPin,expectedArduinoAnaOutPinValue)
    time.sleep(0.2)



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
    global expectedArduinoAnaOutPinValue
    global arduinoAnaOutPinValue

    if (sim_pause==0):
        checkCounter = checkCounter + 1
        checkEq1 = (expectedArduinoDigOutPinBValue==arduinoDigOutPinBValue)
        checkEq2 = (expectedArduinoAnaOutPinValue==arduinoAnaOutPinValue)
        if (checkEq1==False):
            print "CHECK 1 Failed:     " + str(expectedArduinoDigOutPinBValue) + "==" + \
                str(arduinoDigOutPinBValue) + " => " + \
                str(checkEq1)
            sys.exit(1)
        if (checkEq2==False):
            print "CHECK 2 Failed:     " + str(expectedArduinoAnaOutPinValue) + "==" + \
                str(arduinoAnaOutPinValue) + " => " + \
                str(checkEq2)
            sys.exit(1)
        print "check " + str(checkCounter) + ": OK   [" + \
                str(arduinoDigOutPinBValue) + "," + \
                str(arduinoAnaOutPinValue) + "]" 

            
def main():
        
    print "Starting????"
    
    
    seasim_set_arduino_code("./libarduino-code.so")
    seasim_initialise();
    seasim_disable_streamed_output()
    print "Register callback for digital "

    seasim_set_dig_callback(newDigOutCallback)
    seasim_set_dig_mode_callback(newDigModeCallback)
    seasim_set_ana_callback(newAnaOutCallback)

    seasim_start();

    tmp = 2 
    setValues(tmp)
    time.sleep(2)
    while True:

        setValues(tmp)
        check_values()

        setValues(tmp+1)
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

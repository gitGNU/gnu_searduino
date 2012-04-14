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
from threading import BoundedSemaphore
import argparse
import time
import sys
from gi.repository import Gtk
from gi.repository import Gdk
#from gi.repository import Glib
from gi.repository import GObject
import os

semaphore = BoundedSemaphore(1)

SEARDUINO_PIN_TYPE_NONE    = 0
SEARDUINO_PIN_TYPE_DIGITAL = 1
SEARDUINO_PIN_TYPE_ANALOG  = 2
SEARDUINO_PIN_TYPE_PWM     = 3
SEARDUINO_PIN_TYPE_END     = 4

SEARDUINO_LOG_LEVEL_NONE    = 0 
SEARDUINO_LOG_LEVEL_INFO    = 1
SEARDUINO_LOG_LEVEL_WARNING = 2
SEARDUINO_LOG_LEVEL_ERROR   = 3

SEARDUINO_LOG_SERIAL   = 10

currentLogLevel = SEARDUINO_LOG_LEVEL_INFO


typeLabels = [None]*(SEARDUINO_PIN_TYPE_END+1)

typeLabels[SEARDUINO_PIN_TYPE_NONE]    = "None"
typeLabels[SEARDUINO_PIN_TYPE_DIGITAL] = "Digital"
typeLabels[SEARDUINO_PIN_TYPE_ANALOG]  = "Analog"
typeLabels[SEARDUINO_PIN_TYPE_PWM]     = "PWM"
typeLabels[SEARDUINO_PIN_TYPE_END]     = "Unknown"


#
# searduino
#

paused = 0 

size = 16

redColor = Gdk.RGBA()
redColor.red=1.0
redColor.green=0.0
redColor.blue=0.5
redColor.alpha=0.7
#gdk_color_parse ("red");
#redColor = Gdk.Color("red")
#redColor = Gdk.color_parse("red")

def getSem():
#    print "Get semaphore"
#    Gdk.threads_enter()
    semaphore.acquire()        

def relSem():
    semaphore.release()        
#    Gdk.threads_leave()
#    print "Rel semaphore"

def pardonPause():
    seasim_pause();
    global pause 
    pause = 1

def pardonResume():
    seasim_resume();
    global pause 
    pause = 0


class pauseButton(Gtk.HBox):
    def __init__(self, parent):
        Gtk.HBox.__init__(self)
        self.par = parent
    
        self.label = Gtk.Label("Pause")
        self.label.set_width_chars(10);
        self.pin = Gtk.ToggleButton()
        self.pin.set_active(True)
        
        self.pack_start(self.label, False, True, 0)
        self.pack_start(self.pin, False, True, 0)

        self.pin.connect("clicked", self.on_pin_toggled, "1")

    def on_pin_toggled(self, widget, name):
        if self.pin.get_active():
            pardonResume()
            print "pause"
            self.label.set_text("Pause  ")
        else:
            pardonPause()
            self.label.set_text("Resume ")
        

class SpinButtonWindow(Gtk.Box):
    
    def __init__(self, parent):
        Gtk.Box.__init__(self)
        self.set_border_width(10)
        
        hbox = Gtk.Box(spacing=10)
        self.add(hbox)
        
        adjustment = Gtk.Adjustment(0, 0, 10000, 1, 100, 0)
        self.spinbutton = Gtk.SpinButton()
        self.spinbutton.set_adjustment(adjustment)
        self.spinbutton.set_numeric(True)
        self.spinbutton.set_value(seasim_get_Write_timelimit())
        self.increment=0
        self.setIncrement()
        self.spinbutton.connect("value-changed", self.on_update)
        
        lab = Gtk.Label("Update limit (msec)")

        hbox.pack_start(lab, False, False, 0)
        hbox.pack_start(self.spinbutton, False, False, 0)
        
    def setIncrement(self):
        cur_value = int(self.spinbutton.get_value_as_int())
        if (cur_value>5000):
            self.increment = 500
        if (cur_value>1000):
            self.increment = 200
        elif (cur_value>500):
            self.increment = 100
        elif (cur_value>200):
            self.increment = 50
        elif (cur_value>120):
            self.increment = 20
        self.spinbutton.set_increments(self.increment, 100)
        

    def on_update(self, disc):
        self.setIncrement()

#        print "===========================================  " +         str(self.spinbutton.get_value_as_int())
        seasim_set_Write_timelimit(int(self.spinbutton.get_value_as_int()))
#        print "======= set to: " + str(searduino_get_digitalWrite_timelimit())


class Pin(Gtk.Widget):

    def __init__(self, parent, pin_type, pin_nr, pin_mode):
        Gtk.Widget.__init__(self)
        self.par = parent
        self.pin_type = pin_type
        self.pin_nr   = pin_nr
        self.pin_mode = pin_mode
        self.prev_pin_type = SEARDUINO_PIN_TYPE_NONE;
        
        # Label 
        self.pinLabel = Gtk.Label(str(pin_nr))
        self.pinLabel.set_width_chars(2);

        # Type
        self.type_text = Gtk.Label("")
        if (pin_type==SEARDUINO_PIN_TYPE_NONE):
            self.type_text.set_text("   None  ")
        elif (pin_type==SEARDUINO_PIN_TYPE_DIGITAL):
            self.type_text.set_text(" Digital ")
        elif (pin_type==SEARDUINO_PIN_TYPE_ANALOG):
            self.type_text.set_text("  Analog ")
        elif (pin_type==SEARDUINO_PIN_TYPE_PWM):
            self.type_text.set_text("   PWM   ")
        elif (pin_type==SEARDUINO_PIN_TYPE_END):
            self.type_text.set_text("   LAST  ")

        # Mode 
        self.mode = Gtk.Label("Undef")
        self.mode.set_width_chars(7);

        # Input  
        #   digital
        self.input = Gtk.ToggleButton()
        self.input.connect("clicked", self.on_dig_toggled, "1")
        #   analog
        self.adjustment = Gtk.Adjustment(0, 0, 1023, 1, 100, 0)
        self.spinbutton = Gtk.SpinButton()
        self.spinbutton.set_adjustment(self.adjustment)
        self.spinbutton.set_numeric(True)
        self.spinbutton.connect("value-changed", self.on_update)

        
        # Output
        self.output_label = Gtk.Label("NaN")

    def updateGenericPin(self, val, pin_type):

        getSem()
        # Handle first update (set prev_pin_typ)
        if (self.pin_type==SEARDUINO_PIN_TYPE_NONE):
            self.prev_pin_type = pin_type

        if (pin_type==self.prev_pin_type):
            self.output_label.set_text(str(val))
        else:
            self.type_text.set_text(typeLabels[pin_type])
            self.prev_pin_type = pin_type
            self.output_label.set_text(str(val))

        self.prev_pin_type = pin_type
        relSem()

    def updateGenericMode(self, pin, mode):
        print "updateGenericMode( " + str(pin) + " , " + str(mode) + ")"
        getSem()
        print "===> setMode"
        if (mode==1):
            self.mode.set_text("OUTPUT")
        else:
            self.mode.set_text("INPUT")
            self.output_label.set_text("")
        print "<=== setMode"
        relSem()


    def on_dig_toggled(self, widget, name):
        val = 0
        if self.input.get_active():
            val = 1
            
        print "Pin toggle " + str(self.pin_nr) + ", " + str(val) + ", " + str(self.pin_type)
        seasim_set_input(self.pin_nr, 
                         val, 
                         self.pin_type )
        
    def on_update(self,disc):
        seasim_set_input(self.pin_nr,
                         self.spinbutton.get_value_as_int(), 
                         self.pin_type)




class MyWindow(Gtk.Window):

    def updateGUI(self):
#        print "updateGUI()  <-- " + str(paused)
        if (paused):
            print "no GUI update"
        else:
            print "Updating GUI manually (not anymore)"
#            self.updateAllOut()
                
        return True


    def updateModes(self):
#        print "  --------------------------------------------- UPDATEMODES ============================================================"
        if (paused):
            print "no GUI update"
        else:
            for i in range(1,size-1):
                mode = seasim_get_pin_mode(i)
                print "updateModes (" + str(i)+ ", " + str(mode) + ")"
                self.pinUpdateMode(i,mode);
                
        self.sendInputPins()        
        return True
        
    def sendInputPins(self):
        if (paused):
            print "no GUI update"
        else:
 #           print "  --------------------------------------------- SIN"
            for i in range(1,size-1):
  #              print "  --------------------------------------------- SIN " + str(i)
                if (seasim_get_pin_mode(i)==0):
                    print "updateModes:"
                    getSem()        
                    value = self.digs[i].getVal()
                    relSem()
#                    print "                                                                         WILL SEND: " + str(value) + "  from " + str(i)
                    seasim_set_input(i,
                                     value, 0)
                
        return True
        
    def __init__(self, size):
#        global size
        
        self.digs = [None]*size
        self.anas = [None]*size

        Gtk.Window.__init__(self, title="Pardon  ( " + seasim_get_searduino_name() + " - " + seasim_get_searduino_version() + " )")

        self.innerbox = Gtk.HBox(spacing=6)

        pinTable = Gtk.Table(10, 10, False)

        pause = pauseButton(self)
        pause2 = pauseButton(self)
        spin = SpinButtonWindow(self)

        self.box = Gtk.VBox(spacing=6)
        self.add(self.box)

        # Serial I/O
        self.serialbox=Gtk.VBox(spacing=6)
        self.seriallabel = Gtk.Label("Serial I/O")
        self.serialbox.pack_start(self.seriallabel,    False, True, 0)
        self.serialbox.pack_start(pause,    False, True, 0)
        self.serialbox.pack_start(spin,    False, True, 0)
        self.serialio = Gtk.TextView()
        self.serialscroll = Gtk.ScrolledWindow()
        self.serialscroll.set_hexpand(True)
        self.serialscroll.set_vexpand(True)
        self.serialtextbuffer = self.serialio.get_buffer()
        self.serialtextbuffer.set_text("First thing..")
        self.serialio.set_cursor_visible(True)
        self.serialio.set_editable(True)
        self.serialscroll.add(self.serialio)
        self.serialbox.pack_start(self.serialscroll,    False, True, 0)


        # EXTRAS
        self.extrasbox=Gtk.VBox(spacing=6)

        self.extraslabel = Gtk.Label("General")
        self.extrasbox.pack_start(self.extraslabel,    False, True, 0)
        self.extrasbox.pack_start(pause,    False, True, 0)
        self.extrasbox.pack_start(spin,    False, True, 0)

        # log window
        self.log = Gtk.TextView()
        self.scroll = Gtk.ScrolledWindow()
        self.scroll.set_hexpand(True)
        self.scroll.set_vexpand(True)
        self.textbuffer = self.log.get_buffer()
        self.textbuffer.set_text("First thing..")
        self.log.set_cursor_visible(True)
        self.log.set_editable(True)
        self.scroll.add(self.log)
        self.extrasbox.pack_start(self.scroll,    False, True, 0)

        self.innerbox.pack_start(pinTable, False, True, 0)
        self.innerbox.pack_start(self.extrasbox, False, True, 0)
        self.innerbox.pack_start(self.serialbox, False, True, 0)
        
        self.bottomlabel = Gtk.Label("Pardon - a simulator frontend. Pardon is part of the " + seasim_get_searduino_name() + "  project")
        self.box.pack_start(self.innerbox,    False, True, 0)
        self.box.pack_start(self.bottomlabel,    False, True, 0)


        pinTable.attach(Gtk.Label("Type"),    1, 2, 1, 2)
        pinTable.attach(Gtk.Label("Pin"),     2, 3, 1, 2)
        pinTable.attach(Gtk.Label("Mode"),    3, 4, 1, 2)
        pinTable.attach(Gtk.Label("Dig in"),  4, 5, 1, 2)
        pinTable.attach(Gtk.Label("Ana in"),  5, 6, 1, 2)
        pinTable.attach(Gtk.Label("Output"),  6, 7, 1, 2)

        for i in range(1,(size-1)):
#            print "Update on pin: " + str(i)
#            self.digs[i] = digitalPin(self,i)
#            digTable.attach(self.digs[i], 0, 1, i, i+1)
#            self.pinUpdate(i,"on")

#            wid = Pin(self,i%5, i, i)
            wid = Pin(self,1, i, i)
            self.anas[i] = wid

            pinTable.attach(wid.type_text,    1, 2, i+1, i+2)
            pinTable.attach(wid.pinLabel,     2, 3, i+1, i+2)
            pinTable.attach(wid.mode,         3, 4, i+1, i+2)
            pinTable.attach(wid.input,        4, 5, i+1, i+2)
            pinTable.attach(wid.spinbutton,   5, 6, i+1, i+2)
            pinTable.attach(wid.output_label, 6, 7, i+1, i+2)

            
        print "init...1"
        self.updateAllOut()
        print "init..."
#        self._positiontimeoutid = GObject.timeout_add(2000, self.updateModes)
        print "init..."
        self._positiontimeoutid = GObject.timeout_add(5000, self.updateGUI)
        print "init..."
        self.updateGUI()
        print "init..."

    def updateDigOutPin(self,pin, val):
#        print "---> get sem #####################################################################     " + str(pin) + " " + str(val)
        print "updateDigOutPin "+ str(pin) + " " + str(val)
        getSem()
#        print "self.digs[" + str(pin) + "].set_text(" + str(val)+ ")"
        self.digs[pin].setVal(val)
        relSem()
#        print "<--- rel sem #####################################################################"

    def updateDigMode(self, pin, mode):
        print "updateDigOutMode( " + str(pin) + " , " + str(mode) + ")"
        getSem()
        self.digs[pin].setMode(mode)
        relSem()
#        print "<--- rel sem #####################################################################"

    def updateAnaOutPin(self,pin, val):
        #        print "---> get sem #####################################################################     " + str(pin) + " " + str(val)
        print "updateAnaOutPin"
        getSem()
#        print "self.digs[" + str(pin) + "].set_text(" + str(val)+ ")"
        self.anas[pin].setVal(val)
        relSem()
#        print "<--- rel sem #####################################################################"

    def updatePin(self, pin, val, pin_type):
#        print "---> get sem #####################################################################     " + str(pin) + " " + str(val)
        print "updatePin(...)"
        getSem()
        print "updatePin(...) 2"
        print "updatePin(...) 3 : " + str(pin) + " " + str(val) + "  type:" + str(pin_type)
        self.anas[pin].updateGenericPin(val, pin_type)
        print "updatePin(...) 4"
        relSem()
        print "updatePin(...) 5"
#        print "<--- rel sem #####################################################################"

    def updateAllOut(self):
        print "will update late"
#        for i in range(1,(size-1)):
#            self.digs[i].setValCond()


    def pinUpdateMode(self, pin, mode):
#        print "digs at  " + str(pin) + " : " + str(self.digs[pin])
        print "pinUpdateMode"
        getSem()
        self.digs[pin].setMode(mode)
        relSem()

    def pinUpdate(self, nr, val_str):
        val=0
#        print "CHECK pin set in GUI: "+str(nr)+ ": " + str(val)
        if (val_str=="on"):
            val=1
        seasim_set_input(nr,val, 0)            
#        self.updateAllOut()



class FileChooserWindow(Gtk.Window):

    def __init__(self):
        dialog = Gtk.FileChooserDialog("Choose a file to load", self,
            Gtk.FileChooserAction.OPEN,
            (Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL,
             Gtk.STOCK_OPEN, Gtk.ResponseType.OK))

        self.add_filters(dialog)

        response = dialog.run()
        if response == Gtk.ResponseType.OK:
            print "Open clicked"
            print "File selected: " + dialog.get_filename()
        elif response == Gtk.ResponseType.CANCEL:
            print "Cancel clicked"

        dialog.destroy()

    def add_filters(self, dialog):
        filter_text = Gtk.FileFilter()
        filter_text.set_name("Text files")
        filter_text.add_mime_type("text/plain")
        dialog.add_filter(filter_text)

        filter_py = Gtk.FileFilter()
        filter_py.set_name("Python files")
        filter_py.add_mime_type("text/x-python")
        dialog.add_filter(filter_py)

        filter_any = Gtk.FileFilter()
        filter_any.set_name("Any files")
        filter_any.add_pattern("*")
        dialog.add_filter(filter_any)

    def on_folder_clicked(self, widget):
        dialog = Gtk.FileChooserDialog("Please choose a folder", self,
            Gtk.FileChooserAction.SELECT_FOLDER,
            (Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL,
             "Select", Gtk.ResponseType.OK))
        dialog.set_default_size(800, 400)

        response = dialog.run()
        if response == Gtk.ResponseType.OK:
            print "Select clicked"
            print "Folder selected: " + dialog.get_filename()
        elif response == Gtk.ResponseType.CANCEL:
            print "Cancel clicked"

        dialog.destroy()


def newDigOutCallback(pin, val):
    if (pin>size):
        print "Pin " + str(pin) + " is bigger than highest pin in simulator (" + str(size) + ". Ignoring pin mode update"
    else:
        global win
        win.updateDigOutPin(pin,val)

def newOutCallback(pin, val, pin_type):
    if (pin>size):
        print "Pin " + str(pin) + " is bigger than highest pin in simulator (" + str(size) + ". Ignoring pin update"
    else:
        global win
        win.anas[pin].updateGenericPin(val, pin_type)

def newLogCallback(level, text):
    getSem()
    print "---------->"
#    print "  LOG:  text  " + text
#    print "  LOG:  level " + str(level)
#    print "  LOG:  curr  " + str(currentLogLevel)
    if ( level == 10 ):
        print " =======================  SERIAL "  + text
        try:
            time.sleep(0.001)
            iter1 = win.serialtextbuffer.get_end_iter()
#            print "iter2 " + str(iter1.get_offset())
            win.serialtextbuffer.insert(iter1, text)
#            win.serialtextbuffer.insert(iter1, text)
 #           win.serialtestbuffer.append(text)
#            print "iter2 " + str(iter1.get_offset())
#            win.serialio.scroll_to_iter(iter1 , 0.0 , False, 0.0, 0.0)
#            win.serialtextbuffer.scroll_to_end()
            time.sleep(0.001)
        except Error:
            print "Error caught"
            time.sleep(10)
                    
    elif ( currentLogLevel <= level ):
        print "********************************** WILL DO " + text
        try:
            time.sleep(0.001)
            iter2 = win.textbuffer.get_end_iter()
            print "mark2 " + str(iter2.get_offset())
            win.textbuffer.insert(iter2, text)
            time.sleep(0.001)
        except Error:
            print "Error caught"
            time.sleep(10)
    else:
        print "********************************** DISCARD" + text
    print "<----------"
    relSem()

def newAnaOutCallback(pin, val):
#    print ""
#    print "==================== in Py:  new ANALOG out: " + str(pin) + " = " + str(val)
#    print ""
    if (pin>size):
        print "Pin " + str(pin) + " is bigger than highest pin in simulator (" + str(size) + ". Ignoring update"
    else:
        global win
        self.anas[pin].setVal(val)

def newDigModeCallback(pin, mode):
#    print ""
    print ">==================== in Py:  new Dig Mode: " + str(pin) + " = " + str(mode)
    if (pin>size):
        print "Pin " + str(pin) + " is bigger than highest pin in simulator (" + str(size) + ". Ignoring update"
    else:
        global win
        win.anas[pin].updateGenericMode(pin,mode)
    print " done with new mode"
    print "<==================== in Py:  new Dig Mode: " + str(pin) + " = " + str(mode)



#file_win = FileChooserWindow()
#file_win.show_all()
def getArduinocodeLibrary():

    dialog = Gtk.FileChooserDialog("Please choose a file", None,
                                   Gtk.FileChooserAction.OPEN,
                                   (Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL,
                                    Gtk.STOCK_OPEN, Gtk.ResponseType.OK))
    
#self.add_filters(dialog)
    
    response = dialog.run()
    if response == Gtk.ResponseType.OK:
        print "Open clicked"
        print "File selected: " + dialog.get_filename()
    elif response == Gtk.ResponseType.CANCEL:
        print "Cancel clicked"
    
    file = dialog.get_filename()
    dialog.destroy()
    return file
    

print "Main - will parse"

parser = argparse.ArgumentParser(prog='Pardon (Arduino Simulator " + seasim_get_searduino_version() + ")')
parser.add_argument('--arduino-code', nargs=1, action="store", dest="ac",   help='Arduino code to test')
parser.add_argument('--i2c-code',     nargs=1, action="store", dest="ic",   help='I2C code for device')
parser.add_argument('--pins',         nargs=1, action="store", dest="pins", help='Number of pins in GUI')
parser.add_argument('--version',      action='version', version=seasim_get_searduino_version())
args = parser.parse_args()


print "continue ..."

ard_code=""
i2c_code=""
if args.ac != None:
    print "AC code"
    ard_code=args.ac[0]
else:
    print "Reading via fc"
    ard_code=getArduinocodeLibrary()

if args.ic != None:
    i2c_code=args.ic[0]
    print "I2C   FOUND" + i2c_code

if args.pins != None:
    print "Setting pins to: " + args.pins[0]
    global size
    size = int(args.pins[0])+2

print "ARD CODE:" + ard_code

if os.path.isdir(ard_code) == True:
    print "Dir"
    command = "arduino-ex2c --shlib  --build " + ard_code
    print "EXEC:   " + command
    os.system(command)
    code_dir = os.path.basename(ard_code)

    path = ard_code.rsplit(os.path.sep)[1:]
    
    for dir in path:
        if (dir!=""):
            code_dir=dir


    dirs = os.listdir( code_dir )
    for file in dirs:
        print file    
        file_suff = os.path.splitext(file)[1]
        if (file_suff == ".so"):
            ard_code = "./" + code_dir + "/" + file
            print "shlib: " + ard_code
            break
        else:
            print "... " + file
else:
    file_suff = os.path.splitext(ard_code)[1]
    print "ARD CODE: " + file_suff
    if (file_suff == ".ino"):
        print "Arduino example"
    else:
        print "shlib: " + ard_code
        
print "ard:  " + ard_code
print "i2c:  " + i2c_code

if i2c_code != "":
    seasim_add_i2c_device(50, i2c_code)

#time.sleep(1)
#time.sleep(10)
seasim_set_arduino_code(ard_code)
seasim_initialise();
seasim_set_Write_timelimit(0)
time.sleep(1)
win = MyWindow(size)
win.connect("delete-event", Gtk.main_quit)
#parser.print_help()

       
#/*
#seasim_set_dig_callback(newDigOutCallback)
#seasim_set_ana_callback(newAnaOutCallback)
#*/
seasim_set_callback(newOutCallback)
seasim_set_dig_mode_callback(newDigModeCallback)
seasim_set_log_callback(newLogCallback)
win.show_all()

#time.sleep(2)
seasim_start();


#sys.exit(1)


#GObject.idle_add(newDigOutCallback)
#GObject.idle_add(newAnaOutCallback)
GObject.idle_add(newOutCallback)
GObject.idle_add(newDigModeCallback)
GObject.idle_add(newLogCallback)

GObject.threads_init()
Gdk.threads_init()
#Gtk.threads_init()

  #GObject.threads_init()
  #mainloop = GObject.MainLoop()
  #mainloop.run()

Gtk.main()

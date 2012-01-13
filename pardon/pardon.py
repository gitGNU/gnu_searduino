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
from gi.repository import Gtk
from gi.repository import Gdk
from gi.repository import GObject

#
# searduino
#

class inPin(Gtk.HBox):

    def __init__(self, parent, nr):
        Gtk.HBox.__init__(self)
        self.par = parent
        self.myNr = nr
        

        label = Gtk.Label("Digital in " + str(nr) + "   ")
        self.pin = Gtk.ToggleButton()
        self.pin.set_active(True)
        
        self.pack_start(label, False, True, 0)
        self.pack_start(self.pin, False, True, 0)

        self.pin.connect("clicked", self.on_pin_toggled, "1")

    def on_pin_toggled(self, widget, name):
#        print "GUI 1 toggle"
        if self.pin.get_active():
#            py_ext_set_input(1,1)
            state = "on"
        else:
            state = "off"
#            py_ext_set_input(1,0)
#        print "state " + state
        self.par.pinUpdate(self.myNr,state)


class MyWindow(Gtk.Window):

    size = 10 
    ins  = [None]*size
    outs = [None]*size

    def updateGUI(self):
        print "Updating GUI manually"
        self.updateAllOut()
        return True
        
    def __init__(self):
        Gtk.Window.__init__(self, title="Searduino Simulator")

        topTable = Gtk.Table(2, 2, False)
        topTable.attach(Gtk.Label("Digital"),0,1,0,1)
        topTable.attach(Gtk.Label("Analogue"),1,2,0,1)
        
        ioTable = Gtk.Table(1, 2, True)
        topTable.attach(ioTable, 0,1,1,2)
#        topTable.attach(Gtk.Label("ett"),0,1,1,2)
        topTable.attach(Gtk.Label("Analogue table soom"),1,2,1,2)

        outTable = Gtk.Table(10, 2, True)
        inTable = Gtk.Table(10, 1, True)

        ioTable.attach(outTable, 0, 1, 0, 1)
        ioTable.attach(inTable, 1, 2, 0, 1)
        topTable.attach(outTable, 0, 1, 0, 1)
        topTable.attach(inTable, 1, 2, 0, 1)

        self.box = Gtk.Box(spacing=6)
        self.add(self.box)


#        self.box.pack_start(ioTable, True, True, 0)
        self.box.pack_start(topTable, False, True, 0)

        for i in range(1,(self.size-1)):
            vb = Gtk.HBox()
            vbl = Gtk.Label("Digital out " + str(i) +"  ")
            vb.pack_start(Gtk.Label("Digital out " + str(i) +"  "), False, True, 0)
            vb.pack_start(vbl, False, True, 0)
            vb.modify_bg(Gtk.StateType.NORMAL, Gdk.Color(65535,1212,1212))
            vb.modify_bg(Gtk.StateType.ACTIVE, Gdk.Color(5535,5535,5535))
            self.outs[i] = vbl
            outTable.attach(vb, 0, 1, i, i+1)

        for i in range(1,(self.size-1)):
#            print "Adding ... " + str(i)
            self.ins[i] = inPin(self,i)
            inTable.attach(self.ins[i], 0, 1, i, i+1)
            self.pinUpdate(i,"on")

        self.updateAllOut()
        self._positiontimeoutid = GObject.timeout_add(10000, self.updateGUI)



    #t = monitorThread()
    #t.start()

    def updateOutPin(self,pin, val):
        self.outs[pin].set_text(str(val))

    def updateAllOut(self):
        for i in range(1,(self.size-1)):
            self.updateOutPin(i,py_digitalRead(i))
#            val = py_digitalRead(i)
#            self.outs[i].set_text(str(val))


    def pinUpdate(self, nr, val_str):
        val=0
#        print "CHECK pin set in GUI: "+str(nr)+ ": " + str(val)
        if (val_str=="on"):
            val=1
        py_ext_set_input(nr,val)            
        self.updateAllOut()




def newDigOutCallback(pin, val):
#    print "==================== in Py:  new dig out: " + str(pin) + " = " + str(val)
    win.updateOutPin(pin,val)


my_set_callback(newDigOutCallback)

win = MyWindow()
win.connect("delete-event", Gtk.main_quit)
win.show_all()


Gtk.main()

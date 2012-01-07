# -*- coding: utf-8 -*-

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


import sys
import time


from threading import Thread

from PySide import QtCore
from PySide import QtGui
from PySide import QtDeclarative

from PyQt4.QtCore import QDateTime, QObject, QUrl, pyqtSignal

class DigIn(QtCore.QObject):

    @QtCore.Slot(str,str)
    def newIO(self, pin, val):
        print 'pin:' + pin + ":" + val
        sys.stdout.flush()


    @QtCore.Slot(str)
    def printer(self,str):
        print "pin update"

class DigOut(QtCore.QObject):

    changed = QtCore.Signal(str,str)

    def test(self):
        print "Tester..."
    
    def updatePin(self,pin,val):
        print "Will emit signal " + str(val) 
        self.changed.emit(pin,val)


def getData():
    ctr=0;
    print ("Getting data ...")
    while (ctr<10):
        print "Getting data ..." + str(ctr)
        line=raw_input()
        ctr=ctr+1
        val = str(ctr%2)
        print "     got ...'" + line + "'  => " + val
        dig_out.updatePin("2",val)
        time.sleep(0)
t = Thread(target=getData, args=())
t.start()


dig_out = DigOut()
dig_out.test

app = QtGui.QApplication(sys.argv)

view = QtDeclarative.QDeclarativeView()
view.setResizeMode(QtDeclarative.QDeclarativeView.SizeRootObjectToView)

dig_in = DigIn()
ctx = view.rootContext()
ctx.setContextProperty("dig_in", dig_in)

view.setSource('uno.qml')
view.show()

rootObject = view.rootObject()
#rootObject.ioEvent.connect(dig_in.newIO)
#QtCore.QObject.connect (dig_out, QtCore.SIGNAL("updatePin"), dig_out.updatePin)
dig_out.changed.connect(rootObject.updatePinVal)


sys.exit(app.exec_())


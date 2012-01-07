/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2011, 2012 Henrik Sandklef 
 *                                                                   
 * This program is free software; you can redistribute it and/or     
 * modify it under the terms of the GNU General Public License       
 * as published by the Free Software Foundation; either version 3    
 * of the License, or any later version.                             
 *                                                                   
 *                                                                   
 * This program is distributed in the hope that it will be useful,   
 * but WITHOUT ANY WARRANTY; without even the implied warranty of    
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     
 * GNU General Public License for more details.                      
 *                                                                   
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software       
 * Foundation, Inc., 51 Franklin Street, Boston,            
 * MA  02110-1301, USA.                                              
 ****/

import QtQuick 1.0

Rectangle {
     id: page
     width: 500; height: 210
     color: "lightgray"

     property string ledcolor ;

     Image {
         source: "pics/uno.jpg"
         anchors.centerIn: parent
     }

     function updateMessage(pin, val) {
     	 dig_in.newIO(pin,val);
     }

     function updatePinVal(pin, val) {

          if (val=="0") { ledcolor = "black";}
          else if (val=="1") { ledcolor = "red" ;}
	  else { ledcolor = "pink" ;}

	  outLabel.text = ledcolor

       	  switch (pin) {
             case "1":
	       pin1.color = ledcolor
               break;
             case "2":
	       pin2.color = ledcolor
               break;
             case "3":
	       pin3.color = ledcolor
               break;
             case "4":
	       pin4.color = ledcolor
               break;
             default:
               break;
          }
     }
 

    Column{
      x:0
      spacing: 2

     Text {
         id: outLabel
         text: "Output"
         y: 30
         font.pointSize: 24; font.bold: true
      }

      DigOut { id: pin1; nr: 1 ; led: "default";} 
      DigOut { id: pin2; nr: 2 } 
      DigOut { id: pin3; nr: 3 } 
      DigOut { id: pin4; nr: 4 } 
      DigOut { id: pin5; nr: 5 } 
      DigOut { id: pin6; nr: 6 } 
      DigOut { id: pin7; nr: 7 } 
    }

    Column{
      x:400
      spacing: 2

     Text {
         id: inLabel
         text: "Input"
         y: 30
         font.pointSize: 24; font.bold: true
      }

      DigIn { nr: 1 ; }
      DigIn { nr: 2 ; }
      DigIn { nr: 3 ; }
      DigIn { nr: 4 ; }
      DigIn { nr: 8 ; }

    }
 }
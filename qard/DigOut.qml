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

Item {
     id: container
     property alias name:   ledName.text
     property alias color:  ledArea.color
     property alias led: container.ledState;

     width: 80; 
     height: 20

     property int nr ; 
     property string ledState ; 

     Rectangle {
         id: ledInfo
         color: "black"
         border.color: "gray"
         anchors.fill: parent

     Text {
         id: ledName
         color: "lightgray"
         text: "Pin " + nr
     }

     Rectangle {
         id: ledArea
         x: 60
         y: 4
         width: 20; height: 12
         color: "black"
         border.color: "gray"
         border.width: 2
     }
     
     }
 }
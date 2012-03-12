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

/*
 *
 * This code is just a dummy lib to make the linker happy when building
 * the python extension. When using the Python extension you should provide
 * a dynamic library called "arduino_code" to the dynamic linker.
 * 
 *
 */

#include <Arduino.h>
#include "arduino/setup.h"


void setup() {
  pinMode(13,1);
  pinMode(6,1);
  pinMode(7,1);
  pinMode(8,1);
}

int main(void)
{
  searduino_setup();   

  setup();
  
  SEARDUINO_LOOP()
    {
      //      digitalWrite(7,1);
      analogWrite(7,1);
      /* Simulator should not get this extra write, 
       * we should only send on change */
      //digitalWrite(7,0);
      analogWrite(7,120);
      delay(200);
    }
  return 0;
}

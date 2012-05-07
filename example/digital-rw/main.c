/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2012 Henrik Sandklef 
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

#include <Arduino.h>
#include "searduino.h"


void setup() {
  pinMode(A1, OUTPUT);      
}




uint8_t main(void)
{
  uint8_t i ;
  
  init();  

  setup();
  
  SEARDUINO_LOOP()
    {
      //      digitalRead(13)? digitalWrite(13,LOW):digitalWrite(13,HIGH);
      printf ("Analog pin %d is now: %d   setting %d\n", A0, analogRead(A0), A1);
      analogWrite(A1,analogRead(A0));
      delay(500);
    }
}


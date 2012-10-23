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

#include <Arduino.h>
#include "searduino.h"

void setup(void) {
  pinMode(3, OUTPUT);      
  pinMode(7, OUTPUT);      
}


int main(void)
{
  init();   

  setup();

  SEARDUINO_LOOP()
    {
      digitalWrite(3,digitalRead(2));

      if ( digitalRead(4) )
	{
	  DEBUG_INFO(("analogWrite(7..)"));
	  analogWrite(7, 250);
	}
      else if ( digitalRead(6) )
	{
	  DEBUG_INFO(("digitalWrite(7..)"));
	  digitalWrite(7,digitalRead(2));
	}

      delay(500); 
    }
}


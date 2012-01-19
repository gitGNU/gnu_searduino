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


void blink_helper(uint8_t pin, unsigned long indelay)
{
  digitalWrite(pin, HIGH);
  delay(indelay);
  digitalWrite(pin, LOW);
  delay(indelay);
}

void 
blink_stupidly(uint8_t pin)
{
  int i ;
  unsigned long mydelay = 5000;

  for (i=0;i<20;i++)
    {
      blink_helper(pin, mydelay);
      mydelay = mydelay / 2;
    }
  digitalWrite(13, LOW);
  delay(2000);
  
}

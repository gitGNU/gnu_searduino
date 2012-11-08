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

void setup() {
  pinMode(13, OUTPUT);      
}


void blink(uint8_t pin, uint16_t del )
{
  digitalWrite(pin, HIGH);
  delay(del);
  digitalWrite(pin, LOW);
  delay(del);
}

int main(void)
{
  uint8_t i;
  init();  
  setup();

  for (;;)
    {
      blink(13, 2000);
      blink(13, 1000);
      blink(13,  500);
      blink(13,  100);
      blink(13,   50);

      for (i=0;i<25;i++)
	{
	  blink(13,i);
	}
      /* Can't run for ever in make check */
      return 0;
    }
}


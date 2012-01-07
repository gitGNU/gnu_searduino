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

#ifndef INTERVAL
#define INTERVAL 200
#endif
#define FIRST_LED 0
#define LAST_LED 20

void setup() {
  int i ; 
  for (i=FIRST_LED;i<=LAST_LED;i++)
    {
      pinMode(i, OUTPUT);      
    }
}


int main(void)
{
  int i ;
  init();  
  
  pinMode(13, OUTPUT);      
  for (;;)
    {
      digitalWrite(13, HIGH);
      delay(2000);
      digitalWrite(13, LOW);
      delay(200);
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
      delay(200);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(200);

      for (i=0;i<25;i++)
	{
	  digitalWrite(13, HIGH);
	  delay(50);
	  digitalWrite(13, LOW);
	  delay(50);
	}

      /*digitalWrite(13, HIGH);
      delay(200);
      digitalWrite(13, LOW);
      delay(2000);
      */
    }
}

int main2(void)
{
  char i ;
  char j ;
  int interval = 100 ;
  char direction = 1;

  init();  
  setup();
  for (;;)
    {
      digitalWrite(13, 1);
      delay(interval);
      digitalWrite(13, 0);
      delay(interval);
    }
  return 0;
}

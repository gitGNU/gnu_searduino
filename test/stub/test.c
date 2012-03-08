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
#include <stdio.h>

#define FIRST_LED 1
#define LAST_LED  3

void setup() {
  int i ; 
  for (i=FIRST_LED;i<=LAST_LED;i++)
    {
      pinMode(i, OUTPUT);      
    }
}


int 
main(void)
{
  char ctr ;
  unsigned int interval = 200;
  unsigned char tmp=0;

  init();  
  setup();

  ctr = 0 ;
  while (ctr++<10)
    {
      if (tmp) tmp=0 ; else tmp=1;
      
      digitalWrite(1,tmp);
      digitalWrite(2,digitalRead(4)+tmp);
      digitalWrite(3,digitalRead(5)+tmp);
/*       digitalWrite(2,digitalRead(2)); */
/*       printf("\n"); */
      delay(interval*5);
    }
  return 0;
}

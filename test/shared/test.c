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

#define FIRST_OUT 1
#define LAST_OUT  5

#define FIRST_IN 6
#define LAST_IN  10

void setup() {
  int i ; 
  for (i=FIRST_OUT;i<=LAST_OUT;i++)
    {
      pinMode(i, OUTPUT);      
    }
}


int main(void)
{
  char ctr =0;
  unsigned int interval = 100;
  unsigned char tmp=0;
  int i ;

  init();  
  setup();

  while (ctr++<50)
    {
      if (tmp) tmp=0 ; else tmp=1;

      printf ("send on 1 %d     \n", tmp);
      digitalWrite(1,digitalRead(tmp));
      for (i=FIRST_OUT;i<=LAST_OUT;i++)
	{
	  digitalWrite(i,digitalRead(LAST_OUT+i));
	}

      delay(interval);
    }
  printf ("fini...\n");
  return 0;
}

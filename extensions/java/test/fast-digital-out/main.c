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


void
setup()
{
  int i ;
  for (i=0;i<6;i++)
    {
      pinMode(i, OUTPUT);
    }
  pinMode(7, OUTPUT);
  pinMode(11, OUTPUT);
  
  serial_setup();
}

int main(void)
{
  int i = 10;
  int mydelay = 1;
  int ctr;
  init();

  setup();

  /* The following line uses a Saerduino macro 
   * You could use a plain "for (;;)" instead
   */
  ctr=0;
  SEARDUINO_LOOP()
    {
      for (i=1;i<5;i++)
	{
	  digitalWrite(i,ctr%2);
	  delay(mydelay);
	}

      digitalWrite(7,digitalRead(6));

      pinMode(8,digitalRead(6));
      if (digitalRead(6)) digitalWrite(8,ctr%2);

      {
	int val = analogRead(12);
	/* printf ("write to %d: %d\n", 14, val); */
	analogWrite(11, (val/4));
      }

      ctr++;
      if (ctr%100==0) fprintf(stderr, "updates: %d k times\n", ctr/10);
      serial_stuff();
    }
}


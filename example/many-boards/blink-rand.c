/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2013 Henrik Sandklef 
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
#include "random.h"

#define NR_PINS 8
int pins[] = { 13, 12, 11, 10, 9, 8, 7 };

void
setup()
{
  int i;
  for (i=0;i<NR_PINS;i++) 
    {
      pinMode(pins[i], OUTPUT);
    }
}




void 
setpin(int a) 
{
  int i;

  int mask = 0x01;
  for (i=0;i<NR_PINS;i++) 
    {
      int new_val = (a & mask)>>i;
      digitalWrite(pins[i],new_val);
      mask = mask * 2;
      SEARDUINO_DEBUG(("%d ", new_val));
    }
  delay(100);
}

int main(void)
{
  init();
  setup();

  /* The following line uses a Saerduino macro 
   * You could use a plain "for (;;)" instead
   */
  SEARDUINO_LOOP()
    {
      #ifdef SEARDUINO_STUB
      static int ctr = 0;
      //      printf ("Loop nr: %d\n", ctr);
      if (ctr++>100) { exit(0); }
      #endif
      
      setpin(get_random_value(0,255));
    }
}


/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 20123 Henrik Sandklef 
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
  pinMode(13, OUTPUT);
}

int main(void)
{
  //  init();
  //setup();

  /* The following line uses a Saerduino macro 
   * You could use a plain "for (;;)" instead
   */
  SEARDUINO_LOOP()
    {
      #ifdef SEARDUINO_STUB
      static int ctr = 0;
      printf ("Loop nr: %d\n", ctr);
      if (ctr++>10) { exit(0); }
      #endif

      digitalWrite(13,1);
      delay(100);
      digitalWrite(13,0);
      delay(100);
    }

}


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
#include "setup.h"

void setup(void) {
  pinMode(13, OUTPUT);      
}

int main(void)
{
  int i =0;
  int j ;

  init();   

  setup();
  
  SEARDUINO_LOOP()
    {
      digitalWrite(13,i++%2);
      i++;
      delay(300); 

      printf ("i:%d\n", i);
      /* We can't test "forever" */
      if (i>30) { return 0; }
    }
  return 0;
}


/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2012 Henrik Sandklef 
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

void setup()
{
  searduino_set_log_level(3);
  pinMode(13,OUTPUT);
}

int main(void)
{
  int i = 0 ;
  init();

  setup();

  SEARDUINO_LOOP()
    {
      searduino_log((SEARDUINO_LOG_ERROR, "Writing %d to pin %d\n", i%2, 13 ));
      digitalWrite(13,i%2);
      i++;
      delay(100);
    }
}

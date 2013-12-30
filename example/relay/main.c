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

#define RELAY_PIN 7
#define INPUT_PIN A0

void setup(void)
{
  pinMode(RELAY_PIN, OUTPUT);
}

int readInput()
{
#ifdef FAKE_CODE
  static unsigned int fake;

  fake = fake + 100;
  if (fake>1000)
    {fake=0;}
  //  printf ("return: %d\n", fake);
  return fake;
#else
  return analogRead(INPUT_PIN);
#endif
}

int validateInput(int in)
{
  if (in>700)
    { 
      return HIGH ;
    }
  return LOW;
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
      if (validateInput(readInput(INPUT_PIN)))
	{
	  digitalWrite(RELAY_PIN,HIGH);
	}
      else
	{
	  digitalWrite(RELAY_PIN,LOW);
	}
      delay(500);
    }
}




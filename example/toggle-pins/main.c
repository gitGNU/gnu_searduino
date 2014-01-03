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

#define SHORT_DELAY() delay(200)
#define LONG_DELAY()  delay(500)

void setup()
{
  ;
}

void do_all(int pin)
{
  /* OUTPUT */
  pinMode(pin, OUTPUT);
  
  /* digitalWrite - should result in pin switching to DIGITAL in simulator */
  digitalWrite(pin, HIGH);
  SHORT_DELAY();
  digitalWrite(pin, HIGH);
  LONG_DELAY();
  
  /* analogWrite - should result in pin switching to PWM in simulator */
  analogWrite(pin, 12);
  SHORT_DELAY();
  analogWrite(pin, 123);
  
  

  /* INPUT */
  pinMode(pin, INPUT);

  /* digitalRead - should result in pin switching to DIGITAL in simulator */
  digitalRead(pin);
  SHORT_DELAY();
  digitalRead(pin);
  LONG_DELAY();
  
  /* analogRead - should result in pin switching to ANALOG in simulator */
  analogRead(pin);
  SHORT_DELAY();
  analogRead(pin);
  SHORT_DELAY();

  analogRead(pin);
  SHORT_DELAY();
  analogRead(pin);
  SHORT_DELAY();
  
	  
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
      do_all(4);
      do_all(6);
      do_all(8);
      do_all(9);

      LONG_DELAY();
    }

}


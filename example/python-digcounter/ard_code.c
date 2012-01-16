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
#include <unistd.h>

#define FIRST_LED 2
#define LAST_LED  8

#define ACK_PIN 5
#define TICK_PIN 1

int searduino_exec = 1 ;


void setup() {
  int i ; 

  pinMode(1, OUTPUT);      

  for (i=FIRST_LED;i<=LAST_LED;i++)
    {
      pinMode(i, OUTPUT);      
    }
}

#define DEBUG_PIN_OUT2
#define ENABLE_SLEEP

#ifdef ENABLE_SLEEP
#define   SEARDUINO_LOOP() for (;;) if (!searduino_exec) { fprintf (stderr, "z"); usleep(1000*200); } else 
#else
#define   SEARDUINO_LOOP() for (;;) 
#endif

#ifdef DEBUG_PIN_OUT
#define   DEBUG_MSG(str)    printf("%s\n", str);fflush(stdout);
#define   DEBUG_IN_PIN(pin) printf(" %d ", pin);fflush(stdout);
#else
#define   DEBUG_MSG(str)    
#define   DEBUG_IN_PIN(pin) 
#endif

int main(void)
{
  int i =0;
  int j ;
  init();   

  setup();

  
  SEARDUINO_LOOP()
    {
      DEBUG_MSG("input  pins (Arduino): ");
      DEBUG_IN_PIN(digitalRead(i%2));
      digitalWrite(1,i%2);
      
      for (j=FIRST_LED;j<=LAST_LED;j++)
	{
	  DEBUG_IN_PIN(digitalRead(j));
	  digitalWrite(j,digitalRead(j));
	}
      DEBUG_MSG("");
      
      i++;
      if (i==8) i=0;

      usleep(1000*50); 
    }
  DEBUG_MSG("");
}


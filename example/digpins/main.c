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
#include "blink.h"

long A  = 110;
long As =117;
long B  =123;
long C =131;
long Cs =139;
long D =147;
long Ds =156;
long E =165;
long F =175;
long Fs =185;
long G =196;
long Gs =208;

int pitcher = 1;

#define WHOLE 600
#define HALF  300
#define QUART 150

void setup() {
  int i ; 
  for (i=FIRST_LED;i<=LAST_LED;i++)
    {
      pinMode(i, OUTPUT);      
    }
}



void buzz(long freq, long len) {
  long  i ;

  long tone_delay;
  long cycles;

  tone_delay = 1000000/freq/2; 
  cycles = freq * len/ 1000;


  digitalWrite(13, HIGH);
  for (i=0; i < cycles; i++){
    digitalWrite(12,HIGH); 
    delayMicroseconds(tone_delay); 
    digitalWrite(12,LOW); 
    delayMicroseconds(tone_delay); 
  }
  digitalWrite(13, LOW);
}


void twinkle()
{
      #define SYMP_DELAY 150
      buzz(C,HALF);
      delay(SYMP_DELAY);
      buzz(C,HALF);
      delay(SYMP_DELAY);

      buzz(G,HALF);
      delay(SYMP_DELAY);
      buzz(G,HALF);
      delay(SYMP_DELAY);
      
      buzz(A*2,HALF);
      delay(SYMP_DELAY);
      buzz(A*2,HALF);
      delay(SYMP_DELAY);
      
      buzz(G,WHOLE);
      delay(SYMP_DELAY);

      buzz(F,HALF);
      delay(SYMP_DELAY);
      buzz(F,HALF);
      delay(SYMP_DELAY);
      
      buzz(E,HALF);
      delay(SYMP_DELAY);
      buzz(E,HALF);
      delay(SYMP_DELAY);
      
      buzz(D,HALF);
      delay(SYMP_DELAY);
      buzz(D,HALF);
      delay(SYMP_DELAY);
      
      buzz(C,WHOLE);
      delay(SYMP_DELAY);
      
      delay(1000);
      
}


void anabuzz(void)
{
  pitcher = 1.5*analogRead(2);

  digitalWrite(13, HIGH);
  buzz(pitcher/2, 10);
  digitalWrite(13, LOW);
}

int main(void)
{
  int i ;
  
  init();  
  setup();
  
  for (;;)
    {
      
      //twinkle();
	    anabuzz();

    }
  
}

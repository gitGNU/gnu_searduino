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

void setup() {
  pinMode(11, OUTPUT);      
  pinMode(12, OUTPUT);      
  pinMode(13, OUTPUT);      
  pinMode(5, OUTPUT);      
  pinMode(6, OUTPUT);      
  pinMode(7, OUTPUT);      
  pinMode(8, OUTPUT);      
}


long toneA  = 110;
long toneAs =117;
long toneB  =123;
long toneC =131;
long toneCs =139;
long toneD =147;
long toneDs =156;
long toneE =165;
long toneF =175;
long toneFs =185;
long toneG =196;
long toneGs =208;

long pitcher1 = 1;
int pitcher2 = 1;

#define WHOLE 600
#define HALF  300
#define QUART 150

long
my_analog_read(uint8_t pin)
{
  long val = analogRead(pin);

  digitalWrite(5,0);
  digitalWrite(6,0);
  digitalWrite(7,0);
  digitalWrite(8,0);
  if (val > 400 ) 
    {
      digitalWrite(5,1);
    }
  if (val > 550 ) 
    {
      digitalWrite(6,1);
    }
  if (val > 700 ) 
    {
      digitalWrite(7,1);
    }
  if (val > 850 ) 
    {
      digitalWrite(8,1);
    }
  return val;
}

void buzzd(long freq, long len) {
  long  i ;

  long tone_delay;
  long cycles;

  tone_delay = 1000000/freq; 
  cycles = freq * len/ 1000 / 2;


  for (i=0; i < cycles; i++){
    digitalWrite(12,HIGH); 

    digitalWrite(11,HIGH); 
    delayMicroseconds(tone_delay/2); 
    digitalWrite(11,LOW); 
    delayMicroseconds(tone_delay/2); 

    digitalWrite(12,LOW); 

    digitalWrite(11,HIGH); 
    delayMicroseconds(tone_delay/2); 
    digitalWrite(11,LOW); 
    delayMicroseconds(tone_delay/2); 

  }
}
void buzz(long freq, long len) {
  long  i ;
  static int   ctr=0;
  long myfreq ;
  long tone_delay;
  long cycles;

  pitcher1 = my_analog_read(2) + 100;
  myfreq = freq * pitcher1 / 200;

  tone_delay = 1000000/myfreq/2; 
  cycles = freq * len/ 1000;


  digitalWrite(13, 1);
  for (i=0; i < cycles; i++){
    digitalWrite(12,HIGH); 

    digitalWrite(11,HIGH); 
    delayMicroseconds(tone_delay/2); 
    digitalWrite(11,LOW); 
    delayMicroseconds(tone_delay/2); 

    digitalWrite(12,LOW); 

    digitalWrite(11,HIGH); 
    delayMicroseconds(tone_delay/2); 
    digitalWrite(11,LOW); 
    delayMicroseconds(tone_delay/2); 

  }
}

void twinkle()
{
  pitcher1 = 1.5*my_analog_read(2);

      #define SYMP_DELAY 150
      buzz(toneC,HALF);
      delay(SYMP_DELAY);
      buzz(toneC,HALF);
      delay(SYMP_DELAY);

      buzz(toneG,HALF);
      delay(SYMP_DELAY);
      buzz(toneG,HALF);
      delay(SYMP_DELAY);
      
      buzz(toneA*2,HALF);
      delay(SYMP_DELAY);
      buzz(toneA*2,HALF);
      delay(SYMP_DELAY);
      
      buzz(toneG,WHOLE);
      delay(SYMP_DELAY);

      buzz(toneF,HALF);
      delay(SYMP_DELAY);
      buzz(toneF,HALF);
      delay(SYMP_DELAY);
      
      buzz(toneE,HALF);
      delay(SYMP_DELAY);
      buzz(toneE,HALF);
      delay(SYMP_DELAY);
      
      buzz(toneD,HALF);
      delay(SYMP_DELAY);
      buzz(toneD,HALF);
      delay(SYMP_DELAY);
      
      buzz(toneC,WHOLE);
      delay(SYMP_DELAY);
      
      delay(1000);
      
}


void anabuzz(void)
{
  pitcher1 = my_analog_read(2);
  buzz(pitcher1/2, 5);
}


int main(void)
{
  int i ;
  
  init();  
  setup();
  for (;;)
    {
      
      twinkle();
      //anabuzz();
    }
}

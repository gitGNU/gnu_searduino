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
#include "mouse.h"

void
setup_mouse()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(12,HIGH);
  pinMode(8,  INPUT);
  pinMode(9,  INPUT);
  pinMode(A0,  INPUT);
  //  pinMode(10, INPUT);
  pinMode(11, INPUT);
  Mouse.begin();
  delay(20);
}

void move_mouse(uint8_t x, uint8_t y, uint8_t times)
{
  uint8_t i;

  digitalWrite(13,1);
  for (i=0;i<times;i++)
    {
      digitalWrite(13,i%2);
      Mouse.move(x,y,0);
      delay(10);
    }
  digitalWrite(13,0);
}

void click_mouse(uint8_t b)
{
  digitalWrite(13,1);
  Mouse.click(b);
  delay(100);
  Mouse.press(b);
  delay(100);
  Mouse.release(b);
  delay(100);
  digitalWrite(13,0);
}

void init_mouse()
{  
  searduino_usb_init();
}

void manage_mouse_pins(void)
{
  int hori  = 0;
  int verti = 0;
  
  //hori  = digitalRead(MOUSE_RIGHT_PIN) - digitalRead(MOUSE_LEFT_PIN) ;
  //  verti = digitalRead(MOUSE_UP_PIN)   - digitalRead(MOUSE_DOWN_PIN)  ;
  if ( ( analogRead(MOUSE_UP_PIN) ) > 600 )
    {
      verti = 1;
    }
  else if ( ( analogRead(MOUSE_UP_PIN) ) < 400 )
    {
      verti = -1;
    }
  else 
    {
      verti = 0;
    }
    

  if ( ( analogRead(MOUSE_RIGHT_PIN) ) > 600 )
    {
      hori = 1;
    }
  else if ( ( analogRead(MOUSE_RIGHT_PIN) ) < 400 )
    {
      hori = -1;
    }
  else 
    {
      hori = 0;
    }
    

  //  SEARDUINO_DEBUG(("    %d,%d\n",hori, verti));

  if (hori||verti)
    {
      Mouse.move(hori, verti,0);
      delay(5);
    }
}



/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2014 Henrik Sandklef 
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
#include "LiquidCrystal.h"

#include "pthread.h"

LiquidCrystal* lcd;

void setup() 
{
  printf ("************* in arduino-lcd.cpp  setup()\n");
  lcd->begin(16, 2);
  lcd->clear();                          
  lcd->setCursor(0,0);                   
  lcd->scrollDisplayLeft();
}


extern "C" {
char * get_lcd_data(void) ;
}


int main(void)
{
  lcd = new LiquidCrystal(8, 9, 4, 5, 6, 7);   // init LiquidCrystal 

  init();
  setup();


  /* The following line uses a Saerduino macro 
   * You could use a plain "for (;;)" instead
   */
  SEARDUINO_LOOP()
    {
      lcd->print("ABCDEFGHIJKLMNOPQRSTUVXYZ");
      delay(100);
    }

}


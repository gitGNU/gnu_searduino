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
#include "LiquidCrystal.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);   // init LiquidCrystal 
#define ANALOG_INPUT A0
#define PHOTO_INPUT A1

extern "C" {

void lcd_setup() {
  lcd.begin(16, 2);
  lcd.clear();                          
  lcd.setCursor(0,0);                   

  Serial.begin(9600);
}

void read_and_write() { 

  static int press ;
  static int last_val;

  int x;
  x = analogRead (ANALOG_INPUT);                  
  x = 25;
  

  Serial.println("Test");

  if (x < 50) {                        
    lcd.setCursor(0,0);
    char *s1 = "ABCDEFGHIJKLMNOPQRSTUVXYZabcdefghijklmno"; 
    char *s2 = "1:0123456789-2:0123456789-3:0123456789==abcdefghijklmnopqrstuvxyz"; 
    lcd.print(s1);

    lcd.setCursor(0,1);
    lcd.print(s2);
    //    lcd.scrollDisplayLeft();
    delay(1000);
  }
  else if (x < 100) {                  
    lcd.setCursor(0,1);
    lcd.print ("Up    ");
  }
  else if (x < 200) {                  
    lcd.setCursor(0,1);
    lcd.print ("200   ");
  }
  else if (x < 400){                   
    lcd.setCursor(0,1);
    lcd.print ("Down  "); 
  }
  else if (x < 600){                   
    lcd.setCursor(0,1);
    lcd.print ("Left  ");
  }
  else if (x < 800){                   
    if (last_val != x) 
      {
	char buf[20];
	press++;
	lcd.setCursor(0,0);
	sprintf(buf, "Control: %d", press);  
	//	lcd.print (buf); 
      }
  }
  else {
    //    lcd.clear();
    char buf[20];
    sprintf(buf, "%.4d   ", x);  
    lcd.setCursor(0,1);                   
    lcd.print(buf);
  }

  last_val = x;
  delay(500);
}
  
}

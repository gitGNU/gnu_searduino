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
#define BUZZER_OUTPUT 11
extern "C" {

  void lcd_setup() {
    lcd.begin(16, 2);
    lcd.clear();                          
    lcd.setCursor(0,0);                   
    pinMode(BUZZER_OUTPUT, OUTPUT);
    Serial.begin(9600);
  }
  
  void playTone (int del) {
    int delay;
    char buf[20];
    int times=10;

    
    if (del > 800) { delayMicroseconds(244); return; }
    delay = del;
    times = 244*100 / del;
    
    lcd.setCursor(0,0);
    sprintf(buf,"value=%.4d (%d)", delay, times);
    lcd.print(buf);
    
    for (long i = 0; i < times; i++ ) 
      // 1 / 2048Hz = 488uS, or 244uS high and 244uS low to create 50% duty cycle
      {
	digitalWrite(BUZZER_OUTPUT, HIGH);
	delayMicroseconds(delay);
	digitalWrite(BUZZER_OUTPUT, LOW);
	delayMicroseconds(delay);
      }
  }

void read_and_write() { 

  static int press ;
  static int last_val;

  int x;
  int resistance;
  char buf[16];

  x = analogRead (ANALOG_INPUT);                  
  resistance = analogRead (PHOTO_INPUT);                  
  //  playTone(resistance);                  

  //  Serial.println(x);
  //Serial.println(resistance);

  lcd.setCursor(0,1);
  printf (" A0 => %d\n", analogRead (A0));                  
  printf (" A1 => %d\n", analogRead (A1));                  
  printf (" A2 => %d\n", analogRead (A2));                  
  printf (" A3 => %d\n", analogRead (A3));                  
  printf (" A4 => %d\n", analogRead (A4));                  
  sprintf(buf,"A0: %d A1: %d" , x, resistance);
  
  lcd.print(buf);

  if (x < 50) {  
    //char *s1 = "Right"; 
    //lcd.setCursor(0,0);
    //    sprintf(buf,"value=%.4d (%d)", resistance, x);
    //lcd.print(buf);
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
	lcd.setCursor(0,1);
	sprintf(buf, "Control: %d", press);  
	//	lcd.print (buf); 
      }

  }

  last_val = x;
  delay(200);
}
  
}

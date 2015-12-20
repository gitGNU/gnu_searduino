/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2012, 2013, 2014 Henrik Sandklef 
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

#include "LiquidCrystal.h"
#include "Arduino.h"
#include "searduino.h"
#include "arduino/ext_io.h"

#define LCD_STORAGE_SIZE 41

#define SCROLL_DISABLED 0
#define SCROLL_LEFT     1
#define SCROLL_RIGHT    2

typedef struct
{
  uint8_t data[LCD_STORAGE_SIZE]; // 40 is the size, on extra for '\0'
} lcd_row_t ;


static uint8_t lcd_lines        = 2;
static uint8_t lcd_cols         = 2;
//static uint8_t lcd_row_indent[] = { 0, 0};
static uint8_t lcd_row_pos[]    = { 0, 0};
static uint8_t lcd_dotsize      = 0;
static lcd_row_t lcd_data_rows[2];
static uint8_t current_row      = 0;
static int     current_pos      = 0; /* for scrolling */
static uint8_t scroll_enable   = SCROLL_DISABLED;


extern "C" {
char *
get_lcd_data(void) 
{
  static char tmpbuf[83];

  sprintf(tmpbuf,
	  "LCD DATA:\n---------------\n1: [%s]\n2: [%s]", 
	  (char*)lcd_data_rows[0].data, 
	  (char*)lcd_data_rows[1].data);

  return tmpbuf;
}
}



LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
			     uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
  ;
}

LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t enable,
			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
			     uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
  ;
}

LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
{
  ;
}

LiquidCrystal::LiquidCrystal(uint8_t rs,  uint8_t enable,
			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
{
  ;
}

void LiquidCrystal::init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
			 uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
			 uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
  _data_pins[0] = d0;
  _data_pins[1] = d1;
  _data_pins[2] = d2;
  _data_pins[3] = d3; 
  _data_pins[4] = d4;
  _data_pins[5] = d5;
  _data_pins[6] = d6;
  _data_pins[7] = d7; 
  clear();
}

void LiquidCrystal::begin(uint8_t cols, uint8_t lines, uint8_t dotsize) 
{
   lcd_lines   = lines;
   lcd_cols    = cols;
   lcd_dotsize = dotsize;

   clear();
}


/** USER FUNCTIONS **/
/********** high level commands, for the user! */
void LiquidCrystal::clear()
{

  current_row    = 0;
  lcd_row_pos[0] = 0;
  lcd_row_pos[1] = 0;

  

  memset(lcd_data_rows[0].data, 0, LCD_STORAGE_SIZE);
  memset(lcd_data_rows[1].data, 0, LCD_STORAGE_SIZE);
  strcpy((char*)lcd_data_rows[0].data, " ");
  strcpy((char*)lcd_data_rows[1].data, " ");

  /*printf ("Emptied them... %d %d\n", 
	  strlen((char*)lcd_data_rows[0].data),
	  strlen((char*)lcd_data_rows[1].data));
  */
   lcd_data_rows[0].data[0]='\0';
   lcd_data_rows[1].data[0]='\0';


   if ( lcd_sim_callback == NULL ) 
     {
       ;
     }
   else 
     {
       lcd_sim_callback((char*)lcd_data_rows[0].data,
			(char*)lcd_data_rows[1].data);
     }

   current_pos = 0 ;
   return ;

}

void LiquidCrystal::home()
{
  current_row    = 0;
  lcd_row_pos[0] = 0;
  lcd_row_pos[1] = 0;
}

void LiquidCrystal::setCursor(uint8_t col, uint8_t row)
{
  //  if ( (col>40) || (row>1) ) { return ; }
  lcd_row_pos[row] = col;
  current_row      = row;
}

// Turn the display on/off (quickly)
void LiquidCrystal::noDisplay() {
  ;
}
void LiquidCrystal::display() {
  ;
}

// Turns the underline cursor on/off
void LiquidCrystal::noCursor() {
  ;
}

void LiquidCrystal::cursor() {
  ;
}

// Turn on and off the blinking cursor
void LiquidCrystal::noBlink() {
  ;
}
void LiquidCrystal::blink() {
  ;
}

// These commands scroll the display without changing the RAM
void LiquidCrystal::scrollDisplayLeft(void) {
  scroll_enable = SCROLL_LEFT ;
}

void LiquidCrystal::scrollDisplayRight(void) {
  scroll_enable = SCROLL_RIGHT ;
}

// This is for text that flows Left to Right
void LiquidCrystal::leftToRight(void) {
  ;
}

// This is for text that flows Right to Left
void LiquidCrystal::rightToLeft(void) {
  ;
}

// This will 'right justify' text from the cursor
void LiquidCrystal::autoscroll(void) {
  ;
}

// This will 'left justify' text from the cursor
void LiquidCrystal::noAutoscroll(void) {
  ;
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LiquidCrystal::createChar(uint8_t location, uint8_t charmap[]) {
  ;
}

size_t LiquidCrystal::write(uint8_t value) {
  uint8_t  pos;
  uint8_t *data;


  if (  searduino_is_halted() ) 
    {
      return 0;
    }
  
  if (value==0) 
    {
      char *start1;
      char *start2;
      static char retbuf1[17];
      static char retbuf2[17];
      static char tmpbuf1[81];
      static char tmpbuf2[81];

      /*
      printf ("LCD: ----- : %u %s \n", 
	      lcd_data_rows[0], 
	      scroll_enable);
      */

      memset(retbuf1, 0, 17);
      memset(retbuf2, 0, 17);
      memset(tmpbuf1, 0, 81);
      memset(tmpbuf2, 0, 81);


      snprintf(tmpbuf1, 81, "%-40s%-40s", 
	      (char*)lcd_data_rows[0].data, 
	      (char*)lcd_data_rows[0].data);
      tmpbuf1[80]='\0';

      snprintf(tmpbuf2, 81, "%-40s%-40s", 
	      (char*)lcd_data_rows[1].data, 
	      (char*)lcd_data_rows[1].data);
      tmpbuf2[80]='\0';

      if (scroll_enable==SCROLL_DISABLED)
	{
	  start1 = tmpbuf1;
	  start2 = tmpbuf2;
	  current_pos = 0;
	}
      else if (scroll_enable==SCROLL_LEFT)
	{
	  start1 = tmpbuf1;
	  start1 = start1 + current_pos;

	  start2 = tmpbuf2;
	  start2 = start2 + current_pos;

	  current_pos++;
	  if (current_pos>40) { current_pos=0; }
	}
      else if (scroll_enable==SCROLL_RIGHT)
	{
	  start1 = tmpbuf1;
	  start1 = start1 + 40 + current_pos;

	  start2 = tmpbuf2;
	  start2 = start2 + 40 + current_pos;

	  current_pos--;
	  if (current_pos<-40) { current_pos=0; }
	}

      /*
      printf ("tmpbuf1 (%d): '%s'\n", current_pos, tmpbuf1);
      printf ("tmpbuf2 (%d): '%s'\n", current_pos, tmpbuf2);
      */
      
      strncpy(retbuf1,start1, 16);
      strncpy(retbuf2,start2, 16);
      retbuf1[16]='\0';
      retbuf2[16]='\0';
      if ( lcd_sim_callback == NULL ) 
	{
	  printf ("LCD Fallback function\n");
	  printf ("  LCD[0]: %s  [%s]\n",
		  retbuf1,
		  lcd_data_rows[0].data);
	  printf ("  LCD[1]: %s  [%s]\n",
		  retbuf2,
		  lcd_data_rows[1].data);
	  fflush(stdout);
	}
      else 
	{
	  lcd_sim_callback(retbuf1,
			   retbuf2);
	  
	  ;
	}
    }

  pos = lcd_row_pos[current_row];
  if (pos>=40) { return 1 ; }

  data = lcd_data_rows[current_row].data; 
  data[pos] = value;
  data[pos+1] = '\0';

  //  printf(" (%d, %d, %c, %s) ", current_row, pos, value, data);

  /*  printf ("LCDc: %c  (crow:%d   pos:%d   )\n",
	  value, 
	  current_row,
	  lcd_row_pos[current_row] );*/
  lcd_row_pos[current_row]++;
  return 1; 
}



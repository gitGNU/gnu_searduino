/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2012 Henrik Sandklef 
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

#include "Arduino.h"
#include "searduino.h"
#include "boards.h"
#include "stdio.h"

typedef int   (*board_setup_ptr)(void); 
static int board_index=0;

const char *SEARDUINO_BOARD_UNO_NAME = "Uno";

enum   
  {
    SEARDUINO_BOARD_UNSET,
    SEARDUINO_BOARD_UNO,
    SEARDUINO_BOARD_MEGA,
    SEARDUINO_BOARD_MEGA_2560,
    SEARDUINO_BOARD_LAST
  };

struct searduino_board_t
{
  int             id;
  char           *name;
  board_setup_ptr setup ;
} ;



static struct searduino_board_t searduino_boards[] = 
  {
    { SEARDUINO_BOARD_UNO, 
      "Uno",
      board_setup_uno
    }
  };


char *
get_board_name(void)
{
  /*
   * print warning in case board not set
   * 
   */
  if ( ( board_index <= SEARDUINO_BOARD_UNSET ) ||
       ( board_index >= SEARDUINO_BOARD_LAST ) )    
    {
      fprintf(stderr, "No board name set\n");
      return NULL;
    }

  searduino_boards[board_index];
}


int
set_board_name(char *board)
{
  int i ;

  if (board==NULL)
    {
      printf ("Invalid board name (NULL)\n");
      return -1;
    }

  for (i=1;i<SEARDUINO_BOARD_LAST;i++)
    {
      if (searduino_boards[i].name==NULL)
	{
	  fprintf(stderr, "Major internal error: %s:%d\n", 
		  __func__, __LINE__);
	  return -2;
	}
      if (strncasecmp(board, 
		      searduino_boards[i].name, 
		      strlen(searduino_boards[i].name))==0)
	{
	  return i;
	}
    }

  printf ("Could not match board name %s\n", board);
  return -1;
}


int
board_setup(void)
{
  if ( ( board_index <= SEARDUINO_BOARD_UNSET ) ||
       ( board_index >= SEARDUINO_BOARD_LAST ) )    
    {
      fprintf(stderr, "No board name set, defaulting to Uno\n");
      board_index = SEARDUINO_BOARD_UNO;
    }
  
  return searduino_boards[board_index].setup();
}


int
board_setup_uno(void)
{
  /*
    From the Arduino Uno page:

    "It has 14 digital input/output pins (of which 6 can be used as PWM outputs), 6 analog inputs,"

    PWM: 3, 5, 6, 9, 10, and 11. Provide 8-bit PWM output with the analogWrite() function. 

    LED: 13. There is a built-in LED connected to digital pin 13. When the pin is HIGH value, the LED is on, when the pin is LOW, it's off. 

   */

  printf ("\n\t*** UNO BOARD SETUP\n\n");
  return 0;
}



/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2012, 2013 Henrik Sandklef 
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
#include "searduino_pin.h"
#include "boards.h"
#include "stdio.h"

/* 
 * Simple macros to make the use of define pin function easier to read
 *  by humans
 */
#define ANALOG_IN      1
#define NO_ANALOG_IN   0

#define DIGITAL_IN     1
#define NO_DIGITAL_IN  0
#define DIGITAL_OUT    1
#define NO_DIGITAL_OUT 0

#define PWM_OUT        1
#define NO_PWM_OUT     0



typedef int   (*board_setup_ptr)(void); 
static int board_index=0;

const char *SEARDUINO_BOARD_UNO_NAME = "Uno";

enum   
  {
    SEARDUINO_BOARD_UNSET,
    SEARDUINO_BOARD_UNO,
    SEARDUINO_BOARD_MEGA,
    SEARDUINO_BOARD_MEGA_2560,
    SEARDUINO_BOARD_LEONARDO,
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
    { SEARDUINO_BOARD_UNSET, 
      "none",
      NULL
    },
    { SEARDUINO_BOARD_UNO, 
      "Uno",
      board_setup_uno
    },
    { SEARDUINO_BOARD_MEGA, 
      "Mega",
      NULL
    },
    { SEARDUINO_BOARD_MEGA_2560, 
      "Mega2560",
      board_setup_mega2560
    },
    { SEARDUINO_BOARD_LEONARDO, 
      "Leonardo",
      board_setup_leonardo
    },
    { SEARDUINO_BOARD_LAST, 
      NULL,
      NULL
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

  /*  printf ("board index: %d\n", board_index);
  printf ("board name:  %p\n", searduino_boards[board_index].name);
  printf ("board name:  %s\n", searduino_boards[board_index].name);
  */
  return searduino_boards[board_index].name;
}


char *
get_supported_boards(void)
{
  static int i=0 ;
  static char buf[1000];

  if (i==0)
    {
      strcpy(buf,"");
      for (i=1;i<SEARDUINO_BOARD_LAST;i++)
	{
	  if (i>1) 
	    {
	      strcat(buf,",");
	    } 
	  strcat(buf,searduino_boards[i].name);
	}
      i=1;
    }
  return buf;
}


int
set_board_name(char *board)
{
  int i ;

  if ( board_index > SEARDUINO_BOARD_UNSET )
    {
      if (strncmp(searduino_boards[board_index].name, 
		  board, strlen(board))==0)
	{
	  printf ("Same board (%s) as before, not reloading\n", 
		  board);
	  return 0;
	}
    }

  board_index = 0;

  printf ("Invalid board name (NULL)\n");

  if (board==NULL)
    {
      printf ("Invalid board name (NULL)\n");
      return 0;
    }
  
  

  for (i=1;i<SEARDUINO_BOARD_LAST;i++)
    {
      /* printf ("   checking %d '%s' == '%s' for settings\n", i, board, searduino_boards[i].name); */
      if (searduino_boards[i].name==NULL)
	{
	  fprintf(stderr, "Major internal error: %s:%d (%s) when setting board to '%s'\n", 
		  __FILE__, __LINE__, __func__, board);
	  return 0;
	}
      if ( (strncasecmp(board, 
		      searduino_boards[i].name, 
		      strlen(searduino_boards[i].name))==0)
	   && (strlen(searduino_boards[i].name) == strlen(board)))
	{
	  /* printf ("   checking %d '%s' is our choice :) \n", i, searduino_boards[i].name); */
	  board_index = i;
	  board_setup();

	  return i;
	}
    }

  printf ("Could not match board name %s\n", board);
  return board_index;
}


int
board_setup(void)
{
  int ret;


  //  printf (" =================== BOARD SETUP (boards.c) ==========================");

  /* Set all pins to zero */
  init_arduino_pins();

  if ( ( board_index <= SEARDUINO_BOARD_UNSET ) ||
       ( board_index >= SEARDUINO_BOARD_LAST ) )    
    {
      fprintf(stderr, "No board name set, defaulting to Uno\n");
      board_index = SEARDUINO_BOARD_UNO;
    }
  
  /*  printf ("SETTING UP BOARD: %s\n", searduino_boards[board_index].name);
   */

  if ( searduino_boards[board_index].setup == NULL )
    {
      fprintf(stderr, "Missing setup function for '%s'\n", 
	      searduino_boards[board_index].name);
      return 1;
    }

  ret = searduino_boards[board_index].setup();

  if (set_generic_nr_of_pins() == 0 )
    {
      return -1;
    }

  return ret;
}

static void print_board_digital_pins(char *s, int type)
{
  int i ; 
  printf ("%s", s);
  for (i=0;i<NR_OF_ARDUINO_PINS;i++)
    {
      if ( has_generic_pin_type(i, type))
	{
	  printf ("%d, ", i);
	}
    }
  printf ("\n");
}

static void print_board_analog_pins(void)
{
  int i ; 
  int j ; 
  int   apins[]     = { A0, A1, A2, A3, A4, A5, A6, A7} ;
  char* apins_str[] = { "A0", "A1", "A2", "A3", "A4", "A5", "A6", "A7"} ;
 

  printf ("Analog pins:  ");
  for (i=0;i<NR_OF_ARDUINO_PINS;i++)
    {
      /* printf (" *%d \n", i); */
      if ( has_generic_pin_type(i,SEARDUINO_PIN_TYPE_ANALOG) )
	{
	  printf ("%d (A%d), ", i, i - A0);
	  /*for (j=0;j<8;j++)
	    {
	      if (apins[j]==i)
		{
		  printf (" (%s)", apins_str[j]);
		  break;
		}
	    }
	    printf (", "); */
	}
    }
  printf ("\n");
}

void 
print_board_setup(void)
{
  printf ("\n");
  printf ("Board settings:\n");
  printf ("---------------\n");
  printf ("Name:         %s\n", get_board_name());
  print_board_digital_pins("Digital pins: ", SEARDUINO_PIN_TYPE_DIGITAL);
  print_board_digital_pins("PWM pins:     ", SEARDUINO_PIN_TYPE_PWM);
  print_board_analog_pins();
  printf ("\n");
}

int
board_setup_uno(void)
{

  /*
    From the Arduino Uno page:

    "It has 14 digital input/output pins (of which 6 can be used as PWM outputs), 6 analog inputs,"

    PWM: 3, 5, 6, 9, 10, and 11. Provide 8-bit PWM output with the analogWrite() function. 

    Analog:  6 analog inputs, labeled A0 through A5

    LED: 13. There is a built-in LED connected to digital pin 13. When the pin is HIGH value, the LED is on, when the pin is LOW, it's off. 

   */
  A0 = 14;
  A1 = 15;
  A2 = 16;
  A3 = 17;
  A4 = 18;
  A5 = 19;

  define_arduino_pin(0,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(1,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(2,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(3,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, PWM_OUT);
  define_arduino_pin(4,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(5,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(6,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, PWM_OUT);
  define_arduino_pin(7,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(8,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(9,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, PWM_OUT);
  define_arduino_pin(10, NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, PWM_OUT);
  define_arduino_pin(11, NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, PWM_OUT);
  define_arduino_pin(12, NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(13, NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);

  define_arduino_pin(A0, ANALOG_IN, NO_DIGITAL_OUT, NO_DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(A1, ANALOG_IN, NO_DIGITAL_OUT, NO_DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(A2, ANALOG_IN, NO_DIGITAL_OUT, NO_DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(A3, ANALOG_IN, NO_DIGITAL_OUT, NO_DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(A4, ANALOG_IN, NO_DIGITAL_OUT, NO_DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(A5, ANALOG_IN, NO_DIGITAL_OUT, NO_DIGITAL_IN, NO_PWM_OUT);

  printf ("\n\t*** UNO board setup done\n\n");

  print_board_setup();
  return 0;
}


int
board_setup_mega2560(void)
{
  int i;
  /*
    From the Arduino Mega2560 page:

    It has 54 digital input/output pins
        (of which 14 can be used as PWM outputs), 16 analog inputs

    PWM: 2 to 13 and 44 to 46. 
         Provide 8-bit PWM output with the analogWrite() function.

    LED: 13. There is a built-in LED connected to digital pin 13. When the pin is HIGH value, the LED is on, when the pin is LOW, it's off. 

   */
  
  A0  = 54;
  A1  = 55;
  A2  = 56;
  A3  = 57;
  A4  = 58;
  A5  = 59;
  A6  = 60;
  A7  = 61;
  A8  = 62;
  A9  = 63;
  A10 = 64;
  A11 = 65;
  A12 = 66;
  A13 = 67;
  A14 = 68;
  A15 = 69;

  /* Pin 1 Digital only pin type*/
  define_arduino_pin(1,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, PWM_OUT);

  /* Pin 2-13  PWM and Digital pin type */
  for(i = 2; i <= 13; i++) {
    define_arduino_pin(i,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  }

  /* Pin 14-43 Digital only pin type */
  for(i = 14; i <= 43; i++) {
    define_arduino_pin(i,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, PWM_OUT);
  }

  /* Pin 44-46  PWM and Digital pin type */
  for(i = 44; i <= 46; i++) {
    define_arduino_pin(i,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  }

  /* Pin 47-54 Digital only pin type */
  for(i = 47; i <= 54; i++) {
    define_arduino_pin(i,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, PWM_OUT);
  }

  /* 16 analog pins */
  for(i = A0; i < A15; i++) {
    define_arduino_pin(i, ANALOG_IN, NO_DIGITAL_OUT, NO_DIGITAL_IN, NO_PWM_OUT);
  }

  printf ("\n\t*** MEGA2560 board setup done\n\n");
  print_board_setup();
  return 0;
}



int
board_setup_leonardo(void)
{
  int i;
  /*
    From the Arduino Leonardo page[1]:

    It has 20 digital input/output pins 
       (of which 7 can be used as PWM outputs and 12 as analog inputs),

    PWM: 3, 5, 6, 9, 10, 11, and 13. 
       Provide 8-bit PWM output with the analogWrite() function. 

    LED: 13. There is a built-in LED connected to digital pin 13. 
       When the pin is HIGH value, the LED is on, when the pin is LOW, it's off. 

    Analog Inputs: A0-A5, A6 - A11 (on digital pins 4, 6, 8, 9, 10, and 12). 
       The Leonardo has 12 analog inputs, labeled A0 through A11, all
       of which can also be used as digital i/o. Pins A0-A5 appear in
       the same locations as on the Uno; inputs A6-A11 are on digital
       i/o pins 4, 6, 8, 9, 10, and 12 respectively. Each analog input
       provide 10 bits of resolution (i.e. 1024 different values). By
       default the analog inputs measure from ground to 5 volts,
       though is it possible to change the upper end of their range
       using the AREF pin and the analogReference() function.

    There are a couple of other pins on the board:

    AREF. Reference voltage for the analog inputs. Used with analogReference().
    Reset. Bring this line LOW to reset the microcontroller. Typically used to add a reset button to shields which block the one on the board. 

   [1] http://arduino.cc/en/Main/ArduinoBoardLeonardo
   */

  A0  = 14;
  A1  = 15;
  A2  = 16;
  A3  = 17;
  A4  = 18;
  A5  = 19;
  A6  = 4;
  A7  = 6;
  A8  = 8;
  A9  = 10;
  A10 = 12;


  /* PWM: 3, 5, 6, 9, 10, 11, and 13. 
     Provide 8-bit PWM output with the analogWrite() function.  */
  define_arduino_pin(3,   NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, PWM_OUT);
  define_arduino_pin(5,   NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, PWM_OUT);
  /* 6 is also analog */
  define_arduino_pin(6,   ANALOG_IN,    DIGITAL_OUT, DIGITAL_IN, PWM_OUT);
  /* 9, 10 is also analog */
  define_arduino_pin(9,   ANALOG_IN,    DIGITAL_OUT, DIGITAL_IN, PWM_OUT);
  define_arduino_pin(10,  ANALOG_IN,    DIGITAL_OUT, DIGITAL_IN, PWM_OUT);
  define_arduino_pin(11,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, PWM_OUT);
  define_arduino_pin(13,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, PWM_OUT);

  /*
   * Rest of them are digital (somoe also analog 
   */
  define_arduino_pin(1,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(2,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  /* 4 is also analog */
  define_arduino_pin(4,  ANALOG_IN,    DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(7,  NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  /* 8 is also analog */
  define_arduino_pin(8,  ANALOG_IN,    DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  /* 12 is also analog */
  define_arduino_pin(12, ANALOG_IN,    DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(14, ANALOG_IN,    DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(15, ANALOG_IN,    DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(16, ANALOG_IN,    DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(17, ANALOG_IN,    DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(18, ANALOG_IN,    DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(19, ANALOG_IN,    DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);
  define_arduino_pin(20, NO_ANALOG_IN, DIGITAL_OUT, DIGITAL_IN, NO_PWM_OUT);

  printf ("\n\t*** Leanoard board setup done\n\n");

  print_board_setup();
  return 0;
}

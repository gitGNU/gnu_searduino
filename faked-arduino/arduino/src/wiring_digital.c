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

#include "Arduino.h"
#include "arduino/wiring_private.h"
#include "arduino/pins_arduino.h"
#include "../include/error.h"
#include "utils/print.h"
#include "utils/types.h"
#include "arduino/error.h"
#include "utils/error.h"

#include "communication/digio.h"
#include "communication/comm.h"
#include "setup.h"

#include <sys/time.h>

typedef struct arduino_pin
{
  uint8_t mode;
  uint8_t val;
  struct timeval  last_time;
} arduino_pin;

/* 
 *  Warning, there be dragons here
 *
 *  Having this static implies zeroing it, which 
 *  sets the mode to INPUT (which is default on Arduinos)
 *
 *  It is ugeested that this is moved to some kind of 
 *  init function later on
 *
 */ 
static arduino_pin arduino_digital_pins[NR_OF_DIGITAL_PINS];

#define PIN_OUT_OF_RANGE(pin)          (pin<0 || pin> NR_OF_DIGITAL_PINS)
#define get_digital_pin_mode(pin)      (arduino_digital_pins[pin].mode) 
#define set_digital_pin_mode(pin,mode)  arduino_digital_pins[pin].mode=mode; 
#define get_digital_pin_val(pin)       (arduino_digital_pins[pin].val) 
#define set_digital_pin_val(pin,val)    arduino_digital_pins[pin].val=(val!=0);

/*
 *
 * Callback used to update in_pins
 * This fun is use (callbacked by) comm layer
 *
 */
void 
digin_callback(uint8_t pin, uint8_t val)
{
  searduino_setup();
  PRINT_FUNCTION_NAME(("%d,%d",pin,val));

  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return ;
    }

  if ( get_digital_pin_mode(pin) != INPUT)
    {
      SEARD_ERROR( SEARD_ARDUINO_WRONG_PIN_MODE);
      return;
    }

  arduino_digital_pins[pin].val=(val!=0);
  /* printf ("%s:%s   storing in[%d].val=%d  (%d)\n",__FILE__, __func__, pin, arduino_in_pins[pin].val, val);  */
  return;
}



/*
 *
 * Callback used to read pin mode
 *   used in comm layer
 *
 */
uint8_t
dig_mode_callback(uint8_t pin)
{
  searduino_setup();
  PRINT_FUNCTION_NAME(("%d",pin));

  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return 0;
    }

  return get_digital_pin_mode(pin);
}

/*
 *
 * Callback used to read out_pins
 *   used in comm layer
 *
 */
uint8_t
digout_callback(uint8_t pin)
{
  searduino_setup();
  PRINT_FUNCTION_NAME(("%d",pin));

  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return 0;
    }

  if ( get_digital_pin_mode(pin) != OUTPUT)
    {
      SEARD_ERROR(SEARD_ARDUINO_WRONG_PIN_MODE);
      return 0;
    }

/*   printf ("PYTHON (in C stub)   returning out[%d].val=%d     GUI\n", pin, arduino_out_pins[pin].val); */
  return   get_digital_pin_val(pin);
}



void pinMode(uint8_t pin, uint8_t mode)
{
  searduino_setup();
  PRINT_FUNCTION_NAME(("%d,%d",pin,mode));
  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return;
    }

  set_digital_pin_mode(pin,mode);

  return;
}

static void turnOffPWM(uint8_t timer)
{
  PRINT_FUNCTION_NAME(("%d",timer));
}

void digitalWrite(uint8_t pin, uint8_t val)
{
  int ret;
  static int discard_ctr;
  struct timeval  cur_time;
  struct timezone zoneData;
  long time_diff;

  searduino_setup();
/*   printf ("PYTHON   (stub) pin:%d=%d   GUI | will set value \n" ,pin,val); */

  PRINT_FUNCTION_NAME(("%d,%d",pin,val));

  if( gettimeofday( &cur_time, &zoneData) == 0 )
    {
      if (arduino_digital_pins[pin].last_time.tv_sec!=0)
	{
	  time_diff = (cur_time.tv_sec - arduino_digital_pins[pin].last_time.tv_sec) * 1000000 +
	    cur_time.tv_usec - arduino_digital_pins[pin].last_time.tv_usec ;

	  /* if (time_diff<20) */
	  /*   { */
	      fprintf (stderr,"micro seconds since last update on pin %d : %lu\n", 
		       pin,
		       time_diff);
	    /* } */
	}
      arduino_digital_pins[pin].last_time = cur_time;
    }
  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return;
    }

  if ( get_digital_pin_mode(pin) != OUTPUT )
    {
      fprintf(stderr, 
	      "Can't write to a pin (%d) with mode (%d) set INPUT\n",
	      pin, get_digital_pin_mode(pin));
      SEARD_ERROR(SEARD_ARDUINO_WRONG_PIN_MODE);
      return;
    }

  /*
   *
   *  Only calling lower layer on chage
   *
   */
  if ( get_digital_pin_val(pin) != val)
    {
      set_digital_pin_val(pin,val);
      /* printf ("wiring_digital()   (will call comm) pin:%d=%d  \n" ,pin,val);  */
      
      ret = comm_digital_write_outpin(pin,val);
      if (ret != SEARD_ARDUINO_OK)
	{
	  SEARD_ERROR(ret);
	  return;
	}
      printf ("                       discarded calls (not on change) so far: %d\n", discard_ctr);
    }
  else
    {
      discard_ctr++;
    }
  return;
}

int digitalRead(uint8_t pin)
{
  searduino_setup();
  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return 0;
    }

  if ( get_digital_pin_mode(pin) != INPUT )
    {
      fprintf(stderr, 
	      "Can't read from a pin (%d) with mode (%d) NOT set INPUT\n",
	      pin, get_digital_pin_mode(pin));
      SEARD_ERROR(SEARD_ARDUINO_WRONG_PIN_MODE);
      return 0;
    }
  

  return get_digital_pin_val(pin);
}

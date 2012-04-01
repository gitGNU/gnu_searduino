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

#include "arduino/wiring_private.h"
#include "arduino/pins_arduino.h"
#include "arduino/setup.h"
#include "../include/arduino/error.h"
#include "utils/print.h"
#include "utils/types.h"
#include "arduino/error.h"
#include "utils/error.h"
#include <sys/time.h>


typedef struct arduino_pin
{
  uint8_t         mode;
  unsigned int    val;
  struct timeval  last_write;
  struct timeval  last_actual_write;
  int             discard_ctr;
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
static arduino_pin arduino_analog_pins[NR_OF_ANALOG_PINS];

#define PIN_OUT_OF_RANGE(pin)          (pin<0 || pin> NR_OF_ANALOG_PINS)
#define get_analog_pin_mode(pin)      (arduino_analog_pins[pin].mode) 
#define set_analog_pin_mode(pin,mode)  arduino_analog_pins[pin].mode=mode; 


uint8_t analog_reference = 0;

void analogReference(uint8_t mode)
{
  analog_reference = mode;
}

unsigned int 
analogRead(uint8_t pin)
{
  searduino_setup();
  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return 0;
    }

  /* printf ("wiring: analogRead(%d) => %d\n",  */
  /* 	  pin, get_analog_pin_val(pin)); */
  return get_analog_pin_val(pin);
}

/*
 *
 * Callback used to update in_pins
 * This fun is use (callbacked by) comm layer
 *
 */
void 
anain_callback(uint8_t pin, unsigned int val)
{
  searduino_setup();
  PRINT_FUNCTION_NAME(("%d,%d",pin,val));

  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return ;
    }

  set_analog_pin_val(pin,val);

  /* printf ("%s:%s   storing in[%d].val=%d  (%d)\n",__FILE__, __func__, pin, arduino_analog_pins[pin].val, val);  */
  return;
}


/*
 *
 * Callback used to read out_pins
 *   used in comm layer
 *
 */
uint8_t
anaout_callback(uint8_t pin)
{
  searduino_setup();
  PRINT_FUNCTION_NAME(("%d",pin));

  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return 0;
    }

  return get_analog_pin_val(pin);
}

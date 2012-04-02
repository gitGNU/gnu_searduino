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
#include "arduino/searduino_pin.h"
#include "arduino/setup.h"
#include "../include/arduino/error.h"
#include "utils/print.h"
#include "utils/types.h"
#include "arduino/error.h"
#include "utils/error.h"
#include <sys/time.h>


uint8_t analog_reference = 0;

void analogReference(uint8_t mode)
{
  analog_reference = mode;
}

int 
analogRead(uint8_t pin)
{
  printf ("analogRead(%d)\n", pin);
  searduino_setup();
  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return 0;
    }
  
  /* printf ("wiring: analogRead(%d) => %d\n",  */
  /* 	  pin, get_analog_pin_val(pin)); */
  printf ("analogRead(%d)=>%d\n", pin, get_analog_pin_val(pin) );
  printf ("analogRead(%d)=>%d\n", pin, get_generic_pin_val(pin, SEARDUINO_PIN_TYPE_ANALOG));
  
  return get_analog_pin_val(pin);
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

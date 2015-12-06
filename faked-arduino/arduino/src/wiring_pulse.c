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

#include "wiring_private.h"
#include "arduino/pins_arduino.h"
#include "arduino/searduino_pin.h"
#include "pins_arduino.h"
#include "utils/print.h"
#include "arduino/setup.h"
#include "../include/arduino/error.h"
#include "utils/print.h"
#include "utils/types.h"
#include "arduino/error.h"
#include "utils/error.h"

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
  int ret_val;

  set_generic_pin_type(pin, SEARDUINO_PIN_TYPE_ANALOG);

  searduino_setup();
  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return 0;
    }
  
  /* printf ("wiring: analogRead(%d) => %d\n",  */
  /* 	  pin, get_analog_pin_val(pin)); */
  /* printf ("analogRead(%d)=>%d\n", pin, get_analog_pin_val(pin) ); */
  /* printf ("analogRead(%d)=>%d\n", pin, get_generic_pin_val(pin, SEARDUINO_PIN_TYPE_ANALOG)); */
  
  ret_val = get_analog_pin_val(pin);

  if (ret_val < state ) 
    {
      log_error("Analog value to return to analogRead is less than 0, returning 0");
      ret_val = 0 ;
    }
  else if (ret_val > 1024) 
    {
      log_error("Analog value to return to analogRead is higher than 1024, returning 1024");
      ret_val = 1024 ;
    }

  return ret_val - timeout/1000;
}

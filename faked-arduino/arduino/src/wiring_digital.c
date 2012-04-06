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
#include "arduino/searduino_pin.h"
#include "../include/arduino/error.h"
#include "utils/print.h"
#include "utils/types.h"
#include "arduino/error.h"
#include "utils/error.h"

#include "ext_io.h"
#include "setup.h"



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

  set_digital_pin_val(pin,val);
  return;
}




void 
pinMode(uint8_t pin, uint8_t mode)
{
  searduino_setup();
  PRINT_FUNCTION_NAME(("%d,%d",pin,mode));
  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return;
    }

  set_digital_pin_mode(pin,mode);

  ext_digital_set_mode(pin, mode);

  return;
}

void turnOffPWM(uint8_t timer)
{
  PRINT_FUNCTION_NAME(("%d",timer));
}

void digitalWrite(uint8_t pin, uint8_t val)
{
  return genericWrite(pin, val, SEARDUINO_PIN_TYPE_DIGITAL);
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

void analogWrite(uint8_t pin, int val)
{
  return genericWrite(pin, val, SEARDUINO_PIN_TYPE_ANALOG);
}



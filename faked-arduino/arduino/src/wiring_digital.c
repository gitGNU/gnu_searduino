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
  
  /* printf (" ====>  pinMode(%d,%d)   was:%d\n",  */
  /* 	  pin, mode , get_generic_pin_mode(pin)	  ); */

  PRINT_FUNCTION_NAME(("%d,%d",pin,mode));
  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_WARNING(SEARD_ARDUINO_OUT_OF_BOUND);
      return;
    }

  ext_digital_set_mode(pin,mode);
  set_digital_pin_mode(pin,mode);

  return;
}

void turnOffPWM(uint8_t timer)
{
  PRINT_FUNCTION_NAME(("%d",timer));
}


void digitalWrite(uint8_t pin, uint8_t val)
{

  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return 0;
    }

  /* printf ("digitalWrite(%d,%d) type=%d\n",pin,val,get_current_pin_type(pin)); */
  if ( get_digital_pin_mode(pin) == INPUT )
    {
      log_error("You're writing (digitalWrite) to pin %d, which is an INPUT pin", pin);
      return;
    }
  
  /* Turn off PWM */
  if ( set_generic_pin_type(pin, SEARDUINO_PIN_TYPE_DIGITAL) )
    {
      log_error("Could not set pin %d to digital (in digitalWrite)", pin);
    }
  
  /* Warn and then discard digital writes to an analog pin */
  if ( has_generic_pin_type(pin, SEARDUINO_PIN_TYPE_ANALOG) &&
       !has_generic_pin_type(pin, SEARDUINO_PIN_TYPE_DIGITAL) )
    {
      log_error("Could not write a digital value to pin %d (in digitalWrite)", pin);
      return;
    }
  
  /* Make sure we're only storing 1 or 0 
   *   0 => 0
   *  !0 => 1*/
  return genericWrite(pin, (val!=0), SEARDUINO_PIN_TYPE_DIGITAL);
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
      log_error("You're reading from pin %d, which is an OUTPUT pin", pin);
    }
  
  /* Turn off PWM */
  if ( set_generic_pin_type(pin, SEARDUINO_PIN_TYPE_DIGITAL) )
    {
      log_error("Could not set pin %d to digital (in digitalRead)", pin);
    }
  
  /*
   * If the digital pin has been used as a PWM, then
   * we're returning HIGH if !=0, otherwise LOW (
   *    (   0 => 0   !0 => 1 )
   */
  return (get_digital_pin_val(pin)!=0);
}




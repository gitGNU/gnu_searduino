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

#include "ext_io.h"
#include "setup.h"


uint8_t analog_reference = 0;

void analogReference(uint8_t mode)
{
  analog_reference = mode;
}

int 
analogRead(uint8_t pin)
{
  /* printf ("analogRead(%d)\n", pin); */
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
  
  return get_analog_pin_val(pin);
}

void analogWrite(uint8_t pin, int val)
{
  /* printf ("analogWrite(%d,%d) type=%d\n",pin,val,get_current_pin_type(pin)); */

  if (has_generic_pin_type(pin, SEARDUINO_PIN_TYPE_ANALOG))
    {
      /* The following behaviour is based on the Leonardo board */
      if (val < 255)
	{
	  genericWrite(pin, 0, SEARDUINO_PIN_TYPE_PWM);
	}
      else 
	{
	  genericWrite(pin, 1023, SEARDUINO_PIN_TYPE_PWM);
	}
      return ;
    }


  /* Arduino sets the pin mode to OUTPUT in the analogWrite function,
     ergo setting the pin mode here */
  pinMode(pin, OUTPUT);

  if (val == 0)
    {
      if ( set_generic_pin_type(pin, SEARDUINO_PIN_TYPE_PWM) )
	{
	  log_error("Could not set pin %d to pwm (in analogWrite)", pin);
	}
      /* On the Arduino boards this is done via digitalWrite, 
	 if we do this we set to digitalWrite and then set back to pwm
	 all the time, 
	 so we do a generic setting of the value and keep the pin as pwm */
      /* Turn on PWM */
      genericWrite(pin, LOW, SEARDUINO_PIN_TYPE_PWM);
    }
  else if (val == 255)
    {
      if ( set_generic_pin_type(pin, SEARDUINO_PIN_TYPE_PWM) )
	{
	  log_error("Could not set pin %d to pwm (in analogWrite)", pin);
	}
      /* See comment on "val == 0" above */
      genericWrite(pin, HIGH, SEARDUINO_PIN_TYPE_PWM);
    }
  else
    {
      if (has_generic_pin_type(pin, SEARDUINO_PIN_TYPE_PWM))
	{
	  set_generic_pin_type(pin, SEARDUINO_PIN_TYPE_PWM);
	  /* TODO: 
	     check if this really should be done
	     are some pins 10 bits???
	  */
	  if ( set_generic_pin_type(pin, SEARDUINO_PIN_TYPE_PWM) )
	    {
	      log_error("Could not set pin %d to pwm (in analogWrite)", pin);
	    }
	  if (val > 255 ) { val = 255; }
	  genericWrite(pin, val, SEARDUINO_PIN_TYPE_PWM);
	}
      else if (has_generic_pin_type(pin,SEARDUINO_PIN_TYPE_DIGITAL))
	{
	  if (val < 128)
	    {
	      digitalWrite(pin, LOW);
	    }
	  else 
	    {
	      digitalWrite(pin, HIGH);
	    }
	}
    }
  
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
  
  if ( get_analog_pin_mode(pin) != INPUT )
    {
      fprintf(stderr, 
	      "Can't read from a pin (%d) with mode (%d) NOT set INPUT\n",
	      pin, get_analog_pin_mode(pin));
      log_error("Can't read from an OUTPUT pin");
      SEARD_ERROR(SEARD_ARDUINO_WRONG_PIN_MODE);
      return 0;
    }      
  
  return get_analog_pin_val(pin);
}

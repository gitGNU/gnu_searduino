/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2011, 2012, 2013 Henrik Sandklef 
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
  int ret_val;

  /* printf ("analogRead(%d)   which has type: %d\n",  
   	  pin,  
   	  get_current_pin_type(pin)); */

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

  if (ret_val < 0 ) 
    {
      log_error("Analog value to return to analogRead is less than 0, returning 0");
      ret_val = 0 ;
    }
  else if (ret_val > 1024) 
    {
      log_error("Analog value to return to analogRead is higher than 1024, returning 1024");
      ret_val = 1024 ;
    }

  return ret_val;
}

void analogWrite(uint8_t pin, int val)
{
  /* printf ("analogWrite(%d,%d) type=%d\n",pin, val, get_current_pin_type(pin)); */

  /*
     printf ("    digital?: %d\n",has_generic_pin_type(pin, SEARDUINO_PIN_TYPE_DIGITAL)); 
     printf ("    pwm?:     %d\n",has_generic_pin_type(pin, SEARDUINO_PIN_TYPE_PWM)); 
     printf ("    analog?:  %d\n",has_generic_pin_type(pin, SEARDUINO_PIN_TYPE_ANALOG)); 
  */

  /* Arduino sets the pin mode to OUTPUT in the analogWrite function,
     ergo setting the pin mode here */
  pinMode(pin, OUTPUT);

  if (val>255)
    {
      log_error("Too high value (%d) in analogWrite in pin %d", val, pin);
      val=255;
    }
  else if (val<0)
    {
      log_error("Too small value (%d) in analogWrite in pin %d", val, pin);
      val=0;
    }
  
  /* if neither digital or pwm: return */ 
  if (!( (has_generic_pin_type(pin, SEARDUINO_PIN_TYPE_DIGITAL)) ||
	 (has_generic_pin_type(pin, SEARDUINO_PIN_TYPE_PWM))))
    {
      log_error("Can't analogWrite (%d) to in pin %d since the pin is neither digital or pwm", val, pin);
      return;
    }
    

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
      /*   we need to write 255 (instead of HIGH) since there's
           no timer do determine pwm or digital*/
      genericWrite(pin, val, SEARDUINO_PIN_TYPE_PWM);
    }
  else
    {
      if (has_generic_pin_type(pin, SEARDUINO_PIN_TYPE_PWM))
	{
	  set_generic_pin_type(pin, SEARDUINO_PIN_TYPE_PWM);

	  if ( set_generic_pin_type(pin, SEARDUINO_PIN_TYPE_PWM) )
	    {
	      log_error("Could not set pin %d to pwm (in analogWrite)", pin);
	    }
	  if (val > 255 ) 
	    { 
	      log_error("You're writing a value bigger than 255 to analogWrite\n");
	      val = 255; 
	    }
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

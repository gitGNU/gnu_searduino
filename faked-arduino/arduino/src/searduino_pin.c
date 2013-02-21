/***** *                                                                   
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
#include "arduino/pins_arduino.h"
#include "arduino/searduino_pin.h"

#include "../include/arduino/error.h"
#include "utils/print.h"
#include "utils/types.h"
#include "arduino/error.h"
#include "utils/error.h"
#include "ext_io.h"
#include "setup.h"
#include "stdio.h"

#include <sys/time.h>


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
static arduino_pin arduino_pins[NR_OF_ARDUINO_PINS+1];
static uint8_t     nr_of_pins;



static unsigned int digitalWrite_timelimit = 20*1000;
#define genericWrite_timelimit digitalWrite_timelimit


uint8_t A0  = 0;
uint8_t A1  = 0;
uint8_t A2  = 0;
uint8_t A3  = 0;
uint8_t A4  = 0;
uint8_t A5  = 0;
uint8_t A6  = 0;
uint8_t A7  = 0;
uint8_t A8  = 0;
uint8_t A9  = 0;
uint8_t A10 = 0;
uint8_t A11 = 0;
uint8_t A12 = 0;
uint8_t A13 = 0;
uint8_t A14 = 0;
uint8_t A15 = 0;


static void zero_pin(uint8_t pin)
{
  arduino_pins[pin].current_mode  = INPUT;
  arduino_pins[pin].current_value = 0;
  arduino_pins[pin].discard_ctr   = 0;
  arduino_pins[pin].in_use        = 0;  
}

void init_arduino_pins(void)
{
  int i ; 
  for (i=0;i<=NR_OF_ARDUINO_PINS;i++)
    {
      zero_pin(i);
    }

  return;
}


void define_arduino_pin(uint8_t pin, 
			uint8_t analog_in, 
			uint8_t digital_out, 
			uint8_t digital_in, 
			uint8_t pwm_out)
{

  zero_pin(pin);
  
  arduino_pins[pin].analog_in   = analog_in ;  
  arduino_pins[pin].digital_out = digital_out;  
  arduino_pins[pin].digital_in  = digital_in;  
  arduino_pins[pin].pwm_out     = pwm_out;  

  arduino_pins[pin].in_use      = 1;  

  if (digital_out)
    {
      set_generic_pin_type(pin, SEARDUINO_PIN_TYPE_DIGITAL);
    }
  else if (analog_in) 
    {
      set_generic_pin_type(pin, SEARDUINO_PIN_TYPE_ANALOG);
    }
  else if (pwm_out)
    {
      set_generic_pin_type(pin, SEARDUINO_PIN_TYPE_PWM);
    }
  

  /*
  arduino_pins[pin].output      = output;  
  arduino_pins[pin].input       = input;  
  */
  return;
}

/*
 *  
 * milli seconds
 *
 */
void 
set_write_timelimit(unsigned int lim)
{
  digitalWrite_timelimit = lim*1000;
}

/*
 *  
 * milli seconds
 *
 */
unsigned int 
get_write_timelimit(void)
{
  return (digitalWrite_timelimit/1000) ;
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

  return   get_digital_pin_val(pin);
}


unsigned int 
get_discard_ctr(unsigned char pin)
{
  return arduino_pins[pin].discard_ctr;
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


int 
get_generic_pin_mode(uint8_t pin)
{
  return arduino_pins[pin].current_mode;
}

int 
has_generic_pin_type(uint8_t pin, uint8_t type)
{
  switch (type)
    {
    case SEARDUINO_PIN_TYPE_DIGITAL:
      return arduino_pins[pin].digital_in && arduino_pins[pin].digital_out;
      break;
    case SEARDUINO_PIN_TYPE_PWM:
      return arduino_pins[pin].pwm_out;
      break;
    case SEARDUINO_PIN_TYPE_ANALOG:
      return arduino_pins[pin].analog_in;
      break;
    }
  return 0;
}

int 
get_current_pin_type(uint8_t pin)
{
  return arduino_pins[pin].current_type ;
}

int 
set_generic_pin_type(uint8_t pin, uint8_t pin_type)
{
  if ( pin_type >= SEARDUINO_PIN_TYPE_END )
    {
      arduino_pins[pin].current_type = SEARDUINO_PIN_TYPE_NONE;
      return 1;
    }

  if (pin_type != arduino_pins[pin].current_type )
    {
      arduino_pins[pin].current_type = pin_type;
      ext_inform_pin_type(pin, pin_type);
    }

  return 0;
}

int 
set_generic_nr_of_pins(void)
{
  int i ;

  for (i=1;i<NR_OF_ARDUINO_PINS+1;i++)
    {
      if (arduino_pins[i].in_use != 0)
	{
	  nr_of_pins = i;
	}
    }
  return nr_of_pins;
}

uint8_t
get_generic_nr_of_pins(void)
{
  return nr_of_pins;
}


int 
set_generic_pin_mode(uint8_t pin, uint8_t mode)
{
  /* printf ("SGM %d %d  (%d || %d)\n", pin, mode, */
  /* 	  has_generic_pin_type(pin, SEARDUINO_PIN_TYPE_DIGITAL),  */
  /* 	  has_generic_pin_type(pin, SEARDUINO_PIN_TYPE_PWM)); */

  
  if ( (has_generic_pin_type(pin, SEARDUINO_PIN_TYPE_DIGITAL)) ||
       (has_generic_pin_type(pin, SEARDUINO_PIN_TYPE_PWM) ))
    {
      arduino_pins[pin].current_mode=mode; 
      return 0;
    }
  else
    {
      if (pin==0)
	{
	  return 0;
	}

      printf ("Failed setting mode %d on pin %d\n", mode, pin);
    }
  return  -1;
}

int 
set_generic_pin_val_impl(uint8_t      pin, 
			 unsigned int val, 
			 uint8_t pin_type, 
			 uint8_t exp_inout)
{
  if (pin_type == SEARDUINO_PIN_TYPE_DIGITAL)
    {
      if (get_digital_pin_mode(pin) != exp_inout)
	{
	  if ( get_digital_pin_mode(pin) == INPUT )
	    {
	      log_warning(("You're writing to a digital pin set to INPUT\n"));
	    }
	  SEARD_WARNING(SEARD_ARDUINO_WRONG_PIN_MODE);
	}
      arduino_pins[pin].current_value=val; 

      return 0;
    }
  else
    {
      /*      if (arduino_pins[pin].current_type==pin_type)
	{
      */
      arduino_pins[pin].current_value=val; 
      return 0;
	  /*
	}
      else
	{
	  SEARD_WARNING( SEARD_ARDUINO_WRONG_PIN_TYPE);
	}
	  */
    }
  return  -1;
}


int 
get_generic_pin_val(uint8_t pin)
{
  return arduino_pins[pin].current_value; 
}

int 
get_pin_val(uint8_t pin)
{
  return arduino_pins[pin].current_value; 
}


void 
genericWrite(uint8_t pin, int val, uint8_t pin_type)
{
  int ret;
  struct timeval  cur_time;
  struct timezone zoneData;
  long time_diff = 0 ;
  uint8_t current_pin_type;

  searduino_setup();

  PRINT_FUNCTION_NAME(("%d,%d",pin,val));
  printf("%s(%d,%d)\n",__func__, pin,val);  

  if (PIN_OUT_OF_RANGE(pin))
    {
      log_error("genericWrite: Pin (%d) out of range\n", pin);
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return;
    }

  if (get_generic_pin_mode(pin) != OUTPUT)
    {
      log_warning("genericWrite: Pin (%d) is not set to OUTPUT\n", pin);
    }


  if( gettimeofday( &cur_time, &zoneData) == 0 )
    {
      if (arduino_pins[pin].last_actual_write.tv_sec!=0)
	{
	  time_diff = (cur_time.tv_sec - arduino_pins[pin].last_actual_write.tv_sec) * 1000000 +
	    cur_time.tv_usec - arduino_pins[pin].last_actual_write.tv_usec ;
	}
    }
  arduino_pins[pin].last_write = cur_time;


  /*
   *
   *  Only calling lower layer on change
   *
   */
  if ( get_pin_val(pin) != val)
    {


      set_generic_pin_val(pin, val, pin_type);
      
      /*
       *
       */
      if ((time_diff<genericWrite_timelimit) && (time_diff!=0) )
	{

	  DEBUG_INFO(("**** NO  micro seconds since last update on pin %d : %lu   (%lu)\n", 
		      pin,
		      time_diff, genericWrite_timelimit));
	  
	} 
      else
	{
	  arduino_pins[pin].last_actual_write = cur_time ;     
	  DEBUG_INFO(("**** YES micro seconds since last update on pin %d : %lu  (%lu  %lu %lu)\n", 
		      pin,
		      time_diff,genericWrite_timelimit, 
		      (arduino_pins[pin].last_write.tv_sec*1000000+arduino_pins[pin].last_write.tv_usec),
		      (arduino_pins[pin].last_actual_write.tv_sec*1000000+arduino_pins[pin].last_actual_write.tv_usec)));
	  ret = ext_generic_write_outpin(pin,val,pin_type);
	  if (ret != SEARD_ARDUINO_OK)
	    {
	      SEARD_ERROR(ret);
	      return;
	    }
	}
      /* fprintf (stderr, " GW discarded calls (not on change) so far: %d\n", arduino_pins[pin].discard_ctr);  */
    }
  else
    {
      /* fprintf (stderr, "GW discard %d %d\n",  */
      /* 	       pin,  val); */
      arduino_pins[pin].discard_ctr++;
    }
  return;
}


/*
 *
x * Callback used to update in_pins
 * This fun is use (callbacked by) comm layer
 *
 */
void 
input_callback(uint8_t pin, unsigned int val, uint8_t pin_type)
{
  searduino_setup();
  PRINT_FUNCTION_NAME(("%d,%d,%d",pin,val, pin_type));

  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return ;
    }

  sim_set_generic_pin_val(pin,val, pin_type);
  return;
}



int
output_callback(uint8_t pin, uint8_t pin_type)
{
  searduino_setup();
  PRINT_FUNCTION_NAME(("%d,%d",pin, pin_type));

  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return 0;
    }

  if ( (arduino_pins[pin].current_type==SEARDUINO_PIN_TYPE_DIGITAL) &&
       (get_digital_pin_mode(pin) != INPUT))
    {
      SEARD_ERROR(SEARD_ARDUINO_WRONG_PIN_MODE);
      return 0;
    }

/*   printf ("PYTHON (in C stub)   returning out[%d].val=%d     GUI\n", pin, arduino_out_pins[pin].val); */
  return   get_generic_pin_val(pin);
}



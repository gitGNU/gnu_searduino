/***** *                                                                   
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

#include "Arduino.h"
#include "arduino/pins_arduino.h"
#include "arduino/searduino_pin.h"

#include "../include/arduino/error.h"
#include "utils/print.h"
#include "utils/types.h"
#include "arduino/error.h"
#include "utils/error.h"

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




static unsigned int digitalWrite_timelimit = 20*1000;
#define genericWrite_timelimit digitalWrite_timelimit


void init_arduino_pins(void)
{
  int i ; 
  for (i=0;i<=NR_OF_ARDUINO_PINS;i++)
    {
      arduino_pins[i].mode=INPUT;
      arduino_pins[i].discard_ctr=0;
    }
  return;
}



/*
 *  
 * milli seconds
 *
 */
void 
set_Write_timelimit(unsigned int lim)
{
  digitalWrite_timelimit = lim*1000;
}

/*
 *  
 * milli seconds
 *
 */
unsigned int 
get_Write_timelimit(void)
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

/*   printf ("PYTHON (in C stub)   returning out[%d].val=%d     GUI\n", pin, arduino_out_pins[pin].val); */
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
get_generic_pin_mode(uint8_t pin, uint8_t pin_type)
{
  return arduino_pins[pin].mode;
}

int 
set_generic_pin_mode(uint8_t pin, uint8_t mode, uint8_t pin_type)
{
  if (arduino_pins[pin].type==SEARDUINO_PIN_TYPE_NONE)
    {
      arduino_pins[pin].type=pin_type;
    }

  if (arduino_pins[pin].type==pin_type)
    {
      printf ("Mode of pin %d:   %d\n", pin, mode);
      arduino_pins[pin].mode=mode; 
      return 0;
    }
  else
    {
      printf ("Failed setting Mode of pin %d:   %d  (%d | %d)\n", pin, mode, pin_type, arduino_pins[pin].type);
      exit(0);
    }
  return  -1;
}

int 
set_generic_pin_val_impl(uint8_t pin, 
			 int val, 
			 uint8_t pin_type, 
			 uint8_t exp_inout)
{
  if (arduino_pins[pin].type==SEARDUINO_PIN_TYPE_NONE)
    {
      arduino_pins[pin].type=pin_type;
    }
    
  if (arduino_pins[pin].type==SEARDUINO_PIN_TYPE_DIGITAL)
    {
      if (get_digital_pin_mode(pin) != exp_inout)
	{
	  SEARD_ERROR( SEARD_ARDUINO_WRONG_PIN_MODE);
	  return;
	}
    }

  if (arduino_pins[pin].type==pin_type)
    {
      arduino_pins[pin].val=val; 
      return 0;
    }
  return  -1;
}


int 
get_generic_pin_val(uint8_t pin, uint8_t pin_type)
{
  return arduino_pins[pin].val; 
}

int 
get_pin_val(uint8_t pin)
{
  return arduino_pins[pin].val; 
}


void 
genericWrite(uint8_t pin, uint8_t val, uint8_t pin_type)
{
  int ret;
  struct timeval  cur_time;
  struct timezone zoneData;
  long time_diff;

  searduino_setup();

  PRINT_FUNCTION_NAME(("%d,%d",pin,val));

  if (PIN_OUT_OF_RANGE(pin))
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return;
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
   *  Only calling lower layer on chage
   *
   */
  if ( get_pin_val(pin) != val)
    {
      set_generic_pin_val(pin, val, pin_type);

      /*
       *
       */
      if (time_diff<genericWrite_timelimit) 
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
	  ret = comm_generic_write_outpin(pin,val,pin_type);
	  if (ret != SEARD_ARDUINO_OK)
	    {
	      SEARD_ERROR(ret);
	      return;
	    }
	}
      //      fprintf (stderr, "  discarded calls (not on change) so far: %d\n", arduino_digital_pins[pin].discard_ctr);
    }
  else
    {
      arduino_pins[pin].discard_ctr++;
    }
  return;
}


/*
 *
 * Callback used to update in_pins
 * This fun is use (callbacked by) comm layer
 *
 */
void 
input_callback(uint8_t pin, uint8_t val, uint8_t pin_type)
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

  if ( (arduino_pins[pin].type==SEARDUINO_PIN_TYPE_DIGITAL) &&
       (get_digital_pin_mode(pin) != INPUT))
    {
      SEARD_ERROR(SEARD_ARDUINO_WRONG_PIN_MODE);
      return 0;
    }

/*   printf ("PYTHON (in C stub)   returning out[%d].val=%d     GUI\n", pin, arduino_out_pins[pin].val); */
  return   get_generic_pin_val(pin, pin_type);
}


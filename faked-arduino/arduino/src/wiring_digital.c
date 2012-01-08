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
#include "../include/error.h"
#include "utils/print.h"
#include "utils/types.h"
#include "arduino/error.h"
#include "utils/error.h"

#include "communication/digio.h"
#include "communication/comm.h"


typedef struct arduino_pin
{
  uint8_t mode;
  uint8_t val;
} arduino_pin;

static arduino_pin arduino_out_pins[NR_OF_OUT_PINS];
static arduino_pin arduino_in_pins[NR_OF_IN_PINS];


/*
 *
 * Callback used to update in_pins
 *   used in comm layer
 *
 */
void 
digin_callback(uint8_t pin, uint8_t val)
{
  searduino_setup();
  PRINT_FUNCTION_NAME(("%d,%d",pin,val));

  if (pin<0 || pin> NR_OF_IN_PINS)
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return ;
    }

  arduino_in_pins[pin].val=val;
/*   printf ("PYTHON (in C stub)   storing in[%d].val=%d  (%d)\n", pin, arduino_in_pins[pin].val, val); */
  return;
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

  if (pin<0 || pin> NR_OF_OUT_PINS)
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return 0;
    }

/*   printf ("PYTHON (in C stub)   returning out[%d].val=%d     GUI\n", pin, arduino_out_pins[pin].val); */
  return   arduino_out_pins[pin].val;
}



void pinMode(uint8_t pin, uint8_t mode)
{
  searduino_setup();
  PRINT_FUNCTION_NAME(("%d,%d",pin,mode));
  if (pin<0 || pin> NR_OF_OUT_PINS)
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return;
    }
  arduino_out_pins[pin].mode=mode;

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
  searduino_setup();
/*   printf ("PYTHON   (stub) pin:%d=%d   GUI | will set value \n" ,pin,val); */

  PRINT_FUNCTION_NAME(("%d,%d",pin,val));
  if (pin<0 || pin> NR_OF_OUT_PINS)
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return;
    }

  if ( arduino_out_pins[pin].mode == 0 )
    {
      fprintf(stderr, "Can't write to a pin with mode set 0\n");
      SEARD_ERROR(SEARD_ARDUINO_PIN_MODE_NOT_SET);
      return;
    }

  /*
   *
   *  Only calling lower layer on chage
   *
   */
  if ( arduino_out_pins[pin].val != val)
    {
      arduino_out_pins[pin].val=val;
      /*   printf ("PYTHON   (stub) pin:%d=%d   GUI | setting value \n" ,pin,val); */
      
      ret = comm_digital_write_outpin(pin,val);
      if (ret != SEARD_ARDUINO_OK)
	{
	  SEARD_ERROR(ret);
	  return;
	}
      printf ("discarded calls (not on change) so far: %d\n", discard_ctr);
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
  if (pin<0 || pin> NR_OF_IN_PINS)
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return 0;
    }

  return arduino_in_pins[pin].val;
}

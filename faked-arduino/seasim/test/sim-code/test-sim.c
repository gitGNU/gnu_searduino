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

#include <Arduino.h>

#include <stdio.h>
#include "seasim/seasim.h"


struct pin
{
  uint val;
  int mode;
  int callbacks ;
};

static struct pin pins[100];
//#define DEBUG
/* 
 * Function to register in the Searduino code
 *
 * This function will be called every time the Arduino program updates a digital output pin (on change only!)
 */
void 
my_out_sim_callback(uint8_t pin, unsigned int val, uint8_t pin_type)
{
  
#ifdef DEBUG
  printf("----->\n%s(%d,%d,%d)   (%d,%d)  callback #:%d\n",
	 __func__, pin, val, pin_type, 
	 SEARDUINO_PIN_TYPE_ANALOG, SEARDUINO_PIN_TYPE_DIGITAL,
	 pins[pin].callbacks); 
#endif

  /* skip first check, to make sure we're in sync */
  if (pins[pin].callbacks !=0 )
    {
      if (val != pins[pin].val)
	{
	  printf ("ERROR(pin[%d] %d %d   (%d)\n", 
		  pin, val, pins[pin-1].val, pins[pin].callbacks);
	  exit(1);
	}
      else
	{
	  printf ("."); fflush(stdout);
	}

    }

  pins[pin].callbacks++;

  if (pin_type == SEARDUINO_PIN_TYPE_ANALOG)
    {
      pins[pin].val = val+1;
      seasim_fake_analog_input (pin-1, pins[pin].val);
    }
  else
    {
      pins[pin].val = !val;
      seasim_fake_digital_input (pin-1, pins[pin].val);
    }

  if (pins[pin].callbacks > 5 )
    {
      printf("Time to quit\n");
      exit(0);
    }
  //  fprintf (stdout,"SIM:%d:%d:%d\n",pin_type, pin, val);
}

/* 
 * Function to register in the Searduino code
 *
 * This function will be called every time the Arduino program updates a digital mode on a digital pin (on change only!)
 */
void 
my_dm_sim_callback(uint8_t pin, uint8_t mode)
{
  pins[pin].mode=mode;
}

void
log_callback(uint8_t level, const char *str)
{
  switch (level)
    {
    case SEARDUINO_LOG_LEVEL_NONE:
      break;
    case SEARDUINO_LOG_LEVEL_INFO:
      printf ("INFO:    %s", str);
      break;
    case SEARDUINO_LOG_LEVEL_WARNING:
      printf ("WARNING: %s", str);
      break;
    case SEARDUINO_LOG_LEVEL_ERROR:
      printf ("ERROR:   %s", str);
      break;
    case SEARDUINO_LOG_SERIAL:
      printf ("SERIAL: %s", str);
      break;
    default:
      break;
    }
}


int 
sim_setup(char *ard_lib)
{
  int ret ; 

  seasim_disable_streamed_output();

  seasim_set_arduino_code_name(ard_lib);

  ret = seasim_setup();
  if (ret!=0)
    {
      return ret;
    }
  
  ret  = seasim_register_out_sim_cb(my_out_sim_callback);
  if (ret != SEARD_ARDUINO_OK)
    {
      fprintf (stderr, "Failed to register callback for Digital output (pin, val)\n");
      return ret;
    }
 

  ret  = seasim_register_dig_mode_sim_cb(my_dm_sim_callback);
  if (ret != SEARD_ARDUINO_OK)
    {
      fprintf (stderr, "Failed to register callback for Digital mode (pin, mode)\n");
      return ret;
    }

  printf ("CHECK IF REGISTRATION SUCCEEDED\n");
  seasim_register_log_cb(log_callback);

  return 0;
}




int 
main(int argc, char **argv)
{
  char *ard_code = "" ;
  int i = 0;
  int ret;


  /* Set to zer0 */
  memset(&pins,0, 100*sizeof(struct pin));
  /*  ret = seasim_i2c_add_device (50, 
			       argv[i+1]);
  */

  sim_setup("../arduino-code/arduino-code.so");

  seasim_fake_digital_input(2, 0);
  seasim_fake_analog_input(A1, 0);
  seasim_fake_digital_input(2, 1);
  seasim_fake_analog_input(A1, 3);

  if (searduino_main_entry!=NULL)
    {
      searduino_main_entry(NULL);
    }
  else
    {
      fprintf (stderr, "Couldn't find an entry point for the Arduino code.\n");
      fprintf (stderr, "This probably means you haven't provided searduino with a shared library containing Arduino code\n");
      fflush (stderr);
    }



  return 0;
}


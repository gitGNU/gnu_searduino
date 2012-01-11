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

#include "stdio.h"
#include "unistd.h"

#include <Arduino.h>
#include <pthread.h>

#include "communication/comm.h"
#include "communication/ext_io.h"
#include "arduino/setup.h"




void my_di_callback(uint8_t pin, uint8_t val)
{
  printf ("Digital in callback pin:%d:%d\n", pin, val);
}


uint8_t my_do_callback(uint8_t pin)
{
  printf ("Digital out callback pin:%d\n", pin);
  return 0;
}

/* 
 * Function to register in the Searduino code
 *
 * This function will be called every time the Arduino program updates a digital output pin (on change only!)
 */
void 
my_do_sim_callback(uint8_t pin, uint8_t val)
{
  printf ("Digital output pin set by Arduino: pin:%d:%d\n", 
	  pin, val);
}

int sim_setup(void)
{
  int ret ; 

  searduino_setup();
  
  ret  = comm_register_digout_sim_cb(my_do_sim_callback);
  if (ret != SEARD_COMM_OK)
    {
      fprintf (stderr, "Failed to register callback for Digital output (pin, val)\n");
      return ret;
    }
 

  comm_register_digout_cb(my_do_callback);
  if (ret != SEARD_COMM_OK)
    {
      fprintf (stderr, "Failed to register callback for Digital output (pin)\n");
      return ret;
    }
 
  

  return 0;
}

void* arduino_code(void *in)
{
  searduino_main();
  return NULL;
}


int main(void)
{
  pthread_t p;
  int i = 0;
  sim_setup();

  pthread_create(&p, NULL, arduino_code, NULL);

  while(1)
    {
      i++;
      usleep (1000*200);
      printf ("Set   %d %d\n", i%6,i%7);
      ext_set_dig_input(i%6,i%7);
    }
}

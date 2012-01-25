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


/* 
 * Function to register in the Searduino code
 *
 * This function will be called every time the Arduino program updates a digital output pin (on change only!)
 */
void 
my_do_sim_callback(uint8_t pin, uint8_t val)
{
  printf ("%s:%s(%d:%d)\n",__FILE__, __func__, pin, val);
  printf ("\n");
}

int sim_setup(void)
{
  int ret ; 

  searduino_disable_streamed_output();
  
  searduino_setup();
  
  ret  = comm_register_digout_sim_cb(my_do_sim_callback);
  if (ret != SEARD_COMM_OK)
    {
      fprintf (stderr, "Failed to register callback for Digital output (pin, val)\n");
      return ret;
    }
 


  return 0;
}

void* arduino_code(void *in)
{
  searduino_main();
  return NULL;
}

void* command_reader(void* in)
{
  char buf[100];
  char *tmp;
  int  pin;
  int  val;

  printf ("COMMAND READER begins\n");
    
  for (;;)
    {
/*       printf ("COMMAND READER reads\n"); */
      fgets(buf, 100, stdin);
/*       printf ("Just read: '%s'\n", buf);  */
      
      if (strncmp(buf,"pin:",4)==0)
	{
	  tmp=&buf[4];
/* 	  printf (": '%s'\n", buf);  */
/*  	  printf ("will parse: '%s'\n", tmp);  */
	  sscanf(tmp, "%d:%d", &pin, &val);
  	  printf ("SIM WILL SET pin:%d val:%d  \n", pin, val);  
	  di_callback(pin,val);
	}
      else if (strncmp(buf,"quit",4)==0)
	{
	  searduino_set_halted();
	  return ;
	}
      else if (strncmp(buf,"pause",5)==0)
	{
	  printf ("Will pause sim\n");
	  searduino_set_paused();
	}
      else if (strncmp(buf,"resume",5)==0)
	{
	  printf ("Will resume sim\n");
	  searduino_set_running();
	}
      usleep (100);
    }
}



int main(void)
{
  pthread_t arduino_thread;
  pthread_t command_thread;

  int i = 0;
  sim_setup();

  pthread_create(&arduino_thread, NULL, arduino_code, NULL);

  command_reader(NULL);

  printf ("Waiting for simulator thread to return\n");
  pthread_join(arduino_thread, NULL);

  usleep(1000*100);
  fflush(stdout);
  printf ("\n *** Simulator will now be closed ***\n");
  fflush(stdout);
  
  return 0;
}

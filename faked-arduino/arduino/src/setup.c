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
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>


#include "arduino/wiring_private.h"
#include "arduino/pins_arduino.h"
#include "searduino.h"
#include "../include/arduino/error.h"
#include "../include/arduino/setup.h"
#include "utils/print.h"
#include "utils/types.h"
#include "arduino/error.h"
#include "utils/error.h"
#include "communication/comm.h"

void     digin_callback (uint8_t pin, uint8_t val); 
void     anain_callback (uint8_t pin, unsigned val); 
uint8_t  digout_callback(uint8_t pin);
uint8_t  anaout_callback(uint8_t pin);
uint8_t  dig_mode_callback(uint8_t pin);

int searduino_exec ;


/* global */
searduino_main_ptr_ptr searduino_main_entry = NULL;

static char arduino_code[1024];

#define SEARDUIONO_SIM_RUNNING 0
#define SEARDUIONO_SIM_PAUSE   1
#define SEARDUIONO_SIM_HALTED  2


uint8_t searduino_is_paused(void)
{
  return (searduino_exec==SEARDUIONO_SIM_PAUSE);
}

uint8_t searduino_is_halted(void)
{
  return (searduino_exec==SEARDUIONO_SIM_HALTED);
}

uint8_t searduino_is_running(void)
{
  return (searduino_exec==SEARDUIONO_SIM_RUNNING);
}

void searduino_set_paused(void)
{
  searduino_exec=SEARDUIONO_SIM_PAUSE;
}

void searduino_set_running(void)
{
  searduino_exec=SEARDUIONO_SIM_RUNNING;
}

void searduino_set_halted(void)
{
  searduino_exec=SEARDUIONO_SIM_HALTED;
}

void init(void)
{
  searduino_setup();
}

int searduino_setup(void)
{
  static int already_setup = 0;
  int ret;


  if (already_setup)
    {
      return 0;
    }
  PRINT_FUNCTION_NAME_NOARGS();

  ret = load_arduino_code();
  if (ret!=0)
    {
      /* printf ("Setting up arduino code: %d\n", 	      ret); */
      return 1;
    }

  init_comm();

  init_time();

  searduino_set_running();

  already_setup=1;

  return 0;
}



static char * 
get_arduino_code_name(void)
{
  char *ret = NULL;
  /* printf ("Getting arduino lib name\n"); */
  if ((arduino_code==NULL) || 
      (arduino_code[0]=='\0'))
    {
      printf ("Could not set arduino library to use\n");
    }
  else
    {
      ret = arduino_code;
    }

  /* printf ("Returning: %s\n", ret); */
  return ret;
}



int 
searduino_set_arduino_code_name(const char* libname)
{
  
  if (libname==NULL)
    {
      printf("Resetting arduino code name");
      arduino_code[0]='\0';
      return 1;
    }
  else if (strlen(libname)>=1024)
    {
      printf ("Too big libname\n");
      printf ("Replace this with not hard coding ret value\n");
      return 1;
    }

  printf("Setting arduino code name: %s\n", libname);
  strncpy (arduino_code, libname, 1024);

  return 0;
}


int
load_arduino_code(void)
{
  void *arduino_lib;
  char *ard_lib_name;

  ard_lib_name = get_arduino_code_name();
  

  if (ard_lib_name == NULL)
    {
      /* If we have NOT been given a library name, we're a static binary */
      printf ("Statically linked code, not loading\n");
    }
  else
    {
      /* If we have been given a library name, load it */
      /* printf ("Dynamically linked code\n"); */
      arduino_lib = dlopen ((const char*)ard_lib_name, RTLD_LAZY);
      if ( arduino_lib == NULL)
	{
	  fprintf (stderr, "Couldn't open dyn lib\n");
	  return 1;
	}
      /* printf ("setup.c:  code at %p\n", arduino_lib); */
      
      searduino_main_entry = (searduino_main_ptr_ptr)dlsym(arduino_lib, "searduino_main");
      if ( searduino_main_entry == NULL)
	{
	  printf ("Couldn't find searduino_main_ptr in arduino code\n");
	  return 1;
	}
      /* printf ("setup.c:  code at %p\n", searduino_main_entry); */
    }
  return 0;
}

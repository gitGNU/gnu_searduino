/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2011-2014 Henrik Sandklef 
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
#include "ext_io.h"
#include "searduino_pin.h"
#include "searduino_log_impl.h"
#include "searduino_internal_log.h"

int searduino_exec ;
int searduino_exec_available = 0 ;

volatile static int dlopen_counter=0;

/* global */
searduino_main_ptr_ptr searduino_main_entry = NULL;

void *arduino_lib;
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
  strcpy(arduino_code, "");;
  searduino_setup();
}

int searduino_setup(void)
{
  static int already_setup = 0;
  int ret;

  /* printf("searduino_setup(void)\n"); */

  if (already_setup)
    {
      /*      printf("searduino_setup(void) returning since already setup\n"); */
      return 0;
    }
  PRINT_FUNCTION_NAME_NOARGS();
  //  printf("searduino_setup(void) init log\n");
  searduino_internal_init_log(NULL);
  
  searduino_internal_log_i("Setting up Searduino\n");
  
  searduino_internal_log_i("Loading Arduino code\n");

  //printf("searduino_setup(void) init ext io\n");
  searduino_internal_log_i("Initialising external IO module\n");
  init_ext_io();
  
  //printf("searduino_setup(void) init time\n");
  searduino_internal_log_i("Initialising time module\n");
  init_time();

  //printf("searduino_setup(void) init pins\n");
  searduino_internal_log_i("Initialising arduino pins module\n");
  init_arduino_pins();

  //printf("searduino_setup(void) set running\n");
  searduino_internal_log_i("Setting program as running\n");
  searduino_set_running();

  already_setup=1;

#ifdef USE_X11
  searduino_internal_log_i("Enabling faked hid\n");
  hid_enable_faked_hid();
#endif
  
  //printf("searduino_setup(void) returning\n");
  return 0;
}



char * 
get_arduino_code_name(void)
{
  char *ret = NULL;

  /* printf ("Getting arduino lib name\n"); */
  if ((arduino_code==NULL) || 
      (arduino_code[0]=='\0'))
    {
      /* This is not an error.... simply means we haven't set the board name yet */
      //fprintf (stderr, "Could not get the name of the arduino library to use\n");
      ret = NULL;
    }
  else
    {
      ret = arduino_code;
    }
  return ret;
}



int 
searduino_set_arduino_code_name(const char* libname)
{
  int ret;
  

  if (libname==NULL)
    {
      fprintf(stderr, "Resetting arduino code name");
      strcpy(arduino_code, "");
      return 1;
    }
  else if (strlen(libname)>=1024)
    {
      fprintf (stderr, "Too big libname\n");
      fprintf (stderr, "Replace this with not hard coding ret value\n");
      return 1;
    }

  /*
  if (strncmp(arduino_code, libname, strlen(libname)==0))
    {
      fprintf(stderr, "Not setting arduino code name: %s to the same thing   (setup.c)\n", libname);
      return 0;
    }
  */

  /* printf(" --------------------------------------- Setting arduino code name: '%s' at %u   (setup.c)\n",  */
  /* 	 libname, */
  /* 	 arduino_code);  */

  /* printf(" --------------------------------------- prev arduino code name: '%s'   (setup.c)\n",  */
  /* 	 arduino_code);  */
  

  strncpy (arduino_code, 
	   libname, 
	   1023);

  ret = load_arduino_code();
  if (ret!=0)
    {
      fprintf (stderr, "Setting up arduino code failed: %d\n", 	      ret);
      return 1;
    }

  return 0;
}



int
load_arduino_code(void)
{
  char *ard_lib_name;

  ard_lib_name = get_arduino_code_name();

  printf ("Trying to load code from %s (counter: %d)\n", ard_lib_name, dlopen_counter);

  if (ard_lib_name == NULL)
    {
      /* If we have NOT been given a library name, we're a static binary */
      fprintf (stderr, "Statically linked code, not loading\n");
    }
  else
    {
      /* If we have been given a library name, load it */
      // fprintf (stderr, "Dynamically linked code, will call dlopen(%s)\n", ard_lib_name); 
      if ( (arduino_lib!=NULL) && (dlopen_counter>0) )
	{
	  dlclose(arduino_lib);
	  dlopen_counter--;
	  usleep(1000);
	}

      arduino_lib = dlopen ((const char*)ard_lib_name, RTLD_LAZY);
      if ( arduino_lib == NULL)
	{
	  fprintf (stderr, "Couldn't open dyn lib (%s)\n", dlerror());
	  return 1;
	}
      else 
	{
	  dlopen_counter++;
	}
      /* printf ("setup.c:  code at %p\n", arduino_lib); */
      
      searduino_main_entry = (searduino_main_ptr_ptr)dlsym(arduino_lib, "searduino_main");
      if ( searduino_main_entry == NULL)
	{
	  fprintf (stderr, "Couldn't find searduino_main in arduino code\n");
	  return 1;
	}
    }
  //  printf ("Successfully loaded code from %s\n", ard_lib_name);
  return 0;
}


int
close_arduino_code(void)
{
  strcpy(arduino_code, "");

  if (arduino_lib!=NULL) 
    {
      //      fprintf(stderr, " ===========================================================CLOSING CL code? at %u  (counter: %d\n)", arduino_lib, dlopen_counter);
      if (dlopen_counter>0)
	{
	  dlclose(arduino_lib);
	  dlopen_counter--;
	}
      arduino_lib=NULL;
    }

  return 0;
}

int 
is_pausable(void)
{
  return searduino_exec_available;
}

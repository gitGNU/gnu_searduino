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

#include "utils/types.h"
#include "utils/error.h"
#include "utils/print.h"

#include "searduino_pin.h"
#include "setup.h"
#include "error.h"
#include "ext_io.h"

/*
#include "stdio.h"
#include "string.h"
#include "unistd.h"

#include "utils/types.h"
#include "utils/print.h"

#include "communication/comm.h"

#include "utils/types.h"
#include "utils/print.h"

#include "communication/comm.h"
#include "communication/error.h"

*/


/*
 *
 * File descriptor to use for all proto printouts
 *
 */
FILE* proto_stream ;


/*
 * integer to store enable/disable for stream output
 * 
 */
static uint8_t stub_output_enabled = 1;



uint8_t
ext_set_generic_input(uint8_t pin, uint8_t val, uint8_t pin_type)
{
  input_callback(pin, val, pin_type);

  DEBUG_INFO(("ext_set_generic_input  %d,%d,%d",pin,val, pin_type));
  return SEARD_SEARDUINO_OK;
}


int
ext_get_generic_output(uint8_t pin, uint8_t pin_type)
{
  DEBUG_INFO(("%d,%d",pin, pin_type));
  return output_callback(pin, pin_type);
}

uint8_t
ext_set_input(uint8_t pin, unsigned int val, uint8_t pin_type)
{
  PRINT_FUNCTION_NAME(("%d,%d,%d",pin,val, pin_type));

  input_callback(pin,val, pin_type);

  DEBUG_INFO(("%d,%d,%d",pin,val, pin_type));
  return SEARD_SEARDUINO_OK;
}

uint8_t 
ext_get_dig_output(uint8_t pin)
{
  uint8_t val ;
  PRINT_FUNCTION_NAME(("%d",pin));

  val = digout_callback(pin);


  DEBUG_INFO(("%d => %d",pin,val));
  return val;
}



unsigned int
ext_get_ana_output(uint8_t pin)
{
  unsigned int val ;
  PRINT_FUNCTION_NAME(("%d",pin));

  val = anaout_callback(pin);

  DEBUG_INFO(("%d => %d",pin,val));
  return val;
}



uint8_t 
ext_get_dig_mode(uint8_t pin)
{
  uint8_t mode ;
  PRINT_FUNCTION_NAME(("%d",pin));

  mode = dig_mode_callback(pin);

  DEBUG_INFO(("%d => %d",pin,mode));
  return mode;
}




out_to_sim_callback_ptr out_sim_callback = NULL;
dm_to_sim_callback_ptr  dm_sim_callback = NULL ;
log_to_sim_callback_ptr log_sim_callback = NULL ;



void 
init_ext_io(void)
{
  static int init;
  if (!init)
    {
      set_proto_stream(SEARDUINO_STREAM_DEFAULT); 
      init=1;
    }
}



uint8_t
set_proto_stream(FILE *f)
{
  if (f!=NULL)
    {
      proto_stream = f;
      return SEARD_SEARDUINO_OK;
    }
  return SEARD_INVALID_STREAM;
}


uint8_t
ext_register_dig_mode_sim_cb(dm_to_sim_callback_ptr cb)
{
  PRINT_FUNCTION_NAME(("%d",(int)cb));

  if (cb==NULL)
    {
      return SEARD_SEARDUINO_NULL_CALLBACK;
    }
  dm_sim_callback = cb;

  return SEARD_SEARDUINO_OK;
}

uint8_t
ext_register_log_cb(log_to_sim_callback_ptr cb)
{
  PRINT_FUNCTION_NAME(("%d",(int)cb));

  if (cb==NULL)
    {
      return SEARD_SEARDUINO_NULL_CALLBACK;
    }
  log_sim_callback = cb;

  return SEARD_SEARDUINO_OK;
}

uint8_t
ext_register_pinout_sim_cb(out_to_sim_callback_ptr cb)
{
  PRINT_FUNCTION_NAME(("%d",(int)cb));
  
  if (cb==NULL)
    {
      return SEARD_SEARDUINO_NULL_CALLBACK;
    }
  out_sim_callback = cb;
  
  return SEARD_SEARDUINO_OK;
}


uint8_t searduino_is_enable_streamed_output(void)
{
  return (stub_output_enabled!=0);
}

void
searduino_enable_streamed_output(void)
{
  stub_output_enabled = 1;
}

void
searduino_disable_streamed_output(void)
{
  stub_output_enabled = 0;
}


int 
ext_digital_set_mode(uint8_t pin, uint8_t mode)
{
  /* Make sure all is set up before continuing*/
  init_ext_io();

  /* If output enabled, print info on pin/val to stream*/
  if ( stub_output_enabled ) 
    {
      fprintf(proto_stream, "dmode:%d:%d  (in stub)\n", pin, mode); 
      fflush(proto_stream);
    }

  /*
   * Call registered listener
   *
   */
  if ( dm_sim_callback != NULL )
    {
      /* Ok, the function pointer is not NULL, 
	 so let's call it */
      dm_sim_callback(pin, mode);
    }
  return SEARD_ARDUINO_OK;
}




int 
ext_generic_write_outpin(uint8_t pin, uint8_t val, uint8_t pin_type)
{
  /* Make sure all is set up before continuing*/
  init_ext_io();

  /* If output enabled, print info on pin/val to stream*/
  if ( stub_output_enabled ) 
    {
      fprintf(proto_stream, "pin:%d:%d:%d  (in stub)\n", pin_type, pin, val); 
      fflush(proto_stream);
    }

  /*
   * Call registered listener
   *
   */
  if ( out_sim_callback != NULL )
    {
      /* Ok, the function pointer is not NULL, 
	 so let's call it */
      out_sim_callback(pin, val, pin_type);
    }
  return SEARD_ARDUINO_OK;
}
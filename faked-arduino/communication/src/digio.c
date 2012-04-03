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
#include "utils/print.h"

#include "communication/comm.h"
#include "communication/error.h"

/*
 * integer to store enable/disable for stream output
 * 
 */
static uint8_t stub_output_enabled = 1;

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
comm_digital_set_mode(uint8_t pin, uint8_t mode)
{
  /* Make sure all is set up before continuing*/
  init_comm();

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
  return SEARD_COMM_OK;
}


#ifdef OBSO
int 
comm_digital_write_outpin(uint8_t pin, uint8_t val)
{
  /* Make sure all is set up before continuing*/
  init_comm();

  /* If output enabled, print info on pin/val to stream*/
  if ( stub_output_enabled ) 
    {
      fprintf(proto_stream, "dpin:%d:%d  (in stub)\n", pin, val); 
      fflush(proto_stream);
    }

  /*
   * Call registered listener
   *
   */
  if ( do_sim_callback != NULL )
    {
      /* Ok, the function pointer is not NULL, 
	 so let's call it */
      do_sim_callback(pin, val);
    }
  return SEARD_COMM_OK;
}


int 
comm_analog_write_outpin(uint8_t pin, unsigned int val)
{
  /* Make sure all is set up before continuing*/
  init_comm();

  /* printf ("comm_analog_write_outpin()\n"); */

  /* If output enabled, print info on pin/val to stream*/
  if ( stub_output_enabled ) 
    {
      fprintf(proto_stream, "apin:%d:%d  (in stub)\n", pin, val); 
      fflush(proto_stream);
    }

  /*
   * Call registered listener
   *
   */
  if ( ao_sim_callback != NULL )
    {
      /* Ok, the function pointer is not NULL, 
	 so let's call it */
      ao_sim_callback(pin, val);
    }

  return SEARD_COMM_OK;
}
#endif


int 
comm_generic_write_outpin(uint8_t pin, uint8_t val, uint8_t pin_type)
{
  /* Make sure all is set up before continuing*/
  init_comm();

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
  return SEARD_COMM_OK;
}

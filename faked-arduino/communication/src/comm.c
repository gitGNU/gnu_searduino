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
#include "string.h"
#include "unistd.h"

#include "utils/types.h"
#include "utils/print.h"

#include "communication/comm.h"
#include "communication/error.h"



/*
 *
 * File descriptor to use for all proto printouts
 *
 */
FILE* proto_stream ;

/*
 *
 * Callback functions used througout this module
 *
 *  di_callback 
 *     used to callback layer above, 
 *     when someone updated the Arduino digital input pin
 *
 *  do_callback
 *     used to callback layer above, 
 *     when someone requests the value for an Arduino output pin
 * 
 *  do_to_sim_callback
 *     used to callback listener when an Arduino output pin is set
 *
 */
ai_callback_ptr ai_callback;
di_callback_ptr di_callback;
ao_callback_ptr ao_callback;
do_callback_ptr do_callback;
do_to_sim_callback_ptr do_sim_callback;
d_mode_callback_ptr    d_mode_callback;
ao_to_sim_callback_ptr ao_sim_callback;
a_mode_callback_ptr    a_mode_callback;




void 
init_comm(void)
{
  static int init;
  if (!init)
    {
      set_proto_stream(COMM_STREAM_DEFAULT); 
      init=1;
    }
}



uint8_t
set_proto_stream(FILE *f)
{
  if (f!=NULL)
    {
      proto_stream = f;
      return SEARD_COMM_OK;
    }
  return SEARD_INVALID_STREAM;
}


uint8_t
comm_register_digin_cb(di_callback_ptr cb)
{
  PRINT_FUNCTION_NAME(("%d",(int)cb));

  if (cb==NULL)
    {
      return SEARD_COMM_NULL_CALLBACK;
    }

  di_callback = cb;
  printf ("di cb done .... at %p\n", di_callback); 
  return SEARD_COMM_OK;
}


uint8_t
comm_register_anain_cb(ai_callback_ptr cb)
{
  PRINT_FUNCTION_NAME(("%d",(int)cb));

  if (cb==NULL)
    {
      return SEARD_COMM_NULL_CALLBACK;
    }

  ai_callback = cb;
  printf ("ai cb done .... at %p\n", ai_callback); 
  return SEARD_COMM_OK;
}



uint8_t
comm_register_digout_cb(do_callback_ptr cb)
{
  PRINT_FUNCTION_NAME(("%d",(int)cb));

  if (cb==NULL)
    {
      return SEARD_COMM_NULL_CALLBACK;
    }

/*   printf ("do cb done\n"); */
  do_callback = cb;
  return SEARD_COMM_OK;
}

uint8_t
comm_register_anaout_cb(do_callback_ptr cb)
{
  PRINT_FUNCTION_NAME(("%d",(int)cb));

  if (cb==NULL)
    {
      return SEARD_COMM_NULL_CALLBACK;
    }

  printf ("ao cb done: %p\n", cb); 
  ao_callback = cb;
  return SEARD_COMM_OK;
}

uint8_t
comm_register_digout_sim_cb(do_to_sim_callback_ptr cb)
{
  PRINT_FUNCTION_NAME(("%d",(int)cb));

  if (cb==NULL)
    {
      return SEARD_COMM_NULL_CALLBACK;
    }

  do_sim_callback = cb;

  return SEARD_COMM_OK;
}

uint8_t
comm_register_anaout_sim_cb(ao_to_sim_callback_ptr cb)
{
  PRINT_FUNCTION_NAME(("%d",(int)cb));

  if (cb==NULL)
    {
      return SEARD_COMM_NULL_CALLBACK;
    }
  ao_sim_callback = cb;

  return SEARD_COMM_OK;
}

uint8_t
comm_register_dig_mode_sim_cb(d_mode_callback_ptr cb)
{
  PRINT_FUNCTION_NAME(("%d",(int)cb));

  if (cb==NULL)
    {
      return SEARD_COMM_NULL_CALLBACK;
    }

  d_mode_callback = cb;

  return SEARD_COMM_OK;
}


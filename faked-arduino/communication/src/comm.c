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
#include "communication/read_command.h"



/*
 *
 * File descriptor to use for all proto printouts
 *
 */
FILE* proto_stream ;
di_callback_ptr di_callback;
do_callback_ptr do_callback;
do_to_sim_callback_ptr do_sim_callback;





void 
init_comm(void)
{
  static int   init;
  if (!init)
    {
      set_proto_stream(COMM_STREAM_DEFAULT); 
      init_command_reader();
      init=1;
    }
}


int 
set_proto_stream(FILE *f)
{
  proto_stream = f;
  return SEARD_COMM_OK;
}


int 
comm_register_digin_cb(di_callback_ptr cb)
{
  PRINT_FUNCTION_NAME(("%d",(int)cb));

  if (cb==NULL)
    {
      return SEARD_COMM_NULL_CALLBACK;
    }

  di_callback = cb;
/*   printf ("di cb done .... at %d\n", di_callback); */
  return SEARD_COMM_OK;
}



int 
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

int 
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


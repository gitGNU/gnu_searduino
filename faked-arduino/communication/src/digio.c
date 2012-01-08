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

int 
comm_digital_write_outpin(uint8_t pin, uint8_t val)
{
  init_comm();
  fprintf(stderr, "pin:%d:%d\n", pin, val); 
  fflush(proto_stream);

  /*
   *
   * Call listeneer
   *
   */
  if ( do_sim_callback != NULL )
    {
      do_sim_callback(pin, val);
    }

  return SEARD_COMM_OK;
}


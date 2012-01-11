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


#include "arduino/wiring_private.h"
#include "arduino/pins_arduino.h"
#include "../include/error.h"
#include "utils/print.h"
#include "utils/types.h"
#include "arduino/error.h"
#include "utils/error.h"
#include "communication/comm.h"

void digin_callback(uint8_t pin, uint8_t val); 
uint8_t  digout_callback(uint8_t pin);



void searduino_setup(void)
{
  static int already_setup = 0;
  int ret;

  if (already_setup)
    {
      return;
    }
  PRINT_FUNCTION_NAME_NOARGS();

  printf ("Registering callbacks....\n");

  init_comm();
  ret = comm_register_digin_cb(digin_callback);
  if (ret != SEARD_COMM_OK)
    {
      fprintf(stderr, "Failed to register di callback");
    }

  ret = comm_register_digout_cb(digout_callback);
  if (ret != SEARD_COMM_OK)
    {
      fprintf(stderr, "Failed to register do callback");
    }

  already_setup=1;
}


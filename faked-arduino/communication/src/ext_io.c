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

#include "communication/comm.h"

int ext_set_dig_input(uint8_t pin, uint8_t val)
{
  PRINT_FUNCTION_NAME(("%d,%d",pin,val));
  di_callback(pin,val);
  DEBUG_INFO(("%d,%d",pin,val));
  return SEARD_COMM_OK;
}

uint8_t ext_get_dig_output(uint8_t pin)
{
  uint8_t val ;
  PRINT_FUNCTION_NAME(("%d",pin));
/*   printf ("Will return using cb at %d\n", do_callback); */
  val = do_callback(pin);
/*   printf ("GUI Will return using cb at %d    pin:%d val=%d\n", do_callback, pin, val); */
  DEBUG_INFO(("%d => %d",pin,val));
  return val;
}



uint8_t ext_get_dig_mode(uint8_t pin)
{
  uint8_t mode ;
  PRINT_FUNCTION_NAME(("%d",pin));
/*   printf ("Will return using cb at %d\n", do_callback); */
  mode = d_mode_callback(pin);
/*   printf ("GUI Will return using cb at %d    pin:%d val=%d\n", do_callback, pin, val); */
  DEBUG_INFO(("%d => %d",pin,mode));
  return mode;
}




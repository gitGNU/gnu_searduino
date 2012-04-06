/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2012 Henrik Sandklef 
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

#include <stdio.h>
#include "i2c_loader.h"

int i2c_setup(int device_nr)
{
  fprintf (stderr, "***  I2C CODE  %s:%d:%s(%d)\n", 
	  __FILE__, __LINE__, __func__, 
	  device_nr);
  
  if (device_nr > 10 ) 
    {
      fprintf (stderr, "\tdevice_nr > 10, returning 0\n");
      return 0;
    }
  

  fprintf (stderr, "\tdevice_nr < 10, returning 1\n");
  return 1;
}

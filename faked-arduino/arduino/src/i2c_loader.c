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

#include <dlfcn.h>
#include "i2c_loader.h"
#include <stdio.h>

int  i2c_add_device (unsigned int device_nr, 
                     const char  *setup_fun)
{
  void         *i2c_code;
  i2c_setup_ptr i2c_setup_fun;
  int           ret;

  if (setup_fun==NULL)
    {
      fprintf (stderr, "Couldn't open dyn lib since none (NULL) was provided \n");
      return 1;
    }

  if ( device_nr == 0)
    {
      fprintf (stderr, "Couldn't open dyn lib since device number is 0 \n");
      return 2;
    }

  i2c_code = dlopen (setup_fun, RTLD_LAZY);
  if ( setup_fun == NULL)
    {
      fprintf (stderr, "Couldn't open dyn lib '%s' \n", setup_fun);
      return 3;
    }
  
  i2c_setup_fun = (i2c_setup_ptr)dlsym(i2c_code, "i2c_setup");
  if ( i2c_setup_fun == NULL)
    {
      fprintf (stderr, "Couldn't find setup in i2c code : %s\n", setup_fun);
      return 4;
    }
  
  ret = i2c_setup_fun(device_nr);
  if ( ret != 0 )
    {
      fprintf (stderr, "Couldn't call i2c_setup properly\n");
      dlclose(i2c_code);
      return 5;
    }

  ret = dlclose(i2c_code);
  if ( ret != 0 )
    {
      fprintf (stderr, "Couldn't close i2c code properly\n");
      ret = 6;
    }


  fprintf (stderr, "I2C code seems to work :)\n");
  return ret;
}


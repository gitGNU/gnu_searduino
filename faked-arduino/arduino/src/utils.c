/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2011, 2012, 2015 Henrik Sandklef 
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

#ifdef DEAD_CODE

#include "stdio.h"
#include "utils/types.h"


int 
seard_print_pin_mode(uint8_t pin, uint8_t mode)
{
  init_proto();
  fprintf(proto_stream, "pinMode(%d,%d)\n", pin, mode);
}


void seard_prot_get_status()
{
  int i ;
  init_proto();
  
  for (i=0;i<get_nr_of_out_pins();i++)
    {
      digitalRead(i);
      digitalReadMode(i);
    }
}


int
ext_digital_read(uint8_t pin)
{
  init_proto();
  return ;
}

int digitalReadMode(uint8_t pin)
{
  int ret;
  if (pin<0 || pin> NR_OF_IN_PINS)
    {
      SEARD_ERROR(SEARD_ARDUINO_OUT_OF_BOUND);
      return;
    }

  ret = ext_digital_write(pin,arduino_in_pins[pin].mode);
  if (ret != SEARD_ARDUINO_OK)
    {
      SEARD_ERROR(ret);
    }

  return arduino_in_pins[pin].mode;
}



uint8_t 
get_nr_of_in_pins()
{
  return NR_OF_IN_PINS;
}

uint8_t 
get_nr_of_out_pins()
{
  return NR_OF_OUT_PINS;
}

#else

typedef int stupid_typedef_to_silent_iso_cc;
#endif /* DEAD_CODE */


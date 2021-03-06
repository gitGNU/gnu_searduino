/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2012, 2015 Henrik Sandklef 
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

#include "hid-generic.h"
#include "hid-x11.h"

int hid_initialise_hid(void)
{
#ifdef USE_X11
  hid_x11_initilise_hid();
#endif  
  return 0;
}

int hid_enable_faked_hid(void)
{
#ifdef USE_X11
  hid_x11_enable_faked_hid();
#endif  
  return 0;
}


int hid_disable_faked_hid(void)
{
#ifdef USE_X11
  hid_x11_disable_faked_hid();
#endif  
  return 0;
}



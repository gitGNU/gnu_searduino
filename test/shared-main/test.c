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

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define DLERR(d)  if(d==0) { printf ("DL Error:  %s\n", dlerror());  exit(1); }


typedef int (*main_ptr)(void); 
void* (*searduino_setup_ptr)(void);
void* (*set_dig_input)(int,int);
int   (*get_dig_output)(int);

extern searduino_main_ptr_ptr searduino_main_entry;

int main(int argc, char **argv)
{

  searduino_set_arduino_code_name("libtest.so");
  
  searduino_setup();
  searduino_main_entry(NULL);

  return 0;
}

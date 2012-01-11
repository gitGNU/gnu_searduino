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

int main(int argc, char **argv)
{

  void *dlib = dlopen ((const char*)"libtest.so", RTLD_NOW);
  printf ("dlib:         %d \n", (int)dlib);
  DLERR(dlib);

  searduino_setup_ptr  = dlsym (dlib, "searduino_setup");
  printf ("setup      %d \n",  (int)searduino_setup_ptr);
  DLERR(searduino_setup_ptr); 
  
  main_ptr main_fun  = dlsym (dlib, "searduino_main");
  printf ("main_fun      %d \n",  (int)main_fun);
  DLERR(main_fun); 

  searduino_setup_ptr();


  set_dig_input = dlsym (dlib, "ext_set_dig_input");
  printf ("set_dig_input %d \n",  (int)set_dig_input);
  DLERR(set_dig_input); 

  get_dig_output = dlsym (dlib, "ext_get_dig_output");
  printf ("get_dig_output %d \n",  (int)get_dig_output);
  DLERR(get_dig_output); 

  main_fun(); 

  return 0;
}

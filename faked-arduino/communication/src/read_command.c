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

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "utils/include/types.h"
#include "../include/comm.h"
#include "../include/read_command.h"


void init_command_reader(void)
{
  pthread_t p;
  if (enable_command_reader)
    {
      pthread_create(&p, NULL, command_reader, NULL);
    }
  return;
}


void* command_reader(void* in)
{
  char buf[100];
  char *tmp;
  int  pin;
  int  val;

  printf ("COMMAND READER begins\n");
    
  for (;;)
    {
/*       printf ("COMMAND READER reads\n"); */
      fgets(buf, 100, stdin);
/*       printf ("Just read: '%s'\n", buf);  */
      
      if (strncmp(buf,"pin:",4)==0)
	{
	  tmp=&buf[4];
/* 	  printf (": '%s'\n", buf);  */
/*  	  printf ("will parse: '%s'\n", tmp);  */
	  sscanf(tmp, "%d:%d", &pin, &val);
  	  printf ("SET pin:%d val:%d  \n", pin, val);  
	  di_callback(pin,val);
	}

      usleep (1000);
    }
}


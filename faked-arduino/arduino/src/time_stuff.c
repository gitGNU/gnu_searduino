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

#include "config.h"
#ifdef HAVE_NANOSLEEP
#define _POSIX_C_SOURCE 199309L
#include <time.h>
#endif

#include "utils/print.h"
#include "time_stuff.h"
#include <sys/time.h>
#include <unistd.h>


static struct timeval arduino_exec_start_time;

#ifdef HAVE_NANOSLEEP
int seard_sleep(int del) {
  struct timespec ts;
  ts.tv_sec  = del/1000000;
  ts.tv_nsec = del- ts.tv_sec * 1000000;
  return nanosleep(&ts, NULL);
}
#else
#ifdef HAVE_USLEEP
int seard_sleep(int del) {
  return usleep(del);
}
#else
#error missing sleep 
#endif /* HAVE_USLEEP */
#endif /* HAVE_NANOSLEEP */



void init_time(void)
{
  PRINT_FUNCTION_NAME_NOARGS();
  gettimeofday( &arduino_exec_start_time, NULL);
  return ;
}

unsigned long 
micros(void)
{
   struct timeval current_time;
   gettimeofday( &current_time, NULL);

   return ((current_time.tv_sec-arduino_exec_start_time.tv_sec) * 1000000 +
	   (current_time.tv_usec-arduino_exec_start_time.tv_usec));
}

unsigned long 
millis(void)
{
   struct timeval current_time;
   gettimeofday( &current_time, NULL);

   return ((current_time.tv_sec-arduino_exec_start_time.tv_sec) * 1000 +
	   (current_time.tv_usec-arduino_exec_start_time.tv_usec)/1000);
}

void 
delay(unsigned long del)
{
  PRINT_FUNCTION_NAME(("%lu",del));
  seard_sleep(del);
}

void 
delayMicroseconds(unsigned long del)
{
  PRINT_FUNCTION_NAME(("%lu",del));
  seard_sleep(del);
}

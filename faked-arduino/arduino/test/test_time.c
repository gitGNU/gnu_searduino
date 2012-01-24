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

#include "time_stuff.h"
#include <stdlib.h>
#include <stdio.h>

int fail_ctr=0;
int succ_ctr=0;
#define DELAY1 10000
#define DELAY2 100000

void test_micros(void)
{
  int i ;
  unsigned long micros_since_start;
  unsigned long expected_time;
  unsigned long prev_rounds_time;
  int percentage;
  double diff;
  
  init_time();


  for (i=1;i<200;i++)
    {
      usleep (DELAY1);
      micros_since_start = micros();
      expected_time +=  DELAY1;

      diff = (double)labs(micros_since_start - expected_time)  /
	(double)micros_since_start ;
      percentage = (int)(diff * 100);

      if (percentage < 3)
	{
	  succ_ctr++;
      }
      else
	{
	  printf ("Fail 1....\n");
	  fail_ctr++;
	}
    }


  for (i=1;i<20;i++)
    {
      usleep (DELAY2);
      micros_since_start = micros();

      expected_time +=  DELAY2;

      diff = (double)labs(micros_since_start - expected_time)  /
	(double)micros_since_start ;
      percentage = (int)(diff * 100);

      if (percentage < 3)
	{
	  succ_ctr++;
      }
      else
	{
	  printf ("Fail 2....%d \n", percentage);
	  fail_ctr++;
	}
    }
}


int main(void)
{
  test_micros();

  printf ("Fails:       %d\n", fail_ctr);
  printf ("Successes:   %d\n", succ_ctr);

  return 0;
}

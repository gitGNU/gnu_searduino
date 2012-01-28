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


unsigned long 
micros(void);



//#include "time_stuff.h"
#include <stdlib.h>
#include <stdio.h>

int fail_ctr=0;
int succ_ctr=0;
#define DELAY1 1000*10
#define DELAY2 1000*100

#define MS_DELAY1 10
#define MS_DELAY2 100

void test_micros(void)
{
  int i ;
  unsigned long micros_since_start;
  unsigned long expected_time = 0;
  unsigned long prev_rounds_time;
  int percentage;
  double diff;
  
  init_time();


  for (i=1;i<5;i++)
    {
      usleep (DELAY1);

      micros_since_start = micros();
      expected_time +=  DELAY1;

      diff = labs(micros_since_start - expected_time);

      percentage = (diff ) / DELAY1;

      if (percentage<20)
	{
	  succ_ctr++;
      }
      else
	{
	  printf ("Fail 1.... %d\n", percentage);
	  fail_ctr++;
	}
    }


  for (i=1;i<5;i++)
    {
      usleep (DELAY2);
      micros_since_start = micros();

      expected_time +=  DELAY2;

      diff = micros_since_start - expected_time ;

      percentage = ( diff ) / DELAY2;

      if (percentage < 50)
	{
	  succ_ctr++;
      }
      else
	{
	  printf ("Fail 2....%d %d  %f  \n", i, percentage, diff);
	  fail_ctr++;
	}
    }
}

void test_delay(void)
{
  int i ;
  int percentage;
  double diff;

  struct timeval start_time;
  struct timeval current_time;

  for (i=1;i<200;i++)
    {
      gettimeofday( &start_time, NULL);
      delay (MS_DELAY1);
      gettimeofday( &current_time, NULL);

      diff = ((current_time.tv_sec  - start_time.tv_sec) * 1000000 +
	      (current_time.tv_usec - start_time.tv_usec));
      
      percentage = (diff / (MS_DELAY1*1000) - 1)*100; 

/*       printf ("perc: %d \n", percentage); */

      if (percentage>4)
	{
	  fail_ctr++;
	}
      else
	{
	  succ_ctr++;
	}

    }
}


int main(void)
{
  test_micros();

  test_delay();

  printf ("Fails:       %d\n", fail_ctr);
  printf ("Successes:   %d\n", succ_ctr);

  return 0;
}

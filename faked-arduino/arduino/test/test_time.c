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
#include <check.h>
#include <stdlib.h>
#include <stdio.h>


#define DELAY1 1000*10
#define DELAY2 1000*100

#define MS_DELAY1 10
#define MS_DELAY2 100

START_TEST (test_micros)
{
  int i ;
  unsigned long micros_since_start;
  unsigned long expected_time = 0;
  unsigned long prev_rounds_time;
  unsigned long diff;
  
  init_time();


  for (i=1;i<5;i++)
    {
      usleep (DELAY1);

      micros_since_start = micros();
      expected_time +=  DELAY1;

      diff = labs(micros_since_start - expected_time)  ;
      
      printf ("Loop: %d  diff: %.6ld     micros:%.8ld    expected_time:%ld\n", 
	      i, diff, micros(), expected_time);
      fail_if(diff > 8000, "sleeping DELAY1 failed");
    }
  
  
  for (i=1;i<5;i++)
    {
      usleep (DELAY2);
      micros_since_start = micros();
      
      expected_time +=  DELAY2;

      diff = micros_since_start - expected_time ;
      fail_if(diff > 10000, "sleeping DELAY2 failed");

    }
}
END_TEST

START_TEST (test_delay)
{
  int i ;
  long diff;

  struct timeval start_time;
  struct timeval current_time;

  for (i=1;i<10;i++)
    {
      gettimeofday( &start_time, NULL);
      delay (MS_DELAY1);
      gettimeofday( &current_time, NULL);

      diff = ((current_time.tv_sec  - start_time.tv_sec) * 1000000 +
	      (current_time.tv_usec - start_time.tv_usec));
      
      printf ("Loop: %d  diff: %.6ld     \n", 
	      i, diff);
      fail_if(diff  > 15000, "Sleeping DELAY2 failed");
    }
}
END_TEST



START_TEST (test_delayMicroseconds)
{
  int i ;
  long diff;

  struct timeval start_time;
  struct timeval current_time;

  for (i=1;i<10;i++)
    {
      gettimeofday( &start_time, NULL);
      delayMicroseconds (DELAY1);
      gettimeofday( &current_time, NULL);

      diff = ((current_time.tv_sec  - start_time.tv_sec) * 1000000 +
	      (current_time.tv_usec - start_time.tv_usec));
      
      printf ("Loop: %d  diff: %.6ld     \n", 
	      i, diff);
      fail_if(diff  > 15000, "Sleeping DELAY1 failed");
    }
}
END_TEST




Suite *
buffer_suite(void) {
  Suite *s = suite_create("Time_Fuctions");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase (s, tc_core);

  tcase_add_test(tc_core, test_micros);
  tcase_add_test(tc_core, test_delay);
  tcase_add_test(tc_core, test_delayMicroseconds);

  return s;
}

int main(void)
{
  int num_failed;
  //  test_micros();

  Suite *s = buffer_suite();
  SRunner *sr = srunner_create(s);

  searduino_set_arduino_code_name("../../../extensions/arduino-lib/.libs/libarduino-code.so");


  srunner_run_all(sr, CK_NORMAL);
  num_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

  /*   test_delay(); */

  return 0;
}

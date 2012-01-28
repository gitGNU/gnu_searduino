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

#include <check.h>
#include "time_stuff.h"
#include <stdlib.h>
#include <stdio.h>


int fail_ctr=0;
int succ_ctr=0;
#define DELAY1 10000
#define DELAY2 100000

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
      fail_if(diff > 5000, "sleeping DELAY1 failed");
    }
  
  
  for (i=1;i<5;i++)
    {
      usleep (DELAY2);
      micros_since_start = micros();
      
      expected_time +=  DELAY2;
      
      diff = labs(micros_since_start - expected_time) ;
      
      printf ("Loop: %d  diff: %.6ld     micros:%.8ld    expected_time:%ld\n", 
	      i, diff, micros(), expected_time);
      fail_if(diff  > 15000, "Sleeping DELAY2 failed");
    }
}
END_TEST



Suite *
buffer_suite(void) {
  Suite *s = suite_create("Buffer");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase (s, tc_core);

  tcase_add_test(tc_core, test_micros);

  return s;
}

int main(void)
{
  int num_failed;
  //  test_micros();

  Suite *s = buffer_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  num_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

  printf ("Fails:       %d\n", fail_ctr);
  printf ("Successes:   %d\n", succ_ctr);

  return 0;
}

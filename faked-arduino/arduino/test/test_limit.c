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


#include "Arduino.h"
#include "time_stuff.h" 
#include "wiring_private.h" 
#include <check.h>
#include <stdlib.h>
#include <stdio.h>


#define PINS_TO_TEST_FIRST 1
#define PINS_TO_TEST_LAST  10

START_TEST (test_discard)
{
  int i ;

  for (i=PINS_TO_TEST_FIRST;i<PINS_TO_TEST_LAST;i++)
    {
      pinMode(i,OUTPUT);
    }
  
  for (i=PINS_TO_TEST_FIRST;i<PINS_TO_TEST_LAST;i++)
    {
      fail_if(get_discard_ctr(i)!=0);
    }
  
  
  for (i=PINS_TO_TEST_FIRST;i<PINS_TO_TEST_LAST;i++)
    {
      /* Alternate setting (same per pin though) 
	 to make sure it works for both setting to 1 and 0 */
      digitalWrite(i,(i%2));
      digitalWrite(i,(i%2));
      digitalWrite(i,(i%2));
    }
  
  for (i=PINS_TO_TEST_FIRST;i<PINS_TO_TEST_LAST;i++)
    {
      printf ("Discard ctr pin %d: %d ? %d\n", 
	      i, get_discard_ctr(i), (2+(i+1)%2));
      fail_if(get_discard_ctr(i)!=(2+(i+1)%2));
    }
}
END_TEST


int test_do_to_sim_callback_ctr;
void test_do_to_sim_callback(uint8_t pin, uint8_t val, int pin_type)
{
  test_do_to_sim_callback_ctr++;
  return ;
}



START_TEST (test_limit)
{
  int i ;

  fail_if(get_write_timelimit()!=20);

  test_do_to_sim_callback_ctr=0;
  seasim_register_out_sim_cb(test_do_to_sim_callback);

  pinMode(1,OUTPUT);
  
  /* Alternate setting (same per pin though) 
     to make sure it works for both setting to 1 and 0 */
  digitalWrite(1,1);
  digitalWrite(1,0);
  digitalWrite(1,1);  
  fail_if(test_do_to_sim_callback_ctr!=1);

  set_write_timelimit(0);
  test_do_to_sim_callback_ctr=0;
  usleep(1000);
  digitalWrite(1,0);
  usleep(1000);
  digitalWrite(1,1);
  usleep(1000);
  digitalWrite(1,0);
  fail_if(test_do_to_sim_callback_ctr!=3);

  set_write_timelimit(200000);
  test_do_to_sim_callback_ctr=0;
  usleep(1000);
  digitalWrite(1,0);
  usleep(1000);
  digitalWrite(1,1);
  usleep(1000);
  digitalWrite(1,0);
  fail_if(test_do_to_sim_callback_ctr!=0);
}
END_TEST



Suite *
buffer_suite(void) {
  Suite *s = suite_create("Limit_Fuctions");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase (s, tc_core);

  tcase_add_test(tc_core, test_discard);
  tcase_add_test(tc_core, test_limit);

  return s;
}

int main(void)
{
  int num_failed;
  //  test_micros();

  Suite *s = buffer_suite();
  SRunner *sr = srunner_create(s);

  seasim_set_board_name("uno");
  searduino_set_arduino_code_name("../../../extensions/arduino-lib/.libs/libarduino-code.so");


  srunner_run_all(sr, CK_NORMAL);
  num_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

  /*   test_delay(); */

  return 0;
}

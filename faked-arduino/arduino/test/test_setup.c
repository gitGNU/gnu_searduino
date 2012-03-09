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
#include <stdlib.h>
#include <stdio.h>


START_TEST (test_setup)
{
  init();

  fail_if(searduino_is_running()==0);
  fail_if(searduino_is_paused()==1);
  fail_if(searduino_is_halted()==1);

  searduino_set_halted();
  fail_if(searduino_is_running()==1);
  fail_if(searduino_is_paused()==1);
  fail_if(searduino_is_halted()==0);

  searduino_set_paused();
  fail_if(searduino_is_running()==1);
  fail_if(searduino_is_paused()==0);
  fail_if(searduino_is_halted()==1);

  searduino_set_running();
  fail_if(searduino_is_running()==0);
  fail_if(searduino_is_paused()==1);
  fail_if(searduino_is_halted()==1);

}
END_TEST


Suite *
buffer_suite(void) {
  Suite *s = suite_create("Setup_Fuctions");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase (s, tc_core);

  printf ("Testing setup functions in faked-arduino/arduino\n");

  tcase_add_test(tc_core, test_setup);

  return s;
}

int main(void)
{
  int num_failed;
  //  test_micros();

  searduino_set_arduino_code_name("../../../extensions/arduino-lib/.libs/libarduino-code.so");

  Suite *s = buffer_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  num_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

  /*   test_delay(); */

  return 0;
}

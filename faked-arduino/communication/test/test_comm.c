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
#include "types.h"
#include "comm.h"

int callbacked_pin ;
int callbacked_val ;

void test_di_callback(uint8_t pin, uint8_t val)
{
  printf ("test_di_callback(%d, %d)\n", 
	  pin, val);

  callbacked_pin = pin;
  callbacked_val = (val!=0);
  return ;
}

uint8_t test_do_callback(uint8_t pin)
{
  printf ("test_do_callback(%d)\n", 
	  pin);

  return callbacked_val;
}

void test_do_to_sim_callback(uint8_t pin, uint8_t val)
{
  printf ("test_do_to_sim__callback(%d, %d)\n", 
	  pin, val);
  callbacked_pin = pin;
  callbacked_val = val;


  return ;
}


START_TEST (test_comm)
{
  init_ext_io();

  fail_if(set_proto_stream(NULL)!=
	  SEARD_INVALID_STREAM);

}
END_TEST


START_TEST (test_di)
{

  fail_if (seasim_register_out_sim_cb(NULL)!=
	   SEARD_COMM_NULL_CALLBACK);	   

  fail_if (seasim_register_out_sim_cb(test_do_to_sim_callback)!=
	   SEARD_COMM_OK);	   

  callbacked_pin = -1;
  callbacked_val = -1;

  callbacked_pin = -1;
  callbacked_val = -1;

}
END_TEST


Suite *
buffer_suite(void) {
  Suite *s = suite_create("Setup_Fuctions");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase (s, tc_core);

  printf ("Testing setup functions in faked-arduino/arduino\n");

  tcase_add_test(tc_core, test_comm);
  tcase_add_test(tc_core, test_di);

  return s;
}

int main(void)
{
  int num_failed;
  //  test_micros();

  Suite *s = buffer_suite();
  SRunner *sr = srunner_create(s);

  searduino_set_arduino_code_name("libarduino-code.so.0");

  srunner_run_all(sr, CK_NORMAL);
  num_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

  /*   test_delay(); */

  return 0;
}

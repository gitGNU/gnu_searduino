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
  init_comm();

  fail_if(set_proto_stream(NULL)!=
	  SEARD_INVALID_STREAM);

}
END_TEST


START_TEST (test_di)
{

  fail_if (comm_register_digin_cb(NULL)!=
	   SEARD_COMM_NULL_CALLBACK);

  fail_if (comm_register_digin_cb(test_di_callback)!=
	   SEARD_COMM_OK);

  fail_if (comm_register_digout_sim_cb(NULL)!=
	   SEARD_COMM_NULL_CALLBACK);	   

  fail_if (comm_register_digout_sim_cb(test_do_to_sim_callback)!=
	   SEARD_COMM_OK);	   

  callbacked_pin = -1;
  callbacked_val = -1;

  ext_set_dig_input(2, 1);
  fail_if(callbacked_pin!=2);
  fail_if(callbacked_val!=1);

  ext_set_dig_input(3, 10);
  fail_if(callbacked_pin!=3);
  fail_if(callbacked_val!=1);
  
  callbacked_pin = -1;
  callbacked_val = -1;

  comm_digital_write_outpin(3, 1);
  fail_if(callbacked_pin!=3);
  fail_if(callbacked_val!=1);

}
END_TEST

START_TEST (test_do)
{

  fail_if (comm_register_digout_cb(NULL)!=
	   SEARD_COMM_NULL_CALLBACK);

  fail_if (comm_register_digout_cb(test_do_callback)!=
	   SEARD_COMM_OK);

  callbacked_val = 1;
  fail_if (ext_get_dig_output(3)!=1);
  callbacked_val = 0;
  fail_if (ext_get_dig_output(3)!=0);

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
  tcase_add_test(tc_core, test_do);

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

  /*   test_delay(); */

  return 0;
}

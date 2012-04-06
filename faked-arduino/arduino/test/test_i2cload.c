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


#include "i2c_loader.h"
#include <check.h>


START_TEST (test_faulty_i2c)
{
  int ret ; 
  
  ret = i2c_add_device (0, "dummy value");
  fail_if(ret!=2, "Failed to yield error on faulty i2c code");
  
  ret = i2c_add_device (1, NULL);
  fail_if(ret!=1, "Failed to yield error on NULL i2c code");
}
END_TEST

START_TEST (test_working_i2c)
{
  int ret ; 
  
  ret = i2c_add_device (5, "./.libs/libi2c.so");
  fail_if(ret==0, "Failed to yield error on faulty i2c code (dev nr 5). Got %d", ret);

  ret = i2c_add_device (50, "./.libs/libi2c.so");
  fail_if(ret!=0, "Failed to load i2c code (dev nr 50). Got %d ", ret);
}
END_TEST


Suite *
buffer_suite(void) {
  Suite *s = suite_create("I2C test");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase (s, tc_core);
  
  //  tcase_add_test(tc_core, test_faulty_i2c);
  tcase_add_test(tc_core, test_working_i2c);
  
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
}

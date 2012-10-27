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


#include "boards.h"
#include "searduino_pin.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>


const char *MY_BOARD      = "leonardo";



START_TEST (test_leo_digpwm)
{
  int ret;
  const int TEST_DIG_PIN = 3 ;

  set_board_name(MY_BOARD);

  board_setup();


  /*
   *
   *   digtalWrite
   *
   */ 

  /* Positive tests (as digital output pin) */
  pinMode(TEST_DIG_PIN, OUTPUT);

  digitalWrite(TEST_DIG_PIN, HIGH);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != HIGH);

  digitalWrite(TEST_DIG_PIN, LOW);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != LOW);  

  /* Negative tests (as digital input pin) */
  pinMode(TEST_DIG_PIN, INPUT);

  digitalWrite(TEST_DIG_PIN, HIGH);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != LOW);

  digitalWrite(TEST_DIG_PIN, LOW);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != LOW);  

  /*
   *
   *   digitalRead
   *
   */ 

  /* Positive tests (as digital input pin) */
  pinMode(TEST_DIG_PIN, INPUT);

  ext_set_generic_input(TEST_DIG_PIN, LOW, SEARDUINO_PIN_TYPE_DIGITAL);
  fail_if( digitalRead(TEST_DIG_PIN) != LOW);

  ext_set_generic_input(TEST_DIG_PIN, HIGH, SEARDUINO_PIN_TYPE_DIGITAL);
  fail_if( digitalRead(TEST_DIG_PIN) != HIGH);

}
END_TEST


START_TEST (test_leo_digana)
{
  int ret;
  const int TEST_DIG_PIN = 6 ;

  set_board_name(MY_BOARD);

  board_setup();


  /*
   *
   *   digtalWrite
   *
   */ 

  /* Positive tests (as digital output pin) */
  pinMode(TEST_DIG_PIN, OUTPUT);

  digitalWrite(TEST_DIG_PIN, HIGH);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != HIGH);

  digitalWrite(TEST_DIG_PIN, LOW);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != LOW);  

  /* Negative tests (as digital input pin) */
  pinMode(TEST_DIG_PIN, INPUT);

  digitalWrite(TEST_DIG_PIN, HIGH);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != LOW);

  digitalWrite(TEST_DIG_PIN, LOW);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != LOW);  

  /*
   *
   *   digitalRead
   *
   */ 

  /* Positive tests (as digital input pin) */
  pinMode(TEST_DIG_PIN, INPUT);

  ext_set_generic_input(TEST_DIG_PIN, LOW, SEARDUINO_PIN_TYPE_DIGITAL);
  fail_if( digitalRead(TEST_DIG_PIN) != LOW);

  ext_set_generic_input(TEST_DIG_PIN, HIGH, SEARDUINO_PIN_TYPE_DIGITAL);
  fail_if( digitalRead(TEST_DIG_PIN) != HIGH);

  /*
   *
   *   analogWrite
   *
   */ 

  /* Positive tests (as analog output pin) */
  pinMode(TEST_DIG_PIN, OUTPUT);

  analogWrite(TEST_DIG_PIN, -10);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != 0);

  analogWrite(TEST_DIG_PIN, 0);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != 0);

  analogWrite(TEST_DIG_PIN, 100);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != 100);

  analogWrite(TEST_DIG_PIN, 254);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != 254);

  analogWrite(TEST_DIG_PIN, 255);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != 255);

  analogWrite(TEST_DIG_PIN, 1000);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != 255);


}
END_TEST



Suite *
buffer_suite(void) {
  Suite *s = suite_create("Boards_Fuctions");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase (s, tc_core);


  searduino_set_arduino_code_name("../../../extensions/arduino-lib/.libs/libarduino-code.so");
  tcase_add_test(tc_core, test_leo_digpwm);
  tcase_add_test(tc_core, test_leo_digana);
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


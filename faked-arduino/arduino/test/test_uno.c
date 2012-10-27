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


const char *MY_UNO      = "uno";


START_TEST (test_uno_11)
{
  int ret;

  set_board_name(MY_UNO);

  board_setup();

  #define TEST_DIG_PIN 11

  /*
   * PWM and Digital pin 11
   *
   */ 

  /* Positive tests (as digital output pin) */
  pinMode(TEST_DIG_PIN,OUTPUT);

  digitalWrite(TEST_DIG_PIN, HIGH);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != HIGH);

  digitalWrite(TEST_DIG_PIN, LOW);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != LOW);  

  /* Positive tests (as digital input pin) */
  pinMode(TEST_DIG_PIN,INPUT);

  digitalWrite(TEST_DIG_PIN, HIGH);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != LOW);

  digitalWrite(TEST_DIG_PIN, LOW);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != LOW);  

  /* Positive tests (as digital output pin) */
  pinMode(TEST_DIG_PIN,OUTPUT);

  /* According to spec, this should result in a digitalWrite (LOW) */
  analogWrite(TEST_DIG_PIN, 0);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != LOW);  

  /* According to spec, this should result in a digitalWrite (HIGH), 
     but Seardino stores this as 255 since there's no timer in searduino */
  analogWrite(TEST_DIG_PIN, 255);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != 255);  

  /* According to spec, this should result in value = 120 */
  analogWrite(TEST_DIG_PIN, 120);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != 120);  

}
END_TEST

START_TEST (test_uno_13)
{
  int ret;

  set_board_name(MY_UNO);

  board_setup();

  #define TEST_DIG_PIN2 13

  /*
   * Digital pin 13 (no pwm)
   *
   */ 

  /* Positive tests (as digital output pin) */
  pinMode(TEST_DIG_PIN2,OUTPUT);

  digitalWrite(TEST_DIG_PIN2, HIGH);
  fail_if(get_generic_pin_val(TEST_DIG_PIN2) != HIGH);

  digitalWrite(TEST_DIG_PIN2, LOW);
  fail_if(get_generic_pin_val(TEST_DIG_PIN2) != LOW);  

  /* Positive tests (as digital input pin) */
  pinMode(TEST_DIG_PIN2,INPUT);

  digitalWrite(TEST_DIG_PIN2, HIGH);
  fail_if(get_generic_pin_val(TEST_DIG_PIN2) != LOW);

  digitalWrite(TEST_DIG_PIN2, LOW);
  fail_if(get_generic_pin_val(TEST_DIG_PIN2) != LOW);  

  /* Positive tests (as digital output pin) */
  pinMode(TEST_DIG_PIN2,OUTPUT);

  /* According to spec, this should result in a digitalWrite (LOW) */
  analogWrite(TEST_DIG_PIN2, 0);
  fail_if(get_generic_pin_val(TEST_DIG_PIN2) != LOW);  

  /* According to spec, this should result in a digitalWrite (HIGH) */
  analogWrite(TEST_DIG_PIN2, 255);
  fail_if(get_generic_pin_val(TEST_DIG_PIN2) != 255);  

  /* According to spec, this should result in value = 0 
     (since this pin is not a pwm) */
  analogWrite(TEST_DIG_PIN2, 120);
  fail_if(get_generic_pin_val(TEST_DIG_PIN2) != 0);  

  /* According to spec, this should result in value = 1 
     (since this pin is not a pwm) */

  analogWrite(TEST_DIG_PIN2, 129);
  fail_if(get_generic_pin_val(TEST_DIG_PIN2) != 1);  

  /* According to spec, this should result in value = 1 
     (since this pin is not a pwm) */
  analogWrite(TEST_DIG_PIN2, 255);
  fail_if(get_generic_pin_val(TEST_DIG_PIN2) != 255);  

  analogWrite(TEST_DIG_PIN2, 1023);
  fail_if(get_generic_pin_val(TEST_DIG_PIN2) != 255);  

}
END_TEST

START_TEST (test_uno_130)
{
  int ret;

  set_board_name(MY_UNO);

  board_setup();

  #define TEST_DIG_PIN3 130

  /*
   * Digital pin 13 (no pwm)
   *
   */ 

  /* Positive tests (as digital output pin) */
  pinMode(TEST_DIG_PIN3,OUTPUT);

  digitalWrite(TEST_DIG_PIN3, HIGH);
  fail_if(get_generic_pin_val(TEST_DIG_PIN3) != LOW);

  /* Positive tests (as digital input pin) */
  pinMode(TEST_DIG_PIN3,INPUT);

  digitalWrite(TEST_DIG_PIN3, HIGH);
  fail_if(get_generic_pin_val(TEST_DIG_PIN3) != LOW);

  digitalWrite(TEST_DIG_PIN3, LOW);
  fail_if(get_generic_pin_val(TEST_DIG_PIN3) != LOW);  

  /* Positive tests (as digital output pin) */
  pinMode(TEST_DIG_PIN3,OUTPUT);

  /* According to spec, this should result in a digitalWrite (LOW) */
  analogWrite(TEST_DIG_PIN3, 0);
  fail_if(get_generic_pin_val(TEST_DIG_PIN3) != LOW);  

  /* According to spec, this should result in a digitalWrite (HIGH) */
  analogWrite(TEST_DIG_PIN3, 255);
  fail_if(get_generic_pin_val(TEST_DIG_PIN3) != LOW);  

  /* According to spec, this should result in value = 0 
     (since this pin is not a pwm) */
  analogWrite(TEST_DIG_PIN3, 120);
  fail_if(get_generic_pin_val(TEST_DIG_PIN3) != 0);  

  /* According to spec, this should result in value = 1 
     (since this pin is not a pwm) */
  analogWrite(TEST_DIG_PIN3, 129);
  fail_if(get_generic_pin_val(TEST_DIG_PIN3) != 0);  

  /* According to spec, this should result in value = 1 
     (since this pin is not a pwm) */
  analogWrite(TEST_DIG_PIN3, 255);
  fail_if(get_generic_pin_val(TEST_DIG_PIN3) != 0);  

}
END_TEST

START_TEST (test_uno_A0)
{
  int ret;

  set_board_name(MY_UNO);

  board_setup();


  /*
   * Analog pin A0 (input)
   *
   */ 

  digitalWrite(A0, LOW);
  fail_if(get_generic_pin_val(A0) != LOW);

  digitalWrite(A0, HIGH);
  fail_if(get_generic_pin_val(A0) != LOW);

  /* normal tests of analogWrite */
  analogWrite(A0, 0);
  fail_if(get_generic_pin_val(A0) != 0);  

  analogWrite(A0, 120);
  fail_if(get_generic_pin_val(A0) != 0);  

  analogWrite(A0, 240);
  fail_if(get_generic_pin_val(A0) != 0);  

  analogWrite(A0, 255);
  fail_if(get_generic_pin_val(A0) != 1023);  

  analogWrite(A0, 500);
  fail_if(get_generic_pin_val(A0) != 1023);  

  analogWrite(A0, 1023);
  fail_if(get_generic_pin_val(A0) != 1023);  
}
END_TEST


Suite *
buffer_suite(void) {
  Suite *s = suite_create("Boards_Fuctions");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase (s, tc_core);


  searduino_set_arduino_code_name("../../../extensions/arduino-lib/.libs/libarduino-code.so");
  tcase_add_test(tc_core, test_uno_11);
  tcase_add_test(tc_core, test_uno_13);
  tcase_add_test(tc_core, test_uno_130);
  tcase_add_test(tc_core, test_uno_A0);
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


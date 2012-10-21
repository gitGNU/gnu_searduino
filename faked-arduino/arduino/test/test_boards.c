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
const char *MY_UNO_MIX  = "uNo";
const char *MY_MEGA     = "meGA";
const char *MY_MEGA_MIX = "MEGa";

const char *MY_BAD_BOARD= "dummy";

void
test_setboard_sub(const char *board)
{
  int ret;
  printf ("* Setting board to %s\n", board);
  ret = set_board_name(board);
  fail_if( ret <= 0 || ret >= 30 );

  printf ("* Comparing board name %s\n", board);
  ret = strncasecmp(get_board_name(), board, strlen(board));
  fail_if( ret !=0 );
}


START_TEST (test_board)
{
  int ret;

  board_setup();

  test_setboard_sub(MY_UNO);
  test_setboard_sub(MY_UNO_MIX);
  test_setboard_sub(MY_MEGA);
  test_setboard_sub(MY_MEGA_MIX);

  printf ("* Setting board to %s\n", MY_BAD_BOARD);
  ret = set_board_name(MY_BAD_BOARD);
  fail_if( ret > 0 );

  printf ("* Comparing board name %s\n", MY_BAD_BOARD);
  fail_if( get_board_name() != NULL );

  printf ("* Setting board to %s\n", "null");
  ret = set_board_name(NULL);
  fail_if( ret > 0 );

  printf ("* Comparing board name %s\n", "null");
  fail_if( get_board_name() != NULL );

  ret = set_generic_pin_type(11, SEARDUINO_PIN_TYPE_DIGITAL);
  fail_if (ret != 0 );

  ret = has_generic_pin_type(11, SEARDUINO_PIN_TYPE_DIGITAL);
  fail_if (ret != 1 );


}
END_TEST


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
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != HIGH);

  digitalWrite(TEST_DIG_PIN, LOW);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != LOW);  

  /* Positive tests (as digital output pin) */
  pinMode(TEST_DIG_PIN,OUTPUT);

  /* According to spec, this should result in a digitalWrite (LOW) */
  analogWrite(TEST_DIG_PIN, 0);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != LOW);  

  /* According to spec, this should result in a digitalWrite (HIGH) */
  analogWrite(TEST_DIG_PIN, 255);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != HIGH);  

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
  fail_if(get_generic_pin_val(TEST_DIG_PIN2) != HIGH);

  digitalWrite(TEST_DIG_PIN2, LOW);
  fail_if(get_generic_pin_val(TEST_DIG_PIN2) != LOW);  

  /* Positive tests (as digital output pin) */
  pinMode(TEST_DIG_PIN2,OUTPUT);

  /* According to spec, this should result in a digitalWrite (LOW) */
  analogWrite(TEST_DIG_PIN2, 0);
  fail_if(get_generic_pin_val(TEST_DIG_PIN2) != LOW);  

  /* According to spec, this should result in a digitalWrite (HIGH) */
  analogWrite(TEST_DIG_PIN2, 255);
  fail_if(get_generic_pin_val(TEST_DIG_PIN2) != HIGH);  

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
  fail_if(get_generic_pin_val(TEST_DIG_PIN2) != 1);  

}
END_TEST

START_TEST (test_supported_boards)
{
  char *tmp;

  tmp = get_supported_boards();
  
  fail_if (tmp == NULL );
  
  printf ("supported bords: %s\n", tmp);
  
}
END_TEST


Suite *
buffer_suite(void) {
  Suite *s = suite_create("Boards_Fuctions");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase (s, tc_core);

  tcase_add_test(tc_core, test_board);
  tcase_add_test(tc_core, test_supported_boards);

  searduino_set_arduino_code_name("../../../extensions/arduino-lib/.libs/libarduino-code.so");
  tcase_add_test(tc_core, test_uno_11);
  tcase_add_test(tc_core, test_uno_13);
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

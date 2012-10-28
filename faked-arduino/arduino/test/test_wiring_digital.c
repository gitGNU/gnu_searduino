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


#include "wiring_private.h"
#include "searduino_pin.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#define INPUT  0 
#define OUTPUT 1



START_TEST (test_digin_callback_raw)
{
  int i ;
  
  printf ("\n\n\n\t*** The following tests will generate a lof of warnings \n"
	  "\t*** from layers below\n"
	  "\t <start>\n");

  for (i=0;i<10;i++)
    {
      /*
       * Make sure we have a known state
       *
       *  set pin mode OUTPUT
       */
      pinMode(i, INPUT);
      digitalWrite(i, 0);
      fail_if(digitalRead(i)==1);

      // set pin mode OUTPUT
      pinMode(i, OUTPUT);
      fail_if(digitalRead(i)==1, "Reading from pin %d was 1", i);

      // call callback to set pin (which should not work)
      digin_callback(i,1);
      fail_if(digitalRead(i)==1, "Reading from pin %d was 1", i);
    }


  // call callback to set an illegal pin (which should not work)
  digin_callback(250, 1);
  digin_callback(1, 250);
  
  fail_if(digitalRead(1000)==1);

  /* Make sure Searduino does not crash when getting stupid values */
  pinMode(1, 250);
  pinMode(250, 1);

  printf ("\t <stop>\n");
  for (i=1;i<10;i++)
    {
      // set pin mode INPUT
      pinMode(i, INPUT);

      sim_set_digital_pin_val(i,1);
      fail_if(digitalRead(i)!=1, "  Setting pin:%d to 1", i);

      sim_set_digital_pin_val(i,0);
      fail_if(digitalRead(i)!=0, "  Setting pin:%d to 0", i);

    }
}
END_TEST

START_TEST (test_dig_mode_callback_raw)
{
  int i ;
  
  for (i=0;i<2;i++)
    {
      pinMode(i, 1);
      fail_if(dig_mode_callback(i)==0);

      pinMode(i, 0);
      fail_if(dig_mode_callback(i)==1);
    }

  fail_if(dig_mode_callback(250)==1);
}
END_TEST

START_TEST (test_dig_write)
{
  #define TEST_DIG_PIN 13

  /* Positive tests (as output pin */

  pinMode(TEST_DIG_PIN,OUTPUT);

  digitalWrite(TEST_DIG_PIN, HIGH);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != HIGH);

  digitalWrite(TEST_DIG_PIN, LOW);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != LOW);

  analogWrite(TEST_DIG_PIN, LOW);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != LOW);

  analogWrite(TEST_DIG_PIN, 120);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != LOW);

  analogWrite(TEST_DIG_PIN, 130);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != HIGH);

  analogWrite(TEST_DIG_PIN, 255);
  fail_if(get_generic_pin_val(TEST_DIG_PIN) != 255);

  /* Negative tests (as output pin */

  pinMode(TEST_DIG_PIN,INPUT);



}
END_TEST

START_TEST (test_digout_callback_raw)
{
  int i ;
  
  printf ("\n\n\n\t*** The following tests will generate a lof of warnings \n"
	  "\t*** from layers below\n"
	  "\t <start>\n");

  for (i=0;i<10;i++)
    {
      /*
       * 
       *         OUTPUT
       *
       */

      // set pin mode OUTPUT,
      pinMode(i, 1);
      // after set pin to 1 
      digitalWrite(i,1);

      // Make sure pin is 1
      fail_if(digout_callback(i)!=1);


      /*
       * 
       *         INPUT
       *
       */

     // set pin mode INPUT
      pinMode(i, 0);

      // try to set pin to 0 (should not work)
      digitalWrite(i,0);

      // Make sure pin is 1
      fail_if(get_digital_pin_val(i)!=1);

      // try to set pin to 1 (should not work)
      digitalWrite(i,1);

      // Make sure pin is 1
      fail_if(get_digital_pin_val(i)!=1);
    }

  // try to set pin to 250 (should not work)
  printf ("Seems ok 1 \n");

  digitalWrite(250,0);
  printf ("Seems ok 2\n");

  digitalWrite(1,123);

  printf ("Seems ok 3\n");


  digout_callback(250);


  printf ("\t <stop>\n");

}
END_TEST



Suite *
buffer_suite(void) {
  Suite *s = suite_create("Time_Fuctions");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase (s, tc_core);
  tcase_add_test(tc_core, test_digin_callback_raw);
  tcase_add_test(tc_core, test_dig_mode_callback_raw);
  tcase_add_test(tc_core, test_digout_callback_raw);

  tcase_add_test(tc_core, test_dig_write);

  return s;
}

int main(void)
{
  int num_failed;

  Suite *s = buffer_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  num_failed = srunner_ntests_failed(sr);
  searduino_set_arduino_code_name("../../../extensions/arduino-lib/.libs/libarduino-code.so");

  //  srunner_print(sr, CK_VERBOSE);

  srunner_free(sr);
  return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

  /*   test_delay(); */

  return 0;
}

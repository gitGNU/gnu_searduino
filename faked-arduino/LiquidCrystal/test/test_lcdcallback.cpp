/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2013 Henrik Sandklef 
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

#include "searduino.h"
#include "ext_io.h"
#include "seasim.h"
#include "LiquidCrystal.h"

const char *start_buffer1 = { "ABCDEFGHIJKLMNOPQRST" };
const char *start_buffer2 = { "abcdefghijklmnopqrst" };

char storage_buffer1[20];
char storage_buffer2[20];


void
lcd_callback(const char *str1, const char *str2)
{
  static int cb_counter;
  printf ("cb %d\n", cb_counter);

  printf ("LCD_CALLACK() LCD[0]: '%s' (size: %d)\n" , str1, strlen(str1));
  printf ("LCD_CALLACK() LCD[1]: '%s' (size: %d)\n" , str2, strlen(str2));
  fflush(stdout);  /*  MIND YOU, IS FLUSH REALLY NEEDED!!! */ 

  strcpy(storage_buffer1, str1);
  strcpy(storage_buffer2, str2);

  /* Check length of recieved string (should be 16) */
  switch (cb_counter)
    {
    case 0:
      printf ("str1 %d   str2 %d\n", strlen(str1), strlen(str2));
      fail_if(strlen(str1)!=16);  
      fail_if(strlen(str2)!=16); 
      fail_if(strncmp(str2,"     " , 5)!=0); 

      break;
    case 1:
      fail_if(strlen(str1)!=16);  
      fail_if(strlen(str2)!=16); 
      break;
    case 2:
      printf ("CB #3 '%s'  '%s'\n", str1, str2);
      fail_if(strlen(str1)!=16); 
      fail_if(strncmp(str1,"     " , 5)!=0); 
      fail_if(strlen(str2)!=16); 
      break;
    case 3:
      {
	int s1 = strlen(str1);
	int s2 = strlen(str2);
	printf ("CB #4 '%s' (%d)  '%s' (%d)\n", str1, s1, str2, s2);
	fail_if(strlen(str1)!=16); 
	fail_if(strncmp(str1,"     " , 5)!=0); 

	fail_if(strlen(str2)!=16); 
	fail_if(strncmp(str2,"     " , 5)!=0); 
      }
      break;
      
    }


  cb_counter++;

}


void wait_for_a_while() 
{
  int i ;
  printf ("Loops left:   ");
  for (i=10;i>0;i--)
    {
      usleep(1000*100);
      printf ("\b\b%.2d", i);
      fflush(stdout);
    }
  printf ("\b\ball loops are now done\n");
}

START_TEST (test_cb)
{
  init();
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
  
  lcd.begin(16, 2);

  seasim_register_lcd_cb(lcd_callback); 

  /* fake lcd print from User   */
  printf ("print 1\n");
  lcd.setCursor(0,0);
  lcd.print(start_buffer1);

  /* fake lcd print from User   */
  printf ("print 1\n");
  lcd.setCursor(0,1);
  lcd.print(start_buffer2);

  /* fake lcd print from User   */
  lcd.setCursor(0,0);
  lcd.print(" ");

  /* fake lcd print from User   */
  lcd.setCursor(0,1);
  lcd.print(" ");
}
END_TEST




Suite *
buffer_suite(void) {
  Suite *s = suite_create("Setup_Fuctions");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase (s, tc_core);

  printf ("Testing callback LiquidCrystal\n");

  tcase_add_test(tc_core, test_cb);

  wait_for_a_while();

  

  return s;
}

int main(void)
{
  int num_failed;
  //  test_micros();

  searduino_set_arduino_code_name("../../../extensions/arduino-lib/.libs/libarduino-code.so");

  Suite *s = buffer_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  num_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

  /*   test_delay(); */

  return 0;
}

/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2013, 2014 Henrik Sandklef 
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

#include "pthread.h"


#define SLEEP_M_SEC(s) usleep(1000*s)
#define STRLEN(s) s==NULL?0:(int)strlen(s)


const char *start_buffer1 = { "ABCDEFGHIJKLMNOPQRST" };
const char *start_buffer2 = { "abcdefghijklmnopqrst" };

char storage_buffer1[20];
char storage_buffer2[20];


pthread_t arduino_thread;

void
lcd_cb(const char *str1, const char *str2)
{
  static int cb_counter;

  memset(storage_buffer1, 0, 20);
  memset(storage_buffer2, 0, 20);

  strcpy(storage_buffer1, str1);
  strcpy(storage_buffer2, str2);

  printf ("LCD_CALLACK() LCD[0]: %s\n" , str1);
  printf ("LCD_CALLACK() LCD[1]: %s\n" , str2);
  printf ("CB #%d '%s'(%d)   '%s'(%d)\n", cb_counter+1, 
	  str1, 
	  (int)strlen(str1), 
	  str2, 
	  (int)strlen(str2));
  fflush(stdout);  /*  MIND YOU, IS FLUSH REALLY NEEDED!!! */ 

  switch (cb_counter)
    {
    case 0:
      /* 1 */
      break;
    case 1:
      /* 2 */
      break;
    case 2:
      /* 3 */
      /*      printf ("CB #3 '%s'  '%s'\n", str1, str2);
      fail_if(strlen(str1)!=0);  
      fail_if(strlen(str2)!=0); */
      break;
    case 3:
      /* 4 */
      break;
    case 4:
      /* 5 */
      break;
    case 5:
      /* 6 */
      printf ("CB #6 '%s'  '%s'\n", str1, str2);
      fail_if(strlen(str1)!=16);  
      fail_if(strlen(str2)!=16); 
    case 6:
      /* 7 */
      printf ("CB #7 '%s'  '%s'\n", str1, str2);
      fail_if(strlen(str1)!=1);  
      fail_if(strlen(str2)!=16); 
      break;
    }


  cb_counter++;

}


void
lcd_cb1(const char *str1, const char *str2)
{
  ;
}

void
lcd_cb2(const char *str1, const char *str2)
{
  static int cb_counter;

  /*
    1 and 2nd time we're called are constructor calls
     next after that we should have the initial string
  */

  if (cb_counter==2) 
    {
      printf ("LCD_CALLACK2() %d:\n", cb_counter);
      printf ("  LCD[0] (%d) : %s\n" , STRLEN(str1), str1);
      printf ("  LCD[1] (%d) : %s\n" , STRLEN(str2), str2);
      
      fail_if(strncmp(str1,"ABCDEFGH", strlen("ABCDEFGH"))!=0);
    }
  memset(storage_buffer1, 0, 20);
  memset(storage_buffer2, 0, 20);

  strcpy(storage_buffer1, str1);
  strcpy(storage_buffer2, str2);

  cb_counter++;
}



void wait_for_a_while() 
{
  int i ;
  #define LOOPS 200
  printf ("Loops left:    ");
  for (i=LOOPS;i>0;i--)
    {
      usleep(1000*100);
      printf ("\b\b\b%.3d", i);
      fflush(stdout);
    }
  printf ("\b\ball loops are now done\n");
}

START_TEST (test_clear)
{
  init();
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
  
  lcd.begin(16, 2);

  seasim_register_lcd_cb(lcd_cb); 

  /* fake lcd print from User   */
  lcd.setCursor(0,0);
  /* 1 */
  lcd.print(start_buffer1);
  lcd.setCursor(0,1);
  /* 2 */
  lcd.print(start_buffer2);

  /* fake lcd print from User   */
  /* 3 */
  lcd.clear();

}
END_TEST


START_TEST (test_home)
{
  init();
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
  
  lcd.begin(16, 2);

  seasim_register_lcd_cb(lcd_cb); 

  /* fake lcd print from User   */
  lcd.setCursor(0,0);

  /* 4 */
  lcd.print(start_buffer1);
  lcd.setCursor(0,1);
  /* 5 */
  lcd.print(start_buffer2);

  /* 6 */
  lcd.home();

  /* 7 */
  lcd.print(" ");

}
END_TEST



void* arduino_code(void *in)
{
  if (searduino_main_entry!=NULL)
    {
      searduino_main_entry(NULL);
    }
  else
    {
      fprintf (stderr, "Couldn't find an entry point for the Arduino code.\n");
      fprintf (stderr, "This probably means you haven't provided searduino with a shared library containing Arduino code\n");
      fflush (stderr);
    }
  return NULL;
}


void my_setup_arduino() 
{
  int ret;

  seasim_set_board_name((char*)"Uno");
  searduino_set_arduino_code_name(ARDUINO_LCD_CODE);
  seasim_setup_board();

  ret = seasim_setup();
  fail_if(ret!=0);  
  
  seasim_register_lcd_cb(lcd_cb1); 
}

START_TEST (test_halt)
{
  int ret;
  int ctr;

  my_setup_arduino();

  printf ("************************************\n");
  printf ("************* ROUND 1 **************\n");
  printf ("************************************\n");

  pthread_create(&arduino_thread, NULL, arduino_code, NULL);
  ctr=0;
  while (ctr++<10) 
    {
      char *tmp;
      tmp = seasim_get_lcd_data();
      
      SLEEP_M_SEC(100);
    }


  seasim_set_halted();
  usleep(200);
  
  ret = pthread_cancel(arduino_thread);
  usleep(200);
  
  usleep(1000);
  seasim_set_running();

  printf ("************************************\n");
  printf ("************* ROUND 2 **************\n");
  printf ("************************************\n");

  seasim_register_lcd_cb(lcd_cb2); 

  pthread_create(&arduino_thread, NULL, arduino_code, NULL);
  usleep(1000);
  ctr=0;
  while (ctr++<10) 
    {
      // char *tmp;
      // tmp = seasim_get_lcd_data();
      
      // printf ("IN test_clear.cpp round 2: %u %d %d  (%s)  \n", 
      // 	      tmp,
      // 	      STRLEN(storage_buffer1),
      // 	      STRLEN(storage_buffer2),
      // 	      tmp);

      SLEEP_M_SEC(100);
    }


  seasim_set_halted();
  usleep(200);
  
  ret = pthread_cancel(arduino_thread);
  usleep(200);
  
}
END_TEST




Suite *
buffer_suite(void) {
  Suite *s = suite_create("Setup_Fuctions");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase (s, tc_core);

  printf ("Testing callback LiquidCrystal\n");


  tcase_add_test(tc_core, test_clear);
  tcase_add_test(tc_core, test_home);
  tcase_add_test(tc_core, test_halt);

  wait_for_a_while();

  return s;
}

int main(void)
{
  int num_failed;
   // test_micros();

  seasim_set_board_name("Uno");
  searduino_set_arduino_code_name(ARDUINO_LCD_CODE);
  seasim_setup_board();
  
  

  Suite *s = buffer_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  num_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

  /*   test_delay(); */

  return 0;
}

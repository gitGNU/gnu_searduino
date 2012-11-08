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
#include "Arduino.h"
#include "searduino.h"
#include <sys/types.h>
#include <sys/stat.h>

START_TEST (test_inc_log)
{
  int level ;

  level = searduino_get_log_level();
  fail_if(level!=0);

  level = searduino_inc_log_level();
  fail_if(level!=1);
}
END_TEST

START_TEST (test_dec_log)
{
  int level ;
  int ret;

  /* reset to 0 */
  searduino_set_log_level(0);
  fail_if(ret!=0);
  level = searduino_get_log_level();
  fail_if(level!=0);

  level = searduino_get_log_level();
  fail_if(level!=0);

  level = searduino_dec_log_level();
  fail_if(level!=0);

  /* set to 3 */
  searduino_set_log_level(3);
  fail_if(ret!=0);
  level = searduino_get_log_level();
  fail_if(level!=3);

  level = searduino_dec_log_level();
  fail_if(level!=2);

  level = searduino_dec_log_level();
  fail_if(level!=1);

  level = searduino_dec_log_level();
  fail_if(level!=0);

  level = searduino_dec_log_level();
  fail_if(level!=0);



}
END_TEST


START_TEST (test_set_log)
{
  int level ;
  int ret   ;

  /* Set to 3 */
  ret = searduino_set_log_level(3);
  fail_if(ret!=0);
  level = searduino_get_log_level();
  fail_if(level!=3);

  /* Set to 0 */
  ret = searduino_set_log_level(0);
  fail_if(ret!=0);
  level = searduino_get_log_level();
  fail_if(level!=0);

  /* Set to 7 */
  ret = searduino_set_log_level(7);
  fail_if(ret!=0);
  level = searduino_get_log_level();
  fail_if(level!=7);
  
  /* reset to 0 */
  searduino_set_log_level(0);
  fail_if(ret!=0);
  level = searduino_get_log_level();
  fail_if(level!=0);

  /* Set to 11 - should fail */
  ret = searduino_set_log_level(11);
  fail_if(ret==0);
  level = searduino_get_log_level();
  fail_if(level!=0);

  /* Set to -11 - should fail */
  ret = searduino_set_log_level(-11);
  fail_if(ret==0);
  level = searduino_get_log_level();
  fail_if(level!=0);

}
END_TEST



START_TEST (test_log_msg)
{
  int level ;
  int ret; 
  int a; 
  int b; 
  int c; 

  ret = searduino_set_log_level(SEARDUINO_LOG_NONE);
  fail_if(ret!=0);

  ret = searduino_log((SEARDUINO_LOG_DEBUG, 
		 "\t\t\t *** This should NOT be seen during tests ****\n"));
  fail_if(ret!=0);


  ret = searduino_set_log_level(SEARDUINO_LOG_ERROR);
  fail_if(ret!=0);

  ret = searduino_log((SEARDUINO_LOG_DEBUG, 
		 "\t\t\t *** This should NOT be seen during tests ****\n"));
  fail_if(ret!=0);
  ret = searduino_log((SEARDUINO_LOG_ERROR, 
		 "\t\t\t *** This should be seen during tests ****   :) \n"));
  fail_if(ret==0);


  ret = searduino_set_log_level(SEARDUINO_LOG_DEBUG);
  fail_if(ret!=0);

  ret = searduino_log((SEARDUINO_LOG_DEBUG, 
		 "\t\t\t *** This should be seen during tests ****   :) \n"));
  fail_if(ret==0);

  ret = searduino_set_log_level(SEARDUINO_LOG_DEBUG);
  fail_if(ret!=0);

  ret = searduino_log((SEARDUINO_LOG_ERROR, 
		 "\t\t\t *** This should be seen during tests ****   :) \n"));
  fail_if(ret==0);

  a=3;
  b=4;
  c=-1;
  ret = searduino_log_impl(SEARDUINO_LOG_ERROR, 
		       "\t\t\t *** This should be seen during tests a(3):%d b(4):%d c(-1):%d  ****   :) \n", a, b, c);
  fail_if(ret==0);

}
END_TEST

START_TEST (test_log_file)
{
  int level ;
  int ret; 
  struct stat statbuf;
  char buf[100];
  FILE *fp;

  ret = searduino_set_log_level(SEARDUINO_LOG_INFO);
  fail_if(ret!=0);

  /*
   *   stderr and NULL
   */
  ret = searduino_log_set_file("stderr");
  fail_if(ret!=0);

  ret = searduino_log((SEARDUINO_LOG_DEBUG, 
		 "Using stderr\n"));
  fail_if(ret==0);

  ret = searduino_log_set_file(NULL);
  fail_if(ret!=0);

  ret = searduino_log((SEARDUINO_LOG_DEBUG, 
		 "Using NULL\n"));
  fail_if(ret==0);


  /*
   *   stdout
   */
  ret = searduino_log_set_file("stdout");
  fail_if(ret!=0);

  ret = searduino_log((SEARDUINO_LOG_DEBUG, 
		 "Using stdout\n"));
  fail_if(ret==0);



  usleep(1000*100);
  /*
   *   File with existing path
   */
  ret = searduino_log_set_file("/tmp/searduino-logtest.log");
  fail_if(ret!=0);

  ret = searduino_log((SEARDUINO_LOG_DEBUG, 
		 "Using file *** THIS SHOULD NOT BE SEEN IN THE TERMINAL WHEN RUNNING THE TESTS\n"));
  fail_if(ret==0);

  searduino_log_close_file();

  usleep(1000*1000);

  ret = stat("/tmp/searduino-logtest.log", &statbuf);
  fail_if(ret!=0);

  fp = fopen("/tmp/searduino-logtest.log", "r");
  fail_if(fp==0);

  usleep(1000*100);

  ret = fgets(buf, 100, fp);
  /* printf ("string read from logfile:  %s\n", buf); */
  ret = fgets(buf, 100, fp);
  /* printf ("string read from logfile:  %s\n", buf); */
  fail_if( (strstr(buf, "THIS SHOULD NOT BE SEEN") == NULL ));
  printf ("  logfile seemd to be ok\n");
  unlink("/tmp/searduino-logtest.log");


  /*
   *   File with non ecisting path
   */
  ret = searduino_log_set_file("/nonexistingpath/searduino-logtest.log");
  fail_if(ret==0);

  ret = searduino_log((SEARDUINO_LOG_DEBUG, 
		 "Using crappy path, so should be sent to stderr\n"));
  fail_if(ret==0);

  ret = stat("/nonexistingpath/searduino-logtest.log", &buf);
  fail_if(ret==0);

}
END_TEST



Suite *
buffer_suite(void) {
  Suite *s = suite_create("Log_Fuctions");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase (s, tc_core);

  printf ("Testing logging functions in faked-arduino/arduino\n");

  tcase_add_test(tc_core, test_set_log);
  tcase_add_test(tc_core, test_inc_log);
  tcase_add_test(tc_core, test_dec_log);
  tcase_add_test(tc_core, test_log_msg);
  tcase_add_test(tc_core, test_log_file);

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

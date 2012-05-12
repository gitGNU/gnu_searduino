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
#include <check.h>
#include <stdlib.h>
#include <stdio.h>

const char *MY_UNO     = "uno";
const char *MY_UNO_MIX = "uNo";

START_TEST (test_uno)
{
  int ret;
  
  board_setup();

  /* UNO */

  printf ("* Setting board to %s\n", MY_UNO);
  ret = set_board_name(MY_UNO);
  fail_if( ret <= 0 || ret >= 30 );

  printf ("* Comparing board name %s\n", MY_UNO);
  ret = strncasecmp(get_board_name(), MY_UNO, strlen(MY_UNO));
  fail_if( ret !=0 );

  /* UNO_MIX */
  printf ("* Setting board to %s\n", MY_UNO_MIX);
  ret = set_board_name(MY_UNO_MIX);
  fail_if( ret <= 0 || ret >= 30 );

  printf ("* Comparing board name %s\n", MY_UNO_MIX);
  ret = strncasecmp(get_board_name(), MY_UNO_MIX, strlen(MY_UNO_MIX));
  fail_if( ret !=0 );

}
END_TEST


Suite *
buffer_suite(void) {
  Suite *s = suite_create("Boards_Fuctions");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase (s, tc_core);

  tcase_add_test(tc_core, test_uno);

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

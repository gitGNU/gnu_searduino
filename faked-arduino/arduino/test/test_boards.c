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

  ret = get_generic_pin_type(11);
  fail_if (ret != SEARDUINO_PIN_TYPE_DIGITAL );

  ret = set_generic_pin_type(11, 128);
  fail_if (ret == 0 );

  ret = get_generic_pin_type(11);
  fail_if (ret != SEARDUINO_PIN_TYPE_NONE );

}
END_TEST


Suite *
buffer_suite(void) {
  Suite *s = suite_create("Boards_Fuctions");
  TCase *tc_core = tcase_create("Core");
  suite_add_tcase (s, tc_core);

  tcase_add_test(tc_core, test_board);

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

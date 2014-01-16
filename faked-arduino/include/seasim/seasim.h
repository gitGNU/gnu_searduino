/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2012-2013 Henrik Sandklef 
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

/**
 * @file   seasim.h
 * @author Henrik Sandklef
 * @date   January 2013
 * @brief  API for simulators and test code. Provides functions to simulate Arduino pin input and means to check Arduino output pins.
 *
 * 
 */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "searduino.h"
#include "searduino_pin.h"
#include "setup.h"
#include "arduino/ext_io.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#ifndef SEASIM_SEASIM_H
#define SEASIM_SEASIM_H

extern searduino_main_ptr_ptr searduino_main_entry;

#ifdef __cplusplus
extern "C"{
#endif
  

  
/**
 * @name    seasim_fake_digital_input
 * @brief   Fakes input on an Arduino digital pin
 *
 * This function should be used if you want to simulate input on the
 * Arduino boards. The coresponds to actually setting the input
 * manually (e.g using power supply) an input pin on the Arduino.
 *
 * @param [uint8_t] pin Digital pin to fake input on
 * @param [uint8_t] value Value (0 or 1) to fake
 *
 * @retval 0 on success
 * @retval !0 on failure
 *
 * Example Usage:
 * @code
 *    seasim_fake_digital_input (7,0);
 * @endcode
 */
uint8_t 
seasim_fake_digital_input (uint8_t pin, uint8_t val);

  
/**
 * @name    seasim_fake_analog_input
 * @brief   Fakes input on an Arduino digital pin
 *
 * This function should be used if you want to simulate input on the
 * Arduino boards. The coresponds to actually setting the input
 * manually (e.g using power supply) an input pin on the Arduino.
 *
 * @param [uint8_t] pin Analog pin to fake input on
 * @param [uint8_t] value Value (0 - 1024) to fake
 *
 * @retval 0 on success
 * @retval !0 on failure
 *
 * Example Usage:
 * @code
 *    seasim_fake_analog_input (8,786);
 * @endcode
 */
uint8_t 
seasim_fake_analog_input (uint8_t pin, unsigned int val);


  /*
   * This functions is obsoleted.
   * It is replaced by the easier to use: 
   *   seasim_fake_digital_input (uint8_t pin, uint8_t val);
   *   seasim_fake_analog_input (uint8_t pin, unsigned int val);
uint8_t 
seasim_set_generic_input(uint8_t pin, unsigned int val, uint8_t pin_type);
   */

  /*
   * This functions is obsoleted.
   * It is replaced by the easier to use: 
unsigned int
seasim_get_generic_output(uint8_t pin, uint8_t pin_type);
   */

/**
 * @name    seasim_fake_input
 * @brief   Fakes input on a general Arduino pin
 *
 * This function should be used if you want to simulate input on the
 * Arduino boards. The coresponds to actually setting the input
 * manually (e.g using power supply) an input pin on the Arduino.
 *
 * @param [uint8_t] pin Analog or Digital pin to fake input on
 * @param [uint8_t] value Value (0 - 1024) to fake
 * @param [uint8_t] type type of pin (SEARDUINO_PIN_TYPE_DIGITAL, SEARDUINO_PIN_TYPE_ANALOG)
 *
 * @retval 0 on success
 * @retval !0 on failure
 *
 * Example Usage:
 * @code
 *    seasim_fake_input (8, 786, SEARDUINO_PIN_TYPE_ANALOG);
 *    seasim_fake_input (13,1,   SEARDUINO_PIN_TYPE_DIGITAL);
 * @endcode
 */
uint8_t
seasim_fake_input(uint8_t pin, unsigned int val, uint8_t type);

/**
 * @name    seasim_get_output
 * @brief   Returns output from a general Arduino pin
 *
 * This function should be used if you want to check the current output
 * on the an Arduino board pin. The output is set by the application running 
 * in the simulated environment (the code you'll put on the Arduino board). 
 *
 * @param [uint8_t] pin Analog or Digital pin to fake input on
 * @param [uint8_t] type type of pin (SEARDUINO_PIN_TYPE_DIGITAL, SEARDUINO_PIN_TYPE_ANALOG)
 *
 * @retval [int] the value of the pin
 *
 * Example Usage:
 * @code
 *    seasim_fake_input (13, SEARDUINO_PIN_TYPE_ANALOG);
 * @endcode
 */
int
seasim_get_output(uint8_t pin, uint8_t pin_type);

/**
 * @name    seasim_is_pausable
 * @brief   Check if you can pause the Arduino code
 *
 * Searduino provides some macros allowing the simluator to pause
 * the code. 
 *
 * @retval [uint8_t] 0 if you can NOT pause the application. Non zero if you can.
 *
 */
uint8_t 
seasim_is_pausable(void);

/**
 * @name    seasim_is_paused
 * @brief   Check if you Arduino code is paused
 *
 * Searduino provides some macros allowing the simluator to pause
 * the code. 
 *
 * @retval [uint8_t] 0 if the application is paused. Non zero if it is not.
 *
 */
uint8_t 
seasim_is_paused(void);

/**
 * @name    seasim_is_paused
 * @brief   Check if you Arduino code is halted (stopped)
 *
 *
 * @retval [uint8_t] 0 if the application is halted (stopped). Non zero if it is still running.
 *
 */
uint8_t 
seasim_is_halted(void);

/**
 * @name    seasim_is_running
 * @brief   Check if you Arduino code is running
 *
 *
 * @retval [uint8_t] 0 if the application is running. Non zero if it is not running.
 *
 */
uint8_t 
seasim_is_running(void);

/**
 * @name    seasim_set_paused
 * @brief   Pauses the Arduino code 
 *
 * Searduino provides some macros allowing the simluator to pause
 * the code. If you're not using these this function has no impact on the 
 * running Arduino code.
 *
 * @retval [void]
 *
 */
void 
seasim_set_paused(void);

/**
 * @name    seasim_set_running
 * @brief   Starts the Arduino code 
 *
 * Searduino provides some macros allowing the simluator to pause
 * the code. If you're not using these this function has no impact on the 
 * running Arduino code.
 *
 * @retval [void]
 *
 */
void 
seasim_set_running(void);


/**
 * @name    seasim_set_halted
 * @brief   Halts the Arduino code 
 *
 * Searduino provides some macros allowing the simluator to pause
 * the code. If you're not using these this function has no impact on the 
 * running Arduino code.
 *
 * @retval [void]
 *
 */
void 
seasim_set_halted(void);

/**
 * @name    seasim_get_dig_mode
 * @brief   Returns the mode from a digital Arduino pin
 *
 * @param [uint8_t] pin Analog or Digital pin to fake input on
 *
 * @retval [int] the mode
 *
 * Example Usage:
 * @code
 *    seasim_get_dig_mode (13);
 * @endcode
 */
uint8_t 
seasim_get_dig_mode(uint8_t pin);


/**
 * @name    seasim_get_arduino_code_name
 * @brief   Returns the name of the Arduino code (file name) loaded
 *
 * The returned string must not be freed. If you need to modify it
 * you must copy the string.
 * 
 * @retval [char*] the name of the Arduino code running
 *
 * Example Usage:
 * @code
 *    char *arduino_code;
 *    arduino_code = seasim_get_arduino_code_name();
 * @endcode
 */
char *
seasim_get_arduino_code_name(void);

int
seasim_close_arduino_code_name(void);


/**
 * @name    seasim_set_arduino_code_name
 * @brief   Sets the name of the Arduino code (file name) loaded
 *
 * @param [const char*] libname The file name of the shared library (including path) you wich to load for later execution.
 *
 * @retval [char*] the name of the Arduino code running
 *
 * Example Usage:
 * @code
 *   int ret;
 *   ret  = seasim_set_arduino_code_name("./my-ard-code.so");
 * @endcode
 */
int 
seasim_set_arduino_code_name(const char* libname);

/**
 * @name    seasim_register_dig_mode_sim_cb
 * @brief   Register a callback for changes in digital modes of pin
 *
 * Whenever a pin changes mode on the Arduino you'll get noticed via 
 * your registered callback.
 *
 * @param [dm_to_sim_callback_ptr] cb The callback
 *
 * @retval [uint8_t] 0 on success. Non zero otherwise.
 *
 * Example Usage:
 * @code
 *  void 
 *  my_dm_sim_callback(uint8_t pin, uint8_t mode)
 *  {
 *    fprintf (stdout,"Pin %d changed mode to %d\n",pin, mode);
 *
 *  }
 *  .....
 *  int ret;
 *  ret  = seasim_register_dig_mode_sim_cb(my_dm_sim_callback);
 * @endcode
 */
uint8_t
seasim_register_dig_mode_sim_cb(dm_to_sim_callback_ptr cb);

/**
 * @name    seasim_register_out_sim_cb
 * @brief   Register a callback for updates on the pin outputs
 *
 * Whenever an output pin changes value on the Arduino you'll get noticed via 
 * your registered callback.
 *
 * @param [out_to_sim_callback_ptr] cb The callback
 *
 * @retval [uint8_t] 0 on success. Non zero otherwise.
 *
 * Example Usage:
 * @code
 *  void
 *  my_out_sim_callback(uint8_t pin, unsigned int value, uint8_t pin_type)
 *  {
 *      fprintf (stdout,
 *	   "Pin%d value:%d type:%d\n",
 *	   pin, 
 *	   value, 
 *	   pin_type);
 *  }
 *  .....
 *  int ret;
 *  ret  = seasim_register_out_sim_cb(my_out_sim_callback);
 * @endcode
 */
uint8_t 
seasim_register_out_sim_cb(out_to_sim_callback_ptr cb);


/**
 * @name    seasim_register_log_cb
 * @brief   Register a callback for log written by the Arduino code
 *
 * Searduino provides some logging functions to the Arduino code.
 * You can register and get those logs via a callback using this function.
 *
 * @param [seasim_register_log_cb] cb The callback
 *
 * @retval [uint8_t] 0 on success. Non zero otherwise.
 *
 * Example Usage:
 * @code
 * void
 * my_log_sim_callback(uint8_t level, const char *str)
 * {
 *    fprintf (stdout,
 *    	   "LOG CALLBACK :%d  msg:%s  %d\n",
 *    	   level, 
 *    	    str, strlen(str));
 * }
 * ....
 * int ret;
 * 	  ret  = seasim_register_log_cb(my_log_sim_callback);
 * @endcode
 */
uint8_t
seasim_register_log_cb(log_to_sim_callback_ptr cb);

uint8_t
seasim_register_lcd_cb(lcd_to_sim_callback_ptr cb);


/**
 * @name    seasim_register_type_cb
 * @brief   Register a callback for type changes on a pin
 *
 * Whenever a pin changes type (e.g from digital to analog) you'll get 
 * notified through the registered callback.
 *
 * @param [pintype_to_sim_callback_ptr] cb The callback
 *
 * @retval [uint8_t] 0 on success. Non zero otherwise.
 *
 * Example Usage:
 * @code
 * void
 * my_type_sim_callback(uint8_t pin, uint8_t pin_type)
 * {
 *    fprintf (stdout,
 *            "TYPE CALLBACK :%d  type:%d\n",
 * 	   pin, 
 * 	   pin_type);
 * 
 * }
 * ...
 * int ret;
 * ret  = seasim_register_type_cb(my_type_sim_callback);
 * 
 * @endcode
 */
uint8_t
seasim_register_type_cb(pintype_to_sim_callback_ptr cb);

/**
 * @name    seasim_register_type_cb
 * @brief   Register a callback for type changes on a pin
 *
 * Setup all functionality of the Searduino simluator part.
 * You can call this function many times - the setup is only 
 * done once.
 *
 * @retval [uint8_t] 0 on success. Non zero otherwise.
 *
 */
int 
seasim_setup(void);


/**
 * @name    seasim_disable_streamed_output
 * @brief   Turn off printouts on terminal
 *
 * Apart from using callbacks to notify simluators/tests
 * of updates Searduino also prints to stdout to inform of changes.
 * This function disables those printouts.
 *
 * The printout is enabled by default.
 */
void 
seasim_disable_streamed_output(void);


/**
 * @name    seasim_is_enable_streamed_output
 * @brief   Chekcs if streamed output is enabled or disabled
 *
 * Apart from using callbacks to notify simluators/tests
 * of updates Searduino also prints to stdout to inform of changes.
 * This function checks if such printout is enabled or disabled.
 *
 * @retval [int] 1 if enabled. 0 if not.
 */
uint8_t 
seasim_is_enable_streamed_output(void);

/**
 * @name    seasim_ensable_streamed_output
 * @brief   Turn on printouts on terminal
 *
 * Apart from using callbacks to notify simluators/tests
 * of updates Searduino also prints to stdout to inform of changes.
 * This function enables those printouts.
 *
 * The printout is enabled by default.
 */
void 
seasim_enable_streamed_output(void);


/**
 * @name    seasim_set_write_timelimit
 * @brief   Set the maximum update frequency for a pin
 *
 * If pins get updated to fast you can limit the speed with
 * this functions.
 * 
 * @param [uint8_t] lim The limit in milli seconds
 *
 * 
 */
void 
seasim_set_write_timelimit(unsigned int lim);

/**
 * @name    seasim_set_write_timelimit
 * @brief   Get the maximum update frequency for a pin
 *
 * If pins get updated to fast you can limit the speed.
 * This function returns the current update limit.
 * 
 * @retval [uint8_t] lim The current limit.
 *
 * 
 */
unsigned int
seasim_get_write_timelimit(void);

int  
seasim_i2c_add_device (unsigned int device_nr, 
		       const char  *setup_fun);


/**
 * @name    seasim_get_searduino_version
 * @brief   Returns the version of Searduino (as a string)
 *
 * @retval [char*] the version of Searduino
 *
 */
const char* 
seasim_get_searduino_version(void);


/**
 * @name    seasim_get_searduino_name
 * @brief   Returns the name of Searduino (as a string)
 *
 * @retval [char*] the name of Searduino
 *
 */
const char* 
seasim_get_searduino_name(void);

/**
 * @name    seasim_set_board_name
 * @brief   Sets the name of board to use
 *
 * If you're setting the name to a board not supported by Searduino
 * the last set board will be kept.
 *
 * @param [char*] the name of board to use. If NULL Searduino sets no board in use.
 *
 * @retval 0 on success
 * @retval !0 on failure
 *
 */
int
seasim_set_board_name(char *board);


/**
 * @name    seasim_get_board_name
 * @brief   Returns the name of currently used board
 *
 * @retval [char*] the name of board in use. NULL if no board has been set.
 *
 */
char *
seasim_get_board_name(void);

/**
 * @name    seasim_get_current_pin_type
 * @brief   Returns the pin type of a pin
 *
 * @param [uint8_t] pin Pin to check
 *
 * @retval [int] the type of the pin
 *
 */
int 
seasim_get_current_pin_type(uint8_t pin);

/**
 * @name    seasim_has_generic_pin_type
 * @brief   Checks if a pin can be of a certain type
 *
 * @param [uint8_t] pin Pin to check
 *
 * @retval 0 if it can not
 * @retval !0 if it can
 *
 */
int 
seasim_has_generic_pin_type(uint8_t pin, uint8_t type);


/**
 * @name    seasim_hid_disable_feedback
 * @brief   Turn off faked hid
 *
 * Searduino can on some platforms move the mouse and keyboard
 * just as Arduino code connected to a computer would do.
 * This functions disables that feature.
 * 
 * @retval 0 on success
 * @retval !0 on failure
 *
 */
uint8_t 
seasim_hid_disable_feedback(void);


/**
 * @name    seasim_hid_enable_feedback
 * @brief   Turn off faked hid
 *
 * Searduino can on some platforms move the mouse and keyboard
 * just as Arduino code connected to a computer would do.
 * This functions enables that feature.
 * 
 * @retval 0 on success
 * @retval !0 on failure
 *
 */
uint8_t 
seasim_hid_enable_feedback(void);


/**
 * @name    seasim_get_supported_boards
 * @brief   Returns a string with all boards supported by Searduino
 *
 * @retval [char*] Returns an empty string if no boards are supported. Otherwise it returns a comma separated list of boards
 *
 * Example Usage:
 * @code
 *    seasim_get_supported_boards(void);
 * @endcode
 * would typically give you a string like this:
 *     "Uno, Leonardo, Mega"
 *  and so on.
 */
char *
seasim_get_supported_boards(void);


/**
 * @name    seasim_get_nr_of_pins
 * @brief   Returns the number of pins of the current board
 *
 * @retval [uint8_t] The number of pins on the currently chose board.
 *
 */
uint8_t
seasim_get_nr_of_pins(void);

int 
seasim_set_log_level(int level);

int
seasim_setup_board(void);

int 
seasim_get_board_pins(char *board);

char * 
seasim_get_board_setup(void);


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif  /* SEASIM_SEASIM_H */


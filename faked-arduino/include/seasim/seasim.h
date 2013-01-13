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

/**
 * @file   seasim.h
 * @Author Henrik Sandklef
 * @date   January 2013
 * @brief  API for simulators and test code. Provides functions to simulate Arduino pin input and means to check Arduino output pins.
 *
 * 
 */


#include "searduino.h"
#include "searduino_pin.h"
#include "setup.h"
#include "arduino/ext_io.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


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
 *    seasim_fake_digital_input (8,786);
 * @endcode
 */
uint8_t 
seasim_fake_analog_input (uint8_t pin, unsigned int val);


  /*
   * This functions will be obsoleted.
   * It is replaced by the easier to use: 
   *   seasim_fake_digital_input (uint8_t pin, uint8_t val);
   *   seasim_fake_analog_input (uint8_t pin, unsigned int val);
   */
uint8_t 
seasim_set_generic_input(uint8_t pin, unsigned int val, uint8_t pin_type);

  /*
   * This functions will be obsoleted.
   * It is replaced by the easier to use: 
   */
unsigned int
seasim_get_generic_output(uint8_t pin, uint8_t pin_type);

uint8_t
seasim_set_input(uint8_t pin, unsigned int val, uint8_t pin_type);

int
seasim_get_output(uint8_t pin, uint8_t pin_type);

uint8_t 
seasim_is_pausable(void);

uint8_t 
seasim_is_paused(void);

uint8_t 
seasim_is_halted(void);

uint8_t 
seasim_is_running(void);

void 
seasim_set_paused(void);

void 
seasim_set_running(void);

void 
seasim_set_halted(void);

uint8_t 
seasim_get_dig_mode(uint8_t pin);

char *
seasim_get_arduino_code_name(void);

int 
seasim_set_arduino_code_name(const char* libname);

uint8_t
seasim_register_dig_mode_sim_cb(dm_to_sim_callback_ptr cb);

uint8_t 
seasim_register_out_sim_cb(out_to_sim_callback_ptr cb);

uint8_t
seasim_register_dig_mode_sim_cb(dm_to_sim_callback_ptr cb);

uint8_t
seasim_register_log_cb(log_to_sim_callback_ptr cb);

uint8_t
seasim_register_type_cb(pintype_to_sim_callback_ptr cb);

int 
seasim_setup(void);

void 
seasim_disable_streamed_output(void);


uint8_t 
seasim_is_enable_streamed_output(void);

void 
seasim_enable_streamed_output(void);

void 
seasim_set_Write_timelimit(unsigned int lim);

unsigned int
seasim_get_Write_timelimit(void);

int  
seasim_i2c_add_device (unsigned int device_nr, 
		       const char  *setup_fun);


const char* 
seasim_get_searduino_version(void);

const char* 
seasim_get_searduino_name(void);

int
seasim_set_board_name(char *board);

char *
seasim_get_board_name(void);

int 
seasim_get_current_pin_type(uint8_t pin);

int 
seasim_has_generic_pin_type(uint8_t pin, uint8_t type);

uint8_t 
seasim_hid_disable_feedback(void);

uint8_t 
seasim_hid_enable_feedback(void);

char *
seasim_get_supported_boards(void);

uint8_t
seasim_get_nr_of_pins(void);


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif  /* SEASIM_SEASIM_H */

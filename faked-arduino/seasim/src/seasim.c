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

#include "seasim/seasim.h"
#include "searduino.h"
#include "boards.h"

const char* seasim_get_searduino_version(void)
{
  return VERSION;
}

const char* seasim_get_searduino_name(void)
{
  return PACKAGE;
}


unsigned int
seasim_get_generic_output(uint8_t pin, uint8_t pin_type)
{
  return ext_get_generic_output(pin, pin_type );
}

uint8_t 
seasim_set_generic_input(uint8_t pin, unsigned int val, uint8_t pin_type)
{
  return ext_set_generic_input(pin, val, pin_type);
}

uint8_t 
seasim_register_out_sim_cb(out_to_sim_callback_ptr cb)
{
  return ext_register_pinout_sim_cb(cb);
}

uint8_t
seasim_register_log_cb(log_to_sim_callback_ptr cb)
{
  return ext_register_log_cb(cb);
}



uint8_t
seasim_set_input(uint8_t pin, unsigned int val, uint8_t pin_type)
{
  return sim_set_generic_pin_val(pin, val, pin_type);
}


int
seasim_get_output(uint8_t pin, uint8_t pin_type)
{
  return ext_get_generic_output(pin, pin_type);
}



uint8_t 
seasim_is_paused(void)
{
  return searduino_is_paused();
}

uint8_t 
seasim_is_halted(void)
{
  return searduino_is_halted();
}

uint8_t 
seasim_is_running(void)
{
  return searduino_is_running();
}

void 
seasim_set_paused(void)
{
  searduino_set_paused();
}

void 
seasim_set_running(void)
{
  return searduino_set_running();
}

void 
seasim_set_halted(void)
{
  return searduino_set_halted();
}

uint8_t 
seasim_get_dig_mode(uint8_t pin)
{
  return ext_get_dig_mode(pin);
}


int 
seasim_set_arduino_code_name(const char* libname)
{
  return searduino_set_arduino_code_name(libname);
}

uint8_t
seasim_register_dig_mode_sim_cb(dm_to_sim_callback_ptr cb)
{
  return ext_register_dig_mode_sim_cb(cb);
}


int 
seasim_setup(void)
{
  searduino_setup();
  return 0;
}

void seasim_disable_streamed_output(void)
{
  searduino_disable_streamed_output();
}

uint8_t 
seasim_is_enable_streamed_output(void)
{
  return searduino_is_enable_streamed_output();
}


void seasim_enable_streamed_output(void)
{
  searduino_enable_streamed_output();
}

void 
seasim_set_Write_timelimit(unsigned int lim)
{
  set_Write_timelimit(lim);
}

unsigned int
seasim_get_Write_timelimit(void)
{
  return get_Write_timelimit();
}

int  
seasim_i2c_add_device (unsigned int device_nr, 
		       const char  *setup_fun)
{
  return i2c_add_device (device_nr, 
			 setup_fun);
}



int
seasim_set_board_name(char *board)
{
  return set_board_name(board);
}

char *
seasim_get_board_name(void)
{
  char *tmp;
  tmp = get_board_name();
  /*
  printf ("SEASIM board: \n");
  printf ("SEASIM board: %p\n", tmp);
  printf ("SEASIM board: %s\n", tmp);
  printf ("SEASIM board: \n");
  */
  return tmp;
}

int 
seasim_get_generic_pin_type(uint8_t pin)
{
  return get_generic_pin_type(pin);
}

uint8_t 
seasim_hid_disable_feedback(void)
{
  return hid_disable_faked_hid();
}

uint8_t 
seasim_hid_enable_feedback(void)
{
  return hid_enable_faked_hid();
}

char *
seasim_get_supported_boards(void)
{
  return get_supported_boards();
}


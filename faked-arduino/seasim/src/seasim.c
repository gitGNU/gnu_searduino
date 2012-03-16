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
#include "communication/comm.h"


extern ai_callback_ptr ai_callback;
extern di_callback_ptr di_callback;
extern ao_callback_ptr ao_callback;
extern do_callback_ptr do_callback;
extern do_to_sim_callback_ptr do_sim_callback;
extern d_mode_callback_ptr    d_mode_callback;
extern ao_to_sim_callback_ptr ao_sim_callback;
extern a_mode_callback_ptr    a_mode_callback;


unsigned int
seasim_get_ana_output(uint8_t pin)
{
  return ext_get_ana_output(pin);
}


uint8_t
seasim_set_ana_input(uint8_t pin, unsigned int val)
{
  return ext_set_ana_input(pin, val);
}


uint8_t 
seasim_get_dig_output(uint8_t pin)
{
  return ext_get_dig_output(pin);
}

uint8_t 
seasim_set_dig_input(uint8_t pin, uint8_t val)
{
  return ext_set_dig_input(pin, val);
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
seasim_register_digout_sim_cb(do_to_sim_callback_ptr cb)
{
  return comm_register_digout_sim_cb(cb);
}


uint8_t
seasim_register_dig_mode_sim_cb(d_mode_callback_ptr cb)
{
  return comm_register_dig_mode_sim_cb(cb);
}

uint8_t
seasim_register_anaout_sim_cb(ao_to_sim_callback_ptr cb)
{
  return comm_register_anaout_sim_cb(cb);
}

int 
seasim_setup(void)
{
  searduino_setup();
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
seasim_set_digitalWrite_timelimit(unsigned int lim)
{
  set_digitalWrite_timelimit(lim);
}

unsigned int
seasim_get_digitalWrite_timelimit(void)
{
  return get_digitalWrite_timelimit();
}

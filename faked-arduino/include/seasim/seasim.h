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

#include "searduino.h"
#include "setup.h"
#include "communication/comm.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


#ifndef SEASIM_SEASIM_H
#define SEASIM_SEASIM_H

extern searduino_main_ptr_ptr searduino_main_entry;



/*
unsigned int
seasim_get_ana_output(uint8_t pin);

uint8_t
seasim_set_ana_input(uint8_t pin, unsigned int val);

uint8_t 
seasim_get_dig_output(uint8_t pin);
*/

int
seasim_get_output(uint8_t pin);

uint8_t
seasim_set_ana_input(uint8_t pin, unsigned int val, uint8_t pin_type);

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

int 
seasim_set_arduino_code_name(const char* libname);

/*
uint8_t 
seasim_register_digout_sim_cb(do_to_sim_callback_ptr cb);

uint8_t
seasim_register_anaout_sim_cb(ao_to_sim_callback_ptr cb);

*/


uint8_t 
seasim_register_out_sim_cb(out_to_sim_callback_ptr cb);

uint8_t
seasim_register_dig_mode_sim_cb(dm_to_sim_callback_ptr cb);

int 
seasim_setup(void);

void seasim_disable_streamed_output(void);


uint8_t 
seasim_is_enable_streamed_output(void);

void seasim_enable_streamed_output(void);

void 
seasim_set_Write_timelimit(unsigned int lim);

unsigned int
seasim_get_Write_timelimit(void);




#endif  /* SEASIM_SEASIM_H */

/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2011, 2012 Henrik Sandklef 
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils/types.h"
#include "pins_arduino.h"

#ifndef SEARDUINO_ARDUINO_SETUP_H
#define SEARDUINO_ARDUINO_SETUP_H

#define NR_OF_DIGITAL_PINS 20
#define NR_OF_ANALOG_PINS 20


/* The macro below enables Serial "over USB" */
#ifndef USBCON
#define USBCON
#endif
#ifndef CDC_ENABLED
#define CDC_ENABLED dummyvalue
#endif


uint8_t  dig_mode_callback(uint8_t pin);
void     input_callback(uint8_t pin, unsigned int val, uint8_t pin_type);

typedef void (*searduino_main_ptr)(void* in); 
typedef searduino_main_ptr searduino_main_ptr_ptr ;

#ifdef __cplusplus
extern "C"{
#endif
  
  
int searduino_setup(void);

void searduino_set_paused(void);

void searduino_set_running(void);

void searduino_set_halted(void);

uint8_t searduino_is_running(void);

uint8_t searduino_is_paused(void);

uint8_t searduino_is_halted(void);

void init(void);

int 
searduino_set_arduino_code_name(const char* libname);

uint8_t 
get_nr_of_pins(void);

void 
set_digitalWrite_timelimit(unsigned int lim);

unsigned int
get_digitalWrite_timelimit(void);

unsigned int 
get_discard_ctr(unsigned char pin);
  
  
int
load_arduino_code(void);
  
void init_time(void);
  
int initialise_hid(void);

char * 
get_arduino_code_name(void);

int
close_arduino_code(void);

int 
is_pausable(void);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* SEARDUINO_ARDUINO_SETUP_H */


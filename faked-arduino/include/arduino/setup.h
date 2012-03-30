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

typedef void (*searduino_main_ptr)(void* in); 
typedef searduino_main_ptr searduino_main_ptr_ptr ;


#define ENABLE_SLEEP
#ifdef  ENABLE_SLEEP
#define   SEARDUINO_LOOP() for (;;)  \
    if      (searduino_is_paused())  { fprintf (stderr, "z"); usleep(1000*200); } \
    else if ( searduino_is_halted()) { fprintf (stderr, "Simulator halted, will return\n"); return 0; } \
    else  
#else
#define   SEARDUINO_LOOP() for (;;) 
#endif

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

int ext_set_input(uint8_t pin, uint8_t val);

void 
set_digitalWrite_timelimit(unsigned int lim);

unsigned int
get_digitalWrite_timelimit(void);

unsigned int 
get_discard_ctr(unsigned char pin);


#ifdef __cplusplus
} // extern "C"
#endif


#endif /* SEARDUINO_ARDUINO_SETUP_H */


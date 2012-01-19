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

#define ENABLE_SLEEP
#ifdef  ENABLE_SLEEP
#define   SEARDUINO_LOOP() for (;;)  \
    if      (searduino_is_paused())  { fprintf (stderr, "z"); usleep(1000*200); } \
    else if ( searduino_is_halted()) { fprintf (stderr, "Simulator halted, will return\n"); return 0; } \
    else  
#else
#define   SEARDUINO_LOOP() for (;;) 
#endif

void searduino_setup(void);


void searduino_set_paused(void);

void searduino_set_running(void);

void searduino_set_halted(void);

uint8_t searduino_is_running(void);

uint8_t searduino_is_paused(void);

uint8_t searduino_is_halted(void);



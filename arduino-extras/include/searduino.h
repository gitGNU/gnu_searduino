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

#ifndef ARDUINO_EXTRAS_SETUP_H
#define ARDUINO_EXTRAS_SETUP_H

#include "setup.h"


#if defined ARDUINO == stub
#define ENABLE_SLEEP
#include <stdio.h>
#else
#undef ENABLE_SLEEP
#endif

#ifdef  ENABLE_SLEEP
#define   SEARDUINO_LOOP() for (;;)  \
    if      (searduino_is_paused())  { fprintf (stderr, "z"); usleep(1000*200); } \
    else if ( searduino_is_halted()) { fprintf (stderr, "Simulator halted, will return\n"); return 0; } \
    else  
#else
#define   SEARDUINO_LOOP() for (;;) 
#endif



#endif /* ARDUINO_EXTRAS_SETUP_H*/

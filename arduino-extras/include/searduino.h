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

#include "Arduino.h"

extern void serialEventRun(void) __attribute__((weak));


#ifdef SEARDUINO_STUB
#define ENABLE_SLEEP
#include "setup.h"
#include "searduino_pin.h"
#include "hid-generic.h"
#include <stdio.h>
extern int searduino_exec ;
extern int searduino_exec_available ;
#else
#undef ENABLE_SLEEP
#endif

#ifdef  ENABLE_SLEEP
#define   SEARDUINO_LOOP() searduino_exec_available = 1 ; for (;;)	\
    if      ( searduino_is_paused()) { fprintf (stderr, "z"); usleep(1000*200); } \
    else if ( searduino_is_halted()) { fprintf (stderr, "Simulator halted, will return\n"); return 0; } \
    else  
#else
#define   SEARDUINO_LOOP() for (;;) 
#endif


#define SEARDUINO_STUB_DEBUG(a)  fprintf(stderr, "[SEARDUINO DEBUG %s:%d:%s()]:  ",__FILE__,__LINE__,__func__); printf a; printf ("\n");
#ifdef  SEARDUINO_STUB
#define SEARDUINO_DEBUG(a)  SEARDUINO_STUB_DEBUG(a)
#else
#define SEARDUINO_DEBUG(a)
#endif  /* SEARDUINO_STUB */


/*
 *  USB stuff
 */
#ifndef  SEARDUINO_STUB
  #if defined(USBCON)
    #define searduino_usb_init()   USBDevice.attach()
    #define SEARDUINO_FLUSH_USB()  
  #else
    #define searduino_usb_init()   
    #define SEARDUINO_FLUSH_USB()  
  #endif
#else
  #if defined(USBCON)
    #define searduino_usb_init()  hid_initialise_hid();
    #define SEARDUINO_FLUSH_USB()  if (serialEventRun) serialEventRun()
  #else
    #define searduino_usb_init()   
    #define SEARDUINO_FLUSH_USB()  
  #endif
#endif  /* SEARDUINO_STUB */

#define SEARDUINO_LOG_NONE    0
#define SEARDUINO_LOG_ERROR   1
#define SEARDUINO_LOG_WARNING 2
#define SEARDUINO_LOG_DEBUG   3
#define SEARDUINO_LOG_INFO    4

/*
 *
 *  Logging functions 
 *
 *  API for simulator usage:
 *     void searduino_log_impl(int level, char *msg, ...)
 *  API for Arduinos:
 *     no implementation - this functions is intended for debugging 
 */
#ifndef  SEARDUINO_STUB
#define searduino_log(a) 
#else
#include "searduino_log.h"
#define searduino_log(a) searduino_log_impl a
#endif


#endif /* ARDUINO_EXTRAS_SETUP_H*/

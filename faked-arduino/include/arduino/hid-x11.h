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

/* TEMPORARILY WHILE DEVELOPING */
#define  USE_X11
/* EO TEMP */

#ifdef USE_X11

#include <Arduino.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

#ifdef __cplusplus
extern "C"{
#endif

int  hid_x11_initilise_hid(void);
void hid_x11_hid_mouse_move(signed char x, signed char y, signed char wheel);
int  hid_x11_hid_key(uint8_t k, uint8_t request );
int  hid_x11_hid_mouse(uint8_t b, uint8_t request);

int  hid_x11_enable_faked_hid(void);
int  hid_x11_disable_faked_hid(void);


#ifdef __cplusplus
}
#endif


#endif /* USE_X11 */

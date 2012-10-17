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

#ifndef SEARDUINO_MOUSE_H
#define SEARDUINO_MOUSE_H

#include <Arduino.h>
#include "searduino.h"

#ifdef __cplusplus
extern "C"{
#endif

#define MOUSE_LEFT_PIN  8
#define MOUSE_RIGHT_PIN 9
#define MOUSE_UP_PIN    10
#define MOUSE_DOWN_PIN  11

  void setup_mouse();
  void move_mouse(uint8_t x, uint8_t y, uint8_t times);
  void click_mouse(uint8_t b);
  void manage_mouse_pins(void);
  void init_mouse();

#ifdef __cplusplus
}
#endif


#endif /* SEARDUINO_MOUSE_H */

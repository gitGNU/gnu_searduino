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

#include "Arduino.h"
#include "arduino/pins_arduino.h"
#include "../include/arduino/error.h"
#include "utils/print.h"
#include "utils/types.h"
#include "arduino/error.h"
#include "utils/error.h"

#ifndef SEARDUINO_PIN_H
#define SEARDUINO_PIN_H

enum {
  SEARDUINO_PIN_TYPE_NONE    = 0,
  SEARDUINO_PIN_TYPE_DIGITAL = 1,
  SEARDUINO_PIN_TYPE_ANALOG  = 2,
  SEARDUINO_PIN_TYPE_PWM     = 3,
  SEARDUINO_PIN_TYPE_END     = 4
};


typedef struct arduino_pin
{
  uint8_t         type;  /* digital, analog, pwm */
  uint8_t         mode;
  int             val;
  struct timeval  last_write;
  struct timeval  last_actual_write;
  int             discard_ctr;
} arduino_pin;


int 
get_generic_pin_mode(uint8_t pin, uint8_t pin_type);

int 
set_generic_pin_mode(uint8_t pin, uint8_t mode, uint8_t pin_type);

int 
set_generic_pin_val_impl(uint8_t pin, int val, uint8_t pin_type, uint8_t exp_inout);

#define sim_set_generic_pin_val(pin, val, pin_type) \
   set_generic_pin_val_impl(pin, val, pin_type, INPUT);

#define set_generic_pin_val(pin, val, pin_type) \
   set_generic_pin_val_impl(pin, val, pin_type, OUTPUT);

int 
get_generic_pin_val(uint8_t pin, uint8_t pin_type);


#define NR_OF_ARDUINO_PINS 20

/*
 * #define PIN_OUT_OF_RANGE(pin)            (pin<0 || pin> NR_OF_ARDUINO_PINS) 
 * 
 * We don't need to check if >0 since it's an unsigned int
 */

#define PIN_OUT_OF_RANGE(pin)            (pin> NR_OF_ARDUINO_PINS)

#define get_digital_pin_mode(pin)        get_generic_pin_mode(pin, SEARDUINO_PIN_TYPE_DIGITAL)
#define set_digital_pin_mode(pin, mode)  set_generic_pin_mode(pin, mode, SEARDUINO_PIN_TYPE_DIGITAL)

#define get_analog_pin_mode(pin)        get_generic_pin_mode(pin, SEARDUINO_PIN_TYPE_ANALOG)
#define set_analog_pin_mode(pin, mode)  set_generic_pin_mode(pin, mode, SEARDUINO_PIN_TYPE_ANALOG)

#define get_digital_pin_val(pin)         get_generic_pin_val(pin, SEARDUINO_PIN_TYPE_DIGITAL)
#define set_digital_pin_val(pin,val)     set_generic_pin_val(pin, val, SEARDUINO_PIN_TYPE_DIGITAL)

#define sim_set_digital_pin_val(pin,val)     set_generic_pin_val(pin, val, SEARDUINO_PIN_TYPE_DIGITAL)

#define set_analog_pin_val(pin,val)      set_generic_pin_val(pin, val%1024, SEARDUINO_PIN_TYPE_ANALOG)
#define get_analog_pin_val(pin)          get_generic_pin_val(pin, SEARDUINO_PIN_TYPE_ANALOG)


void 
genericWrite(uint8_t pin, uint8_t val, uint8_t pin_type);

int 
get_pin_val(uint8_t pin);


void 
set_Write_timelimit(unsigned int lim);

unsigned int 
get_Write_timelimit(void);

int
output_callback(uint8_t pin, uint8_t pin_type);

uint8_t
digout_callback(uint8_t pin);

uint8_t
anaout_callback(uint8_t pin);

void init_arduino_pins(void);



#endif /* SEARDUINO_PIN_H */

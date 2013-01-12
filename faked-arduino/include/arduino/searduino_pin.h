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
#include "arduino/error.h"
#include "utils/print.h"
#include "utils/types.h"
#include "arduino/error.h"
#include "utils/error.h"
#include <sys/time.h>

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
  /* 
   * Pin capabilities / features
   */
  uint8_t         analog_in;  
  uint8_t         digital_out;  
  uint8_t         digital_in;  
  uint8_t         pwm_out;  
  /*  uint8_t         analog_out;  analog out = pwm out */
  /*  uint8_t         pwm_in;  pwm in = analog in*/
  uint8_t         output;  
  uint8_t         input;  


  /* 
   * Current pin values/settings
   */
  uint8_t         current_type;  
  uint8_t         current_mode;  
  int             current_value;   

  /* 
   * Internal variables to keep track of execution
   */
  struct timeval  last_write;
  struct timeval  last_actual_write;

  /* How many updates to same/current value have we discarded? */
  int             discard_ctr;

  int             in_use;

} arduino_pin;


int 
get_generic_pin_mode(uint8_t pin);

int 
set_generic_pin_mode(uint8_t pin, uint8_t mode);

int 
set_generic_pin_val_impl(uint8_t pin, unsigned int val, uint8_t pin_type, uint8_t exp_inout);

#define sim_set_generic_pin_val(pin, val, pin_type) \
   set_generic_pin_val_impl(pin, val, pin_type, INPUT);

#define set_generic_pin_val(pin, val, pin_type) \
   set_generic_pin_val_impl(pin, val, pin_type, OUTPUT);


/*
 * This function simply returns the value currently stored
 * in the pin struct. 
 *
 * It does not check for pin types, modes or anything.
 *
 */
int 
get_generic_pin_val(uint8_t pin);


#define NR_OF_ARDUINO_PINS 100

/*
 * #define PIN_OUT_OF_RANGE(pin)            (pin<0 || pin> NR_OF_ARDUINO_PINS) 
 * 
 * We don't need to check if >0 since it's an unsigned int
 */
#define PIN_OUT_OF_RANGE(pin)            (pin> NR_OF_ARDUINO_PINS)

#define get_digital_pin_mode(pin)        get_generic_pin_mode(pin)
#define set_digital_pin_mode(pin, mode)  set_generic_pin_mode(pin, mode)

#define get_analog_pin_mode(pin)         get_generic_pin_mode(pin)
#define set_analog_pin_mode(pin, mode)   set_generic_pin_mode(pin, mode)

#define get_digital_pin_val(pin)         get_generic_pin_val(pin)
#define set_digital_pin_val(pin,val)     set_generic_pin_val(pin, val, SEARDUINO_PIN_TYPE_DIGITAL)

#define sim_set_digital_pin_val(pin,val) set_generic_pin_val(pin, val, SEARDUINO_PIN_TYPE_DIGITAL)

#define set_analog_pin_val(pin,val)      set_generic_pin_val(pin, val%1024, SEARDUINO_PIN_TYPE_ANALOG)
#define get_analog_pin_val(pin)          get_generic_pin_val(pin)


void 
genericWrite(uint8_t pin, int val, uint8_t pin_type);

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

void 
init_arduino_pins(void);

void define_arduino_pin(uint8_t pin, 
			uint8_t analog_in, 
			uint8_t digital_out, 
			uint8_t digital_in, 
			uint8_t pwm_out);


int 
set_generic_pin_type(uint8_t pin, uint8_t pin_type);

int 
get_current_pin_type(uint8_t pin);

int 
has_generic_pin_type(uint8_t pin, uint8_t type);

int 
set_generic_nr_of_pins(void);

uint8_t
get_generic_nr_of_pins(void);


extern uint8_t A0 ;
extern uint8_t A1 ;
extern uint8_t A2 ;
extern uint8_t A3 ;
extern uint8_t A4 ;
extern uint8_t A5 ;
extern uint8_t A6 ;
extern uint8_t A7 ;
extern uint8_t A8 ;
extern uint8_t A9 ;
extern uint8_t A10 ;
extern uint8_t A11 ;
extern uint8_t A12 ;
extern uint8_t A13 ;
extern uint8_t A14 ;
extern uint8_t A15 ;


#endif /* SEARDUINO_PIN_H */

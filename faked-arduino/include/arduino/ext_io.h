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

#ifndef ARDUINO_EXT_IO_H
#define ARDUINO_EXT_IO_H

#include <stdio.h>

/*
 *
 *
 */
#define  SEARDUINO_STREAM_TERMINAL stdout
#define  SEARDUINO_STREAM_NETWORK
#define  SEARDUINO_STREAM_DEFAULT  SEARDUINO_STREAM_TERMINAL

#define  SEARD_SEARDUINO_OK            0
#define  SEARD_SEARDUINO_NULL_CALLBACK 1
#define  SEARD_INVALID_STREAM     2



/*
 * Function pointer definitions
 *  
 */
typedef void    (*dm_to_sim_callback_ptr)     (uint8_t pin, uint8_t mode); 
typedef void    (*out_to_sim_callback_ptr)    (uint8_t pin, unsigned int val, uint8_t pin_type); 
typedef void    (*log_to_sim_callback_ptr)    (uint8_t level, const char*);
typedef void    (*lcd_to_sim_callback_ptr)    (const char*, const char*);
typedef void    (*pintype_to_sim_callback_ptr)(uint8_t pin, uint8_t type); 


/*
 * Streams to print messages to
 */
extern FILE* proto_stream ;

/*
 * External function pointers
 */
extern dm_to_sim_callback_ptr  dm_sim_callback;
extern out_to_sim_callback_ptr out_sim_callback;
extern log_to_sim_callback_ptr log_sim_callback;
extern lcd_to_sim_callback_ptr lcd_sim_callback;


/*
 *
 * Description:   
 *  
 * Register a callback to get notifications on 
 *   digital out from as set by the Arduino program
 *
 * 
 * Function name: ext_register_digout_sim_cb
 *
 * Arguments:     do_to_sim_callback_ptr
 *
 *    cb callback to register
 *
 * Return:           uint8_t
 * ----------------------------------
 *    If ok:         SEARD_SEARDUINO_OK 
 *    if cb NULL     SEARD_SEARDUINO_NULL_CALLBACK
 *
 * Comment: This is used by simulator, comm module
 *          calls back on this function when an output
 *          digital pin is set in the Arduino code
 *
uint8_t ext_register_digout_sim_cb(do_to_sim_callback_ptr cb);
 */


/*
 *
 * Description:   
 *  
 *    Initialize the communication module
 * 
 * Function name: init_extio
 *
 * Arguments:     void
 *
 * Return:        void
 *
 */
void init_extio(void);

uint8_t
ext_register_pinout_sim_cb(out_to_sim_callback_ptr cb);

uint8_t
ext_register_log_cb(log_to_sim_callback_ptr cb);

uint8_t
ext_register_lcd_cb(lcd_to_sim_callback_ptr cb);

uint8_t
ext_register_dig_mode_sim_cb(dm_to_sim_callback_ptr cb);



/*
 *
 * Description:   
 *  
 *    Set stream to use for stub printout
 * 
 * Function name: set_proto_stream
 *
 * Arguments:     FILE *f
 *
 *    f - stream to print to
 *
 * Return:           uint8_t
 * ----------------------------------
 *    If ok:         SEARD_SEARDUINO_OK 
 *    if bad stream  SEARD_INVALID_STREAM
 *
 */
uint8_t set_proto_stream(FILE *f);



/*
 *
 * Description:   
 *  
 *    Get the value on the Arduino board's output pin
 * 
 * Function name: ext_get_dig_output
 *
 * Arguments:     uint8_t pin
 *
 *    pin - the to get output value for
 *
 *
 */
uint8_t ext_get_dig_output(uint8_t pin);



/*
 *
 * Description:   
 *  
 *    Set the value on the Arduino board's input pin
 * 
 * Function name: ext_set_dig_output
 *
 * Arguments:     uint8_t pin, uint8_t val
 *
 *    pin - input put to set
 *    val - value to set
 *
 *
 */
uint8_t ext_set_dig_input(uint8_t pin, uint8_t val);





/*
 * 
 * This is a prototype for the main function
 * in the simulator
 * 
 */
int searduino_main(void);

/*
 *  TODO: Document this function
 *
 *    ask registered callback for mode of pin
 *
 */
uint8_t 
ext_get_dig_mode(uint8_t pin);

uint8_t 
ext_set_ana_input(uint8_t pin, unsigned int val);

/*int 
ext_set_input(uint8_t pin, uint8_t val);
*/

int
ext_get_generic_output(uint8_t pin, uint8_t pin_type);

uint8_t
ext_set_generic_input(uint8_t pin, unsigned int val, uint8_t pin_type);

uint8_t 
ext_get_dig_mode(uint8_t pin);


/*
 *
 * Description:   
 *  
 *    Callback registered function (one function)
 *    with value and pin (Arduino board's output pins)
 * 
 * Function name: ext_digital_write_outpin
 *
 * Arguments:     uint8_t pin, uint8_t val
 *
 *    pin - the output pin to inform value for
 *    val - the value (for the pin) to report
 *
 * Return:        uint8_t
 *    If ok:      SEARD_SEARDUINO_OK 
 *
 */
uint8_t  ext_digital_write_outpin(uint8_t pin, uint8_t val);

/*
 *
 * Description:   searduino_enable_streamed_output
 *  
 *    Enable printouts to stream
 * 
 * Function name: 
 *
 * Arguments:     void
 *
 * Returns:       void
 *
 */
void searduino_enable_streamed_output(void);

/*
 *
 * Description:   searduino_disable_streamed_output
 *  
 *    Disable printouts to stream
 * 
 * Function name: 
 *
 * Arguments:     void
 *
 * Returns:       void
 *
 */
void searduino_disable_streamed_output(void);

uint8_t searduino_is_enable_streamed_output(void);

int 
ext_generic_write_outpin(uint8_t pin, unsigned int val, uint8_t pin_type);

int 
ext_digital_set_mode(uint8_t pin, uint8_t mode);

int 
ext_analog_set_mode(uint8_t pin, uint8_t mode);



#endif /* ARDUINO_EXT_IO_H */

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

#ifndef COMMUNICATION_COMM_H
#define COMMUNICATION_COMM_H




/*
 *
 *
 */
#define  COMM_STREAM_TERMINAL stdout
#define  COMM_STREAM_NETWORK
#define  COMM_STREAM_DEFAULT  COMM_STREAM_TERMINAL

#define  SEARD_COMM_OK            0
#define  SEARD_COMM_NULL_CALLBACK 1
#define  SEARD_INVALID_STREAM     2


/*
 * Function pointer definitions
 *  
 */
typedef void    (*di_callback_ptr)(uint8_t pin, uint8_t val); 
typedef void    (*do_to_sim_callback_ptr)(uint8_t pin, uint8_t val); 
typedef uint8_t (*do_callback_ptr)(uint8_t pin); 
typedef uint8_t (*d_mode_callback_ptr)(uint8_t pin); 

/*
 * Streams to print messages to
 */
extern FILE* proto_stream ;

/*
 * External function pointers
 */
extern di_callback_ptr di_callback;
extern do_callback_ptr do_callback;
extern do_to_sim_callback_ptr do_sim_callback;
extern d_mode_callback_ptr    d_mode_callback;

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
 *    If ok:         SEARD_COMM_OK 
 *    if bad stream  SEARD_INVALID_STREAM
 *
 */
uint8_t set_proto_stream(FILE *f);

/* void  comm_setup(void); */


/*
 *
 * Description:   
 *  
 *    Set callback for function anwsering on calls
 *    for the value of Arduino's digital input pin
 * 
 * Function name: comm_register_digin_cb
 *
 * Arguments:     di_callback_ptr cb
 *
 *    cb callback to register
 *
 * Return:           uint8_t
 * ----------------------------------
 *    If ok:         SEARD_COMM_OK 
 *    if cb NULL     SEARD_COMM_NULL_CALLBACK
 *
 * Comment: This is used by module "above" communication 
 *          (most likely faked-arduino/arduino). Comm
 *          module (this module) need to ask for values.
 *
 */
uint8_t comm_register_digin_cb(di_callback_ptr cb);

/*
 *
 * Description:   
 *  
 *    Set callback for function wanting info on 
 *    updates on Arduino's digital output pin
 * 
 * Function name: comm_register_digout_cb
 *
 * Arguments:     do_callback_ptr cb
 *
 *    cb callback to register
 *
 * Return:           uint8_t
 * ----------------------------------
 *    If ok:         SEARD_COMM_OK 
 *    if cb NULL     SEARD_COMM_NULL_CALLBACK
 *
 * Comment: This is used by module "above" communication 
 *          (most likely faked-arduino/arduino). Comm
 *          module (this module) need to ask for values.
 *
 */
uint8_t comm_register_digout_cb(do_callback_ptr cb);


/*
 *
 * Description:   
 *  
 * Register a callback to get notifications on 
 *   digital out from as set by the Arduino program
 *
 * 
 * Function name: comm_register_digout_sim_cb
 *
 * Arguments:     do_to_sim_callback_ptr
 *
 *    cb callback to register
 *
 * Return:           uint8_t
 * ----------------------------------
 *    If ok:         SEARD_COMM_OK 
 *    if cb NULL     SEARD_COMM_NULL_CALLBACK
 *
 * Comment: This is used by simulator, comm module
 *          calls back on this function when an output
 *          digital pin is set in the Arduino code
 *
 */
uint8_t comm_register_digout_sim_cb(do_to_sim_callback_ptr cb);


/*
 *
 * Description:   
 *  
 *    Initialize the communication module
 * 
 * Function name: init_comm
 *
 * Arguments:     void
 *
 * Return:        void
 *
 */
void init_comm(void);



#endif /* COMMUNICATION_COMM_H */

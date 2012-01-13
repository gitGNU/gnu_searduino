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


/*
 *%
 *
 */
#define  COMM_STREAM_TERMINAL stdout
#define  COMM_STREAM_NETWORK
#define  COMM_STREAM_DEFAULT  COMM_STREAM_TERMINAL

#define  SEARD_COMM_OK            0
#define  SEARD_COMM_NULL_CALLBACK 1

typedef void (*di_callback_ptr)(uint8_t pin, uint8_t val); 
typedef void (*do_to_sim_callback_ptr)(uint8_t pin, uint8_t val); 
typedef uint8_t (*do_callback_ptr)(uint8_t pin); 

extern FILE* proto_stream ;
extern di_callback_ptr di_callback;
extern do_callback_ptr do_callback;
extern do_to_sim_callback_ptr do_sim_callback;

int set_proto_stream(FILE *f);

void  comm_setup(void);

int comm_register_digin_cb(di_callback_ptr cb);

int comm_register_digout_cb(do_callback_ptr cb);


/*
 * 
 * Register a callback to get notifications on 
 *   digital out from as set by the Arduino program
 *
 */
int comm_register_digout_sim_cb(do_to_sim_callback_ptr cb);

void init_comm(void);




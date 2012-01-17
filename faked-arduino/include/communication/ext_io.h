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

#ifndef COMMUNICATION_EXT_IO_H
#define COMMUNICATION_EXT_IO_H

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



#endif /* COMMUNICATION_EXT_IO_H */

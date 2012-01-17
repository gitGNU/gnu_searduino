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

#ifndef COMMUNICATION_DIGIO_H
#define COMMUNICATION_DIGIO_H

/*
 *
 * Description:   
 *  
 *    Callback registered function (one function)
 *    with value and pin (Arduino board's output pins)
 * 
 * Function name: comm_digital_write_outpin
 *
 * Arguments:     uint8_t pin, uint8_t val
 *
 *    pin - the output pin to inform value for
 *    val - the value (for the pin) to report
 *
 * Return:        uint8_t
 *    If ok:      SEARD_COMM_OK 
 *
 */
uint8_t  comm_digital_write_outpin(uint8_t pin, uint8_t val);

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

#endif  /* COMMUNICATION_DIGIO_H */

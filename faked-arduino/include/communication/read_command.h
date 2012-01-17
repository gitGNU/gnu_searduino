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

#ifndef COMM_READ_COMMAND_H
#define COMM_READ_COMMAND_H

/*
 *
 * Description:   
 *  
 * Initialises the command reader
 * Creates and starts a thread, to get input from user via stdin
 *
 * 
 * Function name: init_command_reader
 *
 * Arguments:     none
 *
 * Return:        none
 *
 * Comment: 
 *          
 */
void init_command_reader(void);

/*
 *
 * Description:   
 *  
 * Function that actually reads input from user via stdin
 *
 * 
 * Function name: command_reader
 *
 * Arguments:     void *in
 *
 *    not used
 *
 * Return:        none
 *
 * Comment: 
 *          
 */
void* command_reader(void* in);



/*
 *
 * Description:   
 *  
 *    Enable command reader
 *
 * 
 * Function name: searduino_ensable_command_reader
 *
 * Arguments:     void
 *
 * Return:        none
 *
 * Comment: 
 *
 *    This has to be called before the call to init_command_reader
 *          
 */
void 
searduino_enable_command_reader(void);

/*
 *
 * Description:   
 *  
 *    Disable command reader
 *
 * 
 * Function name: searduino_disable_command_reader
 *
 * Arguments:     void
 *
 * Return:        none
 *
 * Comment: 
 *
 *    This has to be called before the call to init_command_reader
 *          
 */
void 
searduino_disable_command_reader(void);


#endif /* COMM_READ_COMMAND_H */

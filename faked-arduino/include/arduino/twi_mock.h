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

#ifndef _TWI_MOCK_H_
#define _TWI_MOCK_H_

#include <inttypes.h>

void twiMock_addTarget(uint8_t adress, void (*write)(uint8_t),
		       uint8_t (*read)(void));
/*uint8_t twiMock_writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait);*/


#endif // _TWI_MOCK_H_

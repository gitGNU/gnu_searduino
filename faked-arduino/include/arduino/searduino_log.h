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


#ifndef SEARDUINO_LOG_H
#define SEARDUINO_LOG_H

#ifndef  SEARDUINO_STUB
/* No implementation needed */
#error Should not reach this place when compiling for Arduino 

#else
int  searduino_log_impl(int , char *, ...);
int  searduino_log_set_file(char *);
int  searduino_get_log_level(void);
int  searduino_set_log_level(int);
int  searduino_inc_log_level(void);
int  searduino_dec_log_level(void);
#endif /* SEARDUINO_STUB */




#endif /* SEARDUINO_LOG_H */

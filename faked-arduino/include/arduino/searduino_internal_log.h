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


#ifndef SEARDUINO_INTERNAL_LOG_H
#define SEARDUINO_INTERNAL_LOG_H

#ifdef NO_INTERNAL_DEBUGGING

#define searduino_internal_log_i
#define searduino_internal_log_w
#define searduino_internal_log_e
#define searduino_internal_log_impl
#define searduino_internal_init_log
#define searduino_internal_log_close_file
#define searduino_internal_get_log_level
#define searduino_internal_set_log_level
#define searduino_internal_inc_log_level
#define searduino_internal_dec_log_level

#else

#include "searduino_log_impl.h"
extern searduino_logger *internal_logger;

#define LOG_FUNCTION() \
  searduino_internal_log_d("%s(...)\n", \
    __func__);	

#define LOG_PIN_VAL_FUNCTION(pin, val)\
  searduino_internal_log_d("%s(%d,%d ...)\n", \
   __func__, pin, val);	

#define LOG_PIN_FUNCTION(pin)\
  searduino_internal_log_d("%s(%d ...)\n", \
    __func__, pin);	

int  searduino_internal_log_d(char *, ...);	
int  searduino_internal_log_i(char *, ...);	
int  searduino_internal_log_w(char *, ...);	
int  searduino_internal_log_e(char *, ...);	
int  searduino_internal_log_impl(int , char *, ...);
int  searduino_internal_init_log(char * name);
void searduino_internal_log_close_file(void);
int  searduino_internal_get_log_level(void);
int  searduino_internal_set_log_level(int);
int  searduino_internal_inc_log_level(void);
int  searduino_internal_dec_log_level(void);

#endif

#endif /* SEARDUINO_INTERNAL_LOG_H */

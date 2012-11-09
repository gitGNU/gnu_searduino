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

#ifndef SEARDUINO_LOG_IMPL_H
#define SEARDUINO_LOG_IMPL_H

#include "searduino.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int   current_log_level;
  FILE *logfile;
  int   counter;
  int   initialised;
} searduino_logger ;


int searduino_internal_init_log(char * name);
/* int searduino_logger_set_file(searduino_logger *logger, char *fname); */
/* int searduino_logger_get_log_level(searduino_logger *logger); */
/* int searduino_logger_set_log_level(searduino_logger *logger, int level); */
/* int searduino_logger_inc_log_level(searduino_logger *logger); */
/* int searduino_logger_dec_log_level(searduino_logger *logger); */
int searduino_logger_log_impl(searduino_logger *logger, 
			      int level, 
			      char *msg,   va_list ap);
void searduino_logger_log_close_file(searduino_logger *logger);


#endif /* SEARDUINO_LOG_IMPL_H */

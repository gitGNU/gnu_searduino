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

#include "searduino.h"
#include "searduino_log.h"
#include "searduino_log_impl.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#ifndef  SEARDUINO_STUB
/* No implementation needed */

#else


static searduino_logger logger;

int searduino_log_set_file(char *fname)
{
  return searduino_logger_set_file(&logger, fname);
}

int searduino_get_log_level(void)
{
  return searduino_logger_get_log_level(&logger);
}

int searduino_set_log_level(int level)
{
  return searduino_logger_set_log_level(&logger, level);
}

int searduino_inc_log_level(void)
{
  return searduino_logger_inc_log_level(&logger);
}

int searduino_dec_log_level(void)
{
  return searduino_logger_dec_log_level(&logger);
}


int searduino_log_impl(int level, char *msg, ...)
{
  va_list ap;
  int ret ; 

  va_start(ap, msg);
  ret = searduino_logger_log_impl(&logger, level, msg, ap );
  va_end(ap);
  return ret;
}


void searduino_log_close_file(void)
{
  searduino_logger_log_close_file(&logger);
}

#endif /* SEARDUINO_STUB */

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
#include "searduino_log_impl.h"
#include "searduino_internal_log.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef  SEARDUINO_STUB
/* No implementation needed */

#else


/* Stub only */

searduino_logger  internal_logger_impl;
searduino_logger *internal_logger;

int searduino_internal_init_log(char * name)
{
  char *env_var ; 
  int level ;


  if (internal_logger_impl.initialised!=0)
    {
      return 0;
    }

  internal_logger = &internal_logger_impl;

  env_var = getenv("SEARDUINO_LOG");
  if (env_var!=NULL)
    {
      name = env_var;
    }

  if (name==NULL)
    {
      return 0;
    }

  searduino_logger_set_file(internal_logger, name);
  level = atoi(getenv("SEARDUINO_LOG_LEVEL"));
  searduino_logger_set_log_level(internal_logger, level);

  return 0;
}

/*
int searduino_internal_get_log_level(void)
{
  return searduino_logger_get_log_level(&logger);
}

int searduino_internal_set_log_level(int level)
{
  return searduino_logger_set_log_level(&logger, level);
}

int searduino_internal_inc_log_level(void)
{
  return searduino_logger_inc_log_level(&logger);
}

int searduino_internal_dec_log_level(void)
{
  return searduino_logger_dec_log_level(&logger);
}

*/

int searduino_internal_log_impl(int level, char *msg, ...)
{
  va_list ap;
  int ret ; 

  va_start(ap, msg);
  ret = searduino_logger_log_impl(internal_logger, level, msg, ap );
  va_end(ap);
  return ret;
}


int searduino_internal_log_w(char * msg, ...)
{
  va_list ap;
  int ret ; 

  va_start(ap, msg);
  ret = searduino_logger_log_impl(internal_logger, 
				  SEARDUINO_LOG_LEVEL_WARNING, 
				  msg, 
				  ap );
  va_end(ap);
  return ret;
}

int searduino_internal_log_i(char * msg, ...)
{
  va_list ap;
  int ret ; 

  va_start(ap, msg);
  ret = searduino_logger_log_impl(internal_logger, 
				  SEARDUINO_LOG_LEVEL_INFO, 
				  msg, 
				  ap );
  va_end(ap);
  return ret;
}

int searduino_internal_log_e(char *msg, ...)
{
  va_list ap;
  int ret ; 

  va_start(ap, msg);
  ret = searduino_logger_log_impl(internal_logger, 
				  SEARDUINO_LOG_LEVEL_ERROR, 
				  msg, 
				  ap );
  va_end(ap);
  return ret;
}

int searduino_internal_log_d(char *msg, ...)
{
  va_list ap;
  int ret ; 

  va_start(ap, msg);
  ret = searduino_logger_log_impl(internal_logger, 
				  SEARDUINO_LOG_LEVEL_DEBUG, 
				  msg, 
				  ap );
  va_end(ap);
  return ret;
}

void searduino_internal_log_close_file(void)
{
  if (internal_logger_impl.logfile==NULL)
    {
      return;
    }

  searduino_logger_log_close_file(internal_logger);
}

#endif /* SEARDUINO_STUB */

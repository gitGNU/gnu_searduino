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

#include "searduino_log.h"
#include <stdarg.h>
#include <stdio.h>

static int current_log_level;

int searduino_get_log_level(void)
{
  return current_log_level;
}

int searduino_set_log_level(int level)
{
  if (level < 0 )
    {
      fprintf (stderr, "Can't set log level lower than 0\n");
      return -1;
    }
  else if (level > 10 )
    {
      fprintf (stderr, "Can't set log level higher than 10\n");
      return -1;
    }
  current_log_level = level;
  return 0;
}

int searduino_inc_log_level(void)
{
  current_log_level++;
  return current_log_level;
}

int searduino_dec_log_level(void)
{
  current_log_level--;
  if ( current_log_level < 0 ) 
    {
      current_log_level = 0 ;
    }
  return current_log_level;
}


int searduino_log_impl(int level, char *msg, ...)
{
  va_list ap;
  int ret ; 

  ret = 0 ;
  if ( level <= current_log_level )
    {
      va_start(ap, msg);
      ret = fprintf(stderr, msg, ap );
      fflush(stderr);
    }
  return ret;
}

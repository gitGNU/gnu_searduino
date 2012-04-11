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

#include "Arduino.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include "utils/print.h"
#include "arduino/ext_io.h"


void
print_function_name (FILE* stream,  const char *fun, char * str,  ...) 
{
  va_list ap;
  char buffer[256];

  va_start(ap, str);
  fprintf (stderr, "%s (", fun);
  vsprintf (buffer, str, ap);
  fprintf (stream,"%s)\n",buffer);
  va_end(ap);

  return;
}


void 
print_dummy_function_implementation (FILE* stream,  
				     const char *file, 
				     int line, 
				     const char *fun) 
{
  fprintf (stream, "%s:%d %s ()", file, line, fun);
  fprintf (stream," - stub implementation.  *** WARNING, this function has no real implementation ***\n");
  return;
}

void 
log_generic(int level, char* s, ...)
{
  va_list ap;
  char buffer[256];

  va_start(ap, s);
  vsprintf (buffer, s, ap);
  va_end(ap);

  if (log_sim_callback!=NULL)
    {
      log_sim_callback(level, buffer);
    }
}

void 
log_error(char* s, ...)
{
  va_list ap;
  char buffer[256];

  va_start(ap, s);
  vsprintf (buffer, s, ap);
  va_end(ap);

  if (log_sim_callback!=NULL)
    {
      log_sim_callback(SEARDUINO_LOG_LEVEL_ERROR, buffer);
    }
}

void 
log_warning(char* s, ...)
{
  va_list ap;
  char buffer[256];

  va_start(ap, s);
  vsprintf (buffer, s, ap);
  va_end(ap);

  if (log_sim_callback!=NULL)
    {
      log_sim_callback(SEARDUINO_LOG_LEVEL_WARNING, buffer);
    }
}


void 
serial_print_s(char* s, ...)
{
  va_list ap;
  char buffer[256];

  va_start(ap, s);
  vsprintf (buffer, s, ap);
  va_end(ap);

  if (log_sim_callback!=NULL)
    {
      log_sim_callback(SEARDUINO_LOG_SERIAL, buffer);
    }
}

void 
serial_print_c(char c )
{
  char buffer[10];

  sprintf(buffer, "%d", c);
  if (log_sim_callback!=NULL)
    {
      log_sim_callback(SEARDUINO_LOG_SERIAL, buffer);
    }
}


/* Make the functions (who calls C++ methods) available in C */
extern "C" {

  void serial_printer_s(char *s)
  {
    Serial.println(s);
  }
  
  void serial_printer_c(char c)
  {
    Serial.println(c);
  }
  
}

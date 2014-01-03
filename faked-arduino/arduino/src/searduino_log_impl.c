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
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef  SEARDUINO_STUB
/* No implementation needed */

#else

static void init_searduino_logger(searduino_logger *logger)
{
  if ( (logger==NULL) || (logger->initialised!=0) )

    {
      return ;
    }
  
  logger->logfile     = stderr;
  logger->counter     = 0;
  logger->initialised = 1;

  return;
}



/* Stub only */

int searduino_logger_set_file(searduino_logger *logger, char *fname)
{
  /* make sure we get a proper logger */
  if (logger==NULL)
    {
      return 1;
    }

  /* Make sure we're initialised*/
  init_searduino_logger(logger);

  /* Gracefully close previous log file if any */
  searduino_logger_log_close_file(logger);

  if ( (fname==NULL) || strncmp(fname, "stderr", strlen("stderr"))==0)
    {
      logger->logfile = stderr;
    }
  else if (strncmp(fname, "stdout", strlen("stdout"))==0)
    {
      logger->logfile = stdout;
    }
  else
    {
      logger->logfile = fopen (fname,"a");
      if (logger->logfile==NULL)
	{
	  return 1;
	}
      searduino_log_impl(SEARDUINO_LOG_INFO, "Log started\n");
    }
  return 0;
}


int searduino_logger_get_log_level(searduino_logger *logger)
{
  /* make sure we get a proper logger */
  if (logger==NULL)
    {
      return 1;
    }
  
  return logger->current_log_level;
}

int searduino_logger_set_log_level(searduino_logger *logger, int level)
{
  /* make sure we get a proper logger */
  if (logger==NULL)
    {
      return 1;
    }

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
  logger->current_log_level = level;
  return 0;
}

int searduino_logger_inc_log_level(searduino_logger *logger)
{
  /* make sure we get a proper logger */
  if (logger==NULL)
    {
      return 1;
    }

  logger->current_log_level++;

  /* if we wrap around */
  if ( logger->current_log_level < 0 ) 
    {
      logger->current_log_level--;
    }
  return logger->current_log_level;
}

int searduino_logger_dec_log_level(searduino_logger *logger)
{
  /* make sure we get a proper logger */
  if (logger==NULL)
    {
      return 1;
    }

  logger->current_log_level--;
  if ( logger->current_log_level < 0 ) 
    {
      logger->current_log_level = 0 ;
    }
  return logger->current_log_level;
}


int searduino_logger_log_impl(searduino_logger *logger, 
			      int level, 
			      char *msg, 
			      va_list ap)
{
  int ret ; 
  FILE *fp;
  static int intro_printed = 0;

  time_t curtime;
  struct tm *loctime;


  /* make sure we get a proper logger */
  if (logger==NULL)
    {
      return 1;
    }

  if ( !( level <= logger->current_log_level ))
    {
      return 0;
    }

  if (logger->logfile==NULL)
    {
      fp = stderr;
    }
  else
    {
      fp = logger->logfile;
    }

  ret = 0 ;

  /* printf ("LEVEL  %d %d  %d \n",   */
  /*  	  level,  logger->current_log_level, ( level <= logger->current_log_level )); */

  curtime = time (NULL); 
  loctime = localtime (&curtime);
  if ( intro_printed == 0 )
    {
      fprintf(fp, " -- Log file for %s (%s) --\n", PACKAGE, VERSION);
      fprintf(fp, " -- Created: %.4d-%.2d-%.2d %.2d:%.2d:%.2d --\n", 
	      1900+loctime->tm_year,
	      loctime->tm_mon,
	      loctime->tm_mday,
	      loctime->tm_hour,
	      loctime->tm_min,
	      loctime->tm_sec  );
      intro_printed = 1;
      
    }
  fprintf(fp, "[%.2d:%.2d:%.2d] ", 
	  loctime->tm_hour,
	  loctime->tm_min,
	  loctime->tm_sec  );
  
  ret = vfprintf(fp, msg, ap );
  fflush(fp);

  return ret;
}


void searduino_logger_log_close_file(searduino_logger *logger)
{
  /* make sure we get a proper logger */
  if (logger==NULL)
    {
      return ;
    }

  if (logger->logfile!=NULL)
    {
      if ( (logger->logfile!=stderr) && (logger->logfile!=stdout) )
	{
	  fclose(logger->logfile);
	}
    }
}

#endif /* SEARDUINO_STUB */

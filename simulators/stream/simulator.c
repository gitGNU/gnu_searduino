/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2011, 2012, 2013 Henrik Sandklef 
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

#ifndef __MINGW32__
#define _XOPEN_SOURCE 500
#endif
#include <Arduino.h>

#include <stdio.h>
#include "seasim/seasim.h"
#include <pthread.h>


#ifndef __MINGW32__
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
void sim_sighandler(int sig);
#endif

pthread_t arduino_thread;

/* 
 * Function to register in the Searduino code
 *
 * This function will be called every time the Arduino program updates a digital output pin (on change only!)
 */
void 
my_out_sim_callback(uint8_t pin, unsigned int val, uint8_t pin_type)
{
  fprintf (stdout,"SIM:%d:%d:%d\n",pin_type, pin, val);
}

/* 
 * Function to register in the Searduino code
 *
 * This function will be called every time the Arduino program updates a digital mode on a digital pin (on change only!)
 */
void 
my_dm_sim_callback(uint8_t pin, uint8_t mode)
{
  fprintf (stdout,"digmod:%d:%d\n",pin, mode);
}

void
lcd_callback(const char *str1, const char *str2)
{
#define LCD_COLS 16
#define LCD_HEADER() {printf ("+"); int i; for (i=0;i<LCD_COLS;i++) { printf ("-"); } printf("+\n");}
#define LCD_FOOTER() LCD_HEADER()
  LCD_HEADER();
  printf ("|%s|\n" , " LCD - printout ");
  LCD_HEADER();
  printf ("|%-16s|\n" , str1);
  printf ("|%-16s|\n" , str2);
  LCD_HEADER();
  fflush(stdout);
}

void
log_callback(uint8_t level, const char *str)
{
  static char serial_buf[1000];
  static int serial_pos;

  switch (level)
    {
    case SEARDUINO_LOG_LEVEL_NONE:
      break;
    case SEARDUINO_LOG_LEVEL_INFO:
      printf ("INFO:    %s", str);
      break;
    case SEARDUINO_LOG_LEVEL_WARNING:
      printf ("WARNING: %s", str);
      break;
    case SEARDUINO_LOG_LEVEL_ERROR:
      printf ("ERROR:   %s", str);
      break;
    case SEARDUINO_LOG_SERIAL:
      if (str[0]=='\0') 
	{
	  fprintf (stdout, "SERIAL: %s\n", serial_buf);
	  fflush(stdout);
	  serial_pos=0;
	  serial_buf[0]='\0';
	}
      else 
	{
	  strcat(&serial_buf[serial_pos], str);
	  serial_pos = serial_pos + strlen(str);
	}
      break;
    default:
      break;
    }
}


int 
sim_setup(char *ard_board, char *ard_lib)
{
  int ret ; 

  seasim_disable_streamed_output();

  seasim_set_board_name(ard_board);

  seasim_set_arduino_code_name(ard_lib);

  ret = seasim_setup();
  if (ret!=0)
    {
      return ret;
    }
  
  ret  = seasim_register_out_sim_cb(my_out_sim_callback);
  if (ret != SEARD_ARDUINO_OK)
    {
      fprintf (stderr, "Failed to register callback for Digital output (pin, val)\n");
      return ret;
    }
 

  ret  = seasim_register_dig_mode_sim_cb(my_dm_sim_callback);
  if (ret != SEARD_ARDUINO_OK)
    {
      fprintf (stderr, "Failed to register callback for Digital mode (pin, mode)\n");
      return ret;
    }

  seasim_register_log_cb(log_callback);

  seasim_register_lcd_cb(lcd_callback);

  printf ("CHECK IF REGISTRATION SUCCEEDED\n");

  usleep(1000*1000*3);
  return 0;
}


void* arduino_code(void *in)
{
  if (searduino_main_entry!=NULL)
    {
      searduino_main_entry(NULL);
    }
  else
    {
      fprintf (stderr, "Couldn't find an entry point for the Arduino code.\n");
      fprintf (stderr, "This probably means you haven't provided searduino with a shared library containing Arduino code\n");
      fflush (stderr);
    }

  printf ("\n");
#ifndef __MINGW32__
  printf ("*** Searduino will now try to close the simulator\n");
  printf ("*** If this fails, type 'quit' followed by enter (or press Ctrl-c) ***\n");
  kill(getpid(), SIGUSR1);
#endif
  return NULL;
}

void* command_reader(void* in)
{
  char buf[100];
  char *tmp;
  int  pin;
  int  val;
  int  type;

  /* printf ("COMMAND READER begins\n"); */
    
  for (;;)
    {
/*       printf ("COMMAND READER reads\n"); */
      fgets(buf, 100, stdin);
/*       printf ("Just read: '%s'\n", buf);  */
      
      if (strncmp(buf,"pin:",4)==0)
	{
	  tmp=&buf[4];
/* 	  printf (": '%s'\n", buf);  */
/*  	  printf ("will parse: '%s'\n", tmp);  */
	  sscanf(tmp, "%d:%d:%d", &type, &pin, &val);
  	  printf ("SIM WILL SET pin:%d val:%d type:%d  \n", pin, val, type);  
	  if (type == SEARDUINO_PIN_TYPE_ANALOG)
	    {
	      seasim_fake_analog_input (pin, val);
	    }
	  else
	    {
	      seasim_fake_digital_input (pin, val);
	    }
	}
      else if (strncmp(buf,"quit",4)==0)
	{
	  seasim_set_halted();
	  return NULL;
	}
      else if (strncmp(buf,"pause",5)==0)
	{
	  printf ("Will pause sim\n");
	  seasim_set_paused();
	}
      else if (strncmp(buf,"a",1)==0)
	{
	  static int a=255;
	  printf ("\n\tSETTING %d\n", a);
	  printf ("%s (%d,%d)\n", __func__, 14, a);
	  seasim_fake_analog_input (14, (unsigned int)a++);
	}
      else if (strncmp(buf,"resume",5)==0)
	{
	  printf ("Will resume sim\n");
	  seasim_set_running();
	}
      else if (strncmp(buf,"limit",5)==0)
	{
	  printf ("setting limit\n");
	  set_write_timelimit(100000);
	}
      else if (strncmp(buf,"ulimit",5)==0)
	{
	  printf ("setting limit\n");
	  set_write_timelimit(10);
	}
      else if (strncmp(buf,"quit",4)==0)
	{
	  return NULL;
	}
      usleep (100);
    }
}


static const char* I2C_CODE_ARG_LONG  = "--i2c-code";
static const char* I2C_CODE_ARG_SHORT = "-ic";
static const char* ARDUINO_CODE_ARG_LONG  = "--arduino-code";
static const char* ARDUINO_CODE_ARG_SHORT = "-ac";
static const char* ARDUINO_BOARD_ARG_LONG  = "--board";
static const char* ARDUINO_BOARD_ARG_SHORT = "-b";
static const char* INTERNAL_LOG_LONG  = "--log-level";
static const char* INTERNAL_LOG_SHORT  = "-l";
static const char* HELP_ARG_LONG  = "--help";
static const char* HELP_ARG_SHORT = "-h";
static const char* VERSION_ARG_LONG  = "--version";
static const char* VERSION_ARG_SHORT = "-V";


static void usage(void)
{
  printf ("NAME\n");
  printf ("\tsearduino-stream-sim\n");
  printf ("\n");
  printf ("VERSION\n");
  printf ("\t%s\n", seasim_get_searduino_version());
  printf ("\n");
  printf ("PROJECT\n");
  printf ("\t%s\n",  seasim_get_searduino_name());
  printf ("\n");
  printf ("OPTIONS\n");
  printf ("\t%s, %s <library>\n", ARDUINO_CODE_ARG_LONG, ARDUINO_CODE_ARG_SHORT);
  printf ("\t\tspecify what arduino code (shared library) to load\n");
  printf ("\t%s, %s <library>\n", I2C_CODE_ARG_LONG, I2C_CODE_ARG_SHORT);
  printf ("\t\tspecify what I2C code (shared library) to load\n");
  printf ("\t%s, %s <library>\n", HELP_ARG_LONG, HELP_ARG_SHORT);
  printf ("\t\tprint this text\n");
  printf ("\n");
}

static void version(void)
{
  printf ("%s\n", seasim_get_searduino_version());
}

#define ARGCMP(arg, along, ashort) 					\
    ( ( strncmp(arg, along, strlen(along))==0)				\
      ||								\
      ( strncmp(arg, ashort, strlen(ashort))==0))


static void 
close_simulator(pthread_t *t)
{
  static int already_closed = 0;

  if (!already_closed)
    {
      printf ("Waiting for simulator thread to return\n");
      pthread_join(*t, NULL);
      
      usleep(1000*100);
      fflush(stdout);
      printf ("\n *** Simulator will now be closed ***\n");
      fflush(stdout);
      already_closed = 1 ;
    }
}

int 
main(int argc, char **argv)
{
  /* pthread_t command_thread; */
  char *ard_code  = "" ;
  char *ard_board = "" ;
  int i = 0;
  int ret;
  int internal_log=0;

  for (i=1;i<argc;i++)
    {
    
      printf ("PARSE: %s\n", argv[i]);

      if (ARGCMP(argv[i], 
		 ARDUINO_CODE_ARG_LONG, 
		 ARDUINO_CODE_ARG_SHORT))
	{
	  if (argv[i+1]==NULL)
	    {
	      printf ("Missing argument to %s, %s\n",
		      ARDUINO_CODE_ARG_LONG, ARDUINO_CODE_ARG_SHORT);
	      return 1;
	    }
	  else
	    {
	      ard_code = argv[i+1];
	      i++;
	    }
	}
      else if (ARGCMP(argv[i], 
		 ARDUINO_BOARD_ARG_LONG, 
		 ARDUINO_BOARD_ARG_SHORT))
	{
	  if (argv[i+1]==NULL)
	    {
	      printf ("Missing argument to %s, %s\n",
		      ARDUINO_BOARD_ARG_LONG, ARDUINO_BOARD_ARG_SHORT);
	      return 1;
	    }
	  else
	    {
	      ard_board = argv[i+1];
	      i++;
	    }
	}
      else if (ARGCMP(argv[i], 
		 INTERNAL_LOG_LONG, 
		 INTERNAL_LOG_SHORT))
	{
	  if (argv[i+1]==NULL)
	    {
	      printf ("Missing argument to %s, %s\n",
		      INTERNAL_LOG_LONG, 
		      INTERNAL_LOG_SHORT);
	      return 1;
	    }
	  else
	    {
	      internal_log = atoi(argv[i+1]);
	      i++;
	    }
	}
      else if (ARGCMP(argv[i], 
		 I2C_CODE_ARG_LONG, 
		 I2C_CODE_ARG_LONG))
	{
	  if (argv[2]==NULL)
	    {
	      printf ("Missing argument to %s, %s\n",
		      I2C_CODE_ARG_LONG, I2C_CODE_ARG_SHORT);
	      return 1;
	    }
	  else
	    {
	      ret = seasim_i2c_add_device (50, 
					   argv[i+1]);
	      if (ret!=0)
		{
		  fprintf(stderr, "Failed to load I2C library\n");
		  usage();
		  return 1;
		}

	      i++;
	    }
	}
      else if (ARGCMP(argv[i], 
		 HELP_ARG_LONG, 
		 HELP_ARG_SHORT))
	{
	  usage();
	  return 0;
	}
      else if (ARGCMP(argv[i], 
		 VERSION_ARG_LONG, 
		 VERSION_ARG_SHORT))
	{
	  version();
	  return 0;
	}
      else
	{
	  usage();
	  return 1;
	}

    }


  printf ("Done parsing\n");
#ifndef __MINGW32__
  signal(SIGUSR1, sim_sighandler);
#endif
  
  if ( (ard_board == NULL) || (strlen(ard_board)==0) )
    {
      fprintf(stderr, "Missing board information.... assuming Uno\n");
      ard_board="Uno";
    }
  if ( ( ard_code==NULL) || ( strlen(ard_code)==0) )
    {
      fprintf(stderr, "Missing arduino code to load\n");
      return 1;
    }

  /* printf ("Using arduino code from library: %s\n",  ard_code);  */
  /* printf ("Using arduino board: %s\n",  ard_board);  */
  if (strncmp(ard_board, "stub", strlen("stub"))==0) 
    {    
      sim_setup("uno", ard_code);
    } 
  else 
    {
      sim_setup(ard_board, ard_code);
    }

  if ( internal_log != 0 ) 
    {
      seasim_set_log_level(internal_log);
    }

  pthread_create(&arduino_thread, NULL, arduino_code, NULL);

  command_reader(NULL);

  close_simulator(&arduino_thread);

  return 0;
}

#ifndef __MINGW32__
void sim_sighandler(int sig)
{
  close_simulator(&arduino_thread);
  exit(0);
}
#endif

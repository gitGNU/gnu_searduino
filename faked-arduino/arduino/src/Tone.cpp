/*****
 *                                                                   
 *               Searduino
 *                      
 *   Copyright (C) 2014 Henrik Sandklef 
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
#include "searduino.h"

#define NR_TONE_PINS 10
typedef struct {
  unsigned int   pin;
  struct timeval stop_time;
} tone_pin;

static tone_pin tone_pins[NR_TONE_PINS];

#define TONE_PIN_SET_INACTIVE(i)        tone_pins[i].pin = -1
#define TONE_PIN_SET_ACTIVE(i, kingpin) tone_pins[i].pin = kingpin
#define TONE_PIN_SET_STOP(i, ts)        tone_pins[i].stop_time = ts
#define TONE_PIN(i)                     tone_pins[i].pin
#define TONE_PIN_STOP_TIME(i)           tone_pins[i].stop_time

/* internal functions */
static void init_tone_pins() ;
void check_tone_pins() ;

/* ------------------ */

static int8_t toneBegin(uint8_t _pin)
{
  return 0;
}


void tone(uint8_t _pin, unsigned int frequency, unsigned long duration)
{
  int i;
  int pin;
  struct timeval current_time;
  init_tone_pins();
  check_tone_pins();

  for (i=0;i<NR_TONE_PINS;i++) 
    {
      // printf ("  find free pin entry at %d\n", i);
      /* find first unused entry */
      pin = TONE_PIN(i) ;
      if (pin==_pin)  
	{
	  // printf ("  find earlier pin entry at %d YES!!!!!  ===> %d\n", i, TONE_PIN(i));
	  break;
	}
      else if (pin==-1) 
	{
	  TONE_PIN_SET_ACTIVE(i, _pin);
	  // printf ("  find free pin entry at %d YES!!!!!  ===> %d\n", i, TONE_PIN(i));
	  break;
	}
    }
  
  if (i>=0 && i<(NR_TONE_PINS-1)) 
    {
      int unsigned long secs;
      int unsigned long usecs;
      int unsigned long sum_usecs;

      gettimeofday(&current_time, NULL);
      
      usecs = current_time.tv_usec;
      secs = current_time.tv_sec;

      sum_usecs = usecs + duration*1000;
      secs      = secs + sum_usecs/1000000;
      usecs     = sum_usecs % 1000000;

      // printf ("TIME: %ld %ld + %ld => \n      %ld %ld\n",
      // 	      current_time.tv_sec, current_time.tv_usec,
      // 	      duration*1000, 
      // 	      secs, usecs);

      current_time.tv_usec = usecs;
      current_time.tv_sec  = secs;


      
      TONE_PIN_SET_STOP(i, current_time);

    }
  analogWrite(_pin, 255);
}


void disableTimer(uint8_t _timer)
{
  ;
}


void noTone(uint8_t _pin)
{
  int i;

  for (i=0;i<NR_TONE_PINS;i++) 
    {
      if (_pin==TONE_PIN(i)) 
	{
	  TONE_PIN_SET_INACTIVE(i);
	  analogWrite(_pin, 0);
	}
    }
}


static void init_tone_pins() 
{
  static int is_initialised=0;
  int i ;

  if (is_initialised!=0) 
    {
      return;
    }

  printf("INIT TONE PINS\n");

  for (i=0;i<NR_TONE_PINS;i++) 
    {
      TONE_PIN_SET_INACTIVE(i);      
    }
  is_initialised=1;
}

static long has_timeout(struct timeval *curr_time, struct timeval *stop_time)
{
  long sec_diff;
  long usec_diff;

  sec_diff  =  curr_time->tv_sec  - stop_time->tv_sec   ;
  usec_diff =  curr_time->tv_usec - stop_time->tv_usec  ;

  // printf ("         DIFFS: %ld %ld\n", 
  // 	  sec_diff, usec_diff);

  if ( (sec_diff<0) || (usec_diff<0) )
    {
      return 0;
    }

  return 1;
}

void check_tone_pins() 
{
  int i ;
  int pin;

  for (i=0;i<NR_TONE_PINS;i++) 
    {
      pin = TONE_PIN(i) ;

      if (pin!=-1) 
	{
	  struct timeval stop_time = TONE_PIN_STOP_TIME(i);
	  struct timeval current_time ;
	  gettimeofday(&current_time, NULL);

	  if (has_timeout(&current_time, &stop_time) ) 
	    {
	      printf ("TIMEOUT.....on pin %d\n", TONE_PIN(i));
	      
	      /* Dont break the order of the two calls below */
	      analogWrite(TONE_PIN(i), 0);
	      TONE_PIN_SET_INACTIVE(i);
	    }
	  
	}
    }
}

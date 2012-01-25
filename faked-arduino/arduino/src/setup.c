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


#include "arduino/wiring_private.h"
#include "arduino/pins_arduino.h"
#include "../include/error.h"
#include "utils/print.h"
#include "utils/types.h"
#include "arduino/error.h"
#include "utils/error.h"
#include "communication/comm.h"

void     digin_callback (uint8_t pin, uint8_t val); 
uint8_t  digout_callback(uint8_t pin);
uint8_t  dig_mode_callback(uint8_t pin);

static int searduino_exec ;

#define SEARDUIONO_SIM_PAUSE   0
#define SEARDUIONO_SIM_RUNNING 1
#define SEARDUIONO_SIM_HALTED  2

uint8_t searduino_is_paused(void)
{
  return (searduino_exec==SEARDUIONO_SIM_PAUSE);
}

uint8_t searduino_is_halted(void)
{
  return (searduino_exec==SEARDUIONO_SIM_HALTED);
}

uint8_t searduino_is_running(void)
{
  return (searduino_exec==SEARDUIONO_SIM_RUNNING);
}

void searduino_set_paused(void)
{
  searduino_exec=SEARDUIONO_SIM_PAUSE;
}

void searduino_set_running(void)
{
  searduino_exec=SEARDUIONO_SIM_RUNNING;
}

void searduino_set_halted(void)
{
  searduino_exec=SEARDUIONO_SIM_HALTED;
}

void searduino_setup(void)
{
  static int already_setup = 0;
  int ret;

  if (already_setup)
    {
      return;
    }
  PRINT_FUNCTION_NAME_NOARGS();

  init_comm();

  init_time();

  ret = comm_register_digin_cb(digin_callback);
  if (ret != SEARD_COMM_OK)
    {
      fprintf(stderr, "Failed to register di callback");
    }

  ret = comm_register_digout_cb(digout_callback);
  if (ret != SEARD_COMM_OK)
    {
      fprintf(stderr, "Failed to register do callback");
    }

  ret = comm_register_dig_mode_sim_cb(dig_mode_callback);
  if (ret != SEARD_COMM_OK)
    {
      fprintf(stderr, "Failed to register do callback");
    }


  searduino_set_running();

  already_setup=1;
}


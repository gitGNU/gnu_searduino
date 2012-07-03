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

#include <Arduino.h>
#include "searduino.h"

#include <mouse.h>
#include <kbd.h>

#define STEPS 30

void setup()
{
  searduino_usb_init();
  init();

#ifdef SEARDUINO_STUB
  /* By default Searduino faked hid is *NOT* enabled */
  hid_enable_faked_hid();
#endif

  setup_mouse();
  setup_kbd();
}

int main(void)
{
  setup();

  while(1)
    {
      move_mouse( 1,  0,  STEPS);
      move_mouse( 0,  1,  STEPS);
      move_mouse(-1,  0,  STEPS);
      move_mouse( 0, -1,  STEPS);
      move_mouse( 1,  1,  STEPS);
      move_mouse(-1, -1,  STEPS);

      press_key(38);
      delay(100);
      release_key(38);
      delay(1000);

      click_mouse(1);
      delay(1000);
    }

}


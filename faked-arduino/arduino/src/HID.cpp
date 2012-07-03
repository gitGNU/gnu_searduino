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

#include "Platform.h"
#include "USBAPI.h"
#include "USBDesc.h"


#include "Platform.h"
#include "USBAPI.h"
#include "USBDesc.h"

#include "searduino.h"
#include "hid-generic.h"
#include "hid-x11.h"

#include <unistd.h>

#if defined(USBCON)
#ifdef HID_ENABLED

Mouse_    Mouse;
Keyboard_ Keyboard;

#define NR_OF_BUTTONS 3
static uint8_t mouse_buttons[NR_OF_BUTTONS];

#define WEAK __attribute__ ((weak))


int WEAK HID_GetInterface(u8* interfaceNum)
{
  return 0;
}

int WEAK HID_GetDescriptor(int i)
{
  return 0;
}

void WEAK HID_SendReport(u8 id, const void* data, int len)
{
  ;
}

bool WEAK HID_Setup(Setup& setup)
{
  return true;
}

//================================================================================
//================================================================================
//	Mouse

Mouse_::Mouse_(void) : _buttons(0)
{
}

void Mouse_::begin(void) 
{
}

void Mouse_::end(void) 
{
}

void Mouse_::click(uint8_t b)
{
  if (b>=NR_OF_BUTTONS)
    {
      fprintf(stderr, "Trying to click too high button nr (%d)\n", b);
      return ;
    }
  fprintf (stderr, "Mouse_::click(%d)\n", b); 
  press(b) ;
  usleep(1000);
  release(b) ;
}

void Mouse_::move(signed char x, signed char y, signed char wheel)
{
  fprintf (stderr, "Mouse_::move(%d,%d,%d)\n", x,y,wheel); 
#ifdef USE_X11
  hid_x11_hid_mouse_move(x,y,wheel);
#endif    
}

void Mouse_::buttons(uint8_t b)
{
  ;
}

void Mouse_::press(uint8_t b) 
{
  fprintf (stderr, "Mouse_::press(%d)\n", b); 
  if (b>=NR_OF_BUTTONS)
    {
      fprintf(stderr, "Trying to press too high button nr (%d)\n", b);
      return ;
    }
  mouse_buttons[b]=BUTTON_PRESS;
#ifdef USE_X11
  hid_x11_hid_mouse(b, BUTTON_PRESS);
#endif    
}

void Mouse_::release(uint8_t b)
{
  fprintf (stderr, "Mouse_::press(%d)\n", b); 
  if (b>=NR_OF_BUTTONS)
    {
      fprintf(stderr, "Trying to release too high button nr (%d)\n", b);
      return ;
    }
  mouse_buttons[b]=BUTTON_RELEASE;
#ifdef USE_X11
  hid_x11_hid_mouse(b, BUTTON_RELEASE);
#endif    
}

bool Mouse_::isPressed(uint8_t b)
{
  if (b>=NR_OF_BUTTONS)
    {
      fprintf(stderr, "Trying to check if button with too high nr (%d) is pressed\n", b);
      return (1==0);
    }
  return (mouse_buttons[b]==BUTTON_PRESSED);
}

Keyboard_::Keyboard_(void) 
{
}

void Keyboard_::begin(void) 
{
}

void Keyboard_::end(void) 
{
}

void Keyboard_::sendReport(KeyReport* keys)
{
  ;
}


uint8_t USBPutChar(uint8_t c);

size_t Keyboard_::press(uint8_t k) 
{
  fprintf (stderr, "Keyboard__::press(%d)\n", k); 
#ifdef USE_X11
  hid_x11_hid_key(k, KEY_PRESS);
#endif    
  
  return 1;
}

size_t Keyboard_::release(uint8_t k) 
{
  fprintf (stderr, "Keyboard__::press(%d)\n", k); 
#ifdef USE_X11
  hid_x11_hid_key(k, KEY_RELEASE);
#endif    
  
  return 1;
}

void Keyboard_::releaseAll(void)
{
  ;
}

size_t Keyboard_::write(uint8_t c)
{	
  fprintf (stderr, "Keyboard__::write(%d)\n", c); 
  press(c);
  usleep(1000);
  release(c);

  return 0;
}

#endif

#endif /* if defined(USBCON) */

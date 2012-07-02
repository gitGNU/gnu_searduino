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


#include "hid-generic.h"
#include "hid-x11.h"

#ifdef USE_X11

#include <stdio.h>

Display *dpy      = NULL;
char     x11_used = 0;
char     xtest_available = 0;

int x11_initilise_hid(void)
{
  int	 xtest_version_major ;  /*!< Major version number of XTest */
  int    xtest_version_minor ;  /*!< Minor version number of XTest */
  int	 xtest_error_basep   ;  /*!< First error number for this extension*/
  int    xtest_event_basep   ;  /*!< First event number for this extension*/
  
  dpy = XOpenDisplay(NULL);
  if (dpy==NULL)
    {
      fprintf(stderr, 
	      "Could not open display. "
	      "Not using X11/XTest for faked HID\n");
      return 1;
    }

  /* fprintf(stderr, "Dpy at: %p\n", dpy); */
  
  if( XTestQueryExtension(dpy,
                          &xtest_event_basep,
                          &xtest_error_basep,
                          &xtest_version_major,
                          &xtest_version_minor) == 0 )
    {
      fprintf(stderr,"XTest extension missing\n");
    }
  else
    {
      xtest_available = 1;
    }
  /* XTestGrabControl (dpy, True); */

  return 0;
}

void x11_hid_mouse_move(signed char x, signed char y, signed char wheel)
{
  if ( (x11_used!=0) && (dpy!=NULL))
    {
      fprintf(stderr, "X11:move %d,%d  \n", x, y);
      /* XSync(dpy, True); */
      XTestFakeRelativeMotionEvent(dpy, 
				   x, 
				   y,
				   0);
      XFlush(dpy);
    }
}  

int x11_hid_key(uint8_t k, uint8_t request )
{
  if ( (x11_used!=0) && (dpy!=NULL))
    {
      fprintf(stderr, "X11:key %d,%d  \n", k, request);
      XTestFakeKeyEvent(dpy, k, request==KEY_PRESS?True:False, 0);
      XFlush(dpy);
    }
  return 0;
}


int  x11_enable_faked_hid(void)
{
  if (xtest_available != 0 )
    {
      x11_used = 1;
    }
  return 0;
}

int  x11_disable_faked_hid(void)
{
  x11_used = 0;
  return 0;
}

int x11_hid_mouse(uint8_t b, uint8_t request)
{
  if ( (x11_used!=0) && (dpy!=NULL))
    {
      fprintf(stderr, "X11:mouse %d,%d  \n", b, request);
      XTestFakeButtonEvent(dpy, b, request==KEY_PRESS?True:False, 0);
      XFlush(dpy);
    }
  return 0;
}



#endif /* USE_X11 */


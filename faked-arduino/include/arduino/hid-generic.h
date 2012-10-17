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



#ifndef HID_GENERIC_H
#define HID_GENERIC_H

enum KEY_STATES
  {
    KEY_RELEASED,
    KEY_PRESSED
  } ;

enum BUTTON_STATES
  {
    BUTTON_RELEASED,
    BUTTON_PRESSED
  } ;

enum KEY_REQUESTS
  {
    KEY_RELEASE,
    KEY_PRESS
  } ;

enum BUTTON_REQUESTS
  {
    BUTTON_RELEASE,
    BUTTON_PRESS
  } ;



#ifdef __cplusplus
extern "C"{
#endif

int hid_initialise_hid(void);
int hid_enable_faked_hid(void);
int hid_disable_faked_hid(void);

#ifdef __cplusplus
}
#endif


#endif /* HID_GENERIC_H */

/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2012, 2015 Henrik Sandklef 
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

#if defined(USBCON)


static inline void WaitIN(void)
{
  ;
}

static inline void ClearIN(void)
{
  ;
}

static inline void WaitOUT(void)
{
  ;
}

static inline u8 WaitForINOrOUT()
{
  return 0;
}

static inline void ClearOUT(void)
{
  ;
}

void Recv(volatile u8* data, u8 count)
{
  printf ("USB:Recv\n");
}

static inline u8 Recv8()
{
  printf ("USB:Recv8\n");
  return 0;	
}

static inline void Send8(u8 d)
{
  ;
}

static inline void SetEP(u8 ep)
{
  ;
}

static inline u8 FifoByteCount()
{
  return 0;
}

static inline u8 ReceivedSetupInt()
{
  return 0;
}

static inline void ClearSetupInt()
{
  ;
}

static inline void Stall()
{
  ;
}

static inline u8 ReadWriteAllowed()
{
  return 0;
}

static inline u8 Stalled()
{
  return 0;
}

static inline u8 FifoFree()
{
  return 0;
}

static inline void ReleaseRX()
{
  ;
}

static inline void ReleaseTX()
{
  ;
}

static inline u8 FrameNumber()
{
  return 0;
}

//==================================================================
//==================================================================

u8 USBGetConfiguration(void)
{
  printf ("USB:USBGetConfiguration\n");
  return 0;
}


//	Number of bytes, assumes a rx endpoint
u8 USB_Available(u8 ep)
{
  return 0;
}

//	Non Blocking receive
//	Return number of bytes read
int USB_Recv(u8 ep, void* d, int len)
{
  return 0;
}

//	Recv 1 byte if ready
int USB_Recv(u8 ep)
{
  return 0;
}

//	Space in send EP
u8 USB_SendSpace(u8 ep)
{
  return 0;
}

//	Blocking Send of data to an endpoint
int USB_Send(u8 ep, const void* d, int len)
{
  return 0;
}


static
void InitEP(u8 index, u8 type, u8 size)
{
  ;
}

static
void InitEndpoints()
{
  ;
}

//	Handle CLASS_INTERFACE requests
static
bool ClassInterfaceRequest(Setup& setup)
{
  return true;
}

void InitControl(int end)
{
  ;
}

static
bool SendControl(u8 d)
{
  return true;
}

//	Clipped by _cmark/_cend
int USB_SendControl(u8 flags, const void* d, int len)
{
  return 0;
}

int USB_RecvControl(void* d, int len)
{
	return 0;
}

int SendInterfaces()
{
  return 0;
}

static
bool SendConfiguration(int maxlen)
{
  return true;
}

static
bool SendDescriptor(Setup& setup)
{
	return true;
}


void USB_Flush(u8 ep)
{
  ;
}


//	VBUS or counting frames
//	Any frame counting?
u8 USBConnected()
{
  return 0;
}

//=======================================================================
//=======================================================================

USBDevice_ USB;

USBDevice_::USBDevice_()
{
}

void USBDevice_::attach()
{
  ;
}

void USBDevice_::detach()
{
}

bool USBDevice_::configured()
{
  return 0;
}

void USBDevice_::poll()
{
}

#endif /* if defined(USBCON) */

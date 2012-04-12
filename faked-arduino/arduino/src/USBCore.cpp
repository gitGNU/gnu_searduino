

/* Copyright (c) 2010, Peter Barrett  
**  
** Permission to use, copy, modify, and/or distribute this software for  
** any purpose with or without fee is hereby granted, provided that the  
** above copyright notice and this permission notice appear in all copies.  
** 
** THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL  
** WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED  
** WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR  
** BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES  
** OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,  
** WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  
** ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS  
** SOFTWARE.  
*/

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
  ;
}

static inline u8 Stalled()
{
  ;
}

static inline u8 FifoFree()
{
  ;
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
  ;
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
  ;
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
};

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

USB_ USB;

USB_::USB_()
{
}

void USB_::attach()
{
  ;
}

void USB_::detach()
{
}

bool USB_::configured()
{
  return 0;
}

void USB_::poll()
{
}

#endif /* if defined(USBCON) */

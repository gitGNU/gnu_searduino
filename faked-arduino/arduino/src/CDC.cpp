#define USBCON
#define CDC_ENABLED

#include "Platform.h"
#include "Stream.h"
#include "USBAPI.h"

#if defined(USBCON)
#ifdef CDC_ENABLED

void Reboot()
{
  printf ("Reboot called in CDC.cpp\n");
}

int CDC_GetInterface(u8* interfaceNum)
{
  return 0;
}

bool CDC_Setup(Setup& setup)
{
  return false;
}

int _serialPeek = -1;
void Serial_::begin(uint16_t baud_count)
{
  ;
}

void Serial_::end(void)
{
  ;
}

int Serial_::available(void)
{
  return USB_Available(CDC_RX);
}

//	peek is nasty
int Serial_::peek(void)
{
  return 0;
}

int Serial_::read(void)
{
  return 0;
}

void Serial_::flush(void)
{
  ;
}

size_t Serial_::write(uint8_t c)
{
  Serial.println(c);
}

Serial_ Serial;


#endif
#endif /* if defined(USBCON) */

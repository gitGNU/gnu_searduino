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




#if defined(UBRRH) || defined(UBRR0H) || defined(UBRR1H) || defined(UBRR2H) || defined(UBRR3H)

#include <HardwareSerial.h>
#include "utils/print.h"

#define SERIAL_BUFFER_SIZE 16


struct ring_buffer
{
  unsigned char buffer[SERIAL_BUFFER_SIZE];
  volatile int head;
  volatile int tail;
};

inline void store_char(unsigned char c, ring_buffer *buffer)
{

}

void serialEventRun(void)
{
}

HardwareSerial::HardwareSerial(ring_buffer *rx_buffer, ring_buffer *tx_buffer,
  volatile uint8_t *ubrrh, volatile uint8_t *ubrrl,
  volatile uint8_t *ucsra, volatile uint8_t *ucsrb,
  volatile uint8_t *udr,
  uint8_t rxen, uint8_t txen, uint8_t rxcie, uint8_t udrie, uint8_t u2x)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

void HardwareSerial::begin(unsigned long baud)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}


void HardwareSerial::end()
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

int HardwareSerial::available(void)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

int HardwareSerial::peek(void)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

int HardwareSerial::read(void)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

void HardwareSerial::flush()
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

size_t HardwareSerial::write(uint8_t c)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}


HardwareSerial Serial(&rx_buffer, &tx_buffer, &UBRR0H, &UBRR0L, &UCSR0A, &UCSR0B, &UDR0, RXEN0, TXEN0, RXCIE0, UDRIE0, U2X0);


#endif // whole file




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

extern "C" {
  #include "utils/types.h"
  #include "utils/print.h"
}

#include <iostream> 
#include "Wire.h"

using namespace std;

TwoWire::TwoWire()
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}


void TwoWire::begin(void)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

void TwoWire::begin(uint8_t address)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

void TwoWire::begin(int address)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

void TwoWire::beginTransmission(uint8_t address)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

void TwoWire::beginTransmission(int address)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

uint8_t TwoWire::endTransmission(void)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

size_t TwoWire::write(uint8_t data)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
  return 0;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
  return 0;
}

int TwoWire::available(void)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
  return 0;
}

int TwoWire::read(void)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
  return 0;
}

int TwoWire::peek(void)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
  return 0;
}

void TwoWire::flush(void)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

void TwoWire::onReceiveService(uint8_t* inBytes, int numBytes)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

void TwoWire::onRequestService(void)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

void TwoWire::onReceive( void (*function)(int) )
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

void TwoWire::onRequest( void (*function)(void) )
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
  return 42;
}

/* 
 *   pre instantiate object, just as Arduino does it 
 */
TwoWire Wire = TwoWire();

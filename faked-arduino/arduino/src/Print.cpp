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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Arduino.h"
//#include "serduino.h"
#include "Print.h"
#include "utils/print.h"

// Default impl, feel free to override this 
size_t Print::write(const uint8_t *buffer, size_t size)
{
  size_t n = 0;
  while (size--) {
#ifdef TESTING
    n += printf ("%c",(*buffer++));
#endif
    n += write((uint8_t)*buffer++);
  }
  write((uint8_t)0);
  return n;
}

size_t Print::print(const __FlashStringHelper *ifsh)
{
  printf ("Print::print() empty impl.\n");
  return 0;
}

size_t Print::print(const String &s)
{


  size_t n = 0;
  log_generic(5, (char *)"Print::print(const String &s)\n");
  for (uint16_t i = 0; i < s.length(); i++) {
    n += printf("%c", (s[i]));
  }
  return n;
}

size_t Print::print(const char str[])
{
  //  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();

  /* len is used to return the length to the Arduino code
  *  We don't care how many chars have been written
  */
  unsigned int len;

  /* Make sure string is not null ;)
   *   ... do we get higher comment grade from this comment? */
  if (str!=NULL){
    write (str);
#ifdef TESTING
    len = strlen(str);

    /* ... and finally: print it to the simulator */
    //    printf ("str=%s\n", str);
    serial_print_s((char *)str);
    return len;
#endif 
    return 0;
  }
  return 0;
}

size_t Print::print(char c)
{ 
  printf ("C=%d\n", c);
  serial_print_c(c);
  return 1;
}

size_t Print::print(unsigned char b, int base)
{
  return print((unsigned long) b, base);
}

size_t Print::print(int n, int base)
{
  return print((long) n, base);
}

size_t Print::print(unsigned int n, int base)
{
  return print((unsigned long) n, base);
}

size_t Print::print(long n, int base)
{
  if (base == 0) {
    return printf("%ld",n);
  } else if (base == 10) {
    serial_print_l(n);
    //    PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
  }
  return 0;
}



size_t Print::print(unsigned long n, int base)
{
  write (n);
  return 0;
  /*
  static char buf[] = {0,0};
  if (base < 0) 
    {
      printf ("LOG SERIAL: %c\n",  (char)n);
      buf[0]=n;
      log_sim_callback(SEARDUINO_LOG_SERIAL, buf);
    }
  else printf("%lu",n);
  return 0;
  */
}

size_t Print::print(double n, int digits)
{
  /* Do as Arduino */
  return printFloat(n, digits);
}

size_t Print::println(const __FlashStringHelper *ifsh)
{
  /* Do as Arduino */
  size_t n = print(ifsh);
  n += println();
  return n;
}

size_t Print::print(const Printable& x)
{
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
  return 0;
}

size_t Print::println(void)
{
  size_t n = printf("%c",'\r');
  n += printf("%c",'\n');
  return n;
}

size_t Print::println(const String &s)
{
  /* Do as Arduino */
  size_t n = print(s);
  n += println();
  return n;
}

size_t Print::println(const char c[])
{
  static int ctr;
  // printf ("%d ", ctr++);
  /* Do as Arduino */
  size_t n = print(c);
  n += println();
  return n;
}

size_t Print::println(char c)
{
  /* Do as Arduino */
  size_t n = print(c);
  n += println();
  return n;
}

size_t Print::println(unsigned char b, int base)
{
  /* Do as Arduino */
  size_t n = print(b, base);
  n += println();
  return n;
}

size_t Print::println(int num, int base)
{
  /* Do as Arduino */
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(unsigned int num, int base)
{
  /* Do as Arduino */
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(long num, int base)
{
  /* Do as Arduino */
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(unsigned long num, int base)
{
  /* Do as Arduino */
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(double num, int digits)
{
  /* Do as Arduino */
  size_t n = print(num, digits);
  n += println();
  return n;
}

size_t Print::println(const Printable& x)
{
  /* Do as Arduino */
  size_t n = print(x);
  n += println();
  return n;
}

// Private Methods /////////////////////////////////////////////////////////////

size_t Print::printNumber(unsigned long n, uint8_t base) {
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
  return 0;
}

size_t Print::printFloat(double number, uint8_t digits) 
{ 
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
  return 0;
}


#include <Arduino.h>
#include <searduino.h>

uint8_t get_distance(void)
{
  uint8_t ret = (analogRead(11) + analogRead(12)); 
  return ret ; 
}



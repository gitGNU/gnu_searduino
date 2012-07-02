#include <Arduino.h>
#include "searduino.h"
#include <kbd.h>


void setup_kbd()
{
  ;
}

void press_key(uint8_t k)
{
  Keyboard.press(k);
}

void release_key(uint8_t k)
{
  Keyboard.release(k);
}


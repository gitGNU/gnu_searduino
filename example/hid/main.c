#include <Arduino.h>
#include "searduino.h"

#include <mouse.h>
#include <kbd.h>

#define STEPS 30

void setup()
{
  searduino_usb_init();
  init();

  x11_enable_faked_hid();

  setup_mouse();
  setup_kbd();
}

int main(void)
{
  setup();

  while(1)
    {
      move_mouse( 1,  0,  STEPS);
      move_mouse( 0,  1,  STEPS);
      move_mouse(-1,  0,  STEPS);
      move_mouse( 0, -1,  STEPS);
      move_mouse( 1,  1,  STEPS);
      move_mouse(-1, -1,  STEPS);

      press_key(38);
      delay(100);
      release_key(38);
      delay(1000);
    }
}


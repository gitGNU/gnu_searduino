#include <Arduino.h>
#include "searduino.h"

void
setup()
{
  pinMode(13, OUTPUT);
  Mouse.begin();
  delay(20);
}

void move_mouse(uint8_t x, uint8_t y, uint8_t times)
{
  uint8_t i;

  digitalWrite(13,1);
  for (i=0;i<times;i++)
    {
      digitalWrite(13,i%2);
      Mouse.move(x,y,0);
      delay(10);
    }
  digitalWrite(13,0);
}

int main(void)
{
  #define STEPS 30
  init();
  searduino_usb_init();
  setup();

  while(1)
    {
      move_mouse( 1,  0,  STEPS);
      move_mouse( 0,  1,  STEPS);
      move_mouse(-1,  0,  STEPS);
      move_mouse( 0, -1,  STEPS);
      move_mouse( 1,  1,  STEPS);
      move_mouse(-1, -1,  STEPS);
    }
}

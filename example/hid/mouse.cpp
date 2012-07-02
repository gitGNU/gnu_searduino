#include <Arduino.h>
#include "searduino.h"
#include "mouse.h"

void
setup_mouse()
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

void click_mouse(uint8_t b)
{
  digitalWrite(13,1);
  Mouse.click(b);
  delay(100);
  Mouse.press(b);
  delay(100);
  Mouse.release(b);
  delay(100);
  digitalWrite(13,0);
}


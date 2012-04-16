#include <Arduino.h>
#include <searduino.h>

void setup()
{
  pinMode(13, OUTPUT);
}


int main(void)
{
  init();

  setup();

  for(;;)
    {    
      digitalWrite(13, 1);
      delay(100);
      digitalWrite(13, 0);
      delay(100);
    }

  return 0;
}

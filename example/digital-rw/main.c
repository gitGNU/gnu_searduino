#include <Arduino.h>
#include "searduino.h"


void setup(void)
{
  pinMode(13, OUTPUT);
}


int main(void)
{
  
  init();
  setup();

  /* The following line uses a Saerduino macro 
   * You could use a plain "for (;;)" instead
   */
  SEARDUINO_LOOP()
    {
      digitalWrite(13, 1);
      delay(100);
      digitalWrite(13, 0);
      delay(100);
    }
}




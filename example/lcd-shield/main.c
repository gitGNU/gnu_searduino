#include <Arduino.h>
#include "searduino.h"


void setup()
{
  lcd_setup();
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
      read_and_write() ;
    }

}


#ifndef SEARDUINO_KBD_H
#define SEARDUINO_KBD_H

#include <Arduino.h>
#include "searduino.h"


#ifdef __cplusplus
extern "C"{
#endif

void setup_kbd();
void press_key(uint8_t k);
void release_key(uint8_t k);

#ifdef __cplusplus
}
#endif


#endif /* SEARDUINO_KBD_H */

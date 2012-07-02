#ifndef SEARDUINO_MOUSE_H
#define SEARDUINO_MOUSE_H

#include <Arduino.h>
#include "searduino.h"

#ifdef __cplusplus
extern "C"{
#endif

void setup_mouse();
void move_mouse(uint8_t x, uint8_t y, uint8_t times);

#ifdef __cplusplus
}
#endif


#endif /* SEARDUINO_MOUSE_H */

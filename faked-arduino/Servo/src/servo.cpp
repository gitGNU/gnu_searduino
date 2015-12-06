/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2012 Henrik Sandklef 
 *                                                                   
 * This program is free software; you can redistribute it and/or     
 * modify it under the terms of the GNU General Public License       
 * as published by the Free Software Foundation; either version 3    
 * of the License, or any later version.                             
 *                                                                   
 *                                                                   
 * This program is distributed in the hope that it will be useful,   
 * but WITHOUT ANY WARRANTY; without even the implied warranty of    
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     
 * GNU General Public License for more details.                      
 *                                                                   
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software       
 * Foundation, Inc., 51 Franklin Street, Boston,            
 * MA  02110-1301, USA.                                              
 ****/

extern "C" {
  #include "utils/types.h"
  #include "utils/print.h"
}

/* 
 *
 *  define NEW_H - Arduino sources defines it since avr doesn't
 * 
 */
#define NEW_H

#include <iostream>
#include <Arduino.h> 
#include "Servo.h"

using namespace std;

uint8_t ServoCount = 0;
static servo_t servos[MAX_SERVOS];

#define SERVO_MIN() (MIN_PULSE_WIDTH - this->min * 4) //minimum value in uS for this servo
#define SERVO_MAX() (MAX_PULSE_WIDTH - this->max * 4) //maximum value in uS for this servo
#define TRIM_DURATION       2

Servo::Servo() {
  if(ServoCount < MAX_SERVOS) {
    this->servoIndex = ServoCount++;
    servos[this->servoIndex].ticks = DEFAULT_PULSE_WIDTH;
  }
  else {
    this->servoIndex = INVALID_SERVO;
  }
}

uint8_t Servo::attach(int pin) {
  return this->attach(pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}

uint8_t Servo::attach(int pin, int min, int max) {
  if(this->servoIndex < MAX_SERVOS) {
    this->min = (MIN_PULSE_WIDTH - min)/4;
    this->max = (MAX_PULSE_WIDTH - max)/4;
    servos[this->servoIndex].Pin.isActive = true;
  }
  return this->servoIndex;
}

void Servo::detach() {
  servos[this->servoIndex].Pin.isActive = false;
}

void Servo::write(int value) {
  if(value < MIN_PULSE_WIDTH) { /* angle (in degree) instead of microseconds */
    if(value < 0)   value = 0;
    if(value > 180) value = 180;
    value = map(value, 0, 180, SERVO_MIN(), SERVO_MAX());
  }
  this->writeMicroseconds(value);
}
    
void Servo::writeMicroseconds(int value) {
  if(this->servoIndex < MAX_SERVOS) {
    if(value < SERVO_MIN()) {
      value = SERVO_MIN();
    }
    else if(value > SERVO_MAX()) {
      value = SERVO_MAX();
    }
    servos[this->servoIndex].ticks = value;
  }
}

int Servo::read() {
  return map(this->readMicroseconds() + 1, SERVO_MIN(), SERVO_MAX(), 0, 180);
}

int Servo::readMicroseconds() {
  int pulseWidth;
  if(this->servoIndex != INVALID_SERVO) {
    pulseWidth = servos[this->servoIndex].ticks; /* Not acctually ticks, but we don't need it in the mock-implementation */
  }
  else {
    pulseWidth = 0;
  }

  return pulseWidth;
}

bool Servo::attached(){
  return servos[this->servoIndex].Pin.isActive;
}

/*****
 *    
 *                   Searduino                                       
 *                                                                   
 *   Copyright (C) 2012 Viktor Green                              
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

#include <stdlib.h> 
#include "twi_mock.h"
#include "twi.h"
#include "utils/print.h"

struct mockTarget {
  uint8_t address;
  void (*write)(uint8_t);
  uint8_t (*read)(void);
  void (*end)(void);
  struct mockTarget* next;
};

struct mockTarget* createTarget(uint8_t address, void (*write)(uint8_t),
				uint8_t (*read)(void), void (*end)(void),
				struct mockTarget* next);

struct mockTarget* twiTargetList;


void twiMock_addTarget(uint8_t address, void (*write)(uint8_t),
		       uint8_t (*read)(void), void (*end)(void)) {
  struct mockTarget* target;
  struct mockTarget* last;

  if(twiTargetList == NULL) {
    twiTargetList = createTarget(address, write, read, end, NULL);
    return;
  }

  target = last = twiTargetList;
  while(target != NULL) {
    if(target->address == address) {
      /*
       * Something is wrong, there should not be two targets with
       * the same address.
       * The user must have done something wrong
       */
      return;
    }

    if(target->address > address) {
      /* Insert target in the linked list */
      last->next = createTarget(address, write, read, end, target);
      if(last->next == NULL) {
	last->next = target;
      }
      return;
    }

    last = target;
    target = target->next;
  }

  /* Target should be at the end of the list */

  last->next = createTarget(address, write, read, end, NULL);
  /* 
   * Does not matter if createTarget returns NULL, since that was
   * the previos value anyway
   */

  return;
}

void twi_init(void) {
  /* Do nothing, original code initializes timers/prescalers and pins here */
}

void twi_setAddress(uint8_t address) {
  /* The twi mock/fake/sim can not be a slave at the moment */
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

uint8_t twi_readFrom(uint8_t address, uint8_t* data, uint8_t length, uint8_t sendStop) {
  
  struct mockTarget* target;
  uint8_t i;

  /* If length is too long, return 0 (indicating no data is read) */
  if(TWI_BUFFER_LENGTH < length) {
    return 0;
  }

  target = twiTargetList;

  /* Find target in address list */

  while(target != NULL && target->address != address) target = target->next;
  if(target == NULL) return 0; /* address not in list, no data is read */

  for(i = 0; i < length; i++) {
    data[i] = target->read();
  }

  /* Tell the target that this transmission is completed */
  target->end();

  return length;
}

uint8_t twi_writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait, uint8_t sendStop) {
  uint8_t i;
  struct mockTarget* target;
  
  if(TWI_BUFFER_LENGTH < length) {
    return 1;
  }

  /* original code waits for TWI to become ready */

  target = twiTargetList;

  /* Find target in address list */
  while(target != NULL && target->address != address) target = target->next;
  if(target == NULL) return 2; /* address not in list */
  
  for(i = 0; i < length; i++) {
    target->write(data[i]);
  }

  /* Tell the target that the transmission has ended */

  target->end();

  return 0; /* success */
}

uint8_t twi_transmit(const uint8_t* data, uint8_t length) {
  /* The twi mock/fake/sim can not be a slave at the moment */
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
  return 2; /* 2 = not a slave transmitter */
}

void twi_attachSlaveRxEvent(void (*function)(uint8_t*, int)) {
  /* The twi mock/fake/sim can not be a slave at the moment */
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

void twi_attachSlaveTxEvent(void (*function)(void)) {
  /* The twi mock/fake/sim can not be a slave at the moment */
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

void twi_reply(uint8_t ack) {
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

void twi_stop(void) {
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

void twi_releaseBus(void) {
  PRINT_DUMMY_FUNCTION_IMPLEMENTATION();
}

struct mockTarget* createTarget(uint8_t address, void (*write)(uint8_t),
				uint8_t (*read)(void), void (*end)(void),
				struct mockTarget* next) {
  struct mockTarget* t = malloc(sizeof(struct mockTarget));
  if(t == NULL) return NULL;
  
  t->address = address;
  t->write = write;
  t->read = read;
  t->next = next;
  t->end = end;

  return t;
}

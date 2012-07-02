/* TEMPORARILY WHILE DEVELOPING */
#define  USE_X11
/* EO TEMP */

#include "hid-x11.h"

enum KEY_STATES
  {
    KEY_RELEASED,
    KEY_PRESSED
  } ;

enum KEY_REQUESTS
  {
    KEY_PRESS,
    KEY_RELEASE
  } ;


int initialise_hid(void);
int enable_faked_hid(void);
int disable_faked_hid(void);


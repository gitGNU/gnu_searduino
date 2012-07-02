/* TEMPORARILY WHILE DEVELOPING */
#define  USE_X11
/* EO TEMP */

#include "hid-x11.h"

enum KEY_STATES
  {
    KEY_RELEASED,
    KEY_PRESSED
  } ;

enum BUTTON_STATES
  {
    BUTTON_RELEASED,
    BUTTON_PRESSED
  } ;

enum KEY_REQUESTS
  {
    KEY_RELEASE,
    KEY_PRESS
  } ;

enum BUTTON_REQUESTS
  {
    BUTTON_RELEASE,
    BUTTON_PRESS
  } ;



int initialise_hid(void);
int enable_faked_hid(void);
int disable_faked_hid(void);


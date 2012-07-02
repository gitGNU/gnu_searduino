#include "hid-x11.h"

int initialise_hid(void)
{
#ifdef USE_X11
  x11_initilise_hid();
#endif  
}

int enable_faked_hid(void)
{
#ifdef USE_X11
  x11_enable_faked_hid();
#endif  
}


int disable_faked_hid(void)
{
#ifdef USE_X11
  x11_disable_faked_hid();
#endif  
}



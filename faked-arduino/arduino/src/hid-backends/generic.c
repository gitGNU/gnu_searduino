#include "hid-x11.h"

int hid_initialise_hid(void)
{
#ifdef USE_X11
  x11_initilise_hid();
#endif  
}

int hid_enable_faked_hid(void)
{
#ifdef USE_X11
  x11_enable_faked_hid();
#endif  
}


int hid_disable_faked_hid(void)
{
#ifdef USE_X11
  x11_disable_faked_hid();
#endif  
}



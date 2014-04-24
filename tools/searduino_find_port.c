#include <Windows.h>
#include <stdio.h>

#define MAX_PORTS 128
#define MAX_LENGTH 64

int main(int argc, char** argv) {
  int i;
  char port_name[MAX_LENGTH];
  DWORD size;
  COMMCONFIG cc;

  for (i = MAX_PORTS; i > 0; i--) {

    port_name[0]='\0';
    sprintf(port_name, "COM%d", i);
    size = sizeof cc;

    if(GetDefaultCommConfig(port_name, &cc, &size) || size > sizeof cc)
      printf("%s\n", port_name);
  }
}

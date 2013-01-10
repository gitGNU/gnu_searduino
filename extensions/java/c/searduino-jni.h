#include "../com_sandklef_searduino_Searduino.h"
#include "seasim/seasim.h"

typedef struct {

  jmethodID digitalModeSimCallBack;
  

} searduino_callbacks;


typedef struct {

  int initialised;

  searduino_callbacks callbacks;

} searduino_jni;



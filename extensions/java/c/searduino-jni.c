
#include "../com_sandklef_searduino_Searduino.h"

//#include <Arduino.h>
#include "seasim/seasim.h"

#include <stdio.h>
#include <pthread.h>


pthread_t arduino_thread;


void 
my_dm_sim_callback(uint8_t pin, uint8_t mode)
{
  fprintf (stdout,"ALMOST JAVA CALLBACK :: digmod:%d:%d\n",pin, mode);
}

void* arduino_code(void *in)
{
  if (searduino_main_entry!=NULL)
    {
      searduino_main_entry(NULL);
    }
  else
    {
      fprintf (stderr, "Couldn't find an entry point for the Arduino code.\n");
    }
}


JNIEXPORT jint JNICALL 
Java_com_sandklef_searduino_Searduino_getWriteTimelimit(JNIEnv *env, jobject obj)
{
  int ret;

  seasim_enable_streamed_output();

  seasim_set_arduino_code_name("../../test/shared/libtest.so");


  ret = seasim_setup();
  if (ret!=0)
    {
      return ret;
    }


  ret  = seasim_register_dig_mode_sim_cb(my_dm_sim_callback);

  pthread_create(&arduino_thread, NULL, arduino_code, NULL);

  return seasim_get_Write_timelimit();
}

JNIEXPORT jint JNICALL 
Java_com_sandklef_searduino_Searduino_registerDgitialModeSimCallback(JNIEnv * env, jobject obj, jlong hwnd) {
{
  JavaVM * g_vm;
  jobject g_obj;
  jmethodID g_mid;

  int returnValue = 0;

  // convert local to global reference 
  // (local will die after this method call)
  g_obj = env->NewGlobalRef(obj);

  // save refs for callback
  jclass g_clazz = env->GetObjectClass(g_obj);
  if (g_clazz == NULL) {
    printf ("Failed to find class\n");
  }
  
  g_mid = env->GetMethodID(g_clazz, "callback", "(I)V");
  if (g_mid == NULL) {
    printf ("Unable to get method ref\n");
  }
  
  return (jboolean)returnValue;
 }
}

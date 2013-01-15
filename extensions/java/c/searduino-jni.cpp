/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2013 Henrik Sandklef 
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

#include "../com_sandklef_searduino_Searduino.h"

#include "searduino-jni.h"
#include "seasim/seasim.h"

#include <stdio.h>
#include <pthread.h>

pthread_t arduino_thread[10];
int thread_index=0;

jmethodID pin_mode_callback;
jmethodID out_callback;
jmethodID type_callback;
jmethodID log_callback;

JavaVM * g_vm;
jobject g_obj;




#define CHECK_JNI(stat, ge, gvm) \
  if (stat == JNI_EDETACHED) {                                   \
    if (gvm->AttachCurrentThread((void **) &ge, NULL) != 0) {    \
      printf("Failed to attach\n");                              \
    }                                                            \
  } else if (stat == JNI_OK) {                                   \
      ;                                                          \
  } else if (stat == JNI_EVERSION) {                             \
      printf("GetEnv: version not supported\n");                 \
  }

#define CHECK_CALLBACK(cb) \
  if (!pin_mode_callback)  \
    {                      \
      return -1;           \
    }

#define CHECK_CALLBACK_VOID(cb) \
  if (!pin_mode_callback)  \
    {                      \
      return ;             \
    }


void 
my_dm_sim_callback(uint8_t pin, uint8_t mode)
{
  //  fprintf (stdout,"ALMOST JAVA (C++) CALLBACK0 :: digmod:%d:%d\n",pin, mode);

  CHECK_CALLBACK_VOID(pin_mode_callback);
  JNIEnv * g_env;
  int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_4);
  
  CHECK_JNI(getEnvStat, g_env, g_vm);

  g_env->CallVoidMethod(g_obj, pin_mode_callback, pin, mode);

  if (g_env->ExceptionCheck()) {
    g_env->ExceptionDescribe();
  }

  g_vm->DetachCurrentThread();
}


void
my_out_sim_callback(uint8_t pin, unsigned int value, uint8_t pin_type)
{
  /*  fprintf (stdout,
	   "ALMOST JAVA (C++) OUT CALLBACK :%d:%d  (type:%d)\n",
	   pin, 
	   value, 
	   pin_type);
  */
  CHECK_CALLBACK_VOID(out_callback);
  JNIEnv * g_env;
  int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_4);
  
  CHECK_JNI(getEnvStat, g_env, g_vm);

  g_env->CallVoidMethod(g_obj, out_callback, pin, value, pin_type);

  if (g_env->ExceptionCheck()) {
    g_env->ExceptionDescribe();
  }

  g_vm->DetachCurrentThread();
}


void
my_log_sim_callback(uint8_t level, const char *str)
{
   // fprintf (stdout,
   // 	   "ALMOST JAVA (C++) LOG CALLBACK :%d  msg:%s  %d\n",
   // 	   level, 
   // 	    str, strlen(str));

  CHECK_CALLBACK_VOID(type_callback);
  JNIEnv * g_env;
  int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_4);
  CHECK_JNI(getEnvStat, g_env, g_vm);

  if ( (g_env!=NULL) && (str!=NULL) && (strlen(str)!=0))
    {
      jstring jstrBuf = (g_env)->NewStringUTF(str);
      g_env->CallVoidMethod(g_obj, log_callback, level, jstrBuf);
    }

}


void
my_type_sim_callback(uint8_t pin, uint8_t pin_type)
{
  /*  fprintf (stdout,
	   "ALMOST JAVA (C++) TYPE CALLBACK :%d  type:%d\n",
	   pin, 
	   pin_type);
  */

  CHECK_CALLBACK_VOID(type_callback);
  JNIEnv * g_env;
  int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_4);
  CHECK_JNI(getEnvStat, g_env, g_vm);

  g_env->CallVoidMethod(g_obj, type_callback, pin, pin_type);

  if (g_env->ExceptionCheck()) {
    g_env->ExceptionDescribe();
  }

  g_vm->DetachCurrentThread();
}



void* arduino_code(void *in)
{
  printf ("arduino_code:    %p\n", searduino_main_entry); fflush(stdout);

  if (searduino_main_entry!=NULL)
    {
      searduino_main_entry(NULL);
    }
  else
    {
      fprintf (stderr, "Couldn't find an entry point for the Arduino code.\n");
    }
  return NULL;
}

JNIEXPORT jint JNICALL Java_com_sandklef_searduino_Searduino_setWriteTimelimit
(JNIEnv *env, jobject o, jint limit)
{
  //seasim_set_Write_timelimit(limit);
  return 0;
}


JNIEXPORT jint JNICALL 
Java_com_sandklef_searduino_Searduino_getWriteTimelimit(JNIEnv *env, jobject obj)
{
  int ret;

  return seasim_get_Write_timelimit();
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
  JNIEnv* env = NULL;
  int ret;

  g_vm=vm;
  jint result;


  result = g_vm->GetEnv((void**) &env, JNI_VERSION_1_4);
  if ( result != JNI_OK) {
    printf ("onload: return -1\n");
    return -1;
  }

  seasim_enable_streamed_output();

  printf ("onload: return %d\n", JNI_VERSION_1_4);
  return JNI_VERSION_1_4;
}



JNIEXPORT jint JNICALL 
Java_com_sandklef_searduino_Searduino_registerPinCallback
(JNIEnv * env, jobject obj_tmp, jobject obj, jint type) {
{
  int returnValue = 0;
  int ret;

  // convert local to global reference 
  // (local will die after this method call)
  
  //  g_obj = env->NewGlobalRef(obs);
  g_obj = env->NewGlobalRef(obj);

  // save refs for callback
  //  jclass g_clazz = env->GetObjectClass(g_obj);

  jclass g_clazz = env->GetObjectClass(g_obj);
  if (g_clazz == NULL) {
    printf ("Failed to find class\n");
  }

  //  const char* strCIn = (env)->GetStringUTFChars(method , 0);
  //printf ("method: %s\n", strCIn);


  printf (" -------------------------------------\n");

  if ( type == 1 ) 
    {

      pin_mode_callback = env->GetMethodID(g_clazz, "handlePinModeEvent", "(II)V");
      //  pin_mode_callback = env->GetMethodID(g_clazz, "handlePinModeEvent", "(I)V");
      if (pin_mode_callback == NULL) {
	printf ("Unable to get method ref\n");
      }
      else
	{
	  ret  = seasim_register_dig_mode_sim_cb(my_dm_sim_callback);
	  printf (" pin_mode_callback=%p\n", pin_mode_callback);
	}
    }
  else if ( type == 2 ) 
    {
      out_callback = env->GetMethodID(g_clazz, "handlePinOutEvent", "(III)V");
      printf (" 5\n");
      if (out_callback == NULL) {
	printf ("Unable to get method ref\n");
      }
      else
	{
	  ret  = seasim_register_out_sim_cb(my_out_sim_callback);
	  printf (" out_callback=%p\n", out_callback);
	}
    }
  else if ( type == 3 ) 
    {
      type_callback = env->GetMethodID(g_clazz, "handlePinTypeEvent", "(II)V");
      printf (" REGISTER CALLBACK FOR TYPE\n");
      if (type_callback == NULL) {
	printf ("Unable to get method ref\n");
      }
      else
	{
	  ret  = seasim_register_type_cb(my_type_sim_callback);
	  printf (" type_callback=%p\n", type_callback);
	}
    }
  else if ( type == 4 ) 
    {
      printf (" REGISTER CALLBACK FOR TYPE 4.1\n");
      log_callback = env->GetMethodID(g_clazz, "handleLogEvent", "(ILjava/lang/String;)V");
      printf (" REGISTER CALLBACK FOR TYPE 4.2\n");
      if (log_callback == NULL) {
	printf ("Unable to get method ref\n");
      }
      else
	{
	  printf (" REGISTER CALLBACK FOR TYPE 4.3\n");
	  ret  = seasim_register_log_cb(my_log_sim_callback);
	  printf (" REGISTER CALLBACK FOR TYPE 4.4\n");
	  printf (" log_callback=%p\n", log_callback);
	}
    }
  else
    {
      printf ("\n\n\n\tCan not register type %s\n\n\n", type);
    }

  printf (" REGISTER CALLBACK TYPE done\n");

  return (jboolean)returnValue;
 }
}


JNIEXPORT void JNICALL Java_com_sandklef_searduino_Searduino_pauseArduinoCode
(JNIEnv *, jobject)
{
  return seasim_set_paused();
}

JNIEXPORT void JNICALL Java_com_sandklef_searduino_Searduino_resumeArduinoCode
  (JNIEnv *, jobject)
{
  return seasim_set_running();
}

JNIEXPORT void JNICALL Java_com_sandklef_searduino_Searduino_haltArduinoCode
  (JNIEnv *, jobject)
{
  int ret;

  printf ("cancel thread\n");

  //  seasim_set_halted();

  ret = pthread_cancel(arduino_thread[thread_index]);
  printf ("cancel thread %d\n", ret);

  printf ("cancel thread returning\n");
  return ;
}

JNIEXPORT jint JNICALL Java_com_sandklef_searduino_Searduino_isPausedArduinoCode
  (JNIEnv *, jobject)
{
  return seasim_is_paused();
}

JNIEXPORT jint JNICALL Java_com_sandklef_searduino_Searduino_isHaltedArduinoCode
  (JNIEnv *, jobject)
{
  return seasim_is_halted();
}

JNIEXPORT jint JNICALL Java_com_sandklef_searduino_Searduino_isRunningArduinoCode
  (JNIEnv *, jobject)
{
  return seasim_is_running();
}


JNIEXPORT jint JNICALL Java_com_sandklef_searduino_Searduino_isPausableArduinoCode
  (JNIEnv *, jobject)
{
  return seasim_is_pausable();
}

JNIEXPORT void JNICALL Java_com_sandklef_searduino_Searduino_disableStreamedOutput
  (JNIEnv *, jobject)
{
  return seasim_disable_streamed_output();
}

JNIEXPORT void JNICALL Java_com_sandklef_searduino_Searduino_enableStreamedOutput
  (JNIEnv *, jobject)
{
  return seasim_enable_streamed_output();
}


JNIEXPORT void JNICALL Java_com_sandklef_searduino_Searduino_startArduinoCode
  (JNIEnv *, jobject)
{
  int retval;
  
  printf ("joining thread....\n");
  //  pthread_join(arduino_thread[thread_index], (void**)&retval);

  //  thread_index++;

  printf ("starting thread....join returned: %d\n", retval);
  printf ("starting thread....thread: %p\n", arduino_thread);
  printf ("starting thread....thread: %p\n", &arduino_thread);
  seasim_set_running();
  pthread_create(&arduino_thread[thread_index], NULL, arduino_code, NULL);
}


JNIEXPORT jstring JNICALL Java_com_sandklef_searduino_Searduino_getSearduinoVersion
  (JNIEnv *, jobject)
{
  const char *src = seasim_get_searduino_version();
  /*  if (src==null)
    {
      return null;
    }
  char *buf = (char*)malloc(strlen(src)+1);
  strcpy(buf, );
  */
  JNIEnv * g_env;
  int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_4);
  jstring jstrBuf = (g_env)->NewStringUTF( src);

  return jstrBuf;
}

JNIEXPORT jstring JNICALL Java_com_sandklef_searduino_Searduino_getSearduinoName
  (JNIEnv *, jobject)
{
  //  return seasim_get_searduino_name();  
}

JNIEXPORT jstring JNICALL Java_com_sandklef_searduino_Searduino_getBoardName
  (JNIEnv *, jobject)
{
  char * src = seasim_get_board_name();

  if (src==NULL)
    {
      src = (char*) "<none>";
    }

  JNIEnv * g_env;
  int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_4);
  jstring jstrBuf = (g_env)->NewStringUTF( src);

  return jstrBuf;
}

JNIEXPORT jint JNICALL Java_com_sandklef_searduino_Searduino_setBoardName
  (JNIEnv *env, jobject obj, jstring board)
{
  JNIEnv * g_env;
  int ret;

  int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_4);
  CHECK_JNI(getEnvStat, g_env, g_vm);

  const char* strCIn = (env)->GetStringUTFChars(board , 0);
  printf ("board: %s\n", strCIn);

  ret = seasim_set_board_name((char*)strCIn);
  
  
}


JNIEXPORT jint JNICALL Java_com_sandklef_searduino_Searduino_getCurrentPinType
  (JNIEnv *env, jobject obj, jint pin)
{
  jint ret =  seasim_get_current_pin_type(pin);

  printf ("SEASIM RET: %d\n", ret);

  return ret;

}

JNIEXPORT jint JNICALL Java_com_sandklef_searduino_Searduino_setGenericInput
  (JNIEnv *env, jobject obj, jint pin, jint val, jint pin_type)
{
  seasim_fake_input(pin, val, pin_type);
}

JNIEXPORT jint JNICALL Java_com_sandklef_searduino_Searduino_getNrOfPins
  (JNIEnv *, jobject)
{
  return seasim_get_nr_of_pins();
}


JNIEXPORT jstring JNICALL Java_com_sandklef_searduino_Searduino_getArduinoCodeName
  (JNIEnv *enc, jobject obj)
{
  JNIEnv * g_env;
  char *str;

  int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_4);

  str = seasim_get_arduino_code_name();
  jstring jstrBuf = (g_env)->NewStringUTF(str);

  return jstrBuf;
}

JNIEXPORT jint JNICALL Java_com_sandklef_searduino_Searduino_setArduinoCodeName
  (JNIEnv *env, jobject obj, jstring str)
{
  JNIEnv * g_env;
  int ret;
  int getEnvStat;
  static int is_setup = 0 ;
  

  getEnvStat  = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_4);
  CHECK_JNI(getEnvStat, g_env, g_vm);

  const char* strCIn = (env)->GetStringUTFChars(str , 0);
  printf ("board code: %s\n", strCIn);

  printf (" ----------------------------------------->  loading code %s\n", strCIn);
  ret = seasim_set_arduino_code_name(strCIn);
  printf (" <-----------------------------------------  loading code returned: %d\n", ret); fflush(stdout); 
  
  if (ret==1)
    {
      printf (" -----------------------------------------  loading code failed (1)\n", ret); fflush(stdout); 
    }
  else if (is_setup!=3)
    {
      printf ("setup\n");
      ret = seasim_setup();
      if (ret!=0)
	{
	  printf (" ----------------------------------------->  seasim setup failed\n");
	}
      is_setup=1;
    }
  return ret;
}


JNIEXPORT jint JNICALL Java_com_sandklef_searduino_Searduino_fakeAnalogInput
  (JNIEnv *env, jobject obj, jint pin, jint val)
{
  return seasim_fake_analog_input (pin, val);
}

JNIEXPORT jint JNICALL Java_com_sandklef_searduino_Searduino_fakeDigitalInput
  (JNIEnv *env, jobject obj, jint pin, jint val)
{
  return seasim_fake_digital_input (pin, val);
}

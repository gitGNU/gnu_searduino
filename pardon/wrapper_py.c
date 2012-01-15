/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2011, 2012 Henrik Sandklef 
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

#include <Python.h>

#include <Arduino.h>
#include <pthread.h>


#include "communication/comm.h"
#include "communication/ext_io.h"
#include "arduino/setup.h"

extern int searduino_exec;
pthread_t   searduino_thread_impl;
pthread_t  *searduino_thread = &searduino_thread_impl;

#ifdef PARD_DEBUG_FUNCATION_CALLS
#define PARD_PRINT_IN()            printf ("--->  %s() \n", __func__); fflush(stdout); 
#define PARD_PRINT_INSIDE()        printf ("--- INSIDE  %s()\n", __func__); fflush(stdout);
#define PARD_PRINT_INSIDE_STR(str) printf ("--- INSIDE  %s():  %s\n", __func__, str); fflush(stdout);
#define PARD_PRINT_OUT()           printf ("<---  %s()\n", __func__);fflush(stdout); 
#else
#define PARD_PRINT_IN() 
#define PARD_PRINT_INSIDE() 
#define PARD_PRINT_INSIDE_STR(str) 
#define PARD_PRINT_OUT() 
#endif



static PyObject *my_callback = NULL;
static PyObject *py_my_set_callback(PyObject *dummy, PyObject *args);


void* arduino_code(void *in);


void new_dig_out(uint8_t pin, uint8_t val)
{
  PyObject *arglist;
  PyObject *result; 

  PyGILState_STATE gstate;   
  gstate = PyGILState_Ensure();   

  PARD_PRINT_IN();

  PARD_PRINT_INSIDE();

  if (my_callback!=NULL)
    {

       arglist = Py_BuildValue("(ii)", pin, val);

      if (arglist==NULL)
	{
	  printf ("wooops, arglist is no no\n");
	  exit(1);
	}

      /* printf(" Arguments to callback:  ");      fflush(stdout); */
      //PyObject_Print(arglist, stdout, Py_PARD_PRINT_RAW);

      PARD_PRINT_INSIDE_STR("    Will call callback\n");
      result = PyEval_CallObject(my_callback, arglist);

      Py_DECREF(arglist);
      
      if (result)
	{
	  Py_DECREF(result);
	}      
    }
  else
    {
      fprintf (stderr, "*** ERRROR ***\n");
      fprintf (stderr, "*** Could not call callback since no callback ***\n");
    }

  PyGILState_Release(gstate);
  PARD_PRINT_OUT();
}

/*
 * Function to be called from Python
 */
static PyObject* py_c_digitalRead(PyObject* self, PyObject* args)
{
  int pin;
  uint8_t val ;
  PARD_PRINT_IN();
  
  PyArg_ParseTuple(args, "i", &pin);

  val = ext_get_dig_output(pin);
  PyObject* o = Py_BuildValue("i", val);

  PARD_PRINT_OUT();
  return o;
}


/*
 * Function to be called from Python
 */
static PyObject* py_c_ext_set_input(PyObject* self, PyObject* args)
{
  int pin;
  int val;
  PARD_PRINT_IN();

  if (!PyArg_ParseTuple(args, "ii", &pin, &val))
    {
      return NULL;
    }

  PARD_PRINT_INSIDE_STR("wrapper code sets input pin\n");

  val= ext_set_dig_input(pin, val);
  PyObject* o = Py_BuildValue("i", val);

  PARD_PRINT_OUT();
  return o;
}




PyObject * c_searduino_pause(void)
{
  PARD_PRINT_INSIDE_STR("in C wrapper: want to pause\n");

  PyObject* res = Py_BuildValue("i", 0);
    
  searduino_exec=0;

  PARD_PRINT_INSIDE_STR("in C: have paused\n");
  return res;
}

PyObject * c_searduino_resume(void)
{
  PyObject* res = Py_BuildValue("i", 0);
  Py_INCREF(Py_None);
  PARD_PRINT_INSIDE_STR("in C wrapper: want to resume\n");

  searduino_exec=1;

  PARD_PRINT_INSIDE_STR("in C: is resumed\n");
  return res;
}



/*
 * Another function to be called from Python
 */
/*
 * Bind Python function names to our C functions
 */
static PyMethodDef myModule_methods[] = {
  {"py_digitalRead", (PyCFunction)py_c_digitalRead, METH_VARARGS, NULL},
  {"py_ext_set_input", (PyCFunction)py_c_ext_set_input, METH_VARARGS, NULL},
  {"my_set_callback", (PyCFunction)py_my_set_callback, METH_VARARGS, NULL},
  {"my_arduino_code", (PyCFunction)arduino_code, METH_VARARGS, NULL},
  {"searduino_pause", (PyCFunction)c_searduino_pause, METH_VARARGS, NULL},
  {"searduino_resume", (PyCFunction)c_searduino_resume, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};



void* arduino_code(void *in)
{

  usleep(1000*1000);
  fprintf (stderr, "Starting Arduino code\n");
  searduino_main();

  return NULL;
}


static PyObject *
py_my_set_callback(PyObject *dummy, PyObject *args)
{
  PyObject *result = NULL;
  PyObject *temp;
  PARD_PRINT_IN();

  if (PyArg_ParseTuple(args, "O:set_callback", &temp)) {
    if (!PyCallable_Check(temp)) {
      PyErr_SetString(PyExc_TypeError, "parameter must be callable");
      PARD_PRINT_OUT();

      return NULL;
    }

    Py_XINCREF(temp);         /* Add a reference to new callback */
    Py_XDECREF(my_callback);  /* Dispose of previous callback */
    my_callback = temp;       /* Remember new callback */

    /* Boilerplate to return "None" */
    Py_INCREF(Py_None);
    result = Py_None;

    PARD_PRINT_INSIDE_STR("Python callck is registered");
    usleep (1000);
  }

  PARD_PRINT_OUT();
  return result;
}

/*
 * Python calls this to let us initialize our module
 */
void initpardon()
{

  PyEval_InitThreads();
  //PyEval_ReleaseLock();


  PARD_PRINT_INSIDE_STR("Init pardon module\n");
  (void) Py_InitModule("pardon", myModule_methods);

  PARD_PRINT_INSIDE_STR("Setting up searduino\n");
  searduino_setup();

  PARD_PRINT_INSIDE_STR("Register callback for dig out"
			"(in communication module)\n");
  comm_register_digout_sim_cb(new_dig_out);
  
  PARD_PRINT_INSIDE_STR("Starting thread for arduino code\n");
  pthread_create(searduino_thread, NULL, arduino_code, NULL);

  PARD_PRINT_INSIDE_STR("*** All set up ***  in wrapper\n");
}

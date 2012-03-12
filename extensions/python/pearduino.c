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

pthread_t   searduino_thread_impl;
pthread_t  *searduino_thread = &searduino_thread_impl;



#define PEARDUINO_DEBUG_FUNCATION_CALLS

#ifdef PEARDUINO_DEBUG_FUNCATION_CALLS
#define PEARDUINO_PRINT_IN()            printf ("--->  %s() \n", __func__); fflush(stdout); 
#define PEARDUINO_PRINT_INSIDE()        printf ("--- INSIDE  %s()\n", __func__); fflush(stdout);
#define PEARDUINO_PRINT_INSIDE_STR(str) printf ("--- INSIDE  %s():  %s\n", __func__, str); fflush(stdout);
#define PEARDUINO_PRINT_OUT()           printf ("<---  %s()\n", __func__);fflush(stdout); 
#else
#define PEARDUINO_PRINT_IN() 
#define PEARDUINO_PRINT_INSIDE() 
#define PEARDUINO_PRINT_INSIDE_STR(str) 
#define PEARDUINO_PRINT_OUT() 
#endif


static PyObject *my_dig_callback = NULL;
static PyObject *my_ana_callback = NULL;
static PyObject *py_my_set_dig_callback(PyObject *dummy, PyObject *args);
static PyObject *py_my_set_ana_callback(PyObject *dummy, PyObject *args);

extern searduino_main_ptr_ptr searduino_main_entry;

void* arduino_code(void *in);


void new_dig_out(uint8_t pin, uint8_t val)
{
  PyObject *arglist;
  PyObject *result; 

  PyGILState_STATE gstate;   
  gstate = PyGILState_Ensure();   

  PEARDUINO_PRINT_IN();

  PEARDUINO_PRINT_INSIDE();

  if (my_dig_callback!=NULL)
    {

       arglist = Py_BuildValue("(ii)", pin, val);

      if (arglist==NULL)
	{
	  printf ("wooops, arglist is no no\n");
	  exit(1);
	}

      /* printf(" Arguments to callback:  ");      fflush(stdout); */
      //PyObject_Print(arglist, stdout, Py_PEARDUINO_PRINT_RAW);

      PEARDUINO_PRINT_INSIDE_STR("    Will call digital callback\n");
      result = PyEval_CallObject(my_dig_callback, arglist);

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
  PEARDUINO_PRINT_OUT();
}


void new_ana_out(uint8_t pin, unsigned int val)
{
  PyObject *arglist;
  PyObject *result; 

  PyGILState_STATE gstate;   
  gstate = PyGILState_Ensure();   

  PEARDUINO_PRINT_IN();

  PEARDUINO_PRINT_INSIDE();

  if (my_ana_callback!=NULL)
    {

       arglist = Py_BuildValue("(ii)", pin, val);

      if (arglist==NULL)
	{
	  printf ("wooops, arglist is no no\n");
	  exit(1);
	}

      /* printf(" Arguments to callback:  ");      fflush(stdout); */
      //PyObject_Print(arglist, stdout, Py_PEARDUINO_PRINT_RAW);

      PEARDUINO_PRINT_INSIDE_STR("    Will call ana callback\n");
      printf("    Will call ana callback: %p\n", my_ana_callback);
      result = PyEval_CallObject(my_ana_callback, arglist);

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
  PEARDUINO_PRINT_OUT();
}



static PyObject* c_py_get_pin_mode(PyObject* self, PyObject* args)
{
  uint8_t pin;
  uint8_t mode ;
  PEARDUINO_PRINT_IN();
  
  PyArg_ParseTuple(args, "i", &pin);

  mode = ext_get_dig_mode(pin);
  PyObject* o = Py_BuildValue("i", mode);

  PEARDUINO_PRINT_OUT();
  return o;
}

static PyObject* c_searduino_set_arduino_code(PyObject* self, PyObject* args)
{
  uint8_t ret;
  char *ard_lib;
  PEARDUINO_PRINT_IN();
  
  PyArg_ParseTuple(args, "s", &ard_lib);

  ret = searduino_set_arduino_code_name(ard_lib);
  PyObject* o = Py_BuildValue("i", ret);

  PEARDUINO_PRINT_OUT();
  return o;
}

static PyObject* c_searduino_set_digitalWrite_timelimit(PyObject* self, PyObject* args)
{
  unsigned int ret;
  unsigned int val;
  PEARDUINO_PRINT_IN();
  
  PyArg_ParseTuple(args, "i", &val);

  /* printf ("pear: before %d\n", get_digitalWrite_timelimit()); */
  set_digitalWrite_timelimit(val);
  /* printf ("pear: after  %d\n", get_digitalWrite_timelimit()); */
  PyObject* o = Py_BuildValue("i", val);

  PEARDUINO_PRINT_OUT();
  return o;
}

static PyObject* c_searduino_get_digitalWrite_timelimit(PyObject* self, PyObject* args)
{
  unsigned int ret;
  PEARDUINO_PRINT_IN();
  
  ret = get_digitalWrite_timelimit();
  PyObject* o = Py_BuildValue("i", ret);

  PEARDUINO_PRINT_OUT();
  return o;
}

static PyObject* c_searduino_initialise(PyObject* self, PyObject* args)
{
  uint8_t ret;
  PEARDUINO_PRINT_IN();
  
  PEARDUINO_PRINT_INSIDE_STR("Setting up searduino\n");

  /*  searduino_set_arduino_code_name("libarduino-code.so"); */
  ret = searduino_setup();
  if (ret!=0)
    {
      PEARDUINO_PRINT_INSIDE_STR("Setting up searduino seem to have failed\n");
      return;
    }
  PEARDUINO_PRINT_INSIDE_STR("Register callback for dig out"
			"(in communication module)\n");
  comm_register_digout_sim_cb(new_dig_out);
  comm_register_anaout_sim_cb(new_ana_out);
  
  PEARDUINO_PRINT_OUT();
  PyObject* o = Py_BuildValue("i", 0);
  return o;
}


static PyObject* c_searduino_start(PyObject* self, PyObject* args)
{
  uint8_t ret;
  PEARDUINO_PRINT_IN();
  
  PEARDUINO_PRINT_INSIDE_STR("Starting thread for arduino code\n");
  pthread_create(searduino_thread, NULL, arduino_code, NULL);

  PEARDUINO_PRINT_OUT();
  PyObject* o = Py_BuildValue("i", 0);
  return o;
}


/*
 * Function to be called from Python
 */
static PyObject* py_c_digitalRead(PyObject* self, PyObject* args)
{
  int pin;
  uint8_t val ;
  PEARDUINO_PRINT_IN();
  
  PyArg_ParseTuple(args, "i", &pin);

  val = ext_get_dig_output(pin);
  PyObject* o = Py_BuildValue("i", val);

  PEARDUINO_PRINT_OUT();
  return o;
}


/*
 * Function to be called from Python
 */
static PyObject* py_c_analogRead(PyObject* self, PyObject* args)
{
  int pin;
  unsigned int val ;
  PEARDUINO_PRINT_IN();
  
  PyArg_ParseTuple(args, "i", &pin);

  val = ext_get_ana_output(pin);

  PyObject* o = Py_BuildValue("i", val);

  PEARDUINO_PRINT_OUT();
  return o;
}


/*
 * Function to be called from Python
 */
static PyObject* py_c_ext_set_ana_input(PyObject* self, PyObject* args)
{
  unsigned int pin;
  unsigned int val;
  PEARDUINO_PRINT_IN();

  if (!PyArg_ParseTuple(args, "ii", &pin, &val))
    {
      return NULL;
    }

  PEARDUINO_PRINT_INSIDE_STR("wrapper code sets input pin\n");

  val= ext_set_ana_input(pin, val);
  PyObject* o = Py_BuildValue("i", val);

  PEARDUINO_PRINT_OUT();
  return o;
}


/*
 * Function to be called from Python
 */
static PyObject* py_c_ext_set_dig_input(PyObject* self, PyObject* args)
{
  int pin;
  int val;
  PEARDUINO_PRINT_IN();

  if (!PyArg_ParseTuple(args, "ii", &pin, &val))
    {
      return NULL;
    }

  PEARDUINO_PRINT_INSIDE_STR("wrapper code sets input pin\n");

  val= ext_set_dig_input(pin, val);
  PyObject* o = Py_BuildValue("i", val);

  PEARDUINO_PRINT_OUT();
  return o;
}




PyObject * c_searduino_pause(void)
{
  PEARDUINO_PRINT_INSIDE_STR("in C wrapper: want to pause\n");

  PyObject* res = Py_BuildValue("i", 0);

  searduino_set_paused();

  PEARDUINO_PRINT_INSIDE_STR("in C: have paused\n");
  return res;
}

PyObject * c_searduino_resume(void)
{
  PyObject* res = Py_BuildValue("i", 0);
  Py_INCREF(Py_None);
  PEARDUINO_PRINT_INSIDE_STR("in C wrapper: want to resume\n");

  searduino_set_running();

  PEARDUINO_PRINT_INSIDE_STR("in C: is resumed\n");
  return res;
}


PyObject * c_searduino_quit(void)
{
  PyObject* res = Py_BuildValue("i", 0);
  Py_INCREF(Py_None);
  PEARDUINO_PRINT_INSIDE_STR("in C wrapper: want to quit\n");

  searduino_set_halted();

  PEARDUINO_PRINT_INSIDE_STR("in C: is set to quit\n");
  return res;
}



/*
 * Another function to be called from Python
 */
/*
 * Bind Python function names to our C functions
 */
static PyMethodDef myModule_methods[] = {
  {"py_analogRead", (PyCFunction)py_c_analogRead, METH_VARARGS, NULL},
  {"py_ext_set_ana_input", (PyCFunction)py_c_ext_set_ana_input, METH_VARARGS, NULL},
  {"py_digitalRead", (PyCFunction)py_c_digitalRead, METH_VARARGS, NULL},
  {"py_ext_set_dig_input", (PyCFunction)py_c_ext_set_dig_input, METH_VARARGS, NULL},
  {"my_set_dig_callback", (PyCFunction)py_my_set_dig_callback, METH_VARARGS, NULL},
  {"my_set_ana_callback", (PyCFunction)py_my_set_ana_callback, METH_VARARGS, NULL},
  {"my_arduino_code", (PyCFunction)arduino_code, METH_VARARGS, NULL},
  {"searduino_pause", (PyCFunction)c_searduino_pause, METH_VARARGS, NULL},
  {"searduino_resume", (PyCFunction)c_searduino_resume, METH_VARARGS, NULL},
  {"searduino_quit", (PyCFunction)c_searduino_quit, METH_VARARGS, NULL},
  {"py_get_pin_mode", (PyCFunction)c_py_get_pin_mode, METH_VARARGS, NULL},
  {"searduino_set_arduino_code", (PyCFunction)c_searduino_set_arduino_code, METH_VARARGS, NULL},
  {"searduino_initialise", (PyCFunction)c_searduino_initialise, METH_VARARGS, NULL},
  {"searduino_start", (PyCFunction)c_searduino_start, METH_VARARGS, NULL},
  {"searduino_set_digitalWrite_timelimit", (PyCFunction)c_searduino_set_digitalWrite_timelimit, METH_VARARGS, NULL},
  {"searduino_get_digitalWrite_timelimit", (PyCFunction)c_searduino_get_digitalWrite_timelimit, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};



void* arduino_code(void *in)
{

  usleep(1000*1000);
  fprintf (stderr, "Starting Arduino code\n");
  usleep(1000000);
  searduino_main_entry(NULL);

  return NULL;
}


static PyObject *
py_my_set_dig_callback(PyObject *dummy, PyObject *args)
{
  PyObject *result = NULL;
  PyObject *temp;
  PEARDUINO_PRINT_IN();

  if (PyArg_ParseTuple(args, "O:set_callback", &temp)) {
    if (!PyCallable_Check(temp)) {
      PyErr_SetString(PyExc_TypeError, "parameter must be callable");
      PEARDUINO_PRINT_OUT();

      return NULL;
    }

    Py_XINCREF(temp);         /* Add a ref to the new callback */
    Py_XDECREF(my_dig_callback);  /* Dispose possible previous callback */
    my_dig_callback = temp;       /* Remember new callback */

    /* Boilerplate to return "None" */
    Py_INCREF(Py_None);
    result = Py_None;

    PEARDUINO_PRINT_INSIDE_STR("Python callback is registered");
    usleep (1000);
  }

  PEARDUINO_PRINT_OUT();
  return result;
}


static PyObject *
py_my_set_ana_callback(PyObject *dummy, PyObject *args)
{
  PyObject *result = NULL;
  PyObject *temp;
  PEARDUINO_PRINT_IN();

  if (PyArg_ParseTuple(args, "O:set_callback", &temp)) {
    if (!PyCallable_Check(temp)) {
      PyErr_SetString(PyExc_TypeError, "parameter must be callable");
      PEARDUINO_PRINT_OUT();

      return NULL;
    }

    Py_XINCREF(temp);         /* Add a ref to the new callback */
    Py_XDECREF(my_ana_callback);  /* Dispose possible previous callback */
    my_ana_callback = temp;       /* Remember new callback */

    /* Boilerplate to return "None" */
    Py_INCREF(Py_None);
    result = Py_None;

    PEARDUINO_PRINT_INSIDE_STR("Python callback is registered");
    usleep (1000);
  }

  PEARDUINO_PRINT_OUT();
  return result;
}

/*
 * Python calls this to let us initialize our module
 */
void initpearduino()
{
  int ret;

  PyEval_InitThreads();
  //PyEval_ReleaseLock();


  PEARDUINO_PRINT_INSIDE_STR("Init pearduino module\n");
  (void) Py_InitModule("pearduino", myModule_methods);

  
  PEARDUINO_PRINT_INSIDE_STR("*** All set up ***  in wrapper\n");
}

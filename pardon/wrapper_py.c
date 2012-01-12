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

static PyObject *my_callback = NULL;
static PyObject *my_set_callback(PyObject *dummy, PyObject *args);

void new_dig_out(uint8_t pin, uint8_t val)
{
  PyObject *arglist;
  PyObject *result; 

  /* printf ("  new DIG OUT: %d %d\n",   */
  /* 	  pin, val);   */

  /* Time to call the callback */
  arglist = Py_BuildValue("(i,i)", pin, val);

  printf ("Calling.....%p\n",my_callback);
  fflush(stdout);
  if (my_callback!=NULL)
    {
      result = PyEval_CallObject(my_callback, arglist);
      printf ("result.....%p\n",result);
      fflush(stdout);
      /* PyObject_CallObject(my_callback, arglist);  */
    }
  Py_DECREF(arglist);
}

/*
 * Function to be called from Python
 */
static PyObject* py_c_digitalRead(PyObject* self, PyObject* args)
{
  int pin;
  uint8_t val ;
  PyArg_ParseTuple(args, "i", &pin);
/*   printf ("GUI:  (c wrapper) Will read from %d\n", pin);  */
  val = ext_get_dig_output(pin);
  return Py_BuildValue("i", val);
}


/*
 * Function to be called from Python
 */
static PyObject* py_c_ext_set_input(PyObject* self, PyObject* args)
{
  int pin;
  int val;
  PyArg_ParseTuple(args, "ii", &pin, &val);

  /* REMOVE ME LATER */
  pinMode(pin,1);

  val= ext_set_dig_input(pin, val);
  return Py_BuildValue("i", val);
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
  {"my_set_callback", (PyCFunction)my_set_callback, METH_VARARGS, NULL},
  {NULL, NULL}
};



void* arduino_code(void *in)
{

  usleep(1000*1000);
  printf ("Starting Arduino code\n");
  searduino_main();
  return NULL;
}


static PyObject *
my_set_callback(PyObject *dummy, PyObject *args)
{
  PyObject *result = NULL;
  PyObject *temp;

  if (PyArg_ParseTuple(args, "O:set_callback", &temp)) {
    if (!PyCallable_Check(temp)) {
      PyErr_SetString(PyExc_TypeError, "parameter must be callable");
      return NULL;
    }

    Py_XINCREF(temp);         /* Add a reference to new callback */
    Py_XDECREF(my_callback);  /* Dispose of previous callback */
    my_callback = temp;       /* Remember new callback */

    /* Boilerplate to return "None" */
    Py_INCREF(Py_None);
    result = Py_None;
  }
  return result;
}

/*
 * Python calls this to let us initialize our module
 */
void initpardon()
{
  pthread_t p;

  printf ("*** Setting up ***\n");
  (void) Py_InitModule("pardon", myModule_methods);
  searduino_setup();
  printf ("*** All set up ***\n");

  comm_register_digout_sim_cb(new_dig_out);

  pthread_create(&p, NULL, arduino_code, NULL);
}

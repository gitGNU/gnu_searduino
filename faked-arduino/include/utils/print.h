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


#ifndef SEARDUINO_PRINT_H
#define SEARDUINO_PRINT_H

#define SEARDUINO_LOG_LEVEL_NONE     0  
#define SEARDUINO_LOG_LEVEL_INFO     1
#define SEARDUINO_LOG_LEVEL_WARNING  2
#define SEARDUINO_LOG_LEVEL_ERROR    3



#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "utils/types.h"
#include "communication/comm.h"

  
#define INFO_STREAM stdout
#define ERR_STREAM  stderr

  
void print_function_name (FILE* stream,  const char* fun, char * str , ...) ;
void log_generic(int level, char* s,  ...);
void log_error(char* s,  ...);

#ifdef  SEARDUINO_STUB
#define SEARDUINO_DEBUG(a)  printf( "[SEARDUINO DEBUG %s:%d:%s]:  ",__FILE__,__LINE__,__func__); printf a; printf ("\n");
#else
#define SEARDUINO_DEBUG(a)
#endif






void 
print_dummy_function_implementation (FILE* stream,  
				     const char *file, 
				     int line, 
				     const char *fun) ;

#define PRINT_DUMMY_FUNCTION_IMPLEMENTATION()  print_dummy_function_implementation(ERR_STREAM, __FILE__, __LINE__, __func__);


/* #define ENANLE_DEBUG_PRINTOUTS */
#ifdef ENANLE_DEBUG_PRINTOUTS
#define PRINT_FUNCTION_NAME_NOARGS() printf( "function: %s (",__func__); printf (")\n");
#define PRINT_FUNCTION_NAME(a)       printf( "function: %s (",__func__); printf a; printf (")\n");
#define DEBUG_INFO(a)                printf( "info:     %s (",__func__); printf a; printf (")\n");
#else
#define PRINT_FUNCTION_NAME_NOARGS() 
#define PRINT_FUNCTION_NAME(a)       
#define DEBUG_INFO(a)                
#endif /* ENANLE_FUNCTION_PRINT_NAME */


#ifdef __cplusplus
}
#endif

#endif /* SEARDUINO_PRINT_H */

/*****                                                                               
 *                                                                                   
 *                   Searduino                                                       
 *                                                                                   
 *   Copyright (C) 2012 Henrik Sandklef                                              
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

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

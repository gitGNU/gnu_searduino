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

package com.sandklef.jearduino;

import java.util.prefs.Preferences;

public class JearduinoPreferences {

    private Preferences jearduinoPrefs;

    private String boardId = "board";

    private String arduinoCodeIdPrefix = "arduinoCode";

    public JearduinoPreferences()
    {
	jearduinoPrefs = Preferences.userRoot().node("Jearduino");
    }

    public String getBoard()
    {
	return jearduinoPrefs.get(boardId, "Uno");
    }

    public void setBoard(String board)
    {
	jearduinoPrefs.put(boardId, board);
    }

    public String getArduinoCodeName(int nr)
    {
	return jearduinoPrefs.get(arduinoCodeIdPrefix+nr, "");
    }

    public void setArduinoCodeName(int nr, String ac)
    {
	jearduinoPrefs.put(arduinoCodeIdPrefix+nr, ac);
    }
    

} 
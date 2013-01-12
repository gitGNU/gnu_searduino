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


public class PreferenceTest {

    private Preferences seardunoPrefs;

    private String boardId = "board";

    public String getBoard()
    {
	prefs.get(boardId, "Uno"))
    }

    public void getBoard(String board)
    {
	prefs.put(boardId, board))
    }

    public void setPreference() {

	prefs = Preferences.userRoot().node("Jearduino");

	String ID1 = "Test1";
	String ID2 = "Test2";
	String ID3 = "Test3";

	// First we will get the values
	// Define a boolean value
	System.out.println(prefs.getBoolean(ID1, true));
	// Define a string with default "Hello World
	System.out.println(prefs.get(ID2, "Hello World"));
	// Define a integer with default 50
	System.out.println(prefs.getInt(ID3, 50));

	// Now set the values
	prefs.putBoolean(ID1, false);
	prefs.put(ID2, "Hello Europa");
	prefs.putInt(ID3, 45);

	// Delete the preference settings for the first value
	prefs.remove(ID1);

    }

    public static void main(String[] args) {
	PreferenceTest test = new PreferenceTest();
	test.setPreference();
    }
} 
/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2014 Henrik Sandklef 
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

public class JearduinoState {

    String searduinoProject;
    String codeName;
    int    buildType;      
    String board;
    int    boardPins;
    String shortCodeName;
    String canonicalCodeName;


    public final int SEARDUINO_STATE_STUB    = 0 ;
    public final int SEARDUINO_STATE_ARDUINO = 1 ;

    JearduinoState() {
	searduinoProject  = "";
	board             = "";
	buildType         = SEARDUINO_STATE_STUB;
	shortCodeName     = "";
	canonicalCodeName = "";
	boardPins         = 0 ;
    }
    
    public String getCurrentSearduinoProject() {
	return searduinoProject;
    }

    public void setCurrentSearduinoProject(String s) {
	searduinoProject=s;
    }

    public int getCurrentBuildType() {
	return buildType;        
    }
    
    public void setCurrentBuildType(int type) {
	buildType=type;
    }

    public int getBoardPins() {
	return boardPins;
    }

    public void setBoardPins(int pins) {
	boardPins=pins;
    }

    public boolean buildTypeArduino() {
	return (buildType==SEARDUINO_STATE_ARDUINO);
    }

    public boolean buildTypeStub() {
	return (buildType==SEARDUINO_STATE_STUB);
    }

    public void setCodeName(String shortName, String canonName) {
	shortCodeName=shortName;
	canonicalCodeName=canonName;
    }
    
    public String  getShortCodeName() {
	return shortCodeName;
    }
    
    public String getCanonicalCodeName(){
	return canonicalCodeName;
    }

    public String getBoard() {
	return board;
    }

    public void setBoard(String b) {
	board = b;
    }

    public String toString() {
	String rs= "JearduinoState:\n";
	rs  = rs + "------------------------------------------------------\n";
	rs  = rs + "  *  SearduinoProject: " + searduinoProject + "\n";
	rs  = rs + "  *  BuildType:        " + buildType + "\n";
	rs  = rs + "  *  Board:            " + board + "\n";
	rs  = rs + "  *    pins:           " + boardPins + "\n";
	rs  = rs + "  *  Code (short):     " + shortCodeName + "\n";
	rs  = rs + "  *  Code (canonical): " + canonicalCodeName + "\n";
	return rs;
    }

}
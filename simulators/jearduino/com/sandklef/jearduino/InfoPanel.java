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

import javax.swing.JPanel;
import javax.swing.JLabel;

public class InfoPanel extends JPanel 
{

    JLabel infoLabel;
    String projectName;
    String boardName;
    String searduinoVersion;
    String arduinoCodeName;
    
    public void updateText()
    {
	String text = "Searduino: "      + searduinoVersion + 
	    "  Board: "        + boardName + 
	    "  Project: "        + projectName + 
	    "  Arduino code: " + arduinoCodeName;
	//	System.out.println("UPDATING INFO TEXT TO: " + text );
	infoLabel.setText(text);

    }

    public void setBoardName(String b)
    {
	boardName = b;
	updateText();
    }

    public void setProjectName(String b)
    {
	projectName = b;
	updateText();
    }

    public void setSearduinoVersion(String v)
    {
	searduinoVersion = v;
	updateText();
    }

    public void setArduinoCodeName(String c)
    {
	arduinoCodeName = c;
	updateText();
    }

    public InfoPanel()
    {
	infoLabel = new JLabel();

	setArduinoCodeName("none");
	setSearduinoVersion("0");
	setProjectName("none");
	setBoardName("none");

	add(infoLabel);

	updateText();
    }

}
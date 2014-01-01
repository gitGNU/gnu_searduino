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
import javax.swing.BorderFactory;

public class ProjectPanel extends JPanel 
{

    JLabel infoLabel;
    String projectName;
    String arduinoCodeName;
    
    public void updateText()
    {
	String text = "  Project: "        + projectName + 
	    "  Arduino code: " + arduinoCodeName;
	infoLabel.setText(text);
    }

    public void setProjectName(String b)
    {
	projectName = b;
	updateText();
    }

    public void setArduinoCodeName(String c)
    {
	arduinoCodeName = c;
	updateText();
    }

    public ProjectPanel()
    {
	infoLabel = new JLabel();

	setBorder(BorderFactory.createTitledBorder("Project"));

	setArduinoCodeName("none");
	setProjectName("none");

	add(infoLabel);

	updateText();
    }

}
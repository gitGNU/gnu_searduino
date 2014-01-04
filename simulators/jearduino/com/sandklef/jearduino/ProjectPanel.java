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
import java.awt.GridLayout;

import java.io.File;

public class ProjectPanel extends JPanel 
{
    JLabel projectLabel;
    JLabel arduinoCodeLabel;

    JLabel projectName;
    JLabel arduinoCodeName;

    private String getName(String s, boolean isDir) {
	String ret="--";

	if (s!=null) {
	    File f = new File(s);
	    
	    if (f.isFile()) {
		if (isDir) {
		    ret = " -- ";
		} else {
		    ret = f.getName();
		}
	    } else if (f.isDirectory()) {
		if (isDir) {
		    ret = f.getName();
		} else {
		    ret = " -- " ;
		}
	    } else {
		ret = s;
	    }
	}
	System.out.println("getName(" + s +");  => " + ret);
	return ret;
    }

    public void setProjectName(String p)
    {
	projectName.setText(getName(p, true));
    }

    public void setArduinoCodeName(String ac)
    {
	arduinoCodeName.setText(getName(ac, false));
    }

    public ProjectPanel()
    {
	super(new GridLayout(3, 3));    
	setBorder(BorderFactory.createTitledBorder("Project"));

	projectLabel     = new JLabel("Project name:");
	arduinoCodeLabel = new JLabel("Arduino code:");

	projectName      = new JLabel("--");
	arduinoCodeName  = new JLabel("--");

	setArduinoCodeName("-");
	setProjectName("-");

	add(projectLabel); 
	add(projectName); 
	add(arduinoCodeLabel); 
	add(arduinoCodeName); 
    }

}
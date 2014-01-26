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

import javax.swing.JButton;
import javax.swing.JPanel;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.border.Border;
import javax.swing.BorderFactory;

public class ExecControl extends JPanel implements ActionListener
{
    private JButton pause; 
    private JButton resume;
    private JButton halt  ;
    private JButton start  ;

    public static final int EXEC_CONTROL_START  = 1;
    public static final int EXEC_CONTROL_PAUSE  = 2;
    public static final int EXEC_CONTROL_RESUME = 3;
    public static final int EXEC_CONTROL_HALT   = 4;

    private ExecEvent ee ; 

    public ExecControl(ExecEvent e)
    {
	
	setBorder(BorderFactory.createTitledBorder("Execution"));
	
	start  = new JButton("Start");

	pause  = new JButton("Pause");

	resume = new JButton("Resume");

	halt   = new JButton("Stop");

	ee = e;

	add(start);
	add(pause);
	add(resume);
	add(halt);
	
	start.addActionListener(this);
	pause.addActionListener(this);
	resume.addActionListener(this);
	halt.addActionListener(this);

	start.setEnabled(false);
	pause.setEnabled(false);
	resume.setEnabled(false);
	halt.setEnabled(false);

	setVisible(true);

    }

    public void setStates(Boolean startState, 
			  Boolean pauseState, 
			  Boolean resumeState, 
			  Boolean haltState)
    {
	start.setEnabled(startState);
	pause.setEnabled(pauseState);
	resume.setEnabled(resumeState);
	halt.setEnabled(haltState);
    }
			  
    public void unsetStartable()
    {
	start.setEnabled(false);
    }
			  
			  
    public void unsetAll()
    {
	start.setEnabled(false);
	pause.setEnabled(false);
	resume.setEnabled(false);
	halt.setEnabled(false);
    }
			  
    public void setStartable()
    {
	start.setEnabled(true);
    }
			  

    public void actionPerformed(ActionEvent e) {
	int type = 0 ; 

	if (e.getSource() == pause) {
	    start.setEnabled(false);
	    pause.setEnabled(false);
	    resume.setEnabled(true);
	    halt.setEnabled(true);
	    type = EXEC_CONTROL_PAUSE;
	}
	else if (e.getSource() == resume) {
	    type = EXEC_CONTROL_RESUME;
	    start.setEnabled(false);
	    pause.setEnabled(true);
	    resume.setEnabled(false);
	    halt.setEnabled(true);
	}
	else if (e.getSource() == halt) {
	    type = EXEC_CONTROL_HALT;
	    start.setEnabled(true);
	    pause.setEnabled(false);
	    resume.setEnabled(false);
	    halt.setEnabled(false);
	}
	else if (e.getSource() == start) {
	    type = EXEC_CONTROL_START;
	    start.setEnabled(false);
	    pause.setEnabled(true);
	    resume.setEnabled(false);
	    halt.setEnabled(true);
	}

	ee.ExecEvent(type);
    }

    public void sendStart(){
	int type;
	type = EXEC_CONTROL_START;

	setStates(false, 
		  true,
		  false,
		  true);
	ee.ExecEvent(type);

    }

}

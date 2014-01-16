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

import javax.swing.JButton;
import java.awt.event.ActionEvent;
import javax.swing.JTextArea;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import java.awt.GridLayout;
import javax.swing.BorderFactory;
import java.awt.Dimension;
import java.awt.event.ActionListener;

class FileLogger extends JPanel implements TailerEvent, ActionListener {

    private JTextArea textArea ;
    Tailer tailer;
    JButton clear;
    JButton printState;
    Jearduino jearduino;
    JPanel pane;
    JScrollPane scrollPane;

    public FileLogger(String str, Jearduino j) {
	super(new GridLayout(2, 1));    
	setBorder(BorderFactory.createTitledBorder(str));

	textArea = new JTextArea();
	scrollPane = new JScrollPane(textArea); 
	//	textArea.setEditable(false);

	/* Button panel */
	pane = new JPanel();
	clear = new JButton("Clear") ;
	printState = new JButton("Print State");

	jearduino = j;

	add(scrollPane);
	add(pane);
	pane.add(clear);
	pane.add(printState);

	scrollPane.setPreferredSize(new Dimension(600, 700)); 
	//textArea.setMinimumSize (new Dimension(300, 750)); 

	clear.addActionListener(this);
	printState.addActionListener(this);


	setVisible(true);
    }


    public void actionPerformed(ActionEvent e) {
	int type = 0 ; 

	if (e.getSource() == clear) {
	    textArea.setText("");
	} else if (e.getSource() == printState) {
	    addLog(jearduino.getJearduinoState());
	    addLog(jearduino.getSearduinoState());
	    addLog(jearduino.searduino.getBoardSetup());
	}
    }

    public void handleFileInput(String text) {
	addLog(text + "\n");
    }
    
    public void start() {
	tailer = new Tailer("/tmp/searduino-internal.log", this);
	Thread t = new Thread(tailer);
	t.start();
    }

    public void addLog(String data) {
	textArea.append(data);
	textArea.setCaretPosition(textArea.getDocument().getLength()); 
	this.validate();
	this.revalidate();
	this.repaint();
    }

}

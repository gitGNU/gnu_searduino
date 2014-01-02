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

import javax.swing.JTextArea;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import java.awt.GridLayout;
import javax.swing.BorderFactory;
import java.awt.Dimension;

class Logger extends JPanel {
    private JTextArea textArea = new JTextArea();

    public Logger(String str) {

	super(new GridLayout(1, 2));    
	setBorder(BorderFactory.createTitledBorder(str));

	add(new JScrollPane(textArea));
	setVisible(true);
    }

    public void addLog(String data) {
	textArea.append(data+"\n");
	this.validate();
	textArea.setCaretPosition(textArea.getDocument().getLength()); 
	this.revalidate();
	this.repaint();
    }
}

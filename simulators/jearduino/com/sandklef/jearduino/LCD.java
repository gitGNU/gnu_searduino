/*****
 *                                                                   
 *                   Searduino
 *                      
 *   Copyright (C) 2013, 2014 Henrik Sandklef 
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

class LCD extends JPanel {
    private JTextArea textArea = new JTextArea();

    public LCD(String str) {

	super(new GridLayout(1, 2));    
	setBorder(BorderFactory.createTitledBorder(str));

	textArea.setColumns(16);

	add(textArea);
	setVisible(true);
    }

    public void setText(String row1, String row2) {
	textArea.setText(row1 + "\n" + row2);
	this.validate();
    }
}

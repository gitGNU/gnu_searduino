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
import javax.swing.JComboBox;
import java.awt.*;

public class Board extends JPanel implements ActionListener
{
    JComboBox boardList ;
    BoardEvent be;

    public Board(BoardEvent e)
    {
	//	super(new GridLayout(1, 1));    
	setBorder(BorderFactory.createTitledBorder("Board"));

	be = e;
	
	String[] boards = { "Uno", "Leonardo", "Mega", "Mega2560" };
	boardList = new JComboBox(boards);
	
	//	boardList.setPreferredSize(new Dimension(100,20));
	boardList.setSelectedIndex(2);
	boardList.addActionListener(this);

	add(boardList);

    }

    public void actionPerformed(ActionEvent e) {
        JComboBox cb = (JComboBox)e.getSource();
        String boardName = (String)cb.getSelectedItem();
	System.out.println("Searduino board:   " + boardName);

	be.handleBoardChoiceEvent(boardName);
    }
    

}
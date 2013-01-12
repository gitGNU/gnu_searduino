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
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.ButtonGroup;

public class JearduinoMenu extends JMenuBar {

    public Menu()
    {
	JMenuBar menuBar = new JMenuBar();
	JMenu menu = new JMenu("Board");
	ButtonGroup boardGroup = new ButtonGroup();


	menuBar.add(menu);
	JRadioButtonMenuItem leoItem = new JRadioButtonMenuItem("Leonardo");
	JRadioButtonMenuItem unoItem = new JRadioButtonMenuItem ("Uno");
	JRadioButtonMenuItem megaItem = new JRadioButtonMenuItem ("Mega");
	JRadioButtonMenuItem mega2560Item = new JRadioButtonMenuItem("Mega 2560");

	menu.add(leoItem);
	leoItem.addActionListener(this);
	unoItem.addActionListener(this);
	megaItem.addActionListener(this);
	mega2560Item.addActionListener(this);
	
	boardGroup.add(unoItem);
	boardGroup.add(megaItem);
	boardGroup.add(mega2560Item);

	menu.add(unoItem);
	menu.add(megaItem);
	menu.add(mega2560Item);

    }


    public void actionPerformed(ActionEvent e) {
	System.out.println("MENU click " + e.getActionCommand());
	setupBoard(e.getActionCommand());
    }



}
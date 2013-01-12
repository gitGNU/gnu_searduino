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
import javax.swing.JButton;
import javax.swing.filechooser.*;
import javax.swing.JFileChooser;
import java.io.File;

import javax.swing.event.*;
import java.awt.event.*;

public class JearduinoMenu extends JMenuBar implements ActionListener {


    BoardEvent be;
    FileEvent  fe;
    ArduinoCodeNameEvent  ae;

    JMenu boardMenu;
    JMenu fileMenu;
    JMenu helpMenu;
    JMenu codeMenu;

    JRadioButtonMenuItem leoItem;
    JRadioButtonMenuItem unoItem ;
    JRadioButtonMenuItem megaItem ;
    JRadioButtonMenuItem mega2560Item;

    JMenuItem boardItem;
    JMenuItem aboutItem;
    JMenuItem codeItem[];

    JFileChooser fc;
    

    public JearduinoMenu(BoardEvent boardEv, FileEvent fileEv, ArduinoCodeNameEvent  ardEv )
    {
	be = boardEv;
	fe = fileEv;
	ae = ardEv;

	codeItem = new JMenuItem[10];

	//	JMenuBar menuBar = new JMenuBar();
	boardMenu = new JMenu("Board");
	fileMenu  = new JMenu("File");
	helpMenu  = new JMenu("Help");
	codeMenu  = new JMenu("Code");

	add(fileMenu);
	add(boardMenu);
	add(helpMenu);
	add(codeMenu);

	createBoardMenu();
	createFileMenu();
	createHelpMenu();
    }

    public void findArduinoCode()
    {
	fc = new JFileChooser();

	int returnVal = fc.showOpenDialog(JearduinoMenu.this);
	
	if (returnVal == JFileChooser.APPROVE_OPTION) {
	    File file = fc.getSelectedFile();
	    //This is where a real application would open the file.
	    try {
		System.out.println("Opening: " + file.getCanonicalPath()  );
		fe.handleArduinoFileEvent(file);
	    }
	    catch (java.io.IOException e)
		{
		    System.out.println("Uh oh... could not get file name" );
		}
	} else {
	    System.out.println("Open command cancelled by user." );
	}
    }

    public void showAbout()
    {
	System.out.println("Show about");
	JearduinoAbout jabout = new JearduinoAbout();

	jabout.pack();
	jabout.setVisible(true);

    }

    public int handleCodeChoice(Object o)
    {
	for (int i=0;i<10;i++)
	    {
		if (o==codeItem[i])
		    {
			System.out.println("Code at " + i +
					   " was choosen " );
			return i;
		    }
	    }
	return -1;
    }


    public void actionPerformed(ActionEvent e) {

	System.out.println("MENU click " + e.getActionCommand());
	
	Object o = e.getSource();

	int codeIdx = handleCodeChoice(o);
	
	if  ( ( o == leoItem ) ||  ( o == unoItem )  || (o==megaItem) || (o==mega2560Item))
	    {
		be.handleBoardChoiceEvent(e.getActionCommand());
	    }
	else if  ( o == boardItem )
	    {
		findArduinoCode();
	    }
	else if  ( o == aboutItem )
	    {
		showAbout();
	    }
	else if ( codeIdx != -1 )
	    {
		System.out.println("Code at " + codeIdx +
				   " was choosen " );
		ae.handleArduinoCodeNameEvent(codeIdx);
	    }
    }
    
    public void createFileMenu()
    {
	boardItem = new JMenuItem("Open Arduino file");

	fileMenu.add(boardItem);
	boardItem.addActionListener(this);
    }
  
    public void createHelpMenu()
    {
	aboutItem = new JMenuItem("About") ;

	helpMenu.add(aboutItem);
	aboutItem.addActionListener(this);
    }
  
    public void removeCodeItems()
    {
	codeMenu.removeAll();
    }


    public void updateCodeItem(int idx, String codeName)
    {
	codeItem[idx] = new JMenuItem(codeName);
	codeMenu.add(codeItem[idx]);
	codeItem[idx].addActionListener(this);
    }
  
	

    public void createBoardMenu()
    {
	ButtonGroup boardGroup = new ButtonGroup();

	leoItem = new JRadioButtonMenuItem("Leonardo");
	unoItem = new JRadioButtonMenuItem ("Uno");
	megaItem = new JRadioButtonMenuItem ("Mega");
	mega2560Item = new JRadioButtonMenuItem("Mega 2560");

	boardMenu.add(leoItem);
	leoItem.addActionListener(this);
	unoItem.addActionListener(this);
	megaItem.addActionListener(this);
	mega2560Item.addActionListener(this);
	
	boardGroup.add(unoItem);
	boardGroup.add(megaItem);
	boardGroup.add(mega2560Item);

	boardMenu.add(unoItem);
	boardMenu.add(megaItem);
	boardMenu.add(mega2560Item);
    }
}
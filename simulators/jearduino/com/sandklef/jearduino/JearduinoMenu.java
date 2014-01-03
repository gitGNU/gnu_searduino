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

    BoardEvent    be;
    FileEvent     fe;
    DirEvent      de;
    InoDirEvent   ie;
    JearduinoEvent je;
    ArduinoCodeNameEvent  ae;

    /* Level 1 */
    JMenu fileMenu;
    JMenu boardMenu;
    JMenu helpMenu;
    JMenu projectMenu;

    /* Level 2 */
    JMenu codeMenu;
    JMenu prevCodeMenu;
    JRadioButtonMenuItem leoItem;
    JRadioButtonMenuItem unoItem ;
    JRadioButtonMenuItem megaItem ;
    JRadioButtonMenuItem mega2560Item;

    JMenuItem loadFromFile;

    /* PRoject menu */
    JMenuItem importArduinoFileItem;
    JMenuItem openSearduinoProjectItem;
    JMenuItem buildItem;

    JMenuItem boardItem;

    JMenuItem aboutItem;
    JMenuItem manualItem;
    JMenuItem codeItem[];

    JFileChooser fc;
    

    public JearduinoMenu(JearduinoEvent jeardEv, BoardEvent boardEv, FileEvent fileEv, 
			 DirEvent dirEv, InoDirEvent inoEv, ArduinoCodeNameEvent  ardEv )
    {
	be = boardEv;
	fe = fileEv;
	de = dirEv;
	ae = ardEv;
	ie = inoEv;
	je = jeardEv;

	codeItem = new JMenuItem[10];

	/* Level 1 */
	fileMenu    = new JMenu("File");
	projectMenu = new JMenu("Project");
	boardMenu   = new JMenu("Board");
	helpMenu    = new JMenu("Help");

	loadFromFile = new JMenuItem("Load code from file");
	loadFromFile.addActionListener(this);


	codeMenu  = new JMenu("Previous code");

	add(fileMenu);
	add(projectMenu);
	add(boardMenu);
	add(helpMenu);

	createBoardMenu();
	createProjectMenu();
	createFileMenu();
	createHelpMenu();
    }

    public void findArduinoCode()
    {
	String searduino_default_path = System.getProperty("user.home") + "/searduino";

	String searduino_dir = System.getProperty("searduino.project.dir");

	System.out.println("findArduinoCode -------------" );


	if (searduino_dir==null) {
	    searduino_dir = searduino_default_path;
	}

	fc = new JFileChooser(new File(searduino_dir));

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

    public void findInoCode()
    {
	String ino_default_path="/usr/share/doc/arduino-core/examples/";

	String ino_dir = System.getProperty("searduino.arduinoex.dir");

	if (ino_dir==null) {
	    ino_dir = ino_default_path;
	}
		
	fc = new JFileChooser(new File(ino_dir));
	fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);

	int returnVal = fc.showOpenDialog(JearduinoMenu.this);

	if (returnVal == JFileChooser.APPROVE_OPTION) {
	    File file = fc.getSelectedFile();
	    //This is where a real application would open the file.
	    try {
		System.out.println("Opening: " + file.getCanonicalPath()  );
		ie.handleInoDirEvent(file);
	    }
	    catch (java.io.IOException e)
		{
		    System.out.println("Uh oh... could not get file name" );
		}
	} else {
	    System.out.println("Open command cancelled by user." );
	}
	
    }

    public void findSerduinoProject()
    {
	String searduino_default_path = System.getProperty("user.home") + "/searduino";

	String searduino_dir = System.getProperty("searduino.project.dir");

	if (searduino_dir==null) {
	    searduino_dir = searduino_default_path;
	}

	fc = new JFileChooser(new File(searduino_dir));
	fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);

	int returnVal = fc.showOpenDialog(JearduinoMenu.this);

	if (returnVal == JFileChooser.APPROVE_OPTION) {
	    File file = fc.getSelectedFile();
	    //This is where a real application would open the file.
	    try {
		System.out.println("Opening: " + file.getCanonicalPath()  );
		de.handleSearduinoDirEvent(file);
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

    public void showManual()
    {
	System.out.println("Show manual");
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

	System.out.println("MENU click " + e.getActionCommand() + " (" + e.getSource() + ")");
	
	Object o = e.getSource();

	int codeIdx = handleCodeChoice(o);
	
	if  ( ( o == leoItem ) ||  ( o == unoItem )  || (o==megaItem) || (o==mega2560Item))
	    {
		be.handleBoardChoiceEvent(e.getActionCommand());
	    }
	else if  ( o == loadFromFile )
	    {
		findArduinoCode();
	    }
	else if  ( o == aboutItem )
	    {
		showAbout();
	    }
	else if  ( o == manualItem )
	    {
		showManual();
	    }
	else if  ( o == buildItem )
	    {
		je.handleJearduinoEvent(JearduinoEvent.JEARDUINO_EVENT_BUILD_PROJECT, null);
	    }
	else if  ( o == importArduinoFileItem )
	    {
		System.out.println("importArduinoFileItem");
		findInoCode();
	    }
	else if  ( o == openSearduinoProjectItem )
	    {
		System.out.println("openSearduinoProjectItem");

		findSerduinoProject();

	    }
	else if ( codeIdx != -1 )
	    {
		System.out.println("Code at " + codeIdx +
				   " was choosen " );
		ae.handleArduinoCodeNameEvent(codeIdx);
		System.out.println("Code at " + codeIdx +
				   " was choosen ... call has been made" );
	    }
    }
    
    public void createFileMenu()
    {
	fileMenu.add(loadFromFile);
	fileMenu.add(codeMenu);
    }
  
    public void createHelpMenu()
    {
	aboutItem = new JMenuItem("About") ;
	manualItem = new JMenuItem("Manual") ;

	helpMenu.add(aboutItem);
	helpMenu.add(manualItem);
	aboutItem.addActionListener(this);
	manualItem.addActionListener(this);
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

    public void createProjectMenu()
    {
	importArduinoFileItem = new JMenuItem("Import Arduino File");
	openSearduinoProjectItem = new JMenuItem("Open Searduino Project");
	buildItem = new JMenuItem("Build");

	importArduinoFileItem.addActionListener(this);
	openSearduinoProjectItem.addActionListener(this);
	buildItem.addActionListener(this);

	projectMenu.add(importArduinoFileItem);
	projectMenu.add(openSearduinoProjectItem);
	projectMenu.add(buildItem);

    }


}
